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
    bool printAllStu();
    bool printAllFac();
    bool printStu(int id);


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
    void save();
    
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
    void pPrintAllStu(TreeNode<Student>* s);
    void pPrintAllFac(TreeNode<Faculty>* f);
    bool printStuForTable(TreeNode<Student>* s);
    bool printFacForTable(TreeNode<Faculty>* f);
    void pPrintAdvisees(TreeNode<int>* n);
    void setAdvisees(TreeNode<int>* n, int x);
    
    // File IO
    void initializeFiles();
    void saveFiles();
    bool checkFiles(std::string fileName);
    const std::string stuFile;
    const std::string facFile;
    int deserializeInt(int &dPtr, char *d);
    void serializeInt(int x, std::fstream &file);
    void stuSerialize(TreeNode<Student>* s, std::fstream &file);
    void facSerialize(TreeNode<Faculty>* f, std::fstream &file);
};

#endif
