#ifndef DATABASEUI_H
#define DATABASEUI_H 

#include "database.h"
#include "UndoRedo.h"

class DatabaseUI {
public:
	DatabaseUI(Database* theDb):db(theDb) {
		history = new UndoRedo(db);
	}
	virtual ~DatabaseUI() {}

	void menu();
	void showAllStudents();
	void showAllFaculty();
	void showStudent();
	void showFaculty();
	void showAdvisor();
	void showAdvisees();
	void addStudent();
	void addFaculty();
	void changeAdvisor();
	void deleteStudent();
	void deleteFaculty();
	void removeAdvisee();
	void rollback();
private:
	Database* db;
	UndoRedo* history;
};
#endif

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