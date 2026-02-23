#pragma once
#include <string>
#include "Doctor.h"
#include "Patient.h"
#include "ScheduleTime.h"

template <class U>
U loguser(std::string type);

void askdr(Doctor D, ScheduleTime& s);
void askp(Patient P, ScheduleTime& s);