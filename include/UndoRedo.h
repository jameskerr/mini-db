#ifndef UNDOREDO_H
#define UNDOREDO_H 

#include "Database.h"
#include "Stack.h"
#include "Commands.h"

class UndoRedo {
public:
	UndoRedo(Database* theDb): db(theDb) {}
	void rollback(int level);
	void insertedStudent(Student student);
	void removedStudent(Student student);
	void insertedFaculty(Faculty faculty);
	void removedFaculty(Faculty faculty);

private:
	Database* db;
	Stack<ICommand*> undo_commands;
	Stack<ICommand*> redo_commands;
};

#endif