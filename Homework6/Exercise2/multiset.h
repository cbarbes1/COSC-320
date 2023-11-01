/******************************************************************************************************
 * Authors: Cole Barbes and Harrison Colborne
 * Creation Date: 10/18/23
 * Last Edited: 10/18/23

 * Description: implementation of a multiset class similar to the stl multiset 
******************************************************************************************************/
#ifndef MULTISET_H
#define MULTISET_H

#include <iostream>
#include <vector>
#include "RBTree.h"

using namespace std;

// multiset class declaration
template<class T>
class multiset : public RBTree<T>{
private:
    void copy(RBTreeNode<T>*, RBTreeNode<T>*&, RBTreeNode<T>*, RBTreeNode<T> *NilPtr);
    ostream& InOrderDisplay(RBTreeNode<T> *, ostream&);
    void InOrderVector(RBTreeNode<T>*, vector<T>&);
    void InOrderArray(RBTreeNode<T>*, T [], int &n, const int);

    bool InOrderSubset(RBTreeNode<T>*, multiset<T>&);
    bool InOrderSubset(RBTreeNode<T>*, RBTreeNode<T>*);
    
    void InOrdercount(RBTreeNode<T>*, T, int &);
public:
    multiset();
    multiset(const multiset<T>&);
    ~multiset();
    
    // insert a value into the multiset
    void insert(T);
    // find a value 
    bool find(T);
    //erase a value from the multiset
    void erase(T);
    // empty function to check if empty
    bool empty();
    // convert the multiset to a vector
    void toVector(vector<T>&);
    // convert the multiset to an array
    void toArray(T arr[], const int size);
    
    int size();
    
    void clear();
    
    int count(T);

    // overloaded assignment operator
    multiset<T> operator=(const multiset<T>& right);

    bool operator==(multiset<T>& right);

    bool operator!=(multiset<T>& right);

    bool operator<(multiset<T>& right);

    bool operator>(multiset<T>& right);

    bool operator<=(multiset<T>& right);

    bool operator>=(multiset<T>& right);

    multiset<T> operator+(multiset<T>& right);

    multiset<T> operator-(multiset<T>& right);
    
    multiset<T> operator*(multiset<T>& right);

    template<class c>
    friend ostream& operator<<(ostream& os, multiset<c>& obj);
    
    
};
    
template<class T>
multiset<T>::multiset()
{
}

template<class T>
multiset<T>::~multiset()
{
    clear();
}


/*
 * copy each node recursively in a sub tree pointed to by nodePtr
 */
template<class T>
void multiset<T>::copy(RBTreeNode<T> *nodePtr, RBTreeNode<T> *&next, RBTreeNode<T> *parent, RBTreeNode<T> *NilPtr)
{
    if(nodePtr != NilPtr){
        next = new RBTreeNode<T>(nodePtr->value, nodePtr->color, RBTree<T>::NIL, RBTree<T>::NIL, parent);
        copy(nodePtr->left, next->left, next, NilPtr);
        copy(nodePtr->right, next->right, next, NilPtr);
    }
}

template<class T>
ostream& multiset<T>::InOrderDisplay(RBTreeNode<T> *nodePtr, ostream &strm)
{
    if(nodePtr != RBTree<T>::NIL){
        InOrderDisplay(nodePtr->left, strm);
        strm<<nodePtr->value;
        InOrderDisplay(nodePtr->right, strm);
    }
    return strm;
}

template<class T>
void multiset<T>::InOrderVector(RBTreeNode<T> *nodePtr, vector<T>& vect)
{
    if(nodePtr != RBTree<T>::NIL){
        InOrderVector(nodePtr->left, vect);
        vect.push_back(nodePtr->value);
        InOrderVector(nodePtr->right, vect);
    }
}

template<class T>
void multiset<T>::InOrderArray(RBTreeNode<T> *nodePtr, T arr[], int &n, const int size)
{
    if(nodePtr != RBTree<T>::NIL && n<size){
        InOrderArray(nodePtr->left, arr, n, size);
        arr[n++] = nodePtr->value;
        InOrderArray(nodePtr->right, arr, n, size);
    }
}

template<class T>
bool multiset<T>::InOrderSubset(RBTreeNode<T> *nodePtr, multiset<T> &other)
{
    if(nodePtr != RBTree<T>::NIL){
        bool left = InOrderSubset(nodePtr->left, other);
        bool right = InOrderSubset(nodePtr->right, other);
        return (other.RBTree<T>::find(nodePtr->value) && left && right);
    }
    return true;
}

template<class T>
bool multiset<T>::InOrderSubset(RBTreeNode<T> *nodePtr, RBTreeNode<T> *nilPtr)
{
    if(nodePtr != nilPtr){
        bool left = InOrderSubset(nodePtr->left, nilPtr);
        bool right = InOrderSubset(nodePtr->right, nilPtr);
        return (RBTree<T>::find(nodePtr->value) && left && right);
    }
    return true;
}

template<class T>
void multiset<T>::InOrdercount(RBTreeNode<T> *nodePtr, T val, int &count)
{
    if(nodePtr != RBTree<T>::NIL){
        InOrdercount(nodePtr->left, val, count);
        if(nodePtr->value == val)
            count++;
        InOrdercount(nodePtr->right, val, count);
    }
}


/*
 * overload the assignment operator
 */
template<class T>
multiset<T> multiset<T>::operator=(const multiset<T>& right)
{
    RBTree<T>::destroySubTree(RBTree<T>::root);
    copy(right.RBTree<T>::root, RBTree<T>::root, RBTree<T>::NIL, right.RBTree<T>::NIL);
}

template<class T>
int multiset<T>::size()
{
    vector<T> V;
    toVector(V);
    
    int size = V.size();
    
    return size;
}

template<class T>
void multiset<T>::clear()
{
    vector<T> V;
    toVector(V);
    
    for(unsigned int i = 0; i<V.size(); i++)
        erase(V[i]);
}

template<class T>
int multiset<T>::count(T val)
{
    if(RBTree<T>::root == RBTree<T>::NIL)
        return 0;
    int count = 0;
    InOrdercount(RBTree<T>::root, val, count);
    return count;
}



template<class T>
multiset<T>::multiset(const multiset<T> &right)
{
    copy(right.RBTree<T>::root, RBTree<T>::root, RBTree<T>::NIL, right.RBTree<T>::NIL);
}


/*
 * Description: Insert function which calls the addElement function and only adds a non copy function
 * Parameters: item to be added
 */
template<class T>
void multiset<T>::insert(T val)
{
    RBTreeNode<T> *newnode = new RBTreeNode<T>(val, RED, RBTree<T>::NIL, RBTree<T>::NIL, RBTree<T>::NIL);
	RBTreeNode<T> *y = RBTree<T>::NIL;
	RBTreeNode<T> *x = RBTree<T>::root;

	while (x != RBTree<T>::NIL) {
		y = x;
		if (val < x->value)
			x = x->left;
		else
			x = x->right;
	}

	newnode->parent = y;
	if (y == RBTree<T>::NIL)
		RBTree<T>::root = newnode;
	else if (newnode->value < y->value)
		y->left = newnode;
	else if(newnode->value >= y->value)
		y->right = newnode;

	//  Adjust the RB tree to retain the properties.
    // if the value is not in the tree insert it
    RBTree<T>::insertFix(newnode);
}


/*
 * Find a value in the multiset
 */
template<class T>
bool multiset<T>::find(T item)
{
    return RBTree<T>::find(item);
}


/*
 * Erase a value from the tree
 */
template<class T>
void multiset<T>::erase(T val)
{
    RBTreeNode<T> *z = RBTree<T>::findNode(val);
	if (z == RBTree<T>::NIL)
		return;

	RBTreeNode<T> *y = z;
	RBTreeNode<T> *x = RBTree<T>::NIL;
	color_t yorigcol = y->color;

	if (z->left == RBTree<T>::NIL) {
		x = z->right;
		RBTree<T>::transplant(z, z->right);
	} else if (z->right == RBTree<T>::NIL) {
		x = z->left;
		RBTree<T>::transplant(z, z->left);
	} else {
		y = RBTree<T>::getMinNode(z->right);
		yorigcol = y->color;
		x = y->right;
		if (y->parent == z)
			x->parent = y;
		else {
			RBTree<T>::transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		RBTree<T>::transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	delete z;
	if (yorigcol == BLACK)
		RBTree<T>::deleteFix(x);
}

// empty function to check if empty
template<class T>
bool multiset<T>::empty()
{
    bool checker = false;

    if(RBTree<T>::root == RBTree<T>::NIL)
        checker = true;

    return checker;
}

// convert the multiset to a vector
template<class T>
void multiset<T>::toVector(vector<T>& vect)
{
    InOrderVector(RBTree<T>::root, vect);
}

// convert the multiset to an array
template<class T>
void multiset<T>::toArray(T arr[], const int size)
{
    int n = 0;
    InOrderArray(RBTree<T>::root, arr, n,  size);
}

template<class T>
bool multiset<T>::operator==(multiset<T>& right)
{
    return InOrderSubset(RBTree<T>::root, right) && InOrderSubset(right.RBTree<T>::root, right.RBTree<T>::NIL);
}

template<class T>
bool multiset<T>::operator!=(multiset<T>& right)
{
    return !(InOrderSubmultiset(RBTree<T>::root, right) && InOrderSubset(right.RBTree<T>::root, right.RBTree<T>::NIL));
}

template<class T>
bool multiset<T>::operator<(multiset<T>& right)
{
    return InOrderSubset(RBTree<T>::root, right) && !(InOrderSubset(right.RBTree<T>::root, right.RBTree<T>::NIL));
}

template<class T>
bool multiset<T>::operator>(multiset<T>& right)
{
    return InOrderSubset(right.RBTree<T>::root, right.RBTree<T>::NIL) && !(InOrderSubset(RBTree<T>::root, right));
}

template<class T>
bool multiset<T>::operator<=(multiset<T>& right)
{
    return InOrderSubset(RBTree<T>::root, right);
}

template<class T>
bool multiset<T>::operator>=(multiset<T>& right)
{
    return InOrderSubset(right.RBTree<T>::root, right.RBTree<T>::NIL);
}


template<class T>
multiset<T> multiset<T>::operator+(multiset<T>& right)
{
    vector<T> vect1;
    toVector(vect1);
    vector<T> vect2;
    right.toVector(vect2);
    multiset<T> temp;

    for(int i = 0; i<vect1.size(); i++){
        int freq1 = count(vect1[i]);
        int freq2 = right.count(vect1[i]);
        if(freq1 >= freq2){
            temp.insert(vect1[i]);
        }
    }


    for(int i = 0; i<vect2.size(); i++){
        int freq1 = count(vect2[i]);
        int freq2 = right.count(vect2[i]);
        if(freq1 < freq2){
            temp.insert(vect2[i]);
        }
    }
    return temp;
}

template<class T>
multiset<T> multiset<T>::operator-(multiset<T>& right)
{
    vector<T> vect1;
    toVector(vect1);
    vector<T> vect2;
    right.toVector(vect2);
    multiset<T> temp;
    for(unsigned int i = 0; i<vect1.size(); i++)
        temp.insert(vect1[i]);
        
    for(unsigned int i = 0; i<vect2.size(); i++)
            temp.erase(vect2[i]);
        
    return temp;
}

template<class T>
multiset<T> multiset<T>::operator*(multiset<T>& right)
{
    multiset<T> temp;
    vector<T> vect;
    toVector(vect);
    
    for(unsigned int i = 0; i<vect.size(); i++){
        if(right.find(vect[i]) && count(vect[i]) > right.count(vect[i]))
            temp.insert(vect[i]);
    }
    
    return temp;
}

template<class T>
ostream& operator<<(ostream& os, multiset<T>& obj)
{
    os<<"{ ";
    vector<T> vect;
    obj.toVector(vect);
    for(unsigned int i = 0; i<vect.size(); i++){
        os<<vect[i];
        if(i != (vect.size() - 1))
            os<<", ";
    }
    os<<" }\n";
    return os;
}

#endif // end of the declaration and implementation of multiset class
    
