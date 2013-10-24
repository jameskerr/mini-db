#ifndef TREENODE_H
#define TREENODE_H 

template <class U>
class SearchTree;

template <class T>
class TreeNode {
public:
	template <class U> friend class SearchTree;
	TreeNode(T theData, TreeNode<T>* theLeft = 0, TreeNode<T>* theRight = 0)
		:data(theData), left(theLeft), right(theRight) {}
	virtual ~TreeNode() {}

private:
	T data;
	TreeNode<T>* left;
	TreeNode<T>* right;
};

#endif