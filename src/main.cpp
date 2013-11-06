#include "Database.h"
#include "DatabaseUI.h"
#include "tools.h"
#include <iostream>

using namespace std;

int main() {
	 Database db;
     DatabaseUI ui(&db);
     
     int choice = 0;
     bool go = true;
     
     while (go) {
     	ui.menu();
     	choice  = getInt("Menu choice: ");
     	switch (choice) {
     		case 1:
     			ui.showAllStudents();
			break;
			case 2:
				ui.showAllFaculty();
			break;
			case 3:
				ui.showStudent();
			break;
			case 4:
				ui.showFaculty();
			break;
			case 5:
				ui.showAdvisor();
			break;
			case 6:
				ui.showAdvisees();
			break;
			case 7:
				ui.addStudent();
			break;
			case 8:
				ui.addFaculty();
			break;
			case 9:
				ui.changeAdvisor();
			break;
			case 10:
				ui.deleteStudent();
			break;
			case 11:
				ui.deleteFaculty();
			break;
			case 12:
				ui.removeAdvisee();
			break;
			case 13:
				ui.rollback();
			break;
            case 14:
                ui.rollforward();
                break;
			case 15:
				ui.save();
			break;
            case 16:
                go = false;
            break;
			default:
			break;
     	}
     }
     db.save();
	return 0;
}


