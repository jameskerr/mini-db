#include "DatabaseUI.h"
#include "tools.h"

using std::cout;
using std::string;
using std::endl;

bool DatabaseUI::getStudentFromKeyboard() {
	cout << "ADD NEW STUDENT" << endl;
	string name = getString("Name: ");
	string level = getString("Level: ");
	string major = getString("Major: ");
	double gpa = getDouble("GPA: ");
	int advisor = getInt("Advisor ID: ");
	// Give option to display all the advisors

	cout << "NAME: " << name << endl;
	cout << "LEVEL: " << level << endl;
	cout << "MAJOR: " << major << endl;
	cout << "GPA: " << gpa << endl;
	cout << "ADVISOR: " << advisor << endl;
	return true;
}