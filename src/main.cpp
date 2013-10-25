#include "BST.h"
#include <iostream>

using namespace std;

int main() {
	
	BST<int> tree;

;
	tree.insert(1430);
	tree.insert(52);
	tree.insert(1115);
	tree.insert(132);
	tree.insert(16);
	tree.insert(140);
	tree.insert(5);
	tree.insert(15);
	tree.insert(12123);
	tree.insert(1116);
	tree.insert(103);
	tree.insert(5);
	tree.insert(1153);
	tree.insert(122);
	tree.insert(16);
	tree.insert(11120);
	tree.insert(5);
	tree.insert(145);
	tree.insert(12);
	tree.insert(136);
	tree.print();

	tree.remove(145);
	tree.remove(1116);
	tree.remove(103);
	tree.remove(16);
	tree.remove(140);
	tree.remove(5);
	tree.remove(145);
	tree.remove(12);
	tree.print();





	return 0;
}