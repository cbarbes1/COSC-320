#ifndef THING1_H
#define THING1_H

#include <iostream>

using namespace std;

template<class T>
class ListNode{
	public:
		T value;
		ListNode* next;
		ListNode* previous;
		ListNode(){
			next = nullptr;
			previous = nullptr;
		}
};


template<class T>
class Thing1{
	protected:
		ListNode* head;
		ListNode* tail;
	public:
		Thing1();
		~Thing1();
		void pushback(T);
		T popback();
		void pushfront(T);
		T popfront();
		int size();
		void clear();
		void printforward(bool print = false);
		void printbackward(bool print = false);
		bool find(T);
		int findpos(T);
		bool isempty();
		T getValue(int);
		void setValue(int, T);
		friend ostream& operator<<(ostream&, Thing1&);
};

Thing1::Thing1()
{
	head = nullptr;
	tail = nullptr;
}

~Thing1::Thing1()
{
	clear();
}

template<class T>
void pushback(T var)
{
	ListNode* tempNode = new ListNode();
	tempNode.value = var;
	if(!head){
		head = tempNode;
	}
	else{
		tail->next = tempNode;
		tail->previous = tail;
		tail = tempNode;
	}
}

template<class T>
T popback()
{
	if(!head){
		return new T();
	}
	else{
		T temp = tail->value;
		ListNode* tempNode = tail;
		tail = tail.previous;
		delete tempNode;
	}
}

template<class T>
void pushfront(T var)
{
	if(!head){
		head = new ListNode(var);
	}
	else{
		ListNode* tempNode = new ListNode(var);
		tempNode->next = head;
		head->previous = tempNode;
		head = tempNode;
	}
}

template<class T>
T popfront()
{
	if(!head){
		return new T();
	}
	else{
		ListNode* tempNode = head->next;
		T temp = head->value;
		delete head;
		return temp;
	}
}

int size()
{
	int count;

	ListNode* nodePtr = head;

	while(nodePtr){
		count++;
		nodePtr = nodePtr->next;
	}

	return count;
}

void clear()
{
	ListNode* nodePtr = head;
	ListNode* nextNode = head->next;

	while(nodePtr){
		delete nodePtr;
		nodePtr = nextNode;
		nextNode = nodePtr->next;
	}

}

void printforward(bool print)
{
	
}

void printbackward(bool print)
{

}

template<class T>
bool find(T val)
{

}

template<class T>
int findpos(T val)
{

}

bool isempty()
{

}

template<class T>
T getValue(int pos)
{

}

template<class T>
void setValue(int pos, T var)
{

}

ostream& operator<<(ostream& strm, Thing1& output)
{

}
