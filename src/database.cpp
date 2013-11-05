//
//  database.cpp
//  Reed Halberg
//  James Kerr
/*
 
This class contains the two trees for students and faculty and manages the correspnding operations.
It will read the databse in from files upon startup and out to files upon closing.
It allows entries to be added, removed, reorganized, and displayed to the user.

*/

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
    // Load data from files if they exist
    initializeFiles();
}

Database::~Database(){
    
}

// Displays all students in the database in a table
bool Database::printAllStu(){
    if (getNumStu() == 0) return false;
     int width = 18;
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

// Recursive helper function that allows simple printing of entire student BST
void Database::pPrintAllStu(TreeNode<Student>* s) {
    if (s == 0) return;
    pPrintAllStu(s->getRight());
    printStuForTable(s);
    pPrintAllStu(s->getLeft());
}

// Helper function for printing all students. Formats student information to fit into table
bool Database::printStuForTable(TreeNode<Student>* s) {
    if (s == 0) return false;
    int width = 18;
    cout << s->getData().getID()
    << std::setw(width) << s->getData().getName()
    << std::setw(width) << s->getData().getGPA()
    << std::setw(width) << s->getData().getLevel()
    << std::setw(width) << s->getData().getMajor()
    << std::setw(width) << s->getData().getAdvisor() << endl;
    return true;
}

// Dispays all faculty members in a table
bool Database::printAllFac(){
    
    if (getNumFac() == 0) return false;
    int width = 22;
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

// Recursive helper function that allows simple printing of entire faculty BST
void Database::pPrintAllFac(TreeNode<Faculty>* f) {
    if (f == 0) return;
    pPrintAllFac(f->getRight());
    printFacForTable(f);
    pPrintAllFac(f->getLeft());
}

// Helper function for printing all faculty. Formats faculty information to fit into table
bool Database::printFacForTable(TreeNode<Faculty>* f) {
    if (f == 0) return false;
    int width = 22;
    cout << f->getDataPtr()->getID()
    << std::setw(width) << f->getDataPtr()->getName()
    << std::setw(width) << f->getDataPtr()->getLevel()
    << std::setw(width) << f->getDataPtr()->getDepartment()
    << std::setw(width) << f->getDataPtr()->getNumAdvisees() << endl;
    return true;
}

// Displays a single student to the user with all relevant information
bool Database::printStu(int id){
    TreeNode<Student>* node = sTree.find(Student(id));
    if (node == 0) return false;
    cout << node->getData().toString() << endl << endl;
    return true;
}

// Displays a single faculty to user with all relevant information
bool Database::printFac(int id){
    TreeNode<Faculty>* node = fTree.find(Faculty(id));
    if (node == 0) return false;
    cout << node->getData().toString() << endl << endl;
    return true;
}

// Takes student id and prints out the faculty member who is the advisor to the student
bool Database::printAdvisor(int id){
    TreeNode<Student>* node = sTree.find(Student(id));
    if (node == 0) return false;
    if (node->getData().getAdvisor() == 0){
        cout << "This student has no advisor." << endl << endl;
    }
    cout << fTree.find(node->getData().getAdvisor())->getData().toString() << endl << endl;
    return true;
}

// Takes faculty id and prints out a table of all students who are advisees to the faculty
bool Database::printAdvisees(int id){
    TreeNode<Faculty>* node = fTree.find(Faculty(id));
    if (node == 0) return false;
    if (node->getDataPtr()->getNumAdvisees() == 0){
        cout << "This faculty member has no advisees." << endl << endl;
        return true;
    }
    int width = 18;
    cout << "ID"
        << std::setw(width) << "Name"
        << std::setw(width) << "GPA"
        << std::setw(width) << "Level"
        << std::setw(width) << "Major"
        << std::setw(width) << "Advisor" << endl;
    pPrintAdvisees(node->getData().getAdvisees()->getRoot());
    return true;
    
}

// Recursive helper function that allows easy printing of faculty advisee BST
void Database::pPrintAdvisees(TreeNode<int>* node){
    if (node == 0) return;
    pPrintAdvisees(node->getRight());
    printStuForTable(sTree.find(Student(node->getData())));
    pPrintAdvisees(node->getLeft());
}

// Adds a student to the database.
// If student has faculty advisor, the faculty member's advisee list is updated.
bool Database::addStu(Student t){
    sTree.insert(t);
    
    if (t.getAdvisor() != 0){
        fTree.find(Faculty(t.getAdvisor()))->getDataPtr()->addAdvisee(t.getID());
    }
    
    return true;
}

// Removes student from database.
// Removes student entry from advisor's advisee list
bool Database::deleteStu(Student t){
    TreeNode<Student>* s = sTree.find(t);
    if (s == 0) return false;
    fTree.find(Faculty(s->getDataPtr()->getAdvisor()))->getDataPtr()->getAdvisees()->remove(t.getID());
    return sTree.remove(t);
}

// Adds faculty member to database
bool Database::addFac(Faculty t){
    fTree.insert(t);
    
    if (t.getAdvisees()->length() != 0){
        setAdvisees(t.getAdvisees()->getRoot(), t.getID());
    }
    
    return true;
}

// Recursive helper function to assist setting all advisee's to give advisor number
void Database::setAdvisees(TreeNode<int>* n, int x){
    if (n == 0) return;
    setAdvisees(n->getLeft(), x);
    sTree.find(Student(n->getData()))->getDataPtr()->setAdvisor(x);
    setAdvisees(n->getRight(), x);
}

// Removes faculty member from database.
// Set's all advisees' advisor to 0, meaning student has no advisor
bool Database::deleteFac(Faculty t){
    TreeNode<Faculty>* f = fTree.find(t);
    
    if (f == 0) return false;
    
    setAdvisees(f->getDataPtr()->getAdvisees()->getRoot(), 0);
    
    return fTree.remove(t);
}

// Takes student id and faculty id.
// Changes the student's advisor to the new id
// Adds student to avisor's advisee list
// Deletes student from old advisor's advisee list
bool Database::changeAdvisor(int sId, int fId){
    TreeNode<Student>* sNode = sTree.find(Student(sId));
    TreeNode<Faculty>* fNode = fTree.find(Faculty(fId));
    // Get student's current advisor
    if (sNode != 0){
    TreeNode<Faculty>* oldFac = fTree.find(Faculty(sNode->getData().getAdvisor()));
        if(fNode != 0){
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

// Take faculty id and student id
// Removes advisee from faculty advisee list
// Set's student advisor to none
bool Database::removeAdvisee(int fId, int sId){
    TreeNode<Faculty>* fNode = fTree.find(Faculty(fId));
    TreeNode<Student>* sNode = sTree.find(Student(sId));
    if(fNode != 0){
        if (sNode != 0) {
            // Set student advisor to empty, if student is an advisee of faculty member
            if (fNode->getDataPtr()->getAdvisees()->find(sId))
                fNode->getDataPtr()->getAdvisees()->remove(sId);
                sNode->getDataPtr()->setAdvisor(0);
            return true;
        }
    }
    return false;
}

// Searches present working directory for the student and faculty database files.
// If found, the contents are loaded into the database
// If not found, user is informed that the files will be created upon exiting the program
void Database::initializeFiles(){
    
     std::cout << "Initializing database..." << endl;
     
     // Declare file names for student/faculty files
     std::fstream sFile;
     std::fstream fFile;
     
     // See if student file exists in current directory, if not, make it
     if(!checkFiles(stuFile)){
         std::cout<<"Student file not found. File will be created upon exit."<<endl;
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
             // Number of students in database
             numEntries = deserializeInt(buffPtr, sData);
             // current next student ID to used when a student is added
             nextStuID = deserializeInt(buffPtr, sData);
         }
         
         // Deserialize each student into the database
         for(int i = 0; i < numEntries; ++i){
             Student t;
             t.deserialize(sData, buffPtr);
             
             sTree.insert(t);
         }
     }
     sFile.close();
    
     // See if faculty file exists in current directory, if not, make it
     if (!checkFiles(facFile)) {
         std::cout<<"Faculty file not found. File will be created upon exit."<<endl;
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
             // Number of faculty in database
             numEntries = deserializeInt(buffPtr, fData);
             // Current next ID to be used when faculty is added
             nextFacID = deserializeInt(buffPtr, fData);
         }
         
         // Load all faculty into database
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
void Database::save(){
    
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
}

// Method to deserialize int from file. Saves into buffer
int Database::deserializeInt(int &dPtr, char *d){
    int x = 0;
    x |= ((int(0 | d[dPtr++]) & 0xFF) << 24);
    x |= ((int(0 | d[dPtr++]) & 0xFF) << 16);
    x |= ((int(0 | d[dPtr++]) & 0xFF) << 8);
    x |= ((int(0 | d[dPtr++]) & 0xFF) << 0);
    return x;
}

// Method to serialize int into file. Saves directly to file
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

// Recursive function to serialize student tree
void Database::stuSerialize(TreeNode<Student>* s, std::fstream &file){
    if (s == 0) return;
    
    stuSerialize(s->getLeft(), file);
    s->getData().serialize(file);
    stuSerialize(s->getRight(), file);
}

// Recursive function to serialize faculty tree
void Database::facSerialize(TreeNode<Faculty>* f, std::fstream &file){
    if (f == 0) return;
    
    facSerialize(f->getLeft(), file);
    f->getDataPtr()->serialize(file);
    facSerialize(f->getRight(), file);
}

// Returns the number of faculty in database
int Database::getNumFac(){
    return fTree.length();
}

// Returns the number of students in database
int Database::getNumStu(){
    return sTree.length();
}