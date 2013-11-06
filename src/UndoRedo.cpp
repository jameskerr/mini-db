#include "UndoRedo.h"

void UndoRedo::rollback(int level) {
	for (int i = 0; i < level; ++i) {
        
        // DELETE
        cout << undo_commands.length() << endl ;
        
		if (undo_commands.length() == 0) {
			cout << "No more undo commands available." << endl;
			return;
		}
		ICommand* cmd = undo_commands.pop();
		cmd->unexecute();
		redo_commands.push(cmd);
	}
}

void UndoRedo::rollforward(int level) {
	for (int i = 0; i < level; ++i) {
		if (redo_commands.length() == 0) {
			cout << "No more redo commands available." << endl;
			return;
		}
		ICommand* cmd = redo_commands.pop();
		cmd->execute();
		undo_commands.push(cmd);
	}
}

void UndoRedo::insertedStudent(Student student) {
    clearRedoStack();
    ICommand* cmd = new InsertStudentCommand(db, student);
	undo_commands.push(cmd);
}
void UndoRedo::removedStudent(Student student) {
	clearRedoStack();
    ICommand* cmd = new RemoveStudentCommand(db, student);
	undo_commands.push(cmd);
}
void UndoRedo::insertedFaculty(Faculty faculty) {
	clearRedoStack();
    ICommand* cmd = new InsertFacultyCommand(db, faculty);
	undo_commands.push(cmd);
}
void UndoRedo::removedFaculty(Faculty faculty) {
	clearRedoStack();
    ICommand* cmd = new RemoveFacultyCommand(db, faculty);
	undo_commands.push(cmd);
}
void UndoRedo::removedAdvisee(int facID, int stuID) {
	clearRedoStack();
    ICommand* cmd = new RemoveAdviseeCommand(db, facID, stuID);
	undo_commands.push(cmd);
}
void UndoRedo::changedAdvisor(int stuID, int newAdvisor, int oldAdvisor) {
	clearRedoStack();
    ICommand* cmd = new ChangeAdvisorCommand(db, stuID, newAdvisor, oldAdvisor);
	undo_commands.push(cmd);
}
void UndoRedo::clearRedoStack() {
    while (redo_commands.length() != 0)
        redo_commands.pop();
}