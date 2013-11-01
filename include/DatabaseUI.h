#ifndef DATABASEUI_H
#define DATABASEUI_H 

class DatabaseUI {
public:
	DatabaseUI() {}
	virtual ~DatabaseUI() {}

	bool getStudentFromKeyboard();
	bool getFacultyFromKeyboard();
};
#endif