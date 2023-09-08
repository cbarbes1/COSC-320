/***************************************************************************************
* Author: Cole Barbes
* Creation Date: 09/03/23
* Last Update: 09/07/23
* Description: This file contains 2 classes to implement a Linked List.
* Notes: Linked Lists are interesting logically because it makes sense to the brain
 ***************************************************************************************/
#ifndef THING1_H
#define THING1_H

#include <iostream>

using namespace std;

// List Node structure to create nodes
template<class T>
class ListNode{
	public:
		T value; // templated value for the node
		ListNode<T>* next; // next pointer
		ListNode<T>* previous; // previous pointer
		ListNode(){
			next = nullptr;
			previous = nullptr;
		}
};

// class structure to implement the linked list
template<class T>
class Thing1{
	protected:
		ListNode<T>* head; // head pointer
		ListNode<T>* tail; // tail pointer
	public:
		Thing1(); // constructor
		~Thing1(); // destructor
		// push value to the end of list
		void pushback(T); 
		// pop value from the back
		T popback();
		// push value to the front of the list
		void pushfront(T);
		// pop value from the front
		T popfront();
		// return the size of the list
		int size();
		// clear the nodes from the list
		void clear();
		// print forward and backward
		void printforward(bool print = false);
		void printbackward(bool print = false);
		
		// find the value
		bool find(T);  
		int findpos(T);

		bool isempty(); // whether list is empty

		// setter and getter
		T getValue(int);
		void setValue(int, T);

		// friend output stream overload
		template<class C>
		friend ostream& operator<<(ostream&, Thing1<C>&);
};


/********************************************************************
 * Constructor
 ********************************************************************/
template<class T>
Thing1<T>::Thing1()
{
	head = nullptr;
	tail = nullptr;
}

/**
 * Deconstructor
 **/
template<class T>
Thing1<T>::~Thing1()
{
	clear();
}

/**
 * Description: Insert value at the end of the list
 * Parameters: Templated value for the node
 */
template<class T>
void Thing1<T>::pushback(T var)
{
	// create the node
	ListNode<T>* tempNode = new ListNode<T>();
	tempNode->value = var;

	if(!head){ // if empty fill it 
		head = tempNode;
		tail = tempNode;
	}
	else{ // otherwise add the new node to the end	
		tail->next = tempNode;
		tempNode->previous = tail;
		tail = tempNode;
		tail->next = nullptr;
	}
}
/*
 * Description: Delete the last node
 * Return: Return the Value being deleted
 */
template<class T>
T Thing1<T>::popback()
{
	if(!head){ // if empty send back default value
		T temp = T();
		return temp;
	}
	else{ // else Remove the node and return it
		T temp = tail->value;
		ListNode<T>* tempNode = tail;
		tail = tail->previous;
		delete tempNode;
		tail->next = nullptr;
		return temp;
	}
}
/*
 * Description: Insert value in the front of the list
 * Parameters: The value being inserted
 */
template<class T>
void Thing1<T>::pushfront(T var)
{
	if(!head){ // if empty place value at the head
		head->value = var;
		
	}
	else{ // push the value to the front shifting the head to it
		ListNode<T>* tempNode = new ListNode<T>();
		tempNode->value = var;
		tempNode->next = head;
		head->previous = tempNode;
		head = tempNode;
	}
}

/* Description: Delete the value in the front of the list and return it
 * Return: The templated value 
 */
template<class T>
T Thing1<T>::popfront()
{
	if(!head){ // if empry return default value
		T temp = T();
		return temp;
	}
	else{ // remove node and return the value
		ListNode<T>* tempNode = head;
		T temp = head->value;
		head = head->next;
		delete tempNode;
		if(!head){
			tail = nullptr;
		}
		return temp;
	}
}

/* Description: Get the size of the list
 * Return: the integer size 
 */
template<class T>
int Thing1<T>::size()
{
	int count = 0;

	// create temp node pointer to start traversal
	ListNode<T>* nodePtr = head;

	while(nodePtr){ // while nodes left, count nodes
		count++;
		nodePtr = nodePtr->next;
	}

	return count;
}

/* Description: Clear the list of all nodes and delete the memory
 * Notes: This can be used to descruct the list
 */
template<class T>
void Thing1<T>::clear()
{
	// set up the traversal pointer
	ListNode<T>* nodePtr = head;
	ListNode<T>* tempPtr;

	while(nodePtr){ // if more nodes traverse farther
		tempPtr = nodePtr->next;
		delete nodePtr;
		nodePtr = tempPtr;
	}

	head = nullptr;
	tail = nullptr;

}

/* Description: Print the list in forward order
 * Parameters: Boolean Value true print line by line false print on one line
 */
template<class T>
void Thing1<T>::printforward(bool print)
{
	ListNode<T>* nodePtr = head;

	while(nodePtr){
		if(print){
			cout<<nodePtr->value<<endl;
		}
		else{
			cout<<nodePtr->value<<" ";
		}
		nodePtr = nodePtr->next;
	}

	cout<<endl;
	
}

/* Description: Print the list in backward order
 * Parameters: Boolean value true print on seperate lines and false print on one line
 */
template<class T>
void Thing1<T>::printbackward(bool print)
{
	// set the pointer to the back for traversing
	ListNode<T>* nodePtr = tail;

	while(nodePtr){ // while nodes print
		if(print){ // seperate lines
			cout<<nodePtr->value<<endl;
		}
		else{ // individual lines
			cout<<nodePtr->value<<" ";
		}
		nodePtr = nodePtr->previous;
	}

	cout<<endl;

}

/* Description: Find the node with the given value if in the list return true
 * Parameters: Templated value 
 * return: boolean value
 */
template<class T>
bool Thing1<T>::find(T val)
{
	// pointer to traverse with starting at the head
	ListNode<T>* nodePtr = head;

	while(nodePtr->value != val && nodePtr != tail){ // if value isn't found or tail isn't reached 
		nodePtr = nodePtr->next;
	}

	return nodePtr->value == val;

}


/* Description: Find the node with the given value and return the indices
 * Parameters: Templated value
 * Return: the integer position
 */
template<class T>
int Thing1<T>::findpos(T val)
{
	// create the pointer for traversal
	ListNode<T>* nodePtr = head;

	int count = 0; // create the count 

	while(nodePtr->value != val && nodePtr != tail){ // while the value isn't reached or the tail isnt reached
		nodePtr = nodePtr->next;
		count++; // count the number of nodes
	}

	if(nodePtr->value==val){ // if its the value then return the count
		return count;
	}
	else {
		return -1;
	}

}

/* Description: find out if the list is empty
 * Return: boolean whether the list is empty true 
 */
template<class T>
bool Thing1<T>::isempty()
{
	return (!head);
}


/* Description: Get the value in the indicated position
 * Parameters: The indices
 * Return: The value
 */
template<class T>
T Thing1<T>::getValue(int pos)
{
	int count = 0;

	// create the node to use when traversing
	ListNode<T>* nodePtr = head;

	while(nodePtr && count != pos){ // while the node is valid and the count hasnt reached the position
		nodePtr = nodePtr->next;
		count++;
	}

	// if count reached the position return the value
	if(count == pos){
		return nodePtr->value;
	}

	else {
		T temp = T();
		return temp;
	}
}


/* Description: set the value of a node at a given position
 * Parameters: The position and the Templated value
 */
template<class T>
void Thing1<T>::setValue(int pos, T var)
{
	int count = 0;

	// create the node to traverse the list with 
	ListNode<T>* nodePtr = head;

	while(nodePtr && count != pos){ // while valid or position is not reached then count
		nodePtr = nodePtr->next;
		count++;
	}

	// if position was reached then set the value at current node
	if(count == pos){
		nodePtr->value = var;
	}

}


/* Description: Overloaded out stream operator
 * Parameters: The stream and the output thing
 */
template<class T>
ostream& operator<<(ostream& strm, Thing1<T> &output)
{
	// Set the pointer to the head 
	ListNode<T>* nodePtr = output.head;

	while(nodePtr){ // while valid node keep traversing
		strm<<nodePtr->value<<" ";
		nodePtr = nodePtr->next;
	}

	return strm;
}


#endif
