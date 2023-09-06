#ifndef THING2_H
#define THING2_H

#include "Thing1.h"

#include <iostream>

using namespace std;

template<class T>
class Thing2: public Thing1<T>{
	private:
	ListNode<T>* iter;
	public:
		Thing2();
		~Thing2();
		void resetIteratorToFront();
		void resetIteratorToBack();
		Thing2<T>& operator++();
		Thing2<T> operator++(int);
		Thing2<T>& operator--();
		Thing2<T> operator--(int);
		void operator+=(int);
		void operator-=(int);
		T get();
		void insertval(T);
		void deleteval();
};

template<class T> 
Thing2<T>::Thing2()
{
	iter = nullptr;
}

template<class T>
Thing2<T>::~Thing2()
{
}

template<class T>
void Thing2<T>::resetIteratorToFront()
{
	iter = Thing1<T>::head;
}

template<class T>
void Thing2<T>::resetIteratorToBack()
{
	iter = Thing1<T>::tail;
}

template<class T>
Thing2<T>& Thing2<T>::operator++()
{
	if(iter->next){
		iter = iter->next;
	}
	return *this;
}

template<class T>
Thing2<T> Thing2<T>::operator++(int)
{
	Thing2<T> temp = *this;
	if(iter->next){
		iter = iter->next;
	}

	return temp;
}


template<class T>
Thing2<T>& Thing2<T>::operator--()
{
	if(iter->previous){
		iter = iter->next;
	}
	return *this;
}

template<class T>
Thing2<T> Thing2<T>::operator--(int)
{
	Thing2<T> temp = *this;
	if(iter->next){
		iter = iter->next;
	}
	return temp;
}


template<class T>
void Thing2<T>::operator+=(int n)
{
	int count = 0;
	if(iter){
		while(count!=n&&iter->next){
			iter = iter->next;
		}
	}
		
}

template<class T>
void Thing2<T>::operator-=(int n)
{
	int count = 0;
	if(iter){
		while(count!=n&&iter->previous){
			iter = iter->previous;
		}
	}
}

template<class T>
T Thing2<T>::get()
{
	return iter->value;
}

template<class T>
void Thing2<T>::insertval(T var)
{
	ListNode<T>* nodePtr = new ListNode<T>;
	ListNode<T>* tempPtr;
	nodePtr->value = var;

	tempPtr = iter->next;
	tempPtr->previous = nodePtr;
	iter->next = nodePtr;

}

template<class T> 
void Thing2<T>::deleteval()
{
	if(iter){
		ListNode<T>* nodePtr;

		nodePtr = iter->next;

		nodePtr->previous = iter->previous;

		delete iter;
	}
}

#endif
