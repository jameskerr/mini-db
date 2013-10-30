#ifndef UNDOREDO_H
#define UNDOREDO_H 

#include "Stack.h"
#include "Commands.h"

class UndoRedo {
public:
	UndoRedo(BST<int>* theDb): db(theDb) {}
	void rollback(int level);
	void insertedStudent(int student);
	void removedStudent(int student);
	void insertedFaculty(int faculty);
	void removedFaculty(int faculty);

private:
	BST<int>* db;  // Replace with the real database
	Stack<ICommand*> undo_commands;
	Stack<ICommand*> redo_commands;
};

#endif