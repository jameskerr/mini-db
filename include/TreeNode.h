#ifndef TREENODE_H
#define TREENODE_H 

template <class U>
class BST;

template <class T>
class TreeNode {
public:
	template <class U> friend class BST;
	TreeNode(T theData, TreeNode<T>* theLeft = 0, TreeNode<T>* theRight = 0, TreeNode<T>* theParent = 0)
		:data(theData), left(theLeft), right(theRight), parent(theParent) {}
	virtual ~TreeNode() {}
	inline T getData() { return data; }
	 bool hasNoChilren();
	 bool hasLeftChild();
	 bool hasRightChild();
private:
	T data;
	TreeNode<T>* left;
	TreeNode<T>* right;
	TreeNode<T>* parent;
};

template <class T>
bool TreeNode<T>::hasNoChilren() { return (left == 0 && right == 0);}

template <class T>
bool TreeNode<T>::hasLeftChild() { return (left != 0); }

template <class T>
bool TreeNode<T>::hasRightChild() { return (right != 0); }

#endif