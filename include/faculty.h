//
//  faculty.h
//  Reed Halberg
//  James Kerr
//

#ifndef FACULTY_H
#define FACULTY_H

#include <iostream>
#include <cstring>
#include "Student.h"
#include "BST.h"

using std::cout;
using std::string;

class Faculty{
public:
    Faculty();
    Faculty(int Id) :ID(Id) {}
    Faculty(int Id, string n, string l, string d);
    virtual ~Faculty();
    
    // Comparison operators
    bool operator > (const Faculty& other);
    bool operator < (const Faculty& other);
    bool operator == (const Faculty& other);
    bool operator != (const Faculty& other);
    
    // TEMPORARILY COMMENTED OUT UNTIL WE MEET AGAIN
    //Serialization/Deserialization operators
    //bool serialize (char* addr, int &dPtr);
    //bool deserialize (char* addr, int &dPtr);
    
    //Methods
    std::string toString();
    
    // Getters/Setters
    int getID() {return ID;};
    string getName() {return name;};
    string getLevel() {return level;};
    string getDepartment() {return department;};
    BST<Student>* getAdvisees() {return &advisees; };
    
private:
    int ID;
    string name;
    string level;
    string department;
    BST<Student> advisees;
    
    // Serialization helper functions
    //void storeStr(string str, int &dPtr, char *d);
    //string getStr(int &dPtr, char *d);
    //void serializeInt(int x, int &dPtr, char *d);
    //void serializeBST(TreeNode<int>*, int dPtr, addr);

};

#endif