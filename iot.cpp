#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class ParkingSpace {
private:
    int id;
    bool isOccupied;

public:
    ParkingSpace(int spaceId) : id(spaceId), isOccupied(false) {}

    void occupy() {
        isOccupied = true;
        std::cout << "Parking space " << id << " is now occupied." << std::endl;
    }

    void vacate() {
        isOccupied = false;
        std::cout << "Parking space " << id << " is now vacant." << std::endl;
    }

    bool isOccupiedStatus() const {
        return isOccupied;
    }
};

class ParkingLot {
private:
    std::vector<ParkingSpace> spaces;

public:
    ParkingLot(int numSpaces) {
        for (int i = 1; i <= numSpaces; ++i) {
            spaces.emplace_back(i);
        }
    }

    void displayAvailability() const {
        std::cout << "Parking space availability:" << std::endl;
        for (const auto& space : spaces) {
            const std::string status = space.isOccupiedStatus() ? "Occupied" : "Vacant";
            std::cout << "Space " << space.getId() << ": " << status << std::endl;
        }
    }

    void simulateParking() {
        srand(static_cast<unsigned int>(time(0)));
        while (true) {
            const int spaceId = rand() % spaces.size();
            ParkingSpace& space = spaces[spaceId];
            if (space.isOccupiedStatus()) {
                space.vacate();
            } else {
                space.occupy();
            }
            displayAvailability();
            // Sleep for 5 seconds before the next iteration
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }
};

int main() {
    // Simulate a parking lot with 5 spaces
    ParkingLot parkingLot(5);
    parkingLot.simulateParking();

    return 0;
}
