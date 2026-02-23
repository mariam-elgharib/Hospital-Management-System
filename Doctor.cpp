#include "User.h"
#include "Doctor.h"
#include "Patient.h"
#include "Scheduletime.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

Doctor::Doctor() : User() {
    profession = -1;
}

Doctor::Doctor(string n, string i) : User(n, i) {
    profession = -1;
}

void Doctor::setproff(int p) {
    profession = p;
}

int Doctor::getprof() {
    return profession;
}

void Doctor::DrExtract() {
    string filename = ID + ".txt";
    ifstream doctorfile;

    try {
        // Attempt to open the file
        doctorfile.open(filename);
        if (!doctorfile.is_open()) {
            // Throw an exception if the file cannot be opened
            throw runtime_error("Error: Unable to open file " + filename);
        }

        string line;
        int age = -1;

        // Read the file line by line
        while (getline(doctorfile, line)) {
            string nameString = "Name:";
            string IDString = "ID:";
            string ageString = "age:";
            string phoneString = "Phonenumber:";
            string emailString = "email:";

            size_t namePosition = line.find(nameString);
            size_t agePosition = line.find(ageString);
            size_t IDPosition = line.find(IDString);
            size_t phonePosition = line.find(phoneString);
            size_t emailPosition = line.find(emailString);

            // Extract and assign each detail to the Doctor object
            if (namePosition != string::npos) {
                this->name = line.substr(namePosition + nameString.length());
                this->name.erase(name.find_last_not_of(" \n\r\t") + 1);
            }
            else if (agePosition != string::npos) {
                string ageStr = line.substr(agePosition + ageString.length());
                ageStr.erase(ageStr.find_last_not_of(" \n\r\t") + 1);
                try {
                    // Attempt to convert the age string to an integer
                    this->age = stoi(ageStr);
                }
                catch (const invalid_argument&) {
                    // Throw an exception if the age format is invalid
                    throw runtime_error("Error: Invalid age format in the file.");
                }
            }
            else if (phonePosition != string::npos) {
                this->phonenum = line.substr(phonePosition + phoneString.length());
                this->phonenum.erase(phonenum.find_last_not_of(" \n\r\t") + 1);
            }
            else if (emailPosition != string::npos) {
                this->email = line.substr(emailPosition + emailString.length());
                this->email.erase(email.find_last_not_of(" \n\r\t") + 1);
            }
        }

        doctorfile.close();
    }
    catch (const exception& e) {
        // Catch any exceptions and print the error message
        cerr << e.what() << endl;
        // Ensure the file is closed if an exception occurs
        if (doctorfile.is_open()) {
            doctorfile.close();
        }
    }
}

void Doctor::printdrdetails() {
    cout << "Name : " << name << endl;
    cout << "Profession : " << profession << endl;
    cout << "Age : " << age << endl;
    cout << "ID : " << ID << endl;
    cout << "Phone number : " << phonenum << endl;
    cout << "Email : " << email << endl;
}

bool Doctor::DrValidation() {
    ifstream doctorfile;
    string dline;
    string filename;

    try {
        // Determine the filename based on the ID prefix
        if (ID[1] == 'C') {
            filename = "Cardiologist.txt";
        }
        else if (ID[1] == 'N') {
            filename = "Neurologist.txt";
        }
        else if (ID[1] == 'D') {
            filename = "Dermatologist.txt";
        }
        else if (ID[1] == 'O') {
            filename = "Ophthalmology.txt";
        }
        else if (ID[1] == 'P') {
            filename = "Psychiatry.txt";
        }
        else {
            cout << "Invalid ID prefix" << endl;
            return false;
        }

        // Attempt to open the file
        doctorfile.open(filename);
        if (!doctorfile.is_open()) {
            // Throw an exception if the file cannot be opened
            throw runtime_error("Failed to open " + filename);
        }

        // Check each line in the file for the Doctor's ID
        while (getline(doctorfile, dline)) {
            stringstream ss(dline);
            string file_id;
            ss >> file_id;

            if (file_id == ID) {
                doctorfile.close();
                return true;
            }
        }
        doctorfile.close();
    }
    catch (const runtime_error& e) {
        // Catch runtime errors and print the error message
        cerr << "File error: " << e.what() << endl;
        return false;
    }
    catch (...) {
        // Catch any other exceptions and print a generic error message
        cerr << "An unexpected error occurred during validation" << endl;
        return false;
    }

    return false;
}

void Doctor::DrUpdate() {
    string data[5];
    int order;
    cout << "1: update phonenumber" << endl;
    cout << "2: update email" << endl;
    cout << "Choose from the options: ";
    cin >> order;

    // Validate user input
    while (order < 1 || order > 3) {
        cout << "Invalid Input! choose again : ";
        cin >> order;
    }

    string filename = ID + ".txt";
    string line;

    ifstream drfile;
    try {
        // Attempt to open the file for reading
        drfile.open(filename, ios::in);
        if (!drfile) {
            // Throw an exception if the file cannot be opened for reading
            throw runtime_error("File could not be opened for reading!");
        }

        // Read the first 5 lines from the file
        for (int i = 0; i < 5; i++) {
            if (getline(drfile, line)) {
                data[i] = line;
            }
            else {
                data[i] = "";
            }
        }
        drfile.close();
    }
    catch (const runtime_error& e) {
        // Catch runtime errors and print the error message
        cerr << e.what() << endl;
        return;
    }

    // Clear input buffer before taking new input
    cin.ignore(10000, '\n');

    try {
        // Update the selected field based on user input
        switch (order) {
        case 1: {
            string newline;
            cout << "Enter new phonenumber: ";
            getline(cin, newline);
            data[3] = "Phonenumber: " + newline;
            break;
        }
        case 2: {
            string newline;
            cout << "Enter new email: ";
            getline(cin, newline);
            data[4] = "email: " + newline;
            break;
        }
        default:
            // Throw an exception if an invalid option is selected
            throw invalid_argument("Invalid option selected!");
        }
    }
    catch (const invalid_argument& e) {
        // Catch invalid argument exceptions and print the error message
        cerr << e.what() << endl;
        return;
    }

    ofstream drfile_out;
    try {
        // Attempt to open the file for writing
        drfile_out.open(filename, ios::out);
        if (!drfile_out) {
            // Throw an exception if the file cannot be opened for writing
            throw runtime_error("File could not be opened for writing!");
        }

        // Write updated data back to the file
        for (int i = 0; i < 5; i++) {
            drfile_out << data[i] << endl;
        }
        drfile_out.close();
    }
    catch (const runtime_error& e) {
        // Catch runtime errors and print the error message
        cerr << e.what() << endl;
    }
}
