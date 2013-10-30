#ifndef LISTNODE_H
#define LISTNODE_H 

template <class U>
class List;

template <class T>
class ListNode {
public:
	template <class U> friend class List;
	ListNode(T theData, ListNode<T>* theNext = 0, ListNode<T>* thePrev = 0)
		:data(theData), next(theNext), prev(thePrev) {}
	virtual ~ListNode() {}

private:
	T data;
	ListNode<T>* next;
	ListNode<T>* prev;
};

#endif