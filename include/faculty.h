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
    

    //Serialization/Deserialization operators
    bool serialize (char* addr, int &dPtr);
    bool deserialize (char* addr, int &dPtr);
    
    //Methods
    std::string toString();
    bool addAvisee();
    
    // Getters/Setters
    int getID() {return ID;};
    string getName() {return name;};
    string getLevel() {return level;};
    string getDepartment() {return department;};
    BST<int>* getAdvisees() {return &advisees;};
    int getNumAdvisees() {return numAdvisees;};
    
private:
    int ID;
    string name;
    string level;
    string department;
    BST<int> advisees;
    int numAdvisees;
    
    // Serialization helper functions
    void storeStr(string str, int &dPtr, char *d);
    string getStr(int &dPtr, char *d);
    void serializeBST(TreeNode<int>*, int &dPtr, char*addr);
    void serializeInt(int x, int &dPtr, char *d);
};

#endif