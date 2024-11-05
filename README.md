# Project Report: Design Decisions for the Club Simulation

## 1. Libraries Imported

I used some standard C++ libraries to handle the basic functionality:

- `<iostream>`: for input and output.
- `<vector>`: to store the list of people in the club.
- `<unordered_map>`: for the entry/exit logs, which simplifies looking up times quickly.
- `<cstdlib>`: to generate random entry and exit times.
- `<ctime>`: to seed random numbers with the current time.
- `<cassert>`: for test cases, to check conditions automatically.

## 2. Classes Created

### Person Class

This class represents a person trying to get into the club. It includes the following:

- **Attributes:**
  - `int age`: the person's age.
  - `std::string name`: the person's name.
  - `bool isVIP`: indicates if they’re a VIP (important for entry priority).
  - `bool isBanned`: `true` if they’re banned from the club.
  - `int ID`: their unique ID.

- **Methods:**
  - `displayPerson()`: prints the person’s details.
  - `checkisBanned()`: returns `true` if they’re banned.
  - `getID()`: returns the unique ID.

### Club Class

The main class that manages the club’s capacity and handles people entering and leaving.

- **Attributes:**
  - `int capacity`: maximum number of people allowed in the club.
  - `int currentCount`: current number of people inside.
  - `std::vector<Person> members`: list of people currently inside.
  - `Event currentEvent`: manages logging the entry and exit times.
  - `NormalLine vipLine`: queue for VIPs.
  - `NormalLine normalLine`: queue for regular people.

- **Methods:**
  - `addPerson()`: admits people from the lines, with logic for underage/banned people and VIP priority.
  - `removePerson()`: removes a person from the club by ID.
  - `calculatePersonDuration()`: calculates how long a person stayed in the club.
  - `isFull()`: checks if the club is full.

### Event Class

This class logs entry/exit times and calculates how long people were inside.

- **Attributes:**
  - `std::unordered_map<int, int> entryLog`: maps client IDs to entry times (in minutes since midnight).
  - `std::unordered_map<int, int> exitLog`: maps client IDs to exit times.

- **Methods:**
  - `logEntry()`: logs the person’s entry time (randomly generated between 21:00 and 00:00).
  - `logExit()`: logs the person’s exit time (randomly generated between 00:01 and 05:00).
  - `calculateDuration()`: subtracts entry time from exit time to determine how long they stayed.

## 3. Data Structures

- `std::vector<Person>`: used in `Club` to track who is inside. It allows dynamic resizing and easy additions/removals.
- `std::unordered_map<int, int>`: used in `Event` for entry and exit logs, allowing fast lookups and updates using IDs.

## 4. Functions Used

- `logEntry()` and `logExit()`: log the times people enter and leave, generated randomly for simplicity.
- `calculateDuration()`: subtracts entry time from exit time to find how long someone stayed. It handles stays past midnight by adjusting the exit time.

## 5. Algorithms Used in Functions

- **Random Time Generation**: Entry times are random between 21:00 and 00:00 (in minutes), and exit times are between 00:01 and 05:00, simulating the club duration.
- **Duration Calculation**: For stays that cross midnight, I subtract the entry time from 1440 (midnight) and add the exit time to correctly calculate total time.
