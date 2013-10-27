//
//  faculty.cpp
//  Reed Halberg
//  James Kerr
//

#include "faculty.h"
#include "sstream"

Faculty::Faculty(){
    this->ID = 0;
    this->name = "";
    this->level = "";
    this->department = "";
}
Faculty::Faculty(int Id, int adv, double g, string n, string l, string m){
    this->ID = Id;
    this->name = n;
    this->level = l;
    this->department;
}
Faculty::~Faculty(){
    
}

// Comparison operators
bool Faculty::operator > (int other){
    return ID > other;
}
bool Faculty::operator < (int other){
    return ID < other;
}
bool Faculty::operator == (int other){
    return ID == other;
}

//Serialization/Deserialization operators
bool Faculty::serialize (char* addr, int &dPtr){
    try{
        // copy ID into char array
        serializeInt(ID, dPtr, addr);
        
        // Load each string field into char array
        storeStr(name, dPtr, addr);
        storeStr(level, dPtr, addr);
        storeStr(department, dPtr, addr);
        
        // Serialize BST
        serializeBST(TreeNode<int>* advisees, dPtr, addr);
        
    }
    catch(std::exception e){
        return false;
    }
    return true;
}
void Faculty::storeStr(string str, int &dPtr, char *d){
    
    const char* s = str.c_str();
    
    for(int i = 0; i < str.length(); ++i){
        d[dPtr] = s[i];
        dPtr++;
    }
    d[dPtr] = '\0';
    dPtr++;
}

void Faculty::serializeInt(int x, int &dPtr, char *d){
    d[dPtr++] = (x >> 24) & 0xFF;
    d[dPtr++] = (x >> 16) & 0xFF;
    d[dPtr++] = (x >> 8) & 0xFF;
    d[dPtr++] = x & 0xFF;
}

void Faculty::serializeBST(TreeNode<int>* n, dPtr, addr){
    int temp = n->getData();
    serializeInt(temp, dPtr, addr);
}



bool Faculty::deserialize (char* addr, int &dPtr){
    try{
        ID = 0;
        
        // Load ID from data
        ID |= ((int(0 | addr[dPtr++]) & 0xFF) << 24);
        ID |= ((int(0 | addr[dPtr++]) & 0xFF) << 16);
        ID |= ((int(0 | addr[dPtr++]) & 0xFF) << 8);
        ID |= ((int(0 | addr[dPtr++]) & 0xFF) << 0);
        
        // Load name
        name = getStr(dPtr, addr);
        // Load level
        level = getStr(dPtr, addr);
        // Load department
        department = getStr(dPtr, addr);

    }
    catch(std::exception e){
        return false;
    }
    return true;
}
string Faculty::getStr(int &dPtr, char *d){
    string temp = "";
    
    while(d[dPtr] != 0){
        temp += d[dPtr++];
    }
    dPtr++; // increments over null character
    
    return temp;
}

std::string Faculty::toString(){
    sstream i;
    i << ID;
    std::string temp = "ID: " + i.str() + "\nName: " + name + "\nDepartment: " + department + "\nLevel: " + level;
    return temp;
}


