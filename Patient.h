#ifndef PATIENT_H
#define PATIENT_H

#include "User.h"
#include "history.h"
#include "payment.h"
#include "Appointment.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Patient : public User {
private:
    History H;
    int field;
    static const int size = 5;
    static const string professions[5];
    Payment Pay;

public:
    Patient();
    Patient(string n, string i);
    Patient(string n, string i, int a, string phn, string em, string h);

    void PtUpdate();
    void takeinfo();
    bool PtValidation();
    void PTExtraction();
    void patientfile();
    void setField(int f);
    int getfield();
    void printPDetails();
    void paymentpatient();
};

#endif // PATIENT_H
