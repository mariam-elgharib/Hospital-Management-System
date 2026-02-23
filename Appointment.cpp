#include "Appointment.h"
#include <iostream>

Appointment::Appointment(int d, int m, const std::string& doctor, const std::string& patient)
    : day(d), month(m), doctorID(doctor), patientID(patient) {}

void Appointment::setPatientID(const std::string& patientID) {
    this->patientID = patientID;
}

std::string Appointment::getPatientID() const {
    return patientID;
}

void Appointment::displayApp() const {
    std::cout << "Appointment for Doctor: " << doctorID << " with Patient: " << patientID << " on Day: " << day << " Month: " << month << std::endl;
}

