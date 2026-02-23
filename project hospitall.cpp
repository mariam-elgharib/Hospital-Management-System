#include <iostream>
#include <string>
#include "Source1.h"
#include "User.h"
#include "Doctor.h"
#include "Patient.h"
#include "ScheduleTime.h"
#include "Appointment.h"
#include "payment.h"
#include "history.h"

using namespace std;

template <class U>
U loguser(string type);

// int IDcnt = 2000; // Commented out as it's not used in this scope
const int size = 5;
ScheduleTime Cardio, Derma, Neuro, Ophtha, Psych;

string professions[] = { "Cardiologist", "Neurologist", "Dermatologist", "Ophthalmology", "Psychiatry" };

int main() {
    string type;
    cout << "Are You a Doctor or a Patient?\n";
    cin >> type;

    while (type != "Doctor" && type != "Patient" && type != "doctor" && type != "patient") {
        cout << "Error! Enter Doctor or Patient: ";
        cin >> type;
    }

    if (type == "Doctor" || type == "doctor") {
        Doctor D = loguser<Doctor>(type);
        string ID = D.getid();
        char i = ID[1];
        switch (i) {
        case 'C':
            askdr(D, Cardio);
            break;
        case 'D':
            askdr(D, Derma);
            break;
        case 'P':
            askdr(D, Psych);
            break;
        case 'O':
            askdr(D, Ophtha);
            break;
        case 'N':
            askdr(D, Neuro);
            break;
        default:
            cout << "Invalid Doctor ID!\n";
            break;
        }
    }
    else if (type == "Patient" || type == "patient") {
        Patient P = loguser<Patient>(type);
        int field = P.getfield();
        switch (field) {
        case 1:
            askp(P, Cardio);
            break;
        case 2:
            askp(P, Neuro);
            break;
        case 3:
            askp(P, Derma);
            break;
        case 4:
            askp(P, Ophtha);
            break;
        case 5:
            askp(P, Psych);
            break;
        default:
            cout << "Invalid Patient Field!\n";
            break;
        }
    }
    return 0;
}