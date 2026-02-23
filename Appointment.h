#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>

class Appointment {
public:
    Appointment(int day, int month, const std::string& doctorID, const std::string& patientID);
    void setPatientID(const std::string& patientID);
    std::string getPatientID() const;
    void displayApp() const;
private:
    int day, month;
    std::string doctorID;
    std::string patientID;
};

#endif // APPOINTMENT_H
