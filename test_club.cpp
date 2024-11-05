#include <iostream>
#include <cassert>
#include "project1Simple.cpp"  // Assuming project1Final.cpp contains your Club, Event, and Person classes

void testAddPersonToClub() {
    Club club(5);  // Club with a capacity of 5

    // Creating some person objects
    Person person1(25, "John", false, false, 1);  // Normal person, not banned, ID: 1
    Person person2(30, "Sarah", true, false, 2);  // VIP person, not banned, ID: 2
    Person person3(28, "Tom", false, false, 3);   // Normal person, not banned, ID: 3
    Person person4(15, "Kyle", false, false, 4); // underaged, should be denied
    Person person5(50, "Derek", false, true, 5); // banned, should be denied

    // queue person
    club.queuePerson(person1);
    club.queuePerson(person2);
    club.queuePerson(person3);
    club.queuePerson(person4);
    club.queuePerson(person5);


    // Adding people to the club
    club.addPerson();
    club.addPerson();
    club.addPerson();
    club.addPerson();
    club.addPerson();

    // Assert that the club has the correct count of people inside
    assert(club.getCurrentCount() == 3);  // Should have 3 people in the club
    std::cout << "Test addPersonToClub passed!" << std::endl;
}

void testRemovePersonFromClub() {
    Club club(5);  // Club with a capacity of 5

    // Creating some person objects
    Person person1(25, "John", false, false, 1);  // Normal person, not banned, ID: 1
    Person person2(30, "Sarah", true, false, 2);  // VIP person, not banned, ID: 2
    Person person3(28, "Tom", false, false, 3);   // Normal person, not banned, ID: 3

    // queue people
    club.queuePerson(person1);
    club.queuePerson(person2);
    club.queuePerson(person3);

    // Adding people to the club
    club.addPerson();
    club.addPerson();
    club.addPerson();

    // Removing people from the club
    club.removePerson(1);  // Remove John (ID: 1)
    club.removePerson(2);  // Remove Sarah (ID: 2)

    // Assert that the club has the correct count of people inside
    assert(club.getCurrentCount() == 1);  // Should have 1 person remaining in the club
    std::cout << "Test removePersonFromClub passed!" << std::endl;
}

void testCalculatePersonDuration() {
    Club club(5);  // Club with a capacity of 5

    // Creating a person object
    Person person1(25, "John", false, false, 1);  // Normal person, not banned, ID: 1

    // queue person
    club.queuePerson(person1);

    // Adding and removing the person
    club.addPerson();
    club.removePerson(1);  // Remove John (ID: 1)

    // Calculate the duration of stay for John
    std::cout << "Calculating duration for person with ID 1..." << std::endl;
    club.calculatePersonDuration(1);  // This should display the person's random stay duration
}

int main() {
    std::cout << "\nRunning tests...\n\n" << std::endl;

    testAddPersonToClub();
    std::cout << "\n" << std::endl;
    testRemovePersonFromClub();
    std::cout << "\n" << std::endl;
    testCalculatePersonDuration();

    std::cout << "\n\nAll tests passed!" << std::endl;
    return 0;
}
