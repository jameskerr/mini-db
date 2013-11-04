#include "DatabaseUI.h"
#include "tools.h"
#include <iostream>


using std::cout;
using std::string;
using std::endl;

void DatabaseUI::menu() {
	cout << endl << "----------------STUDENT & FACULTY DATABASE--------------" << endl;
	cout << "Select an option." << endl;
	cout << "1) Show all students" << endl;
	cout << "2) Show all faculty" << endl;
	cout << "3) Show a student" << endl;
	cout << "4) Show a faculty" << endl;
	cout << "5) Show a student's advisor" << endl;
	cout << "6) Show a faculty's advisees" << endl;
	cout << "7) Add a student" << endl;
	cout << "8) Add a faculty" << endl;
	cout << "9) Change a student's advisor" << endl;
	cout << "10) Delete a student" << endl;
	cout << "11) Delete a faculty" << endl;
	cout << "12) Remove advisee from faculty" << endl;
	cout << "13) Rollback the database" << endl;
	cout << "14) Exit" << endl;
	cout << endl;
}

void DatabaseUI::showAllStudents() {
	db->printAllStu();
}

void DatabaseUI::showAllFaculty() {
	db->printAllFac();
}

void DatabaseUI::showStudent() {
	int id = getInt("Student ID: ");
	if (!db->printStu(id))
		cout << "There is no student with that ID." << endl;
}

void DatabaseUI::showFaculty() {
	int id = getInt("Faculty ID: ");
	if (!db->printFac(id))
		cout << "There is no faculty with that ID." << endl;
}

void DatabaseUI::showAdvisor() {
	int id = getInt("Student ID: ");
	if (!db->printAdvisor(id))
		cout << "There is no student with that ID." << endl;
}

void DatabaseUI::showAdvisees() {
	int id = getInt("Faculty ID: ");
	if (!db->printAdvisor(id))
		cout << "There is no faculty with that ID." << endl;
}

void DatabaseUI::addStudent() {
    cout << "ADD NEW STUDENT" << endl;
	string name = getString("Name: ");
	string level = getString("Level: ");
	string major = getString("Major: ");
	double gpa = getDouble("GPA: ");
	while (gpa < 0 || gpa > 4.0) {
		cout << "GPA must be between 0.0 and 4.0." << endl;
		gpa = getDouble("GPA: ");	
	}

	int advisor = getInt("Advisor ID: ");
	while (db->fTree.find(Faculty(advisor)) != 0) {
		cout << "There is no advisory with an ID of: " + advisor << endl;
		advisor = getInt("Advisor ID: ");
	}
	Student s(db->autoStuID(), advisor, gpa, name, level, major);
	db->addStu(s);
	history->insertedStudent(s);
	cout << "Student has been added." << endl;
}

void DatabaseUI::addFaculty() {
	cout << "ADD NEW Faculty" << endl;
	string name = getString("Name: ");
	string level = getString("Level: ");
	string department = getString("Department: ");

	Faculty f(db->autoFacID(), name, level, department);
	db->addFac(f);
	history->insertedFaculty(f);
	cout << "Faculty has been added." << endl;
}

void DatabaseUI::changeAdvisor() {
	int stu = getInt("Student ID: ");
	int fac = getInt("New faculty advisor ID: ");
	if (!db->changeAdvisor(stu, fac)) {
		cout << "Error.  Student ID or Faculty ID do not exist.";
	} else
	cout << "Student #" << stu << " now has faculty #" << fac << " as his/her advisor." << endl;
}

void DatabaseUI::deleteStudent() {

}

void DatabaseUI::deleteFaculty() {

}

void DatabaseUI::removeAdvisee() {

}

void rollback() {

}