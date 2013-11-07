//
//  student.cpp
//  Reed Halberg
//  James Kerr
//

#include "student.h"
#include <sstream>
#include <fstream>

Student::Student(){
    this->ID = 0;
    this->advisor = 0;
    this->GPA = 0;
    this->name = "";
    this->level = "";
    this->major = "";
}
Student::Student(int Id, int adv, double g, string n, string l, string m){
    this->ID = Id;
    this->advisor = adv;
    this->GPA = g;
    this->name = n;
    this->level = l;
    this->major = m;
}
Student::~Student(){
    
}

// Comparison operators
bool Student::operator > (const Student& other){
    return ID > other.ID;
}
bool Student::operator < (const Student& other){
    return ID < other.ID;
}
bool Student::operator == (const Student& other){
    return ID == other.ID;
}

bool Student::operator != (const Student& other) {
    return ID != other.ID;
}

//Serialization/Deserialization operators
bool Student::serialize (std::fstream &file){
    try{
        
        char temp[8];
        
        // copy ID into char array
        temp[0] = (ID >> 24) & 0xFF;
        temp[1] = (ID >> 16) & 0xFF;
        temp[2] = (ID >> 8) & 0xFF;
        temp[3] = ID & 0xFF;
        
        // copy Advisor into char array
        temp[4] = (advisor >> 24) & 0xFF;
        temp[5] = (advisor >> 16) & 0xFF;
        temp[6] = (advisor >> 8) & 0xFF;
        temp[7] = advisor & 0xFF;
        
        // Load GPA into char array
        char temp2[8];
        memcpy(&temp2, &GPA, sizeof(double));
        
        if (file.is_open()){
            file.write(temp, 8);
            file.write(temp2, 8);
        }
        
        // Load each string field into char array
        storeStr(name, file);
        storeStr(level, file);
        storeStr(major, file);
        
        
    }
    catch(std::exception e){
        return false;
    }
    return true;
}

// Saves string into file
void Student::storeStr(string str, std::fstream &file){
    
    const char* s = str.c_str();
    
    if (file.is_open()) {
        file.write(s, str.length() + 1);
    }
}

// Loads student from file data
void Student::deserialize (char* addr, int &dPtr, unsigned long buffSize){
    ID = 0;
    
    // Load ID from data
    if (!checkBuffForBytes(4, dPtr, buffSize)) throw 10;
    ID |= ((int(0 | addr[dPtr++]) & 0xFF) << 24);
    ID |= ((int(0 | addr[dPtr++]) & 0xFF) << 16);
    ID |= ((int(0 | addr[dPtr++]) & 0xFF) << 8);
    ID |= ((int(0 | addr[dPtr++]) & 0xFF) << 0);

    // Load Advisor
    if (!checkBuffForBytes(4, dPtr, buffSize)) throw 10;
    advisor |= ((int(0 | addr[dPtr++]) & 0xFF) << 24);
    advisor |= ((int(0 | addr[dPtr++]) & 0xFF) << 16);
    advisor |= ((int(0 | addr[dPtr++]) & 0xFF) << 8);
    advisor |= ((int(0 | addr[dPtr++]) & 0xFF) << 0);
    
    // Load GPA
    //Load GPA
    GPA = 0;
    char tGPA[8];
    if (!checkBuffForBytes(8, dPtr, buffSize)) throw 10;
    for (int p = 0; p < 8; ++p, ++dPtr){
        tGPA[p] = addr[dPtr];
    }
    
    GPA = *(double*)tGPA;
    
    // Load name
    name = getStr(dPtr, addr, buffSize);
    // Load level
    level = getStr(dPtr, addr, buffSize);
    // Load major
    major = getStr(dPtr, addr, buffSize);
}

bool Student::checkBuffForBytes(int bytes, int &dPtr, unsigned long buffSize){
    return (dPtr <= buffSize - bytes);
}

// reads string in buffer
string Student::getStr(int &dPtr, char *d, unsigned long buffSize){
    string temp = "";
    
    while(d[dPtr] != 0){
        if (!checkBuffForBytes(1, dPtr, buffSize)) throw 10;
        temp += d[dPtr++];
    }
    dPtr++; // increments over null character
    
    return temp;
}

// Student toString used for printing
std::string Student::toString(){
    std::stringstream i, g, a;
    i << ID;
    g << GPA;
    a << advisor;
    std::string temp = "ID: " + i.str() + "\nName: " + name + "\nAdvisor: " + a.str() + "\nMajor: " + major + "\nLevel: " + level + "\nGPA: " + g.str();
    return temp;
}

