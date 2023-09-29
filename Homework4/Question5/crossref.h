/* Created By: Cole Barbes
 * Creation date: 09/29/23
 * Purpose: Implements a cross reference
 */
#ifndef CROSSREF_H
#define CROSSREF_H

#include <iostream>
#include "BST.h"
#include <fstream>
#include <string>

using namespace std;

//*********************************************
// The ListNode class creates a type used to  *
// store a node of the linked list.           *
//*********************************************

template<class T>
class ListNode {
public:
	T value;           // Node value
	ListNode<T> *next; // Pointer to the next node

	// Constructor
	ListNode(T nodeValue) {
		value = nodeValue;
		next = nullptr;
	}
};

//*********************************************
// crossrefNode class                           *
//*********************************************

template<class T>
class crossrefNode {
private:
	ListNode<T> *head;   // List head pointer

public:

	string value;
	crossrefNode<T> *left;
	crossrefNode<T> *right;

	// Constructor
	crossrefNode();

	// Destructor
	~crossrefNode();

	// Linked list operations
	void appendNode(T);
	void insertNode(T);
	void deleteNode(T);
	void displayList() const;
    void setWord(string);
    string getWord();

};

//**************************************************
// Constructor for the linked list class           *
//**************************************************
template<class T>
crossrefNode<T>::crossrefNode() {
		head = nullptr;
		left = nullptr;
		right = nullptr;
}

//**************************************************
// appendNode appends a node containing the value  *
// pased into newValue, to the end of the list.    *
//**************************************************

template<class T>
void crossrefNode<T>::appendNode(T newValue) {
	ListNode<T> *newNode;  // To point to a new node
	ListNode<T> *nodePtr;  // To move through the list

	// Allocate a new node and store newValue there.
	newNode = new ListNode<T>(newValue);

	// If there are no nodes in the list
	// make newNode the first node.
	if (!head)
		head = newNode;
	else  // Otherwise, insert newNode at end.
	{
		// Initialize nodePtr to head of list.
		nodePtr = head;

		// Find the last node in the list.
		while (nodePtr->next){
			nodePtr = nodePtr->next;
		}
		// Insert newNode as the last node.
		nodePtr->next = newNode;
	}
}

//**************************************************
// displayList shows the value stored in each node *
// of the linked list pointed to by head.          *
//**************************************************

template<class T>
void crossrefNode<T>::displayList() const {
	ListNode<T> *nodePtr;  // To move through the list

	// Position nodePtr at the head of the list.
	nodePtr = head;
	// While nodePtr points to a node, traverse
	// the list.
	while (nodePtr) {
		// Display the value in this node.
		cout<<nodePtr->value<< " ";

		// Move to the next node.
		nodePtr = nodePtr->next;
	}
}

//**************************************************
// The insertNode function inserts a node with     *
// newValue copied to its value member.            *
//**************************************************

template<class T>
void crossrefNode<T>::insertNode(T newValue) {
	ListNode<T> *newNode;				// A new node
	ListNode<T> *nodePtr;				// To traverse the list
	ListNode<T> *previousNode = nullptr; // The previous node

	// Allocate a new node and store newValue there.
	newNode = new ListNode<T>(newValue);

	// If there are no nodes in the list
	// make newNode the first node
	if (!head) {
		head = newNode;
		newNode->next = nullptr;
	} else  // Otherwise, insert newNode
	{
		// Position nodePtr at the head of list.
		nodePtr = head;

		// Initialize previousNode to nullptr.
		previousNode = nullptr;

		// Skip all nodes whose value is less than newValue.
		while (nodePtr != nullptr && nodePtr->value < newValue) {
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		// If the new node is to be the 1st in the list,
		// insert it before all other nodes.
		if (previousNode == nullptr) {
			head = newNode;
			newNode->next = nodePtr;
		} else  // Otherwise insert after the previous node.
		{
			previousNode->next = newNode;
			newNode->next = nodePtr;
		}
	}
}

//*****************************************************
// The deleteNode function searches for a node        *
// with searchValue as its value. The node, if found, *
// is deleted from the list and from memory.          *
//*****************************************************

template<class T>
void crossrefNode<T>::deleteNode(T searchValue) {
	ListNode<T> *nodePtr;       // To traverse the list
	ListNode<T> *previousNode;  // To point to the previous node

	// If the list is empty, do nothing.
	if (!head)
		return;

	// Determine if the first node is the one.
	if (head->value == searchValue) {
		nodePtr = head->next;
		delete head;
		head = nodePtr;
	} else {
		// Initialize nodePtr to head of list
		nodePtr = head;

		// Skip all nodes whose value member is
		// not equal to num.
		while (nodePtr != nullptr && nodePtr->value != searchValue) {
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		// If nodePtr is not at the end of the list,
		// link the previous node to the node after
		// nodePtr, then delete nodePtr.
		if (nodePtr) {
			previousNode->next = nodePtr->next;
			delete nodePtr;
		}
	}
}

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
//**************************************************

template<class T>
crossrefNode<T>::~crossrefNode() {
	ListNode<T> *nodePtr;   // To traverse the list
	ListNode<T> *nextNode;  // To point to the next node

	// Position nodePtr at the head of the list.
	nodePtr = head;

	// While nodePtr is not at the end of the list...
	while (nodePtr != nullptr) {
		// Save a pointer to the next node.
		nextNode = nodePtr->next;

		// Delete the current node.
		delete nodePtr;

		// Position nodePtr at the next node.
		nodePtr = nextNode;
	}
}

/*
 * Set the word to the given string value
 * parameters: string value
 */
template<class T>
void crossrefNode<T>::setWord(string w)
{
	value = w;
}

/*
 * return the private data member word
 */
template<class T>
string crossrefNode<T>::getWord()
{
    return value;
}

// end of new node type

// cross reference class inherited off the binary search tree implementing its own node
class crossref : public BST<string, crossrefNode<int>> {
private:
	void printDataBaseRec(crossrefNode<int>*);
public: 
	crossref(string FileName);
	virtual ~crossref();

	void insert(string, int);
	void printDataBase(){
		printDataBaseRec(this->root);
	}
};

#endif  
