#include "Database.h"
#include "DatabaseUI.h"
#include <iostream>

using namespace std;

int main() {
	 Database d;
     DatabaseUI ui(&d);
     ui.menu();

	return 0;
}