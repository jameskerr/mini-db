//
//  database.h
//  Reed Halberg
//  James Kerr
//
//

#ifndef ____database__
#define ____database__

#include <iostream>
#include "BST.h"
#include "Student.h"
#include "Faculty.h"

using std::cout;
using std::endl;

class DatabaseUI;

class Database{
public:
    Database();
    virtual ~Database();
    
    friend class DatabaseUI;

    // Database operations
    void printAllStu();
    bool printAllFac();
    bool printStu(int id);
    bool printStuForTable(TreeNode<Student>* s);
    bool printFacForTable(TreeNode<Faculty>* f);
    bool printFac(int id);
    bool printAdvisor(int id);
    bool printAdvisees(int id);
    bool addStu(Student t);
    bool deleteStu(Student t);
    bool addFac(Faculty t);
    bool deleteFac(Faculty t);
    bool changeAdvisor(int sId, int fId);
    bool removeAdvisee(int fId, int sId);
    inline int autoStuID() { return nextStuID++; }
    inline int autoFacID() { return nextFacID++; }

    // NEED TO SAVE THE CURRENT IDs WHEN WE SERIALIZE
    
    /*
     Print all students
     Print all faculty
     Print student (student id)
     Print faculty (faculty id)
     Print faculty adviser (student id)
     Print all advisees (faculty id)
     Add student (student data)
     Delete student (student id)
     Add faculty (faculty data)
     Delete faculty (faculty id)
     Change student adviser(student id, faculty id)
     Remove advisee from faculty(faculty id, student id)
     Rollback
     Exit
     */
    
    
private:
    // Private Attributes
    BST<Student> sTree;
    BST<Faculty> fTree;
    int nextStuID;
    int nextFacID;
    
    int buffPtr;
    //Methods
    int getNumStu();
    int getNumFac();
    
    // File IO
    void initializeFiles();
    void saveFiles();
    bool checkFiles(std::string fileName);
    const std::string stuFile;
    const std::string facFile;
    bool save();
    void pPrintAllStu(TreeNode<Student>* s);
    void pPrintAllFac(TreeNode<Faculty>* f);
};

#endif
