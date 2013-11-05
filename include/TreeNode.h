#ifndef TREENODE_H
#define TREENODE_H 

template <class U>
class BST;

template <class T>
class TreeNode {
public:
	template <class U> friend class BST;
	TreeNode(T theData, TreeNode<T>* theLeft = 0, TreeNode<T>* theRight = 0)
		:data(theData), left(theLeft), right(theRight) {}
	virtual ~TreeNode() {}
	inline T getData() { return data; }
	inline TreeNode<T>* getLeft() { return left; };
	inline TreeNode<T>* getRight() { return right; };

	 bool hasNoChilren();
	 bool hasLeftChild();
	 bool hasRightChild();
private:
	T data;
	TreeNode<T>* left;
	TreeNode<T>* right;
};

template <class T>
bool TreeNode<T>::hasNoChilren() { return (left == 0 && right == 0);}

template <class T>
bool TreeNode<T>::hasLeftChild() { return (left != 0); }

template <class T>
bool TreeNode<T>::hasRightChild() { return (right != 0); }

#endif