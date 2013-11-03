#include "UndoRedo.h"

void UndoRedo::rollback(int level) {
	for (int i = 0; i < level; ++i) {
		if (undo_commands.length() == 0) return;
		ICommand* cmd = undo_commands.pop();
		cmd->unexecute();
		redo_commands.push(cmd);
	}
}

void UndoRedo::insertedStudent(int student) {
	ICommand* cmd = new InsertStudentCommand(db, student);
	undo_commands.push(cmd);
}
void UndoRedo::removedStudent(int student) {
	ICommand* cmd = new RemoveStudentCommand(db, student);
	undo_commands.push(cmd);
}
void UndoRedo::insertedFaculty(int faculty) {
	ICommand* cmd = new InsertFacultyCommand(db, faculty);
	undo_commands.push(cmd);
}
void UndoRedo::removedFaculty(int faculty) {
	ICommand* cmd = new RemoveFacultyCommand(db, faculty);
}
