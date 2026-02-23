#include "ScheduleTime.h"
#include "Appointment.h"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <sstream>
using namespace std;
using namespace chrono; // Add this to use std::chrono types without qualification

// Initialize static variables
const string ScheduleTime::dayname[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
const string ScheduleTime::time[] = { "Morning", "Afternoon", "Evening" };

// Get the filename based on the second character of the doctor ID
string ScheduleTime::getFilename(const string& doctorID) {
    if (doctorID.length() < 2) {
        throw invalid_argument("Invalid doctor ID.");
    }

    char doctorType = doctorID[1];
    cout << "Debug: Received doctor ID: " << doctorID << ", Doctor Type: " << doctorType << endl;

    switch (doctorType) {
    case 'C': return "CardiologistSchedule.txt";
    case 'N': return "NeurologistSchedule.txt";
    case 'D': return "DermatologistSchedule.txt";
    case 'O': return "OphthalmologySchedule.txt";
    case 'P': return "PsychiatrySchedule.txt";
    default:
        cout << "Invalid doctor ID prefix: " << doctorType << endl;
        throw invalid_argument("Invalid doctor ID prefix.");
    }
}

ScheduleTime::ScheduleTime() : count(0), day(0), month(0), year(0) {
    auto now = system_clock::now();
    time_t currentTime = system_clock::to_time_t(now);
    tm currentLocalTime;

    localtime_s(&currentLocalTime, &currentTime);

    day = currentLocalTime.tm_mday;
    month = currentLocalTime.tm_mon + 1; // Months are 0-based
    year = currentLocalTime.tm_year + 1900; // Years since 1900

    for (int i = 0; i < days; ++i) {
        for (int j = 0; j < slots; ++j) {
            schedules[i][j] = nullptr;
        }
    }
}

ScheduleTime::~ScheduleTime() {
    for (int i = 0; i < days; ++i) {
        for (int j = 0; j < slots; ++j) {
            delete schedules[i][j];
        }
    }
}

void ScheduleTime::addSlot(const std::string& doctorID) {
    int selectedDay, selectedSlot;

    try {
        cout << "Select a day to reserve a slot:\n";
        for (int d = 0; d < days; d++) {
            cout << d + 1 << ". " << dayname[d] << endl;
        }
        cout << "Enter the number of the day: ";
        cin >> selectedDay;
        if (selectedDay < 1 || selectedDay > days) {
            throw invalid_argument("Invalid day number!");
        }

        cout << "Reminder! The time range of each slot is:\n";
        for (int i = 0; i < slots; i++) {
            cout << "Slot " << i + 1 << ": " << time[i] << endl;
        }
        cout << "Enter the number of slot to be reserved: ";
        cin >> selectedSlot;
        if (selectedSlot < 1 || selectedSlot > slots) {
            throw invalid_argument("Invalid slot number!");
        }

        // Load the existing schedule
        loadSchedule(doctorID);

        // Assuming getNextWeekdayDate and other related function implementations exist
        tm appointmentDate = getNextWeekdayDate(selectedDay - 1);

        Appointment* newAppointment = new Appointment(
            appointmentDate.tm_mday,
            appointmentDate.tm_mon + 1,
            doctorID,
            "no patient yet"
        ); // Ensure this constructor exists

        schedules[selectedDay - 1][selectedSlot - 1] = newAppointment;
        count++;
        string profession;

        // Save the updated schedule
        saveSchedule(profession);
    }
    catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }
}

bool ScheduleTime::addAppointmentForPatient(const std::string& patientID, int field) {
    // Load the schedule for the chosen profession
    string profession;
    switch (field) {
    case 1:
        profession = "Cardiologist";
        break;
    case 2:
        profession = "Neurologist";
        break;
    case 3:
        profession = "Dermatologist";
        break;
    case 4:
        profession = "Ophthalmology";
        break;
    case 5:
        profession = "Psychiatry";
        break;
    }
    try {
        loadSchedule(profession);
    }
    catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
        return false;
    }

    displayForPatient(profession);

    // Let the patient choose from the displayed appointments
    int selectedDay, selectedSlot;
    cout << "Enter the day (1-7): ";
    cin >> selectedDay;
    cout << "Enter the slot number (1-" << slots << "): ";
    cin >> selectedSlot;

    try {
        if (selectedDay < 1 || selectedDay > days || selectedSlot < 1 || selectedSlot > slots) {
            throw invalid_argument("Invalid day or slot number.");
        }

        // Check if the selected appointment slot is available
        if (schedules[selectedDay - 1][selectedSlot - 1] != nullptr) {
            throw runtime_error("This slot is already reserved!");
        }

        // Assign patient ID to the selected appointment slot
        schedules[selectedDay - 1][selectedSlot - 1] = new Appointment(
            selectedDay,
            month,
            "placeholder doctor ID",
            patientID
        ); // Create Appointment object with proper parameters

        // Save the updated schedule
        saveSchedule(profession);

        cout << "Appointment booked successfully!" << endl;
        return true; // Return true to indicate successful booking
    }
    catch (const invalid_argument& e) {
        cout << "Invalid argument: " << e.what() << endl;
    }
    catch (const runtime_error& e) {
        cout << "Runtime error: " << e.what() << endl;
    }

    return false; // Return false if booking failed
}

void ScheduleTime::saveSchedule(const string& profession) {
    //string filename = getFilename(doctorID);
    string filename;

    // Map the profession to the corresponding file prefix
    if (profession == "Cardiologist") {
        filename = "CardiologistSchedule.txt";
    }
    else if (profession == "Neurologist") {
        filename = "NeurologistSchedule.txt";
    }
    else if (profession == "Dermatologist") {
        filename = "DermatologistSchedule.txt";
    }
    else if (profession == "Ophthalmology") {
        filename = "OphthalmologySchedule.txt";
    }
    else if (profession == "Psychiatry") {
        filename = "PsychiatrySchedule.txt";
    }
    else {
        cout << "Error: Unknown profession " << profession << endl;
        return;
    }

    ofstream outFile(filename);
    if (!outFile) {
        throw runtime_error("Error: Unable to open file for writing.");
    }

    // Write the schedule to the file
    for (int d = 0; d < days; ++d) {
        for (int s = 0; s < slots; ++s) {
            if (schedules[d][s] != nullptr) {
                outFile << dayname[d] << " " << time[s] << " " << schedules[d][s]->getPatientID() << endl;
            }
        }
    }

    outFile.close(); // Close the file after writing
}

void ScheduleTime::loadSchedule(const string& doctorID) {
    string filename;

    // Map the profession to the corresponding file prefix
    if (doctorID[1] == 'C') {
        filename = "CardiologistSchedule.txt";
    }
    else if (doctorID[1] == 'N') {
        filename = "NeurologistSchedule.txt";
    }
    else if (doctorID[1] == 'D') {
        filename = "DermatologistSchedule.txt";
    }
    else if (doctorID[1] == 'O') {
        filename = "OphthalmologySchedule.txt";
    }
    else if (doctorID[1] == 'P') {
        filename = "PsychiatrySchedule.txt";
    }
    ifstream inFile(filename);
    if (!inFile) {
        // If the file doesn't exist yet, no appointments exist
        return;
    }

    // Clear existing schedule
    for (int d = 0; d < days; ++d) {
        for (int s = 0; s < slots; ++s) {
            delete schedules[d][s];
            schedules[d][s] = nullptr;
        }
    }

    // Read appointments from file and add them to the schedule
    string dayOfWeek, timeSlot, patientID;
    int dayIndex, slotIndex;
    while (inFile >> dayOfWeek >> timeSlot >> patientID) {
        // Find the day index
        dayIndex = find(begin(dayname), end(dayname), dayOfWeek) - begin(dayname);
        // Find the time slot index
        slotIndex = find(begin(time), end(time), timeSlot) - begin(time);

        // Create an appointment and assign it to the schedule
        Appointment* newAppointment = new Appointment(0 // Need proper day
            , 0 // Need proper month
            , doctorID
            , patientID);
        schedules[dayIndex][slotIndex] = newAppointment;
    }

    inFile.close(); // Close the file after reading
}

// Implement other member functions similarly, ensuring all necessary variables are properly declared and used

void ScheduleTime::removeSlot(const string& doctorID) {
    int selectedDay = 0;
    int selectedSlot = 0;

    try {
        cout << "Select a day to remove a slot:\n";
        for (int d = 0; d < days; d++) {
            cout << d + 1 << ". " << dayname[d] << endl;
        }
        cout << "Enter the number of the day: ";
        cin >> selectedDay;
        if (selectedDay < 1 || selectedDay > days) {
            throw invalid_argument("Invalid day number!");
        }

        cout << "Enter the number of slot to remove: ";
        cin >> selectedSlot;
        if (selectedSlot < 1 || selectedSlot > slots) {
            throw invalid_argument("Invalid slot number!");
        }

        delete schedules[selectedDay - 1][selectedSlot - 1];
        schedules[selectedDay - 1][selectedSlot - 1] = nullptr;
        count--;
        string profession;
        switch (doctorID[1]) {
        case 'C':
            profession = "Cardiologist";
            break;
        case 'D':
            profession = "Dermatologist";
            break;
        case 'N':
            profession = "Neurologist";
            break;
        case 'O':
            profession = "Ophthalmology";
            break;
        case 'P':
            profession = "Psychiatry";
            break;
        }
        // Save the updated schedule
        saveSchedule(profession);
    }
    catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }
}

tm ScheduleTime::getNextWeekdayDate(int weekday) {
    // Get the current time
    auto now = system_clock::now();
    time_t currentTime = system_clock::to_time_t(now);
    tm currentLocalTime;
    localtime_s(&currentLocalTime, &currentTime);

    // Calculate days to add to reach the desired weekday
    int currentWeekday = currentLocalTime.tm_wday; // Sunday=0, Monday=1, ..., Saturday=6
    int daysToAdd = (weekday - currentWeekday + 7) % 7; // Calculate difference in days

    // Add the days to get to the next desired weekday
    currentLocalTime.tm_mday += daysToAdd;
    mktime(&currentLocalTime); // Normalize the time structure

    return currentLocalTime;
}

void ScheduleTime::displaySchedule() {
    cout << "Schedule:\n";
    for (int d = 0; d < days; d++) {
        cout << "Day: " << dayname[d] << endl;
        for (int s = 0; s < slots; s++) {
            cout << "Slot: " << s + 1 << " Time: " << time[s] << endl;
            if (schedules[d][s] == nullptr) {
                cout << "No Appointment Reserved" << endl;
            }
            else {
                schedules[d][s]->displayApp();
            }
        }
    }
}

void ScheduleTime::displayForPatient(const string& profession) {
    string filename;

    // Map the profession to the corresponding file prefix
    if (profession == "Cardiologist") {
        filename = "CardiologistSchedule.txt";
    }
    else if (profession == "Neurologist") {
        filename = "NeurologistSchedule.txt";
    }
    else if (profession == "Dermatologist") {
        filename = "DermatologistSchedule.txt";
    }
    else if (profession == "Ophthalmology") {
        filename = "OphthalmologySchedule.txt";
    }
    else if (profession == "Psychiatry") {
        filename = "PsychiatrySchedule.txt";
    }
    else {
        cout << "Error: Unknown profession " << profession << endl;
        return;
    }

    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error: Unable to load appointments for doctor " << profession << endl;
        return;
    }

    cout << "Schedule for " << profession << ":\n";
    string line;
    while (getline(inFile, line)) {
        istringstream iss(line);
        string dayOfWeek, timeSlot, patientID;

        if (!(iss >> dayOfWeek >> timeSlot >> ws && getline(iss, patientID))) {
            cout << "Error: Malformed line in schedule file: " << line << endl;
            continue;
        }

        cout << "Day: " << dayOfWeek << ", Slot: " << timeSlot << ", Patient: " << patientID << endl;
    }

    inFile.close();
}

void ScheduleTime::removeAppointmentForPatient(const string& patientID, const string& profession) {
    int selectedDay, selectedSlot;
    cout << "Enter the day (1-7): ";
    cin >> selectedDay;
    cout << "Enter the slot (1-3): ";
    cin >> selectedSlot;

    try {
        if (selectedDay < 1 || selectedDay > days || selectedSlot < 1 || selectedSlot > slots) {
            throw invalid_argument("Invalid day or slot number.");
        }

        // Determine doctor ID placeholder for loading schedule
        string filename;

        if (profession == "Cardiologist") {
            filename = "CardiologistSchedule.txt";
        }
        else if (profession == "Neurologist") {
            filename = "NeurologistSchedule.txt";
        }
        else if (profession == "Dermatologist") {
            filename = "DermatologistSchedule.txt";
        }
        else if (profession == "Ophthalmology") {
            filename = "OphthalmologySchedule.txt";
        }
        else if (profession == "Psychiatry") {
            filename = "PsychiatrySchedule.txt";
        }
        else {
            cout << "Error: Unknown profession " << profession << endl;
            return;
        }
        string f = "A" + filename.substr(0, 1) + "C";
        loadSchedule(f); // Load the schedule for the profession

        if (schedules[selectedDay - 1][selectedSlot - 1] != nullptr) {
            if (schedules[selectedDay - 1][selectedSlot - 1]->getPatientID() == patientID) {
                delete schedules[selectedDay - 1][selectedSlot - 1];
                schedules[selectedDay - 1][selectedSlot - 1] = nullptr;
                cout << "Appointment removed successfully.\n";
            }
            else {
                throw runtime_error("You are not authorized to remove this appointment.");
            }
        }
        else {
            throw runtime_error("No appointment found at the selected day and slot.");
        }

        saveSchedule(profession); // Save the updated schedule back to the file
    }
    catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }
    catch (const runtime_error& e) {
        cout << e.what() << endl;
    }
}

void ScheduleTime::extractSchedule(const string& doctorID) {
    string filename;
    if (doctorID[1] == 'C') {
        filename = "CardiologistSchedule.txt";
    }
    else if (doctorID[1] == 'N') {
        filename = "NeurologistSchedule.txt";
    }
    else if (doctorID[1] == 'D') {
        filename = "DermatologistSchedule.txt";
    }
    else if (doctorID[1] == 'O') {
        filename = "OphthalmologySchedule.txt";
    }
    else if (doctorID[1] == 'P') {
        filename = "PsychiatrySchedule.txt";
    }
    string f = "A" + filename.substr(0, 1) + "C";
    loadSchedule(f); // Load the existing appointments from the file
    cout << "Appointments extracted and loaded for doctor ID: " << doctorID << endl;
}