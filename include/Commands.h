#ifndef COMMANDS_H
#define COMMANDS_H 

#include <iostream>
#include "database.h"
#include "ICommand.h"
#include "Student.h"
#include "Faculty.h"

class InsertStudentCommand : public ICommand {
public:
	InsertStudentCommand(Database* theDb, Student theStudent): db(theDb), student(theStudent) {}
	inline void execute() { 
		db->addStu(student);
		cout << "Added student #" << student.getID() << endl;
	}
	inline void unexecute() { 
		db->deleteStu(student);
		cout << "Deleted student #" << student.getID() << endl;
	}
private:
	Database* db;
	Student student; 
};

class RemoveStudentCommand : public ICommand {
public:
	RemoveStudentCommand(Database* theDb, Student theStudent): db(theDb), student(theStudent) {}
	inline void execute() { 
		db->deleteStu(student);
		cout << "Deleted student #" << student.getID() << endl;
	}
	inline void unexecute() { 
		db->addStu(student);
		cout << "Added student #" << student.getID() << endl;
	}
private:
	Database* db;
	Student student;
};

class InsertFacultyCommand : public ICommand {
public:
	InsertFacultyCommand(Database* theDb, Faculty theFaculty): db(theDb), faculty(theFaculty) {}
	inline void execute() { 
		db->addFac(faculty);
		cout << "Added faculty #" << faculty.getID() << endl;
	}
	inline void unexecute() { 
		db->deleteFac(faculty);
		cout << "Deleted faculty #" << faculty.getID() << endl;
	}
private:
	Database* db;
	Faculty faculty;
};

class RemoveFacultyCommand : public ICommand {
public:
	RemoveFacultyCommand(Database* theDb, Faculty theFaculty): db(theDb), faculty(theFaculty) {}
	inline void execute() { 
		db->deleteFac(faculty);
		cout << "Deleted faculty #" << faculty.getID() << endl;
	}
	inline void unexecute() { 
		db->addFac(faculty);
		cout << "Added faculty #" << faculty.getID() << endl;
	}
private:
	Database* db;
	Faculty faculty; 
};

class RemoveAdviseeCommand : public ICommand {
public:
	RemoveAdviseeCommand(Database* theDb, int theFacID, int theStuID): db(theDb), facID(theFacID), stuID(theStuID) {}
	inline void execute() {
		db->removeAdvisee(facID, stuID);
		cout << "Removed student #" << stuID << " from faculty #" << facID << endl;
	}
	inline void unexecute() {
		db->changeAdvisor(stuID, facID);
		cout << "Student # " << stuID << " now has faculty #" << facID << " as his/her advisor." << endl;
	}
private:
	Database* db;
	int facID;
	int stuID;
};

class ChangeAdvisorCommand : public ICommand {
public:
	ChangeAdvisorCommand(Database* theDb, int theStuID, int theNewAdvisor, int theOldAdvisor) 
	:db(theDb), stuID(theStuID), newAdvisor(theNewAdvisor), oldAdvisor(theOldAdvisor) {}
	inline void execute() {
		db->changeAdvisor(stuID, newAdvisor);
		cout << "Student # " << stuID << " now has faculty #" << newAdvisor << " as his/her advisor." << endl;
	}
	inline void unexecute() {
		db->changeAdvisor(stuID, oldAdvisor);
		cout << "Student # " << stuID << " now has faculty #" << oldAdvisor << " as his/her advisor." << endl;
	}
private:
	Database* db;
	int stuID;
	int newAdvisor;
	int oldAdvisor;
};
#endif
