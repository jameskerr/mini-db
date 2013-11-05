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
	if (!db->printAllStu())
		cout << "No students..." << endl << endl;
	pause("\nPress ENTER to continue...");
}

void DatabaseUI::showAllFaculty() {
	if (!db->printAllFac())
		cout << "No faculty members..." << endl << endl;
	pause("\nPress ENTER to continue...");
}

void DatabaseUI::showStudent() {
	cout << "SHOW A STUDENT" << endl;
	int id = getInt("Student ID: ");
	if (!db->printStu(id))
		cout << "There is no student with that ID." << endl;
	pause("\nPress ENTER to continue...");
}

void DatabaseUI::showFaculty() {
	cout << "SHOW A FACULTY" << endl;
	int id = getInt("Faculty ID: ");
	if (!db->printFac(id))
		cout << "There is no faculty with that ID." << endl;
	pause("\nPress ENTER to continue...");
}

void DatabaseUI::showAdvisor() {
	cout << "SHOW A STUDENT'S ADVISOR" << endl;
	int id = getInt("Student ID: ");
	if (!db->printAdvisor(id))
		cout << "There is no student with that ID." << endl;
	pause("\nPress ENTER to continue...");
}

void DatabaseUI::showAdvisees() {
	int id = getInt("Faculty ID: ");
	if (!db->printAdvisees(id))
		cout << "There is no faculty with that ID." << endl;
	pause("\nPress ENTER to continue...");
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
	
	int advisor = 0;
	// Ask if they want to add the advisor
	char choice = getChar("Would you like to add an advisor? (y/n)\n");
	if (lowerCase(choice) == 'y') {
		advisor = getInt("Advisor ID: ");
		while (db->fTree.find(Faculty(advisor)) == 0) {
			cout << "There is no faculty with an ID of: " << advisor << endl;
			choice = getChar("Would you like to add a faculty? (y/n)\n");
			if (lowerCase(choice) == 'y') {
				addFaculty();
				cout << "(Returning to the add student form...)\n";
			}
			advisor = getInt("Advisor ID: ");
		}
	}
	int id = db->autoStuID();
	Student s(id, advisor, gpa, name, level, major);
	db->addStu(s);
	db->changeAdvisor(id, advisor);
	history->insertedStudent(s);
	cout << "\nSTUDENT HAS BEEN ADDED" << endl;
	cout << s.toString() << endl << endl;
	pause("\nPress ENTER to continue...");
}

void DatabaseUI::addFaculty() {
	cout << "ADD NEW FACULTY" << endl;
	string name = getString("Name: ");
	string level = getString("Level: ");
	string department = getString("Department: ");

	Faculty f(db->autoFacID(), name, level, department);
	cout << "I am about to addFac" << endl;
	db->addFac(f);
	history->insertedFaculty(f);
	cout << "\nFACULTY HAS BEEN ADDED" << endl;
	cout << f.toString() << endl << endl;
	pause("\nPress ENTER to continue...");
}

void DatabaseUI::changeAdvisor() {
	cout << "CHANGE A STUDENT'S ADVISOR" << endl;
	int stu = getInt("Student ID: ");
	TreeNode<Student>* sNode = db->sTree.find(Student(stu));
	
	if (sNode == 0) {
		cout << "That student does not exist." << endl;
	} else {
		int oldAdvisor = db->sTree.find(Student(stu))->getData().getAdvisor();
		int fac = getInt("New faculty advisor ID: ");
		if (!db->changeAdvisor(stu, fac)) {
			cout << "That faculty do not exist." << endl;
		} else {
			history->changedAdvisor(stu, fac, oldAdvisor);
			cout << "Student #" << stu << " now has faculty #" << fac << " as his/her advisor." << endl;
		}
	}
	pause("\nPress ENTER to continue...");
}

void DatabaseUI::deleteStudent() {
    cout << "DELETE A STUDENT" << endl;
    int stu = getInt("Student ID: ");
    TreeNode<Student>* sNode = db->sTree.find(Student(stu));
    if (sNode == 0)
        cout << "Student does not exist." << endl;
    else{
        history->removedStudent(sNode->getData());
        db->deleteStu(Student(stu));
        cout << "Student #" << stu << " has been deleted." << endl;
    }
	pause("\nPress ENTER to continue...");
}

void DatabaseUI::deleteFaculty() {
    cout << "DELETE A FACULTY" << endl;
    int fac = getInt("Faculty ID: ");
    TreeNode<Faculty>* fNode = db->fTree.find(Faculty(fac));
    if (fNode == 0){
        cout << "Faculty does not exist." << endl;
    }
    else{
        history->removedFaculty(fNode->getData());
        db->deleteFac(Faculty(fac));
        cout << "Faculty #" << fac << " has been deleted." << endl;
    }
	pause("\nPress ENTER to continue...");
}

void DatabaseUI::removeAdvisee() {
	cout << "REMOVE AN ADVISEE FROM A FACULTY" << endl;
	int stu = getInt("Student ID: ");
	int fac = getInt("Faculty ID: ");
	if (!db->removeAdvisee(fac, stu)) {
		cout << "Error.  Student ID or Faculty ID do not exist." << endl;
	} else {
		history->removedAdvisee(fac, stu);
		cout << "Removed student #" << stu << " from faculty #" << fac << endl;
	}
		
	pause("\nPress ENTER to continue...");
}

void DatabaseUI::rollback() {
	int steps = getInt("Number of steps to reverse: ");
	history->rollback(steps);
	pause("\nPress ENTER to continue...");
}