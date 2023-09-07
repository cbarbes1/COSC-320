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
		void operator++();
		void operator++(int);
		void operator--();
		void operator--(int);
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
void Thing2<T>::operator++()
{
	if(iter->next){
		iter = iter->next;
	}
	
}

template<class T>
void Thing2<T>::operator++(int)
{
	if(iter->next){
		iter = iter->next;
	}
	
}


template<class T>
void Thing2<T>::operator--()
{
	if(iter->previous){
		iter = iter->previous;
	}
}

template<class T>
void Thing2<T>::operator--(int)
{
	if(iter->previous){
		iter = iter->previous;
	}
	
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
	iter->next = nodePtr;
	nodePtr->previous = iter;
	nodePtr->next = tempPtr;

}

template<class T> 
void Thing2<T>::deleteval()
{
	if(!iter->next){
		Thing1<T>::tail = Thing1<T>::tail->previous;
		Thing1<T>::tail->next = nullptr;

		delete iter;
		iter = Thing1<T>::head;
	}
	else{
		ListNode<T>* nodePtr;
		ListNode<T>* previousNode;

		previousNode = iter->previous;
		nodePtr = iter->next;
		previousNode->next = nodePtr;
		nodePtr->previous = previousNode;
		delete iter;
		iter = Thing1<T>::head;
	}
}

#endif
