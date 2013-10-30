#ifndef STACK_H
#define STACK_H

#include "List.h"

template <class T>
class Stack {
public:
	Stack();
	virtual ~Stack();

	void push(T data);
	T pop();
	int length();
	void print();
private:
	IList<T>* list;
};

template <class T>
Stack<T>::Stack() {
	list = new List<T>;
}

template <class T>
Stack<T>::~Stack() {
	delete list;
}

template <class T>
void Stack<T>::push(T data) {
	list->addToFront(data);
}

template <class T>
T Stack<T>::pop() {
	return list->removeFromFront();
}

template <class T>
int Stack<T>::length() {
	return list->length();
}

template <class T>
void Stack<T>::print() {
	list->print();
}

#endif