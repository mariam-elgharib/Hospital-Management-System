#include "Patient.h"
#include <fstream>
#include <regex>
#include <stdexcept>
#include <iostream>
#include <limits>
#include <cctype>
#include "payment.h"

using namespace std;

const string Patient::professions[] = { "Cardiologist", "Neurologist", "Dermatologist", "Ophthalmologist", "Psychiatrist" };

Patient::Patient() : User(), H() {
    field = -1;
}

Patient::Patient(string n, string i, int a, string phn, string em, string h) : User(n, i, a, phn, em), H() {
    field = -1;
}

Patient::Patient(string n, string i) : User(n, i), H() {
    field = -1;
}

void Patient::takeinfo() {
    try {
        cout << "Enter Age: ";
        if (!(cin >> age)) {
            throw runtime_error("Invalid input for age. Please enter a valid number.");
        }

        // Clear input buffer after taking age
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Email validation loop
        bool validEmail = false;
        while (!validEmail) {
            cout << "Enter Email: ";
            cin >> email;
            std::regex emailPattern(R"((\w+)(\.|\_)?(\w*)@(\w+)(\.(\w+))+)");
            if (std::regex_match(email, emailPattern)) {
                validEmail = true;
            }
            else {
                cout << "Invalid email. Please enter a valid email address." << endl;
            }
        }

        // Phone number validation loop
        bool validPhone = false;
        while (!validPhone) {
            cout << "Enter Phone Number: ";
            cin >> phonenum;
            validPhone = true;
            if (phonenum.length() < 5) {
                validPhone = false;
            }
            else {
                for (char c : phonenum) {
                    if (!isdigit(c)) {
                        validPhone = false;
                        break;
                    }
                }
            }
            if (!validPhone) {
                cout << "Invalid phone number. Please enter at least 5 digits." << endl;
            }
        }

        H.setHistory();

        for (int i = 0; i < 5; i++) {
            cout << i + 1 << ". " << professions[i] << endl;
        }

        cout << "Enter Profession: ";
        if (!(cin >> field) || field < 1 || field > 5) {
            throw runtime_error("Invalid profession selection. Please enter a number between 1 and 5.");
        }

        patientfile();

    }
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
        // Clear the input buffer in case of an invalid input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

bool Patient::PtValidation() {
    string filename = ID + ".txt";
    ifstream file(filename);
    if (file.is_open()) {
        file.close();
        return true;
    }
    else {
        return false;
    }
}
void Patient::PTExtraction() {
    string filename = ID + ".txt";
    ifstream patientfile;
    bool historyStarted = false;
    string totalHistory;

    try {
        patientfile.open(filename);
        if (!patientfile.is_open()) {
            throw runtime_error("Error: Unable to open file " + filename);
        }

        string line;
        while (getline(patientfile, line)) {
            string nameString = "Name:";
            string ageString = "Age:";
            string phoneString = "Phone number:";
            string emailString = "Email:";
            string fieldString = "field:";
            string historyString = "History:";
            size_t namePosition = line.find(nameString);
            size_t agePosition = line.find(ageString);
            size_t phonePosition = line.find(phoneString);
            size_t emailPosition = line.find(emailString);
            size_t fieldPosition = line.find(fieldString);
            size_t historyPosition = line.find(historyString);

            if (namePosition != string::npos) {
                this->name = line.substr(namePosition + nameString.length());
                this->name.erase(this->name.find_last_not_of(" \n\r\t") + 1);
                cout << "Name extracted: " << this->name << endl; // Debug output
            }
            else if (agePosition != string::npos) {
                string ageStr = line.substr(agePosition + ageString.length());
                ageStr.erase(ageStr.find_last_not_of(" \n\r\t") + 1);
                try {
                    this->age = stoi(ageStr);
                    cout << "Age extracted: " << this->age << endl; // Debug output
                }
                catch (const invalid_argument&) {
                    throw runtime_error("Error: Invalid age format in the file.");
                }
            }
            else if (phonePosition != string::npos) {
                this->phonenum = line.substr(phonePosition + phoneString.length());
                this->phonenum.erase(this->phonenum.find_last_not_of(" \n\r\t") + 1);
                cout << "Phone number extracted: " << this->phonenum << endl; // Debug output
            }
            else if (emailPosition != string::npos) {
                this->email = line.substr(emailPosition + emailString.length());
                this->email.erase(this->email.find_last_not_of(" \n\r\t") + 1);
                cout << "Email extracted: " << this->email << endl; // Debug output
            }
            else if (fieldPosition != string::npos) {
                string fieldStr = line.substr(fieldPosition + fieldString.length());
                fieldStr.erase(fieldStr.find_last_not_of(" \n\r\t") + 1);
                try {
                    this->field = stoi(fieldStr);
                    cout << "Field extracted: " << this->field << endl; // Debug output
                }
                catch (const invalid_argument&) {
                    throw runtime_error("Error: Invalid field format in the file.");
                }
            }
            else if (historyPosition != string::npos) {
                historyStarted = true;
                string historyLine = line.substr(historyPosition + historyString.length());
                historyLine.erase(historyLine.find_last_not_of(" \n\r\t") + 1);
                totalHistory += historyLine + "\n";
            }
            else if (historyStarted) {
                totalHistory += line + "\n";
            }
        }

        if (historyStarted) {
            H.settotal(totalHistory);
            cout << "History extracted: " << totalHistory << endl; // Debug output
        }
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }

    if (patientfile.is_open()) {
        patientfile.close();
    }
}




void Patient::patientfile() {
    ofstream patientdata;
    string filename = ID + ".txt";

    patientdata.open(filename, ios::app);
    if (patientdata.is_open()) {
        patientdata << "Name:" << name << endl;
        patientdata << "ID:" << ID << endl;
        patientdata << "Age:" << age << endl;
        patientdata << "Phone number:" << phonenum << endl;
        patientdata << "Email:" << email << endl;
        patientdata << "Field:" << field << endl;
        patientdata << "History:" << H.getHistory() << endl;
        patientdata << "--------------------------------" << endl;
        patientdata.close();
    }
}
void Patient::PtUpdate() {
    string data[6];
    int order;
    cout << "1: Update phone number" << endl;
    cout << "2: Update email" << endl;
    cout << "3: Update field" << endl;
    cout << "4: Update history" << endl;
    cout << "Choose from the options: ";
    cin >> order;
    while (order < 1 || order > 4) {
        cout << "Invalid Input! Choose again: ";
        cin >> order;
    }

    string filename = ID + ".txt";
    string line;

    ifstream ptfile;
    try {
        ptfile.open(filename, ios::in);
        if (!ptfile) {
            throw runtime_error("File could not be opened for reading!");
        }

        for (int i = 0; i < 6; i++) {
            if (getline(ptfile, line)) {
                data[i] = line;
            }
            else {
                data[i] = ""; // Handle case when fewer than 6 lines in file
            }
        }
        ptfile.close();
    }
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return;
    }

    // Clear input buffer before taking new input
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string Hnewline;
    try {
        switch (order) {
        case 1: {
            string newline;
            cout << "Enter new phone number: ";
            getline(cin, newline);
            data[3] = "Phone number: " + newline; // Correct array index and format
            break;
        }
        case 2: {
            string newline;
            cout << "Enter new email: ";
            getline(cin, newline);
            data[4] = "Email: " + newline; // Correct array index and format
            break;
        }
        case 3: {
            string newline;
            cout << "Enter new field: ";
            getline(cin, newline);
            data[5] = "field: " + newline; // Correct array index and format
            break;
        }
        case 4:
        {
            cout << "Enter new History: ";
            getline(cin, Hnewline);
            // Correct array index and format
            break;
        }
        default:
            throw invalid_argument("Invalid option selected!");
        }
    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
        return;
    }
    ofstream ptfile_out;
    try {
        switch (order)
        {
        case 1:
        {
            ptfile_out.open(filename, ios::out);
            if (!ptfile_out)
            {
                throw runtime_error("File could not be opened for writing!");
            }

            for (int i = 0; i < 6; i++)
            {
                ptfile_out << data[i] << endl;
            }
            ptfile_out.close();
            break;
        }
        case 2:
        {
            ptfile_out.open(filename, ios::out);
            if (!ptfile_out)
            {
                throw runtime_error("File could not be opened for writing!");
            }

            for (int i = 0; i < 6; i++)
            {
                ptfile_out << data[i] << endl;
            }
            ptfile_out.close();
            break;
        }
        case 3:
        {
            ptfile_out.open(filename, ios::out);
            if (!ptfile_out)
            {
                throw runtime_error("File could not be opened for writing!");
            }

            for (int i = 0; i < 6; i++)
            {
                ptfile_out << data[i] << endl;
            }
            ptfile_out.close();
            break;
        }
        case 4:
        {
            ptfile_out.open(filename, ios::app);
            if (!ptfile_out)
            {
                throw runtime_error("File could not be opened for writing!");
            }
            ptfile_out << endl << "updated history: " << Hnewline << endl;
            break;
        }
        }
    }
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }
}

void Patient::setField(int f) {
    field = f;
}

int Patient::getfield() {
    return field;
}

void Patient::printPDetails() {
    cout << "Patient's Details:" << endl;
    cout << "Name: " << name << endl;
    cout << "ID: " << ID << endl;
    cout << "Age: " << age << endl;
    cout << "Phone number: " << phonenum << endl;
    cout << "Email: " << email << endl;
    cout << "History: " << H.getHistory() << endl;
}

void Patient::paymentpatient() {
    Pay.setPriceBasedOnField(field);
    Pay.chooseInsurance();
    Pay.applyInsuranceDiscount();
    Pay.calculateFinalBill();
    Pay.printBill();
}
