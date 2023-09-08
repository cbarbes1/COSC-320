/* Author: Cole Barbes
 * Creation Date: 09/05/23
 * Last Update: 09/07/23
 * Description: This class implements an iterator over top of the Linked list done in Thing1
 */
#ifndef THING2_H
#define THING2_H

#include "Thing1.h"

#include <iostream>

using namespace std;

// implement inherited class Thing2 of Thing1
template<class T>
class Thing2: public Thing1<T>{
	private:
		// create pointer to iterate over the list
		ListNode<T>* iter;
	public:
		// constructor and destructor
		Thing2();
		~Thing2();
		// reset iterator back and front
		void resetIteratorToFront();
		void resetIteratorToBack();
		// prefix and postfix operator overload incrementer
		void operator++();
		void operator++(int);
		void operator--();
		void operator--(int);
		// overload the incremental += and -=
		void operator+=(int);
		void operator-=(int);
		// get the value of the node pointed to by the iterator
		T get();
		// insert the value at the iterator 
		void insertval(T);
		// delete the value pointed to by the iterator
		void deleteval();
};

/*
 * Constructor
 */
template<class T> 
Thing2<T>::Thing2()
{
	iter = nullptr;
}

/*
 * Destructor
 */
template<class T>
Thing2<T>::~Thing2()
{
	Thing1<T>::clear();
}

/*
 * reset the iterator to the head
 */
template<class T>
void Thing2<T>::resetIteratorToFront()
{
	iter = Thing1<T>::head;
}

/*
 * reset the iterator to the tail
 */
template<class T>
void Thing2<T>::resetIteratorToBack()
{
	iter = Thing1<T>::tail;
}

/*
 * Increment the iterator one node down the list prefix
 */
template<class T>
void Thing2<T>::operator++()
{
	if(iter->next){
		iter = iter->next;
	}
	
}

/*
 * Increment the iterator one down the list postfix
 */
template<class T>
void Thing2<T>::operator++(int)
{
	if(iter->next){
		iter = iter->next;
	}
	
}

/*
 * decrement the iterator one up the list prefix
 */
template<class T>
void Thing2<T>::operator--()
{
	if(iter->previous){
		iter = iter->previous;
	}
}

/*
 * Decrement the iterator one up the list postfix
 */
template<class T>
void Thing2<T>::operator--(int)
{
	if(iter->previous){
		iter = iter->previous;
	}
	
}

/*
 * Increment the Iterator n nodes down the list
 * Parameters: the n number of nodes 
 */
template<class T>
void Thing2<T>::operator+=(int n)
{
	int count = 0;
	if(iter){
		while(count!=n&&iter->next){
			iter = iter->next;
			count++;
		}
	}
		
}

/*
 * Decrement the iterator n nodes up the list
 * parameters: n number of nodes
 */
template<class T>
void Thing2<T>::operator-=(int n)
{
	int count = 0;
	if(iter){
		while(count!=n&&iter->previous){
			iter = iter->previous;
			count++;
		}
	}
}

/*
 * Get the iterators value
 * Return the value of the iterator
 */
template<class T>
T Thing2<T>::get()
{
	return iter->value;
}

/*
 * Insert the value given into the list at the location after the iterator and before the next node
 * parameters: the templated value 
 */
template<class T>
void Thing2<T>::insertval(T var)
{
	// create the new node
	ListNode<T>* nodePtr = new ListNode<T>;
	// create the temporary node to hold the iterators next
	ListNode<T>* tempPtr;
	nodePtr->value = var;
	
	// set all of the needed pointers to their respective nodes
	tempPtr = iter->next;
	iter->next = nodePtr;
	nodePtr->previous = iter;
	nodePtr->next = tempPtr;

}

/* 
 * Delete the value pointed to by the iterator 
 */
template<class T> 
void Thing2<T>::deleteval()
{
	if(!iter->next){ // if theres no next node just delete
		Thing1<T>::tail = Thing1<T>::tail->previous;
		Thing1<T>::tail->next = nullptr;

		delete iter;
		iter = Thing1<T>::head;
	}
	else if(iter==Thing1<T>::head){ // if the iterator is at the head then delete the head and move forward one
		Thing1<T>::head = Thing1<T>::head->next;
		delete iter;
		iter = Thing1<T>::head;
	}
	else{ // all other cases move more memory addresses
		//create the temporary pointers
		ListNode<T>* nodePtr;
		ListNode<T>* previousNode;
		// save the previous and next node
		previousNode = iter->previous;
		nodePtr = iter->next;
		
		// set the last node next to the node before and the nexts previous to the next
		previousNode->next = nodePtr;
		nodePtr->previous = previousNode;
		//delete the  node and set the iter to the next node
		delete iter;
		iter = nodePtr;
	}
}

#endif
