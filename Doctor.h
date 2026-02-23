#pragma once
#include "User.h"
#include "Patient.h"
#include "Scheduletime.h"
class Doctor : public User
{
protected:
	int profession;
public:
	Doctor();
	//Doctor(string i);
	Doctor(string n,string i);
	void setproff(int p) ;
    int getprof();
    void printdrdetails();
	void DrExtract();
	void DrUpdate();
    bool DrValidation();
};

