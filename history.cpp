#include "history.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <limits> // Include the limits header

using namespace std;

History::History() {
    numa = 0;
    nump = 0;
    numcm = 0;
    Allergies = nullptr;
    PastSurgeries = nullptr;
    CurrentMedication = nullptr;
}

History::~History() {
    if (Allergies != nullptr) {
        delete[] Allergies;
        Allergies = nullptr;
    }
    if (PastSurgeries != nullptr) {
        delete[] PastSurgeries;
        PastSurgeries = nullptr;
    }
    if (CurrentMedication != nullptr) {
        delete[] CurrentMedication;
        CurrentMedication = nullptr;
    }
}

void History::setHistory() {
    int n;
    try {
        cout << "Number of Current Medication: ";
        cin >> n;
        if (!cin || n < 0 || n > 100) {
            throw invalid_argument("Invalid input for number of current medications.");
        }
        setnumcm(n);

        cout << "Number of Past Surgeries: ";
        cin >> n;
        if (!cin || n < 0 || n > 100) {
            throw invalid_argument("Invalid input for number of past surgeries.");
        }
        setnump(n);

        cout << "Number of Allergies: ";
        cin >> n;
        if (!cin || n < 0 || n > 100) {
            throw invalid_argument("Invalid input for number of allergies.");
        }
        setnuma(n);
    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Corrected error handling
    }
    catch (const bad_alloc& e) {
        cerr << "Memory allocation failed: " << e.what() << endl;
    }
}

void History::setnuma(int n) {
    numa = n;
    delete[] Allergies;
    Allergies = nullptr;
    try {
        Allergies = new string[numa];
        setAllergies();
    }
    catch (const bad_alloc& e) {
        cerr << "Memory allocation failed: " << e.what() << endl;
        numa = 0;
    }
}

void History::setnumcm(int n) {
    numcm = n;
    delete[] CurrentMedication;
    CurrentMedication = nullptr;
    try {
        CurrentMedication = new string[numcm];
        setCurrentMedication();
    }
    catch (const bad_alloc& e) {
        cerr << "Memory allocation failed: " << e.what() << endl;
        numcm = 0;
    }
}

void History::setnump(int n) {
    nump = n;
    delete[] PastSurgeries;
    PastSurgeries = nullptr;
    try {
        PastSurgeries = new string[nump];
        setPastSurgeries();
    }
    catch (const bad_alloc& e) {
        cerr << "Memory allocation failed: " << e.what() << endl;
        nump = 0;
    }
}

void History::setAllergies() {
    cout << "Enter allergies:" << endl;
    for (int i = 0; i < numa; ++i) {
        cout << "Allergy " << i + 1 << ": ";
        cin >> Allergies[i];
        if (!cin) {
            cerr << "Invalid input for allergy." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return; // Exiting the function due to invalid input
        }
    }
}

void History::setPastSurgeries() {
    cout << "Enter past surgeries:" << endl;
    for (int i = 0; i < nump; ++i) {
        cout << "Past Surgery " << i + 1 << ": ";
        cin >> PastSurgeries[i];
        if (!cin) {
            cerr << "Invalid input for past surgery." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return; // Exiting the function due to invalid input
        }
    }
}

void History::setCurrentMedication() {
    cout << "Enter Current Medication:" << endl;
    for (int i = 0; i < numcm; ++i) {
        cout << "Current Medication " << i + 1 << ": ";
        cin >> CurrentMedication[i];
        if (!cin) {
            cerr << "Invalid input for current medication." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return; // Exiting the function due to invalid input
        }
    }
}

void History::displayAllergies() const {
    cout << "Allergies:" << endl;
    for (int i = 0; i < numa; ++i) {
        cout << "Allergy " << i + 1 << ": " << Allergies[i] << endl;
    }
}

void History::displayPastSurgeries() const {
    cout << "Past Surgeries:" << endl;
    for (int i = 0; i < nump; ++i) {
        cout << "Past Surgery " << i + 1 << ": " << PastSurgeries[i] << endl;
    }
}

void History::displayCurrentMedication() const {
    cout << "Current Medication:" << endl;
    for (int i = 0; i < numcm; ++i) {
        cout << "Current Medication " << i + 1 << ": " << CurrentMedication[i] << endl;
    }
}

string History::getHistory() const {
    string historyString;

    historyString += "Allergies:\n";
    for (int i = 0; i < numa; ++i) {
        historyString += "Allergy " + to_string(i + 1) + ": " + Allergies[i] + "\n";
    }

    historyString += "Current Medication:\n";
    for (int i = 0; i < numcm; ++i) {
        historyString += "Medication " + to_string(i + 1) + ": " + CurrentMedication[i] + "\n";
    }

    historyString += "Past Surgeries:\n";
    for (int i = 0; i < nump; ++i) {
        historyString += "Surgery " + to_string(i + 1) + ": " + PastSurgeries[i] + "\n";
    }

    return historyString;
}

void History::settotal(string t) {
    totalhistory = t;
}

string History::gettotal() {
    return totalhistory;
}
