#ifndef BST_H
#define BST_H

#include "TreeNode.h"
#include <iostream> // cout
#include <cassert> // assert

// NON-SELF BALANCING...YET...BINARY SEARCH TREE CLASS
template <class T>
class BST {
public:
	// CONSTRUCTORS
	BST();
	virtual ~BST();
	// PUBLIC METHODS
	void insert(T data);
	bool delete(T data);
	T* toArray();
	void print();
	int length();

private:
	// PRIVATE ATTRIBUTES
	TreeNode<T>* root;
	int size;

	// UTILITY FUNCTIONS
	void clobber(TreeNode<T>* node);
	void pPrint(TreeNode<T>* node);
	TreeNode<T>* getSuccessor(TreeNode<T>* node);
	TreeNode<T>* getPredecessor(TreeNode<T>* node);
};

template <class T>
BST<T>::BST() :size(0), root(0) {}

template <class T>
BST<T>::~BST() {
	clobber(root);
}

template <class T>
void BST<T>::insert(T data) {
	TreeNode<T>** cursor = &root;
	while (*cursor != 0) {
		if ((*cursor)->data < data)
			cursor = &((*cursor)->left);
		else
			cursor = &((*cursor)->right);
	}
	*cursor = new TreeNode<T>(data);
	++size;
}

template <class T>
bool BST<T>::delete(T data) {
	// do some awesome stuff in here
	// Just go throught the cases
}

template <class T>
void BST<T>::print() {
	pPrint(root);
}

template <class T>
int BST<T>::length() {
	return size;
}

template <class T>
void BST<T>::pPrint(TreeNode<T>* node) {
	if (node == 0) return;
	pPrint(node->left);
	std::cout << node->data << " ";
	pPrint(node->right);
}

template <class T>
void BST<T>::clobber(TreeNode<T>* node) {
	if (node == 0) return;
	clobber(node->left);
	clobber(node->right);
	delete node;
	return;
}

template <class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T>* node) {
	if (node->right == 0) return 0;
	node = node->right;
	while (node->left != 0) node = node->left;
	return node;
}

template <class T>
TreeNode<T>* BST<T>::getPredecessor(TreeNode<T>* node) {
	if (node->left == 0) return 0;
	node = node->left;
	while (node->right != 0) node = node->right;
	return node;
}
#endif