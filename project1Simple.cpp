// project1Simple.cpp is used with test_club.cpp

// write a program that simulates a night club in C++.
// There needs to be an entry line and separate VIP line. 
// Normal line does not move until VIP line is empty. 
//      Exit order. First VIP, then normal line.
//      Implement 2 queues. 
// Queues are filled with People objects.
// Age to get into the club is 21 and up
// Club capacity is 100 people
// We might need a club class that tracks people inside and capacity and has an add and remove method also.
// Person{} class, NormalLine{} class, VIPLine{} class, Club{} class
#include <iostream>    // For input/output operations (e.g., std::cout, std::cin)
#include <queue>       // For the queue data structure
#include <string>      // For handling strings (e.g., Person names)
#include <cstdlib>     // For generating random numbers (e.g., to simulate people)
#include <vector>
#include <ctime>     // For time()
#include <unordered_map>
using namespace std;

class Person{
    private:
        int age;
        string name;
        bool isVIP;
        bool isBanned;
        int ID;
    public:
        // Constructor 
        Person(int newAge, string newName, bool newIsVIP, bool newIsBanned, int newID){
            this->age = newAge;
            this->name = newName;
            this->isVIP = newIsVIP;
            this->isBanned = newIsBanned;
            this->ID = newID;
        }
        // method to get age
        int getAge() const { 
            // The const keyword next to the methods in the Person class ensures 
            // that those methods do not modify the object’s state.
            return this->age;
        }
        // method to check if person is a VIP
        bool checkVIP() const {
            return this->isVIP;
        }
        // method to check is a person is Banned
        bool checkisBanned() const {
            return this->isBanned;
        }
        // display the Person's details
        void displayPerson() const {
            cout << "\nName: " << name << "\nAge: " << age
                 << "\nVIP: " << (isVIP ? "Yes" : "No")
                 << "\nBanned: " << (isBanned ? "Yes" : "No") 
                 << "\nID: " << ID << endl;
        }
        // method to show name
        string getName() const {
            return this->name;
        }
        // method to show ID
        int getID() const {
            return this->ID;
        }
};

// banned person can wait in line but can't enter club
class NormalLine{
    private:
        queue<Person> normalQueue; // line implemented as a queue
    public:

        // method to add a person to line
        void addPerson(Person p){
            normalQueue.push(p);
        }

        // method to remove and return the person in the front of the line
        Person removePerson(){
            if (!normalQueue.empty()){
                Person frontPerson = normalQueue.front();
                normalQueue.pop();
                return frontPerson;
            }
            else {
                throw runtime_error("Normal line is empty!");
            }
        }

        // check if Normal Line is empty
        bool isEmpty() const {
            return normalQueue.empty();
        }

        // method to get size of Normal Line
        int getSize() const {
            return normalQueue.size();
        }

        // method to display the normal line
        void displayLine() const {
            if (normalQueue.empty()){
                cout << "Normal Line is empty!" << endl;
                return;
            }
            
            cout << "People in the Normal Line: " << endl;
            queue<Person> tempQueue = normalQueue; // copy normal queue to display everyone

            while (!tempQueue.empty()){
                Person p = tempQueue.front();
                p.displayPerson();
                tempQueue.pop();
            }
        }
};


#include <iostream>
#include <unordered_map>
#include <cstdlib>   // For rand()
#include <ctime>     // For time()

class Event {
private:
    // Entry and exit logs using client ID (int) and their respective times (in minutes since midnight)
    std::unordered_map<int, int> entryLog;
    std::unordered_map<int, int> exitLog;

public:
    Event() {
        std::srand(std::time(0));  // Seed the random number generator
    }

    // Generate random time between 21:00 and 00:00 (21*60 to 24*60)
    int generateRandomEntryTime() const {
        return (std::rand() % 180) + (21 * 60);  // Random time between 1260 (21:00) and 1440 (00:00)
    }

    // Generate random time between 00:01 and 05:00 (1 to 300)
    int generateRandomExitTime() const {
        return (std::rand() % 300) + 1;  // Random time between 1 and 300 (00:01 and 05:00)
    }

    // Log client entry
    void logEntry(int clientId) {
        int entryTime = generateRandomEntryTime();
        entryLog[clientId] = entryTime;
        std::cout << "Logged entry for client ID: " << clientId << " at " << (entryTime / 60) << ":" << (entryTime % 60) << std::endl;
    }

    // Log client exit
    void logExit(int clientId) {
        int exitTime = generateRandomExitTime();
        exitLog[clientId] = exitTime;
        std::cout << "Logged exit for client ID: " << clientId << " at " << (exitTime / 60) << ":" << (exitTime % 60) << std::endl;
    }

    // Calculate duration of stay for a given client ID
    double calculateDuration(int clientId) const {
        if (entryLog.find(clientId) != entryLog.end() && exitLog.find(clientId) != exitLog.end()) {
            int entryTime = entryLog.at(clientId);
            int exitTime = exitLog.at(clientId);
            int duration = (1440 - entryTime) + exitTime;  // Handle crossing midnight
            return duration;  // Return the duration in minutes
        } else {
            std::cerr << "Error: Client has not completed both entry and exit." << std::endl;
            return 0.0;
        }
    }
};




class Club {
private:
    NormalLine normalLine;
    NormalLine vipLine;
private:
    int capacity;       // Maximum number of people allowed in the club
    int currentCount;   // Current number of people inside the club
    std::vector<Person> members;  // People currently inside the club
    Event currentEvent;  // Manage an event to log entry/exit

public:
    // Constructor
    Club(int maxCapacity) : capacity(maxCapacity), currentCount(0) {}

    // Check if the club is full
    bool isFull() const {
        return currentCount >= capacity;
    }

    // Add a person to the club and log entry
    void addPerson() {
        if (isFull()) {
            cout << "The club is full! No more people can enter." << endl;
            return;
    }

    // Check the VIP line first
    if (!vipLine.isEmpty()) {
        Person vip = vipLine.removePerson();
        if (vip.checkisBanned() || vip.getAge() < 18) {  // Person is denied entry
            cout << "Person is denied entry because they are banned or underaged:" << endl;
            vip.displayPerson();
        } else {  // Entry allowed
            cout << "Admitting VIP: ";
            vip.displayPerson();
            currentCount++;
            members.push_back(vip);
            currentEvent.logEntry(vip.getID());  // Log the random entry time using client ID
        }
    }
    // If no VIP, check the normal line
    else if (!normalLine.isEmpty()) {
        Person normal = normalLine.removePerson();
        if (normal.checkisBanned() || normal.getAge() < 18) {  // Person is denied entry
            cout << "Person is denied entry because they are banned or underaged:" << endl;
            normal.displayPerson();
        } else {  // Entry allowed
            cout << "Admitting person from the normal line: ";
            normal.displayPerson();
            currentCount++;
            members.push_back(normal);
            currentEvent.logEntry(normal.getID());  // Log the random entry time using client ID
        }
    } else {
        cout << "Both the VIP and normal lines are empty." << endl;
    }
}


    // Remove a person from the club and log their exit
    void removePerson(int targetID) {
        for (auto it = members.begin(); it != members.end(); ) {
            if (it->getID() == targetID) {
                std::cout << "Removing person with ID: " << targetID << std::endl;
                it = members.erase(it);  // erase() returns the next iterator
                currentCount--;
                currentEvent.logExit(targetID);  // Log random exit time for this person
                return;
            } else {
                ++it;  // Move to the next person
            }
        }
        std::cout << "Person with ID " << targetID << " not found in club." << std::endl;
    }

    // Calculate the duration of stay for a person
    void calculatePersonDuration(int clientId) const {
        double duration = currentEvent.calculateDuration(clientId);
        if (duration > 0) {
            std::cout << "Person with ID " << clientId << " stayed for " << duration << " minutes." << std::endl;
        }
    }



    // Add a person to either the normal or VIP line
    void queuePerson(Person p) {
        if (p.checkVIP()) {
            vipLine.addPerson(p);
            cout << p.getName() << " added to the VIP line." << endl;
        } else {
            normalLine.addPerson(p);
            cout << p.getName() << " added to the normal line." << endl;
        }
    }

    // Display both lines
    void displayLines() const {
        cout << "\nVIP Line:" << endl;
        vipLine.displayLine();
        cout << "\nNormal Line:" << endl;
        normalLine.displayLine();
    }

    // Check how many people are inside the club
    int getCurrentCount() const {
        return currentCount;
    }

    // Display club's current status
    void displayClubStatus() const {
        cout << "\nPeople currently in the club: " << currentCount << "/" << capacity << endl;

        if (members.empty()) {
            cout << "No people are inside the club." << endl;
        } else {
            cout << "Members currently inside the club:" << endl;
            for (const Person& member : members) {
                member.displayPerson();
            }
        }
    }

};
