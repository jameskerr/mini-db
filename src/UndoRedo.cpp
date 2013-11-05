#include "UndoRedo.h"

void UndoRedo::rollback(int level) {
	for (int i = 0; i < level; ++i) {
		if (undo_commands.length() == 0) {
			cout << "No more undo commands available." << endl;
			return;
		}
		ICommand* cmd = undo_commands.pop();
		cmd->unexecute();
		redo_commands.push(cmd);
	}
}

void UndoRedo::insertedStudent(Student student) {
	ICommand* cmd = new InsertStudentCommand(db, student);
	undo_commands.push(cmd);
}
void UndoRedo::removedStudent(Student student) {
	ICommand* cmd = new RemoveStudentCommand(db, student);
	undo_commands.push(cmd);
}
void UndoRedo::insertedFaculty(Faculty faculty) {
	ICommand* cmd = new InsertFacultyCommand(db, faculty);
	undo_commands.push(cmd);
}
void UndoRedo::removedFaculty(Faculty faculty) {
	ICommand* cmd = new RemoveFacultyCommand(db, faculty);
	undo_commands.push(cmd);
}
void UndoRedo::removedAdvisee(int facID, int stuID) {
	ICommand* cmd = new RemoveAdviseeCommand(db, facID, stuID);
	undo_commands.push(cmd);
}