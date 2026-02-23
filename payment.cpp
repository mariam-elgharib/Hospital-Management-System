#include "Patient.h"
#include "payment.h"

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;
const string Payment::professions[5] = { "Cardiologist", "Neurologist", "Dermatologist", "Ophthalmology", "Psychiatry" };
Payment::Payment(int pID) : patientID(pID), totalBill(0.0), hasInsurance(false), discount(0.0) {}

Payment::Payment() {
    patientID = 0;
    totalBill = 0;
    hasInsurance = false;
    discount = 0;
}
void Payment::setPriceBasedOnField(int field) {
    try {
        if (field == 1) {
            totalBill = 250.0;
        }
        else if (field == 2) {
            totalBill = 200.0;
        }
        else if (field == 3) {
            totalBill = 150.0;
        }
        else if (field == 4) {
            totalBill = 300.0;
        }
        else if (field == 5) {
            totalBill = 500.0;
        }
        else {
            throw invalid_argument("Unknown field");  // i will throw el invalid argument
        }
    }
    catch (const invalid_argument& e) {
        cout << e.what() << ", setting default price to $100.0" << endl;
        totalBill = 100.0;
    }
}

void Payment::chooseInsurance() {
    char hasIns;
    cout << "Do you have insurance? (Y/N): ";
    cin >> hasIns;

    if (cin.fail()) {
        cin.clear(); // clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ba clear el input buffer aashan el leftovers mayedkholosh alaa baad // betreturn el maximum value el bey represent the number of char read aw writ
        // streamsize de bet represent el number of charachters read or written
        cout << "Invalid input. Please enter Y or N." << endl;
        chooseInsurance();
    }
    else if (hasIns == 'Y' || hasIns == 'y') {
        hasInsurance = true;
        cout << "Choose your insurance type (C for company, M for medical syndicate, E for engineering syndicate): ";
        cin >> insuranceType;
        if (insuranceType != "C" && insuranceType != "M" && insuranceType != "E") {
            cout << "Invalid insurance type. Setting insurance to 'None'." << endl;
            hasInsurance = false;
            insuranceType = "None";
        }
    }
    else if (hasIns == 'N' || hasIns == 'n') {
        hasInsurance = false;
        insuranceType = "None";
    }
    else {
        cout << "Invalid input. Please enter Y or N." << endl;
        chooseInsurance();
    }
}

void Payment::applyInsuranceDiscount() {
    if (hasInsurance) {
        if (insuranceType == "C") {
            discount = 1.0;
        }
        else if (insuranceType == "M") {
            discount = 0.20;
        }
        else if (insuranceType == "E") {
            discount = 0.25;
        }
        else {
            discount = 0.0;
        }
    }
    else {
        discount = 0.0;
    }
}

double Payment::calculateFinalBill() {
    if (discount == 1.0) {
        return 0.0;
    }
    return totalBill * (1 - discount);
}

void Payment::printBill() {
    try {
        double finalAmount = calculateFinalBill();
        cout << "Original Bill Amount: $" << totalBill << endl
            << "Insurance Type: " << insuranceType << endl
            << "Final Bill Amount: $" << finalAmount << endl;
    }
    catch (const exception& e) {   // el catch betemsek el exception(moshkila)
        cout << "An error occurred while printing the bill: " << e.what() << endl;  //fun
        // el .what bet return a c string bet describe moshkelet el exception

    }
}
