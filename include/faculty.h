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
    Faculty(const Faculty &t);

    Faculty(int Id, string n, string l, string d);
    virtual ~Faculty();
    
    // Comparison operators
    bool operator > (const Faculty& other);
    bool operator < (const Faculty& other);
    bool operator == (const Faculty& other);
    bool operator != (const Faculty& other);

    

    //Serialization/Deserialization operators
    bool serialize (std::fstream &file);
    bool deserialize (char* addr, int &dPtr);
    
    //Methods
    std::string toString();
    bool addAdvisee(int id);
    
    // Getters/Setters
    int getID() {return ID;};
    string getName() {return name;};
    string getLevel() {return level;};
    string getDepartment() {return department;};
    BST<int>* getAdvisees() {return &advisees;};
    int getNumAdvisees() {return advisees.length();};
    
private:
    int ID;
    string name;
    string level;
    string department;
    BST<int> advisees;
    
    // Serialization helper functions
    void storeStr(string str, std::fstream &file);
    string getStr(int &dPtr, char *d);
    void serializeBST(TreeNode<int>*, std::fstream &file);
    void serializeInt(int x, std::fstream &file);
};

#endif