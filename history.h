#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
#include <string>

using namespace std;

class History {
private:
    int numa; // Number of allergies
    int nump; // Number of past surgeries
    int numcm; // Number of current medications
    string* Allergies;
    string* PastSurgeries;
    string* CurrentMedication;
    string totalhistory;

public:
    History();
    ~History();

    void setHistory();
    void setnuma(int n);
    void setnumcm(int n);
    void setnump(int n);

    void setAllergies();
    void setPastSurgeries();
    void setCurrentMedication();

    void displayAllergies() const;
    void displayPastSurgeries() const;
    void displayCurrentMedication() const;
    void settotal(string t);
    string gettotal();
    string getHistory() const;
};

#endif // HISTORY_H
