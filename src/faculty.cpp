//
//  faculty.cpp
//  Reed Halberg
//  James Kerr
//

#include "Faculty.h"
#include "sstream"
#include <fstream>

Faculty::Faculty(){
    this->ID = 0;
    this->name = "";
    this->level = "";
    this->department = "";
}
Faculty::Faculty(int Id, string n, string l, string d){
    this->ID = Id;
    this->name = n;
    this->level = l;
    this->department = d;
}
Faculty::~Faculty(){
    
}

// Comparison operators
bool Faculty::operator > (const Faculty& other){
    return ID > other.ID;
}
bool Faculty::operator < (const Faculty& other){
    return ID < other.ID;
}
bool Faculty::operator == (const Faculty& other){
    return ID == other.ID;
}
bool Faculty::operator != (const Faculty& other) {
    return ID != other.ID;
}

//Serialization/Deserialization operators
bool Faculty::serialize (std::fstream &file){
     try{
         // copy ID into char array
         serializeInt(ID, file);
        
         // Load each string field into char array
         storeStr(name, file);
         storeStr(level, file);
         storeStr(department, file);
        
         // Serialize numAdvisees
         serializeInt(getNumAdvisees(), file);
         
         // Serialize BST
         serializeBST(advisees.getRoot(), file);
        
     }
     catch(std::exception e){
         return false;
     }
     return true;
 }
 void Faculty::storeStr(string str, std::fstream &file){
    
     const char* s = str.c_str();
     
     if (file.is_open()) {
         file.write(s, str.length() + 1);
     }
 }

void Faculty::serializeInt(int x, std::fstream &file){
    char temp[4];
    temp[0] = (x >> 24) & 0xFF;
    temp[1] = (x >> 16) & 0xFF;
    temp[2] = (x >> 8) & 0xFF;
    temp[3] = x & 0xFF;
    
    if(file.is_open()){
        file.write(temp, 4);
    }
 }

 void Faculty::serializeBST(TreeNode<int>* n, std::fstream &file){
     if (n == 0) return;
     serializeBST(n->getLeft(), file);
     serializeInt(n->getData(), file);
     serializeBST(n->getRight(), file);
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
         
         // number of advisees
         int numAdvisees = 0;
         numAdvisees |= ((int(0 | addr[dPtr++]) & 0xFF) << 24);
         numAdvisees |= ((int(0 | addr[dPtr++]) & 0xFF) << 16);
         numAdvisees |= ((int(0 | addr[dPtr++]) & 0xFF) << 8);
         numAdvisees |= ((int(0 | addr[dPtr++]) & 0xFF) << 0);

         for (int i = 0; i < numAdvisees; ++i) {
             int temp = 0;
             temp |= ((int(0 | addr[dPtr++]) & 0xFF) << 24);
             temp |= ((int(0 | addr[dPtr++]) & 0xFF) << 16);
             temp |= ((int(0 | addr[dPtr++]) & 0xFF) << 8);
             temp |= ((int(0 | addr[dPtr++]) & 0xFF) << 0);
             
             advisees.insert(temp);
         }
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
    std::stringstream i;
    i << ID;
    std::string temp = "ID: " + i.str() + "\nName: " + name + "\nDepartment: " + department + "\nLevel: " + level;
    return temp;
}