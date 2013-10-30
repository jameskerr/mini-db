#ifndef COMMANDS_H
#define COMMANDS_H 

#include <iostream>
#include "BST.h"
#include "ICommand.h"
//#include "Student.h"
//#include "Faculty.h"

class InsertStudentCommand : public ICommand {
public:
	InsertStudentCommand(BST<int>* theDb, int theStudent): db(theDb), student(theStudent) {}
	inline void execute() { 
		db->insert(student);
	}
	inline void unexecute() { 
		db->remove(student);
	}
private:
	BST<int>* db; // replace this with the database
	int student;  // replace int fg
};

class RemoveStudentCommand : public ICommand {
public:
	RemoveStudentCommand(BST<int>* theDb, int theStudent): db(theDb), student(theStudent) {}
	inline void execute() { 
		db->remove(student);
	}
	inline void unexecute() { 
		db->insert(student);
	}
private:
	BST<int>* db; // replace this with the database
	int student;  // replace int with Student
};

class InsertFacultyCommand : public ICommand {
public:
	InsertFacultyCommand(BST<int>* theDb, int theFaculty): db(theDb), faculty(theFaculty) {}
	inline void execute() { 
		db->insert(faculty);
	}
	inline void unexecute() { 
		db->remove(faculty);
	}
private:
	BST<int>* db; // replace this with the database
	int faculty; // replace int with Faculty
};

class RemoveFacultyCommand : public ICommand {
public:
	RemoveFacultyCommand(BST<int>* theDb, int theFaculty): db(theDb), faculty(theFaculty) {}
	inline void execute() { 
		db->remove(faculty);
	}
	inline void unexecute() { 
		db->insert(faculty);
	}
private:
	BST<int>* db; // replace this with the database
	int faculty;  // replace int with Faculty
};



#endif
