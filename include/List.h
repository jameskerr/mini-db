#ifndef LIST_H
#define LIST_H

#include "IList.h"
#include "ListNode.h"
#include "cassert"
#include <iostream>

template <class T>
class List: public IList<T> {
public:
	List():front(0) :back(0) {}
	virtual ~List() {}

	void addToBack(T data);
	void addToFront(T data);
	T removeFromBack();
	T removeFromFront();
	T peekFront();
	T peekBack();
	void print();
	int length();

private:
	ListNode<T>* front;
	ListNode<T>* back;
	int size;
};


template <class T>
void List<T>::addToBack(T data) {
	// Case for the first node
	if (back == 0) {
		back = new ListNode<T>(data);
		front = back;
	} 
	// Case for all other nodes
	else {
		back->next = new ListNode<T>(data, 0, back);
		back = back->next;
	}
	size += 1;
}

template <class T>
void List<T>::addToFront(T data) {
	// Case for the first node
	if (front == 0) {
		front = new ListNode<T>(data);
		back = front;
	} 
	// Case for all other nodes
	else {
		front->prev = new ListNode<T>(data, front, 0);
		front = front->prev;
	}
	size += 1;
}

template <class T>
T List<T>::removeFromBack() {
	// Make sure the list is not empty
	assert(back != 0);
	// If there is only one item in the list
	--size;
	if (front == back) {
		T retData = back->data;
		delete back;
		front = back = 0;
		return retData;
	}
	// All other cases
	T retData = back->data; // Grab return data
	ListNode<T>* temp = back; // Grab the item to delete
	back = back->prev; // Move back up one
	back->next = 0; // Null out back's next
	delete temp;  // Clobber the bitch
	return retData; // Duh
}

template <class T>
T List<T>::removeFromFront() {
	// Make sure the list is not empty
	assert(front != 0);
	// If there is only one item in the list
	--size;
	if (front == back) {
		T retData = front->data;
		delete front;
		front = back = 0;
		return retData;
	}
	// All other cases
	T retData = front->data; // Grab return data
	ListNode<T>* temp = front; // Grab the item to delete
	front = front->next; // Move front down one
	back->prev = 0; // Null out front's prev
	delete temp;  // Clobber the bitch
	return retData; // Duh
}

template <class T>
T List<T>::peekFront() {
	// Make sure the list is not empty
	assert(front != 0);
	return front->data;
}

template <class T>
T List<T>::peekBack() {
	// Make sure the list is not empty
	assert(back != 0);
	return back->data;
}

template <class T>
void List<T>::print() {
	ListNode<T>* cursor = front;
	int count = 1;
	while (cursor != 0) {
		if (count < size) {
			std::cout << cursor->data << ", ";
			++count;
		}
		else {
			std::cout << cursor->data;
			++count;
		}
		cursor = cursor->next;
	}
}

template <class T>
int List<T>::length() {
	return size;
}

#endif