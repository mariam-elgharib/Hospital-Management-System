#include "User.h"
#include<iostream>
#include <string>
#include<fstream>
#include <stdexcept>   
using namespace std;

User::User()
{
    name = " ";
    ID = " ";
    age = 0;
}

User::User(string n, string i) {
    name = n;
    ID = i;
    age = 0;
}
User::User(string i) {
    ID = i;
    name = " ";
    age = 0;
}
User::User(string n, string i, int ag, string phn, string em) {
    name = n;
    ID = i;
    age = ag;
    phonenum = phn;
    email = em;
    if (ag < 0 || ag > 150) {
        throw invalid_argument("Invalid age provided.");
    }
    if (phn.length() != 10) { // Assuming phone number should be 10 digits
        throw invalid_argument("Invalid phone number provided.");
    }
    if (em.find('@') == string::npos) { // Basic email validation
        throw invalid_argument("Invalid email address provided.");
    }
}
void User::setname(string n) {
    if (n.empty()) {
        throw invalid_argument("Name cannot be empty.");
    }
    name = n;
}
void User::setage(int a) {
    if (a < 0 || a > 150) {
        throw invalid_argument("Invalid age provided.");
    }

    age = a;
}
void User::setid(string i) {
    if (i.empty()) {
        throw invalid_argument("ID cannot be empty.");
    }
    ID = i;
}
void User::setphone(string p) {
    if (p.length() != 11) {
        throw invalid_argument("Invalid phone number provided.");
    }
    phonenum = p;
}
void User::setemail(string e) {
    if (e.find('@') == string::npos) {
        throw invalid_argument("Invalid email address provided.");
    }
    email = e;
}
string User::getname() {
    return name;
}
int User::getage() {
    return age;
}
string User::getid() {
    return ID;
}
string User::getphone() {
    return phonenum;
}
string User::getemail() {
    return email;
}

