#ifndef ILIST_H
#define ILIST_H

template <class T>
class IList {
public:
	IList() {}
	virtual ~IList() {}
	virtual void addToBack(T data) = 0;
	virtual void addToFront(T data) = 0;
	virtual T removeFromBack() = 0;
	virtual T removeFromFront() = 0;
	virtual T peekFront() = 0;
	virtual T peekBack() = 0;
	virtual int length() = 0;
	virtual void print() = 0;
};

#endif