//
//  database.cpp
//  Reed Halberg
//  James Kerr
//

#include "Database.h"
#include "dirent.h"

Database::Database()
    :nextStuID(100),
    nextFacID(100)
{
    // initializeFiles();
}

Database::~Database(){
    
}


bool Database::printAllStu(){
    
}
bool Database::printAllFac(){
    
}
bool Database::printStu(int id){
    TreeNode<Student>* node = sTree.find(Student(id));
    if (node == 0) return false;
    cout << node->getData().toString() << endl;
    return true;

}
bool Database::printFac(int id){
    TreeNode<Faculty>* node = fTree.find(Faculty(id));
    if (node == 0) return false;
    cout << node->getData().toString() << endl;
    return true;
}
bool Database::printAdvisor(int id){
    TreeNode<Student>* node = sTree.find(Student(id));
    if (node == 0) return false;
    cout << node->getData().getAdvisor() << endl;
    return true;
}
bool Database::printAdvisees(int id){
    TreeNode<Faculty>* node = fTree.find(Faculty(id));
    if (node == 0) return false;
    cout << node->getData().getAdvisees() << endl;
    return true;
}
bool Database::addStu(Student t){
    
}
bool Database::deleteStu(int id){
    
}
bool Database::addFac(Faculty t){
    
}
bool Database::deleteFac(int id){
    
}
bool Database::changeAdvisor(int sId, int fId){
    
}
bool Database::removeAdvisee(int fId, int sId){
    
}


// void Database::initializeFiles(){
    
//     // Declare file names for student/faculty files
//     fstream sFile;
//     fstream fFile;
    
//     // See if student file exists in current directory, if not, make it
//     if(!checkFiles(stuFile)){
//         sFile.open(stuFile, ios::in|ios::out|ios::binary|ios::trunc);
//     }
//     else{
//             // If files already exist
            
//             // Read studentFile into buffer
//             size_t size = sFile.tellg();
//             sFile.seekg(0, ios::beg);
//             char sData[size+1];
//             sFile.read(sData, size);
            
//             // checks if ID is null
//                 // if it is, there are no more students
//             buffPtr = 0;
//             int fileChecker;
//             memcpy(fileChecker, sData[0], 4);
//             while(){
//                 student t;
//                 t.deserialize(sData, buffPtr);
                
//                 sTree.insert(t);
                
//                 memcpy(fileChecker, sData[buffPtr], 4);
//             }
//         }
//     sFile.close();
    
//     // See if faculty file exists in current directory, if not, make it
//         if (!checkFiles(facFile)) {
//             fFile.open(facFile, ios::in|ios::out|ios::binary|ios::trunc);
//         }
//         else{
//             // Read facultyFile into buffer
//             size_t size = fFile.tellg();
//             fFile.seekg(0, ios::beg);
//             char fData[size+1];
//             fFile.read(sData, size);
            
//             // checks if ID is null
//             // if it is, there are no more students
//             buffPtr = 0;
//             memcpy(fileChecker, fData[0], 4);
//             while(){
//                 faculty t;
//                 t.deserialize(fData, buffPtr);
                
//                 fTree.insert(t);
                
//                 memcpy(fileChecker, fData[buffPtr], 4);
//             }
//         }
//     fFile.close();
// }

//search directory for student/faculty files
// bool Database::checkFiles(std::string fileName){
    
// }


// Operation helper functions FACULTY
// void Database::pFac(Faculty f){
//     cout<<f.toString()<<std::endl;
// }

void Database::printFacForTable(Faculty f){
    
}

// bool Database::pAdvisees(Faculty f){
//     std::cout<<f.toString()<<std::endl<<std::endl
//     if(advisees.length() != 0){
//         std::cout<<"Advisee List:"<< std::endl;
//         s.getAdvisees().DFSvisit(s.getAdvisees().getRoot(), printForTable());
//         return true;
//     }
//     else
//         return false;
// }


// Operation helper functions STUDENT


// void Database::pStu(Student s){
//     cout<< s.toString()<<endl;
// }

void Database::printStuForTable(Student s){
    
}

// bool Database::pAdvisor(Student s){
//     if(!printFac(s.getAdvisor)){
//         return false;
//     }
//     else{
//         return true;
//     }
// }
