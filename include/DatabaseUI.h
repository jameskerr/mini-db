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
    void rollforward();
    void save();
private:
	Database* db;
	UndoRedo* history;
};
#endif