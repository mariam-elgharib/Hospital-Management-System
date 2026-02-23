#pragma once
#include <iostream>
#include<string>
using namespace std;
class User
{
protected:
    string name;
    string ID;
    int age;
    string phonenum;
    string email;
public:
    User();
    User(string n,string i);
    User (string i);
    User(string n,string i,int ag,string phn,string em);
    void setname(string n);
    void setage(int a);
    void setid(string i);
    void setphone(string p);
    void setemail(string e);
    string getname();
    int getage();
    string getid();
    string getphone();
    string getemail();
};

