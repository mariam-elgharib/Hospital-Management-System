#ifndef SCHEDULETIME_H
#define SCHEDULETIME_H

#include <string>

// Forward declaration of the Appointment class
#include "Appointment.h"

class ScheduleTime {
public:
    ScheduleTime();
    ~ScheduleTime();
    void addSlot(const std::string& doctorID);
    bool addAppointmentForPatient(const std::string& patientID, int field); 
    void saveSchedule(const std::string& doctorID);
    void loadSchedule(const std::string& doctorID);
    void removeSlot(const std::string& doctorID);
    void displaySchedule();
    void displayForPatient(const std::string& profession);
    void removeAppointmentForPatient(const std::string& patientID, const std::string& profession);
    void extractSchedule(const std::string& profession);
    static std::string getFilename(const std::string& doctorID);

private:
    static const std::string dayname[7];
    static const std::string time[3];
    static const int days = 7;
    static const int slots = 3;
    Appointment* schedules[days][slots];
    int count;
    int day, month, year;  // Add these declarations

    // Assume this function is implemented elsewhere
    tm getNextWeekdayDate(int weekday);
};

#endif // SCHEDULETIME_H