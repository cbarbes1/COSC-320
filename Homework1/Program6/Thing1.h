#ifndef THING1_H
#define THING1_H

#include <iostream>

using namespace std;

template<class T>
class ListNode{
	public:
		T value;
		ListNode<T>* next;
		ListNode<T>* previous;
		ListNode(){
			next = nullptr;
			previous = nullptr;
		}
};


template<class T>
class Thing1{
	protected:
		ListNode<T>* head;
		ListNode<T>* tail;
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
		template<class C>
		friend ostream& operator<<(ostream&, Thing1<C>&);
};

template<class T>
Thing1<T>::Thing1()
{
head = nullptr;
tail = nullptr;
}

template<class T>
Thing1<T>::~Thing1()
{
clear();
}

template<class T>
void Thing1<T>::pushback(T var)
{
	ListNode<T>* tempNode = new ListNode<T>();
	tempNode->value = var;

	if(!head){
		head = tempNode;
		tail = tempNode;
	}
	else{	
		tail->next = tempNode;
		tempNode->previous = tail;
		tail = tempNode;
	}
}

template<class T>
T Thing1<T>::popback()
{
	if(!head){
		T temp;
		return temp;
	}
	else{
		T temp = tail->value;
		ListNode<T>* tempNode = tail;
		tail = tail->previous;
		delete tempNode;
		tail->next = nullptr;
		return temp;
	}
}

template<class T>
void Thing1<T>::pushfront(T var)
{
	if(!head){
		head = new ListNode<T>(var);
	}
	else{
		ListNode<T>* tempNode = new ListNode<T>(var);
		tempNode->next = head;
		head->previous = tempNode;
		head = tempNode;
	}
}

template<class T>
T Thing1<T>::popfront()
{
	if(!head){
		T temp;
		return temp;
	}
	else{
		ListNode<T>* tempNode = head->next;
		T temp = head->value;
		delete head;
		head = tempNode;
		return temp;
	}
}

template<class T>
int Thing1<T>::size()
{
	int count = 0;

	ListNode<T>* nodePtr = head;

	while(nodePtr){
		count++;
		nodePtr = nodePtr->next;
	}

	return count;
}

template<class T>
void Thing1<T>::clear()
{
	ListNode<T>* nodePtr = head;
	ListNode<T>* tempPtr;
	while(nodePtr){
		tempPtr = nodePtr->next;
		delete nodePtr;
		nodePtr = tempPtr;
	}

}

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

template<class T>
void Thing1<T>::printbackward(bool print)
{
	ListNode<T>* nodePtr = tail;

	while(nodePtr){
		if(print){
			cout<<nodePtr->value<<endl;
		}
		else{
			cout<<nodePtr->value<<" ";
		}
		nodePtr = nodePtr->previous;
	}

	cout<<endl;

}

template<class T>
bool Thing1<T>::find(T val)
{
	ListNode<T>* nodePtr = head;

	while(nodePtr->value != val && nodePtr != tail){
		nodePtr = nodePtr->next;
	}
	return nodePtr->value == val;
	
}

template<class T>
int Thing1<T>::findpos(T val)
{
	ListNode<T>* nodePtr = head;

	int count = 0;

	while(nodePtr->value != val && nodePtr != tail){
		nodePtr = nodePtr->next;
		count++;
	}
	if(nodePtr->value==val){
		return count;
	}
	else {
		return -1;
	}

}

template<class T>
bool Thing1<T>::isempty()
{
	return (!head);
}

template<class T>
T Thing1<T>::getValue(int pos)
{
	int count = 0;

	ListNode<T>* nodePtr = head;

	while(nodePtr && count != pos){
		nodePtr = nodePtr->next;
		count++;
	}


	if(count == pos){
		return nodePtr->value;
	}

	else {
		T temp;
		return temp;
	}
}

template<class T>
void Thing1<T>::setValue(int pos, T var)
{
	int count = 0;

	ListNode<T>* nodePtr = head;

	while(nodePtr && count != pos){
		nodePtr = nodePtr->next;
		count++;
	}

	if(count == pos){
		nodePtr->value = var;
	}

}

template<class T>
ostream& operator<<(ostream& strm, Thing1<T> &output)
{
	ListNode<T>* nodePtr = output.head;

	while(nodePtr){
		strm<<nodePtr->value<<" ";
		nodePtr = nodePtr->next;
	}

	return strm;
}


#endif
