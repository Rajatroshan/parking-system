#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

const char* serverUrl = "http://your-server-url.com/update-parking-status";
int parkingSpaceId = 1;
bool isOccupied = false;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  pinMode(2, INPUT_PULLUP); // Assuming you have a sensor connected to pin 2
}

void loop() {
  // Read the sensor input
  bool sensorValue = digitalRead(2);

  // Check if the parking space occupancy has changed
  if (sensorValue != isOccupied) {
    isOccupied = sensorValue;
    sendParkingStatusToServer();
  }

  delay(1000); // Adjust the delay as per your requirements
}

void sendParkingStatusToServer() {
  HTTPClient http;
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Prepare the payload
  String payload = "spaceId=" + String(parkingSpaceId) + "&occupied=" + String(isOccupied);

  // Send the POST request
  int httpResponseCode = http.POST(payload);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("Server response: " + response);
  } else {
    Serial.println("Error in sending HTTP request");
  }

  http.end();
}
