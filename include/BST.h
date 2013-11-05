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
	BST(const BST& source);
	virtual ~BST();

	// OPERATOR OVERLOADS
	BST<T>& operator = (const BST<T>& source);

	// PUBLIC METHODS
	void insert(T data);
	TreeNode<T>* find(T data);
	bool remove(T data);
	void print();
	int length();
    TreeNode<T>* getRoot();

private:
	// PRIVATE ATTRIBUTES
	TreeNode<T>* root;
	int size;

	// UTILITY FUNCTIONS
	void clobber(TreeNode<T>* node);
	void pPrint(TreeNode<T>* node);
	TreeNode<T>* getSuccessor(TreeNode<T>* node);
	TreeNode<T>* getPredecessor(TreeNode<T>* node);
	TreeNode<T>* pCopy(TreeNode<T>* node);
};

template <class T>
BST<T>::BST() :size(0), root(0) {}

template <class T>
BST<T>::~BST() {
	clobber(root);
}

template <class T>
BST<T>::BST(const BST<T>& source) {
	this = source;
}

template <class T>
BST<T>& BST<T>::operator = (const BST<T>& source) {
	size = source.size;
	clobber(root);
	if (source.root != 0)
		root = new TreeNode<T>(source.root->data, pCopy(source.root->left), pCopy(source.root->right));
	return *this;
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
	*cursor = new TreeNode<T>(data,0,0);
	++size;
}

template <class T>
TreeNode<T>* BST<T>::find(T data) {
	TreeNode<T>** cursor = &root;
	while (*cursor != 0 && (*cursor)->data != data) {
		if ((*cursor)->data < data)
			cursor = &((*cursor)->left);
		else 
			cursor = &((*cursor)->right);
	}
	return *cursor;
}

template <class T>
bool BST<T>::remove(T data) {
	TreeNode<T>* parent = 0;
	TreeNode<T>* target = root;
	
	while (target != 0 && target->data != data) {		// Code to find the target and its parent
		parent = target;
		if (target->data < data)
			target = target->left;
		else 
			target = target->right;
	}

	if (target == 0) return false;   						// The data doesn't exist return false

	if (target == root) { 									// Case for the root
		if (root->hasLeftChild() && root->hasRightChild()) { 	// The root has two children
			root = getSuccessor(target);
			root->left = target->left;
			root->right = target->right;
		}
		else
		if (root->hasLeftChild()) 							// The root only has a left child
			root = root->left;
		else
		if (root->hasRightChild()) 							// The root only has a right child
			root = root->right;
		else												// The root has no chilren
			root = 0;
	}
	else
	if (target->hasLeftChild() && target->hasRightChild()) {	// The target has two children
		if (parent->left == target) {
			TreeNode<T>* pred = getPredecessor(target);
			parent->left = pred;
			pred->right = target->right;
		}			
		else {
			TreeNode<T>* succ = getSuccessor(target);
			parent->right = succ;
			succ->left = target->left;
		}
	}
	else 
	if (target->hasLeftChild()) {							// The target only has left child
		if (parent->left == target)
			parent->left = target->left;
		else
			parent->right = target->left;
	}
	else
	if (target->hasRightChild()) {							// The target only has a right child
		if (parent->left == target)
			parent->left = target->right;
		else
			parent->right = target->right;
	}
	else {													// Thee target has no chilren
		if (parent->left == target) 				
			parent->left = 0;
		else
			parent->right = 0;
	}
	delete target;
	--size;
	return true;
}

template <class T>
void BST<T>::print() {
	pPrint(root);
	std::cout << std::endl;
}

template <class T>
int BST<T>::length() {
	return size;
}

template <class T>
TreeNode<T>* BST<T>::getRoot() { return root; }

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
TreeNode<T>* BST<T>::pCopy(TreeNode<T>* source) {
	if (source == 0) return 0;
	return new TreeNode<T>(source->data, pCopy(source->left), pCopy(source->right));
}

template <class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T>* node) {
	if (node->right == 0) return 0;
	TreeNode<T>* parent = node;
	node = node->right;

	if (!node->hasLeftChild()) {						// Case if the the node to the right is the predecessor
		parent->right = node->right;
		return node;
	}
	while (node->left != 0) { parent = node; node = node->left; }
	parent->left = 0;
	return node;
}

template <class T>
TreeNode<T>* BST<T>::getPredecessor(TreeNode<T>* node) {
	if (node->left == 0) return 0;
	TreeNode<T>* parent = node;
	node = node->left;

	if (!node->hasRightChild()) {					// Case if the the node to the left is the predecessor
		parent->left = node->left;
		return node;
	}

	while (node->right != 0) { parent = node; node = node->right; }
	parent->right = 0;
	return node;
}
#endif