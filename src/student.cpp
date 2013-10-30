//
//  student.cpp
//  Reed Halberg
//  James Kerr
//

#include "student.h"
#include <sstream>

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
bool Student::serialize (char* addr, int &dPtr){
    try{
        // copy ID into char array
        addr[dPtr++] = (ID >> 24) & 0xFF;
        addr[dPtr++] = (ID >> 16) & 0xFF;
        addr[dPtr++] = (ID >> 8) & 0xFF;
        addr[dPtr++] = ID & 0xFF;
        
        // copy Advisor into char array
        addr[dPtr++] = (advisor >> 24) & 0xFF;
        addr[dPtr++] = (advisor >> 16) & 0xFF;
        addr[dPtr++] = (advisor >> 8) & 0xFF;
        addr[dPtr++] = advisor & 0xFF;
        
        // Load GPA into char array
        char temp[8];
        memcpy(&temp, &GPA, sizeof(double));
        for(int i = 0; i < 8; ++i){
            addr[dPtr++] = *(temp + i);
        }
        
        // Load each string field into char array
        storeStr(name, dPtr, addr);
        storeStr(level, dPtr, addr);
        storeStr(major, dPtr, addr);
        
        
    }
    catch(std::exception e){
        return false;
    }
    return true;
}
void Student::storeStr(string str, int &dPtr, char *d){
    
    const char* s = str.c_str();
    
    for(int i = 0; i < str.length(); ++i){
        d[dPtr] = s[i];
        dPtr++;
    }
    d[dPtr] = '\0';
    dPtr++;
}


bool Student::deserialize (char* addr, int &dPtr){
    try{
        ID = 0;
        
        // Load ID from data
        ID |= ((int(0 | addr[dPtr++]) & 0xFF) << 24);
        ID |= ((int(0 | addr[dPtr++]) & 0xFF) << 16);
        ID |= ((int(0 | addr[dPtr++]) & 0xFF) << 8);
        ID |= ((int(0 | addr[dPtr++]) & 0xFF) << 0);

        // Load Advisor
        advisor |= ((int(0 | addr[dPtr++]) & 0xFF) << 24);
        advisor |= ((int(0 | addr[dPtr++]) & 0xFF) << 16);
        advisor |= ((int(0 | addr[dPtr++]) & 0xFF) << 8);
        advisor |= ((int(0 | addr[dPtr++]) & 0xFF) << 0);
        
        // Load GPA
        //Load GPA
        GPA = 0;
        char tGPA[8];
        for (int p = 0; p < 8; ++p, ++dPtr){
            tGPA[p] = addr[dPtr];
        }
        
        GPA = *(double*)tGPA;
        
        // Load name
        name = getStr(dPtr, addr);
        // Load level
        level = getStr(dPtr, addr);
        // Load major
        major = getStr(dPtr, addr);

    }
    catch(std::exception e){
        return false;
    }
    return true;
}
string Student::getStr(int &dPtr, char *d){
    string temp = "";
    
    while(d[dPtr] != 0){
        temp += d[dPtr++];
    }
    dPtr++; // increments over null character
    
    return temp;
}

std::string Student::toString(){
    std::stringstream i, g, a;
    i << ID;
    g << GPA;
    a << advisor;
    std::string temp = "ID: " + i.str() + "\nName: " + name + "\nAdvisor: " + a.str() + "\nMajor: " + major + "\nLevel: " + level + "\nGPA: " + g.str();
    return temp;
}

