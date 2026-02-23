#include <iostream>
#include <string>
#include "Doctor.h"
#include "Patient.h"
#include "Source1.h"
#include "ScheduleTime.h"
#include "payment.h"

using namespace std;

int IDcnt = 2000;

// Template Specialization for Doctor
template <>
Doctor loguser<Doctor>(string type) {
    string i;
    cout << "Enter ID: ";
    std::cin >> i;

    while (i[0] != 'D') {
        cout << "Invalid ID! Enter Your ID Again: ";
        std::cin >> i;
    }
    Doctor D;
    D.setid(i);
    bool b = D.DrValidation();
    while (!b) {
        cout << "You're not registered! Enter Your ID Again: ";
        std::cin >> i;
        D.setid(i);
        b = D.DrValidation();
    }
    D.DrExtract();
    cout << "Welcome Dr " << D.getname() << "!" << endl;
    return D;
}

// Template Specialization for Patient
template <>
Patient loguser<Patient>(string type) {
    string choice;
    cout << "Are you New or Old?\n";
    std::cin >> choice;

    while (choice != "Old" && choice != "New" && choice != "old" && choice != "new") {
        cout << "Error! Enter Old or New: ";
        std::cin >> choice;
    }

    string n, i;
    cout << "Enter Name: ";
    std::cin >> n;

    if (choice == "Old" || choice == "old") {
        cout << "Enter ID: ";
        std::cin >> i;
        while (i[0] != 'P') {
            cout << "Invalid ID! Enter Your ID Again: ";
            std::cin >> i;
        }
        Patient P(n, i);
        bool b = P.PtValidation();
        if (!b) {
            cout << "ID Not Found! Enter Your Info:" << endl;
            P.takeinfo();
        }
        else {
            P.PTExtraction();
        }
        return P;
    }
    else if (choice == "New" || choice == "new") {
        string i = "P" + to_string(IDcnt++);
        Patient P(n, i);
        P.takeinfo();
        return P;
    }

    throw runtime_error("Invalid patient type");
}

void askp(Patient P, ScheduleTime& s) {
    cout << "What do you want to do? " << endl;
    string options[3] = { "Update Information", "Book an Appointment", "Cancel An Appointment" };
    int op;
    for (int j = 0; j < 3; ++j) {
        cout << j + 1 << ": " << options[j] << endl;
    }
    cout << "Choose an option: (Enter 0 to exit) ";
    std::cin >> op;
    int f = P.getfield();
    string proff;
    switch (f) {
    case 1:
        proff = "Cardiologist";
        break;
    case 2:
        proff = "Neurologist";
        break;
    case 3:
        proff = "Dermatologist";
        break;
    case 4:
        proff = "Ophthalmology";
        break;
    case 5: 
        proff = "Psychiatry";
        break;
    }
    while (true) {
        if (op == 0) {
            cout << "Program Exited Successfully" << endl;
            break;
        }
        if (op < 1 || op > 3) {
            cout << "Option isn't available. Enter again: ";
            std::cin >> op;
            continue;
        }
        switch (op) {
        case 1:
            P.PtUpdate();
            break;
        case 2: {
            //s.displayForPatient(proff);
            bool app = s.addAppointmentForPatient(P.getid(), P.getfield());
            if (app) {
                cout << endl << "Appointment made successfully." << endl;
                s.saveSchedule(proff); // Save the schedule after adding an appointment
                P.paymentpatient(); // Call the paymentpatient() function here
            }
            else {
                cout << "Appointment couldn't be booked." << endl;
            }
            break;
        }
        case 3: {
            s.displayForPatient(proff);
            s.removeAppointmentForPatient(P.getid(), proff);
            break;
        }
        }
        for (int j = 0; j < 3; ++j) {
            cout << j + 1 << ": " << options[j] << endl;
        }
        cout << endl;
        cout << "Choose an option: (Enter 0 to exit) ";
        std::cin >> op;
    }
}

void askdr(Doctor D, ScheduleTime& s) {
    string ops[4] = { "Update Information","Book An Appointment", "Cancel An Appointment", "Display Appointments" };
    int op;
    int f = D.getprof();
    string proff;
    switch (f) {
    case 1:
        proff = "Cardiologist";
        break;
    case 2:
        proff = "Neurologist";
        break;
    case 3:
        proff = "Dermatologist";
        break;
    case 4:
        proff = "Ophthalmology";
        break;
    case 5:
        proff = "Psychiatry";
        break;
    }
    s.extractSchedule(D.getid());
    cout << "What do you want to do? \n";
    for (int j = 0; j < 4; ++j) {
        cout << j + 1 << ": " << ops[j] << endl;
    }
    cout << "Choose an option: (Enter 0 to exit) ";
    std::cin >> op;
    while (true) {
        if (op == 0) {
            cout << "Program Exited Successfully" << endl;
            break;
        }
        if (op < 1 || op > 4) {
            cout << "Option isn't available. Enter again: ";
            std::cin >> op;
            continue;
        }
        int num;
        switch (op) {
        case 1: 
            D.DrUpdate();
            break;
        case 2: {
            cout << "How many slots do you want to add? ";
            std::cin >> num;
            for (int i = 0; i < num; i++) {
                s.addSlot(D.getid());
            }
            s.saveSchedule(D.getid()); // Save the schedule after adding slots
            break;
        }
        case 3: {
            cout << "How many slots do you want to remove? ";
            std::cin >> num;
            for (int i = 0; i < num; i++) {
                s.removeSlot(D.getid());
            }
            s.saveSchedule(D.getid()); // Save the schedule after removing slots
            break;
        }
            
        case 4:
            s.displaySchedule();
            break;
        }
        cout << endl;
        for (int j = 0; j < 4; ++j) {
            cout << j + 1 << ": " << ops[j] << endl;
        }
        cout << "Choose an option: (Enter 0 to exit) ";
        std::cin >> op;
    }
}

// Explicit template instantiation to avoid linking errors
template Doctor loguser<Doctor>(string);
template Patient loguser<Patient>(string);
