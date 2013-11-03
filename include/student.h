//
//  student.h
//  Reed Halberg
//  James Kerr
//

#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <cstring>

using std::cout;
using std::string;

class Student{
public:
    Student();
    Student(int Id): ID(Id) {}
    Student(int Id, int adv, double g, string n, string l, string m);
    virtual ~Student();
    
    // Comparison operators
    bool operator > (const Student& other);
    bool operator < (const Student& other);
    bool operator == (const Student& other);
    bool operator != (const Student& other);
    
    //Serialization/Deserialization operators
    bool serialize (char* addr, int &dPtr);
    bool deserialize (char* addr, int &dPtr);
    
    //Methods
    std::string toString();
    
    // Getters/Setters
    int getID() {return ID;};
    int getAdvisor() {return advisor;};
    void setAvisor(int x) {advisor = x;};
    double getGPA() {return GPA;};
    string getName() {return name;};
    string getLevel() {return level;};
    string getMajor() {return major;};
    
private:
    int ID;
    int advisor;
    double GPA;
    string name;
    string level;
    string major;
    
    // Serialization helper functions
    void storeStr(string str, int &dPtr, char *d);
    string getStr(int &dPtr, char *d);
};

#endif