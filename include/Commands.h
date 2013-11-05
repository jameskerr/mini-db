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
	}
	inline void unexecute() { 
		db->deleteStu(student);
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
	}
	inline void unexecute() { 
		db->addStu(student);
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
	}
	inline void unexecute() { 
		db->deleteFac(faculty);
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
	}
	inline void unexecute() { 
		db->addFac(faculty);
	}
private:
	Database* db;
	Faculty faculty; 
};



#endif
