// payment.h : Include file for standard system include files,
// or project specific include files.

#pragma once

// Header for the Payment class
#ifndef PAYMENT_H_INCLUDED
#define PAYMENT_H_INCLUDED

#include "Patient.h"
#include <iostream>
#include <string>
using namespace std;

class Payment {
private:
    static const string professions[5];
    int patientID;
    double totalBill;
    bool hasInsurance;
    string insuranceType;
    double discount;

public:
    Payment();
    Payment(int pID);

    void setPriceBasedOnField(int field);

    void chooseInsurance();

    void applyInsuranceDiscount();

    double calculateFinalBill();

    void printBill();
};

#endif // PAYMENT_H_INCLUDED
