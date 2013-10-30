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

class Database{
public:
    Database();
    virtual ~Database();
    
    // Database operations
    bool printAllStu();
    bool printAllFac();
    bool printStu(int id);
    bool printFac(int id);
    bool printAdvisor(int id);
    bool printAdvisees(int id);
    bool addStu(Student t);
    bool deleteStu(int id);
    bool addFac(Faculty t);
    bool deleteFac(int id);
    bool changeAdvisor(int sId, int fId);
    bool removeAdvisee(int fId, int sId);
    
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
    
    //Methods
    
    // File IO
    // void initializeFiles();
    // void saveFiles();
    // bool checkFiles(std::string fileName);
    // const std::string stuFile = "studentTable.kh";
    // const std::string facFile = "facultyTable.kh";
    
    //Operations helper functions
        //Faculty
    void pFac(Faculty f);
    void printFacForTable(Faculty f);
    bool pAdvisees(Faculty f);
        //Student
    void pStu(Student s);
    void printStuForTable(Student s);
    bool pAdvisor(Student s);
};

#endif
