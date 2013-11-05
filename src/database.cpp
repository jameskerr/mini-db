//
//  database.cpp
//  Reed Halberg
//  James Kerr
//

#include "Database.h"
#include "dirent.h"
#include <fstream>
#include <iostream>
#include <iomanip> // for setw

using std::setw;

Database::Database()
    :nextStuID(100),
    nextFacID(100),
    stuFile("studentTable.kh"),
    facFile("facultyTable.kh")
{
    initializeFiles();
}

Database::~Database(){
    
}


bool Database::printAllStu(){
    if (getNumStu() == 0) return false;
     int width = 13;
     cout << "ALL STUDENTS:" << endl;
     cout << "ID" 
         << std::setw(width) << "Name"
         << std::setw(width) << "GPA"
         << std::setw(width) << "Level"
         << std::setw(width) << "Major"
         << std::setw(width) << "Advisor" << endl;
     TreeNode<Student>* cursor = sTree.getRoot();
     pPrintAllStu(cursor);
    return true;
}

void Database::pPrintAllStu(TreeNode<Student>* s) {
    if (s == 0) return;
    pPrintAllStu(s->getLeft());
    printStuForTable(s);
    pPrintAllStu(s->getRight());
}

bool Database::printAllFac(){
    if (getNumFac() == 0) return false;
    int width = 13;
    cout << "ALL FACULTY:" << endl;
    cout << "ID"
        << std::setw(width) << "Name"
        << std::setw(width) << "Level"
        << std::setw(width) << "Department"
        << std::setw(width) << "Advisees" << endl;
    TreeNode<Faculty>* cursor = fTree.getRoot();
    pPrintAllFac(cursor);
    return true;
}
void Database::pPrintAllFac(TreeNode<Faculty>* f) {
    if (f == 0) return;
    pPrintAllFac(f->getLeft());
    printFacForTable(f);
    pPrintAllFac(f->getRight());
}
bool Database::printStu(int id){
    TreeNode<Student>* node = sTree.find(Student(id));
    if (node == 0) return false;
    cout << node->getData().toString() << endl << endl;
    return true;
}
bool Database::printStuForTable(TreeNode<Student>* s) {
    if (s == 0) return false;
    int width = 13;
    cout << s->getData().getID() 
         << std::setw(width) << s->getData().getName()
         << std::setw(width) << s->getData().getGPA()
         << std::setw(width) << s->getData().getLevel()
         << std::setw(width) << s->getData().getMajor()
         << std::setw(width) << s->getData().getAdvisor() << endl;
    return true;
}
bool Database::printFac(int id){
    TreeNode<Faculty>* node = fTree.find(Faculty(id));
    if (node == 0) return false;
    cout << node->getData().toString() << endl << endl;
    return true;
}
bool Database::printFacForTable(TreeNode<Faculty>* f) {
    if (f == 0) return false;
    int width = 13;
    cout << f->getData().getID() 
         << std::setw(width) << f->getData().getName()
         << std::setw(width) << f->getData().getLevel()
         << std::setw(width) << f->getData().getDepartment()
         << std::setw(width) << f->getData().getNumAdvisees() << endl;
    return true;
}
bool Database::printAdvisor(int id){
    TreeNode<Student>* node = sTree.find(Student(id));
    if (node == 0) return false;
    cout << fTree.find(node->getData().getAdvisor())->getData().toString() << endl << endl;
    return true;
}
bool Database::printAdvisees(int id){
    TreeNode<Faculty>* node = fTree.find(Faculty(id));
    if (node == 0) return false;
    pPrintAdvisees(node->getData().getAdvisees()->getRoot());
    return true;
}

void pPrintAdvisees(TreeNode<int>* node){
    if (node == 0) return;
    pPrintAdvisees(node->getLeft());
    cout << sTree.find(node->getData()).getData().toString() << endl << endl;
    pPrintAdvisees(node->getRight());
}

bool Database::addStu(Student t){
    
    if (sTree.find(t))
        return false;
    else{
        sTree.insert(t);
        ++nextStuID;
    }
    return true;
}
bool Database::deleteStu(Student t){
    return sTree.remove(t);
}
bool Database::addFac(Faculty t){
    if (fTree.find(t))
        return false;
    else {
        fTree.insert(t);
        ++nextFacID;
    }
    return true;
}
bool Database::deleteFac(Faculty t){
    return fTree.remove(t);
}
bool Database::changeAdvisor(int sId, int fId){
    TreeNode<Student>* sNode = sTree.find(Student(sId));
    TreeNode<Faculty>* fNode = fTree.find(Faculty(fId));
    if (fNode != 0){
        if(sNode != 0){
            sNode->getData().setAvisor(fId);
            return true;
        }
    }
    return false;
    
}
bool Database::removeAdvisee(int fId, int sId){
    TreeNode<Faculty>* fNode = fTree.find(Faculty(fId));
    if(fNode != 0){
        fNode->getData().getAdvisees()->remove(sId);
        return true;
    }
    return false;
}


 void Database::initializeFiles(){
    
     std::cout << "Initializing database..." << endl;
     
     // Declare file names for student/faculty files
     std::fstream sFile;
     std::fstream fFile;
     
     // See if student file exists in current directory, if not, make it
     if(!checkFiles(stuFile)){
         sFile.open(stuFile.c_str(), std::ios::in|std::ios::out|std::ios::binary|std::ios::trunc);
         std::cout<<"Student file not found. Creating file."<<endl;
     }
     else{

         
         // If files already exist
         std::cout<<"Student file found. Reading Contents into database."<<endl;
         
        sFile.open(stuFile.c_str(), std::ios::in|std::ios::out|std::ios::binary);

         // Read studentFile into buffer
         sFile.seekg(0, std::ios::end);
         size_t size = sFile.tellg();
         sFile.seekg(0, std::ios::beg);
         char* sData = new char[size+1];
         sFile.read(sData, size);
         
         
         buffPtr = 0;
         int numEntries = 0;
         if (size >= 4){
             numEntries |= ((int(0 | sData[buffPtr++]) & 0xFF) << 24);
             numEntries |= ((int(0 | sData[buffPtr++]) & 0xFF) << 16);
             numEntries |= ((int(0 | sData[buffPtr++]) & 0xFF) << 8);
             numEntries |= ((int(0 | sData[buffPtr++]) & 0xFF) << 0);
         }
         
         for(int i = 0; i <= numEntries; ++i){
             Student t;
             t.deserialize(sData, buffPtr);
             
             sTree.insert(t);
         }
     }
     sFile.close();
    
     // See if faculty file exists in current directory, if not, make it
     if (!checkFiles(facFile)) {
         fFile.open(facFile.c_str(), std::ios::in|std::ios::out|std::ios::binary|std::ios::trunc);
         std::cout<<"Faculty file not found. Creating file."<<endl;
     }
     else{
         std::cout<<"Faculty file found. Reading contents into database."<<endl;
         fFile.open(facFile.c_str(), std::ios::in|std::ios::out|std::ios::binary);

         // Read facultyFile into buffer
         fFile.seekg(0, std::ios::end);
         size_t size = fFile.tellg();
         fFile.seekg(0, std::ios::beg);
         char fData[size+1];
         fFile.read(fData, size);
        
         buffPtr = 0;
         int numEntries = 0;
         if (size >= 4){
             numEntries |= ((int(0 | fData[buffPtr++]) & 0xFF) << 24);
             numEntries |= ((int(0 | fData[buffPtr++]) & 0xFF) << 16);
             numEntries |= ((int(0 | fData[buffPtr++]) & 0xFF) << 8);
             numEntries |= ((int(0 | fData[buffPtr++]) & 0xFF) << 0);
         }
         for (int i = 0; i < numEntries; ++i) {
             Faculty t;
             t.deserialize(fData, buffPtr);
            
             fTree.insert(t);
         }
     }
     fFile.close();
     
     std::cout << "Database initialized." << endl << endl;
 }

//search directory for student/faculty files
bool Database::checkFiles(std::string fileName){
    if(std::fstream(fileName.c_str()).good()){
        return true;
    }
    return false;
 }

// This function saves the state of the database to the files
bool Database::save(){
    
    // SAVE STUDENT FILE
    std::fstream sFile;
    sFile.open(stuFile.c_str(), std::ios::in|std::ios::out|std::ios::binary|std::ios::app);
    int numS = getNumStu();
    int sSize = sizeof(Student) * numS;
    char sBuffer[sSize];
    int buffPtr = 0;
    // Load student table into buffer
    // This function will save the number of students to the buffer first
    Faculty::serializeInt(numS, buffPtr, sBuffer);
    
    //sTree.visit(sTree.getRoot(), Student.serialize(char* sBuffer, int &buffPtr))
    //sFile.write(sBuffer, buffPtr);
    sFile.close();
    
    // SAVE FACULTY TABLE
    std::fstream fFile;
    fFile.open(stuFile.c_str(), std::ios::in|std::ios::out|std::ios::binary|std::ios::app);
    int numF = getNumFac();
    int fSize = sizeof(fTree);
    char fBuffer[fSize];
    buffPtr = 0;
    // Load faculty table into buffer
    // First save number of faculty to file
    Faculty::serializeInt(numF, buffPtr, fBuffer);
    
    //fTree.visit(fTree.getRoot(), Faculty.serialize(char* fBuffer, int &buffPtr))
    //fFile.write(fBuffer, buffPtr);
    fFile.close();
    
    return false; // false until functional
}

int Database::getNumFac(){
    return fTree.length();
}

int Database::getNumStu(){
    return sTree.length();
}