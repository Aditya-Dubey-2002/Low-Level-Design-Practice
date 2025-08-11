#include <bits/stdc++.h>
#define int long long
using namespace std;

// Optional ANSI colors (works on most modern terminals)
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define CYAN "\033[36m"
#define YELLOW "\033[33m"
#define BOLD "\033[1m"

class Car
{
private:
    string ownerName;
    string ownerContact;
    string spaceId;
    bool isInLot;
    string carNo;

public:
    string getCarNo() { return this->carNo; }
    void parkCar(string spaceId)
    {
        setSpaceId(spaceId);
        this->isInLot = true;
    }
    void setSpaceId(string space) { this->spaceId = space; }
    string getSpaceId() { return this->spaceId; }
    void freeCar()
    {
        setSpaceId("");
        this->isInLot = false;
    }
    Car(string carNo, string ownerName, string ownerContact)
    {
        this->carNo = carNo;
        this->ownerName = ownerName;
        this->ownerContact = ownerContact;
        this->isInLot = false;
        this->spaceId = "";
    }
    Car() {}
};

class Space
{
private:
    bool isFree;
    string id;

public:
    bool getSpaceStatus() { return isFree; }
    void bookSpace() { this->isFree = false; }
    void freeSpace() { this->isFree = true; }
    Space(string id)
    {
        this->id = id;
        this->isFree = true;
    }
    Space() {}
};

class ParkingLot
{
private:
    unordered_map<string, Car> carsMap;
    map<string, Space> spacesMap;
    int totalSpaces;
    int counter;

public:
    string getStatus()
    {
        return BOLD + to_string(this->totalSpaces - this->counter) + RESET +
               " spaces left out of " + BOLD + to_string(totalSpaces) + RESET + ".\n";
    }
    string allotSpace(Car &car)
    {
        if (this->counter == this->totalSpaces)
            return RED "Oops! No spaces left.\n" RESET;
        if (carsMap.count(car.getCarNo()))
            return YELLOW "Car already in lot!\n" RESET;

        for (auto &i : this->spacesMap)
        {
            if (i.second.getSpaceStatus())
            {
                auto result = this->carsMap.emplace(car.getCarNo(), car);
                auto it = result.first;
                Car &storedCar = it->second;
                i.second.bookSpace();
                storedCar.parkCar(i.first);
                this->counter++;
                return GREEN "Space allotted!\n" RESET
                             "Please park at parking ID: " BOLD +
                       i.first + "\n" RESET;
            }
        }
        return RED "No free space found.\n" RESET;
    }
    string freeSpace(string carNo)
    {
        if (!carsMap.count(carNo))
            return RED "No such car found.\n" RESET;
        Car &car = this->carsMap[carNo];
        string spaceId = car.getSpaceId();
        if (spaceId == "")
            return YELLOW "Car is not parked.\n" RESET;
        Space &space = this->spacesMap[spaceId];
        space.freeSpace();
        car.freeCar();
        if (this->counter > 0)
            this->counter--;
        return GREEN "Car freed! Happy Journey.\n" RESET;
    }
    void getSpacesList()
    {
        cout << CYAN << "\n--- Parking Spaces Status ---\n"
             << RESET;
        cout << BOLD << setw(10) << "Spot ID" << setw(15) << "Status" << RESET << "\n";
        for (auto &i : spacesMap)
        {
            cout << setw(10) << i.first
                 << setw(15) << (i.second.getSpaceStatus() ? (GREEN "Free" RESET) : (RED "Occupied" RESET))
                 << "\n";
        }
    }
    ParkingLot(int n)
    {
        this->counter = 0;
        this->totalSpaces = n;
        for (int i = 0; i < n; i++)
        {
            this->spacesMap.emplace(to_string(i), Space(to_string(i)));
        }
    }
};

int32_t main()
{
    cout << CYAN << BOLD << "=== Welcome to the Parking Lot System ===\n"
         << RESET;
    cout << "Please enter the size of parking lot: ";
    int n;
    cin >> n;
    ParkingLot DBParking(n);

    int input = -1;
    cout << CYAN << "\n======= Main Menu =======\n"
         << RESET;
    cout << "1. Allot Space\n";
    cout << "2. Free Space\n";
    cout << "3. Get Status\n";
    cout << "4. Get Spaces List\n";
    cout << "5. Exit\n";
    cout << "6. Main Menu\n";
    int check=100;
    // cout << "Enter choice: ";
    while (input != 5&&check--)
    {
        cout<<"Enter Choice:";
        cin >> input;
        
        if (input == 1)
        {
            string carNo, ownerName, ownerContact;
            cout << "Enter Car No.: ";
            cin >> carNo;
            cout << "Enter Owner's Name: ";
            cin >> ownerName;
            cout << "Enter Contact Number: ";
            cin >> ownerContact;
            Car newCar(carNo, ownerName, ownerContact);
            cout << DBParking.allotSpace(newCar);
        }
        else if (input == 2)
        {
            string carId;
            cout << "Enter Car number to free: ";
            cin >> carId;
            cout << DBParking.freeSpace(carId);
        }
        else if (input == 3)
        {
            cout << DBParking.getStatus();
        }
        else if (input == 4)
        {
            DBParking.getSpacesList();
        }
        else if (input == 5)
        {
            cout << RED "Invalid option. Try again.\n" RESET;
        }
        else if(input ==6)
        {
            cout << CYAN << "\n======= Main Menu =======\n"
                 << RESET;
            cout << "1. Allot Space\n";
            cout << "2. Free Space\n";
            cout << "3. Get Status\n";
            cout << "4. Get Spaces List\n";
            cout << "5. Exit\n";
            cout << "6. Main Menu\n";
            cout << "Enter choice: ";
        }
    }
    cout << GREEN << "Thank you for using the system. Goodbye!\n"
         << RESET;
    return 0;
}
