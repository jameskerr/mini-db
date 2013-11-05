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
    cout << f->getDataPtr()->getID()
         << std::setw(width) << f->getDataPtr()->getName()
         << std::setw(width) << f->getDataPtr()->getLevel()
         << std::setw(width) << f->getDataPtr()->getDepartment()
         << std::setw(width) << f->getDataPtr()->getNumAdvisees() << endl;
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
    if (node->getDataPtr()->getNumAdvisees() == 0){
        cout << "This faculty member has no advisees." << endl << endl;
        return false;
    }
    int width = 13;
    cout << "ID"
        << std::setw(width) << "Name"
        << std::setw(width) << "GPA"
        << std::setw(width) << "Level"
        << std::setw(width) << "Major"
        << std::setw(width) << "Advisor" << endl;
    pPrintAdvisees(node->getData().getAdvisees()->getRoot());
    return true;
}

void Database::pPrintAdvisees(TreeNode<int>* node){
    if (node == 0) return;
    pPrintAdvisees(node->getLeft());
    printStuForTable(sTree.find(Student(node->getData())));
    pPrintAdvisees(node->getRight());
}

bool Database::addStu(Student t){
    sTree.insert(t);
    return true;
}

bool Database::deleteStu(Student t){
    return sTree.remove(t);
}

bool Database::addFac(Faculty t){
    fTree.insert(t);
    return true;
}
    
bool Database::deleteFac(Faculty t){
    return fTree.remove(t);
}

bool Database::changeAdvisor(int sId, int fId){
    TreeNode<Student>* sNode = sTree.find(Student(sId));
    TreeNode<Faculty>* fNode = fTree.find(Faculty(fId));
    // Get student's current advisor
    TreeNode<Faculty>* oldFac = fTree.find(Faculty(sNode->getData().getAdvisor()));
    if (fNode != 0){
        if(sNode != 0){
            // Add new advisor to student
            sNode->getDataPtr()->setAdvisor(fId);
            
            // Add student to advisee list
            fNode->getDataPtr()->getAdvisees()->insert(sId);
            
            // Delete student from old advisor
            if (oldFac != 0) {
                oldFac->getDataPtr()->getAdvisees()->remove(sId);
            }
            return true;
        }
    }
    return false;
    
}
bool Database::removeAdvisee(int fId, int sId){
    TreeNode<Faculty>* fNode = fTree.find(Faculty(fId));
    TreeNode<Student>* sNode = sTree.find(Student(sId));
    if(fNode != 0){
        fNode->getDataPtr()->getAdvisees()->remove(sId);
        if (sNode != 0) {
            // Set student advisor to empty
            sNode->getDataPtr()->setAdvisor(0);
        }
        
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
         std::cout<<"Student file not found. File will be created."<<endl;
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
             numEntries = deserializeInt(buffPtr, sData);
             nextStuID = deserializeInt(buffPtr, sData);
         }
         
         for(int i = 0; i < numEntries; ++i){
             Student t;
             t.deserialize(sData, buffPtr);
             
             sTree.insert(t);
         }
     }
     sFile.close();
    
     // See if faculty file exists in current directory, if not, make it
     if (!checkFiles(facFile)) {
         std::cout<<"Faculty file not found. Files will be created."<<endl;
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
         if (size >= 8){
             numEntries = deserializeInt(buffPtr, fData);
             nextFacID = deserializeInt(buffPtr, fData);
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
    {
        std::fstream sFile;
        sFile.open(stuFile.c_str(), std::ios::in|std::ios::out|std::ios::binary|std::ios::trunc);
        int numS = getNumStu();
        
        // Load student table into buffer
        // This function will save the number of students to the buffer first
        serializeInt(numS, sFile);
        serializeInt(nextStuID, sFile);
        stuSerialize(sTree.getRoot(), sFile);
        sFile.close();
    }
    // SAVE FACULTY TABLE
    {
        std::fstream fFile;
        fFile.open(facFile.c_str(), std::ios::in|std::ios::out|std::ios::binary|std::ios::trunc);
        int numF = getNumFac();
        
        // Load faculty table into buffer
        serializeInt(numF, fFile);
        serializeInt(nextFacID, fFile);
        facSerialize(fTree.getRoot(), fFile);
        fFile.close();
    }
    
    return false; // false until functional
}

int Database::deserializeInt(int &dPtr, char *d){
    int x = 0;
    x |= ((int(0 | d[dPtr++]) & 0xFF) << 24);
    x |= ((int(0 | d[dPtr++]) & 0xFF) << 16);
    x |= ((int(0 | d[dPtr++]) & 0xFF) << 8);
    x |= ((int(0 | d[dPtr++]) & 0xFF) << 0);
    return x;
}

void Database::serializeInt(int x, std::fstream &file){
    
    char temp[4];
    temp[0] = (x >> 24) & 0xFF;
    temp[1] = (x >> 16) & 0xFF;
    temp[2] = (x >> 8) & 0xFF;
    temp[3] = x & 0xFF;
    
    if(file.is_open()){
        file.write(temp, 4);
    }
}

void Database::stuSerialize(TreeNode<Student>* s, std::fstream &file){
    if (s == 0) return;
    
    stuSerialize(s->getLeft(), file);
    s->getData().serialize(file);
    stuSerialize(s->getRight(), file);
}
void Database::facSerialize(TreeNode<Faculty>* f, std::fstream &file){
    if (f == 0) return;
    
    facSerialize(f->getLeft(), file);
    f->getDataPtr()->serialize(file);
    facSerialize(f->getRight(), file);
}


int Database::getNumFac(){
    return fTree.length();
}

int Database::getNumStu(){
    return sTree.length();
}