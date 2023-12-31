/******************************************************************************************************
 * Authors: Cole Barbes
 * Creation Date: 10/18/23
 * Last Edited: 11/2/23
 * Description: implementation of a multiset class similar to the stl multiset
******************************************************************************************************/
#ifndef SET_H
#define SET_H

#include <iostream>
#include <vector>
#include "RBTree.h"

using namespace std;

// multiset class declaration
template<class T>
class multiset : public RBTree<T>{
private:
    // below are all recursive private functions for use by the other functions
    void copy(RBTreeNode<T>*, RBTreeNode<T>*&, RBTreeNode<T>*, RBTreeNode<T> *NilPtr);

    // in order recursive functions
    ostream& InOrderDisplay(RBTreeNode<T> *, ostream&, int&);
    void InOrderVector(RBTreeNode<T>*, vector<T>&);
    void InOrderArray(RBTreeNode<T>*, T [], int &n, const int);
    bool InOrderSubset(RBTreeNode<T>*, multiset<T>&);
    bool InOrderSubset(RBTreeNode<T>*, RBTreeNode<T>*);
    void InOrderInsert(RBTreeNode<T>*, multiset<T> &other);
    void InOrderErase(RBTreeNode<T>*, multiset<T> &other);
    int InOrderNumElems(RBTreeNode<T> *, int&);
    int InOrderNumElemsType(RBTreeNode<T> *, int&, T);
public:
    multiset();
    multiset(const multiset<T>&);
    virtual ~multiset();

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
    int size(); // return the size
    int count(T);
    void clear(); // clear the multiset

    // overloaded assignment operator
    multiset<T> operator=(const multiset<T>& right);
    // overloaded operators
    bool operator==(multiset<T>& right);
    bool operator!=(multiset<T>& right);
    bool operator<(multiset<T>& right);
    bool operator>(multiset<T>& right);
    bool operator<=(multiset<T>& right);
    bool operator>=(multiset<T>& right);
    multiset<T> operator+(multiset<T> right);
    multiset<T> operator-(multiset<T> right);
    multiset<T> operator*(multiset<T> right);
    template<class c>
    friend ostream& operator<<(ostream& os, multiset<c>& obj);
};

/*
 * empty constructor
 */
template<class T>
multiset<T>::multiset()
{
}

/*
 * destructor which has no purpose
 */
template<class T>
multiset<T>::~multiset()
{
}

/*
 * copy constructor for the multiset
 * parameters: the right multiset
 */
template<class T>
multiset<T>::multiset(const multiset<T> &right)
{
    // call copy recursive function
    copy(right.RBTree<T>::root, RBTree<T>::root, RBTree<T>::NIL, right.RBTree<T>::NIL);
}

/*
 * copy each node recursively in a sub tree pointed to by nodePtr
 * parameters: the node of the other subtree, the next node of the next subtree, the parent of this subtree, the nil of the other tree
 */
template<class T>
void multiset<T>::copy(RBTreeNode<T> *nodePtr, RBTreeNode<T> *&next, RBTreeNode<T> *parent, RBTreeNode<T> *NilPtr)
{
    // if the nil is encountered stop the copy process
    if(nodePtr != NilPtr){
        next = new RBTreeNode<T>(nodePtr->value, nodePtr->color, RBTree<T>::NIL, RBTree<T>::NIL, parent);
        copy(nodePtr->left, next->left, next, NilPtr);
        copy(nodePtr->right, next->right, next, NilPtr);
    }
}

/*
 * display the multiset in InOrder
 * parameters: the subtree pointer, the outstream var by reference
 * return the stream
 */
template<class T>
ostream& multiset<T>::InOrderDisplay(RBTreeNode<T> *nodePtr, ostream &strm, int &count)
{
    // if nil end the print process
    // call left and right display
    if(nodePtr != RBTree<T>::NIL){
        InOrderDisplay(nodePtr->left, strm, count);
        strm<<nodePtr->value;
        if(count!=(size()-1)){ // if the end is reached then dont print the last ,
            strm<<", ";
            count++;
        }
        InOrderDisplay(nodePtr->right, strm, count);
    }
    return strm;
}

/*
 * insert the multiset into a vector using an in order traversal
 * paremeters: the node of the subtree, the vector
 */
template<class T>
void multiset<T>::InOrderVector(RBTreeNode<T> *nodePtr, vector<T>& vect)
{
    // if nil is encountered then stop
    if(nodePtr != RBTree<T>::NIL){
        InOrderVector(nodePtr->left, vect);
        vect.push_back(nodePtr->value);
        InOrderVector(nodePtr->right, vect);
    }
}

/*
 * insert the multiset into an array using an in order traversal
 * parameters: the node of the subtree, the array, the number of elements that have been inserted, the size of the array
 */
template<class T>
void multiset<T>::InOrderArray(RBTreeNode<T> *nodePtr, T arr[], int &n, const int size)
{
    if(nodePtr != RBTree<T>::NIL && n<size){
        InOrderArray(nodePtr->left, arr, n, size);
        arr[n++] = nodePtr->value;
        InOrderArray(nodePtr->right, arr, n, size);
    }
}

/*
 * check if A is a submultiset of B
 * parameters: node of the subtree, the other multiset which is being compared to
 * return whether this is a subset of the other
 */
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

/*
 * check if A is a subset of B
 * parameters: the pointer to the other multiset node, and the nil of that multiset
 * return whether this A is a subset of B
 */
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

/*
 * insert the multiset into a another using an in order traversal
 * parameters: the node and the other multiset
 */
template<class T>
void multiset<T>::InOrderInsert(RBTreeNode<T> *nodePtr, multiset<T> &other)
{
    if(nodePtr != RBTree<T>::NIL && other.count(nodePtr->value) != count(nodePtr->value)){
        InOrderInsert(nodePtr->left, other);
        if(other.count(nodePtr->value) < count(nodePtr->value))
            other.insert(nodePtr->value);
        InOrderInsert(nodePtr->right, other);
    }
}

/*
 * insert the multiset into a vector using an in order traversal
 * parameters: the node of this multiset and the other multiset being erased from
 */
template<class T>
void multiset<T>::InOrderErase(RBTreeNode<T> *nodePtr, multiset<T> &other)
{
    if(nodePtr != RBTree<T>::NIL){
        InOrderErase(nodePtr->left, other);
        other.erase(nodePtr->value);
        InOrderErase(nodePtr->right, other);
    }
}

template<class T>
int multiset<T>::InOrderNumElems(RBTreeNode<T> *nodePtr, int &count)
{
    if(nodePtr != RBTree<T>::NIL){
        InOrderNumElems(nodePtr->left, count);
        count++;
        InOrderNumElems(nodePtr->right, count);
    }
    return count;
}

template<class T>
int multiset<T>::InOrderNumElemsType(RBTreeNode<T> *nodePtr, int &count, T val)
{
    if(nodePtr != RBTree<T>::NIL){
        InOrderNumElemsType(nodePtr->left, count, val);
        if(val == nodePtr->value)
            count++;
        InOrderNumElemsType(nodePtr->right, count, val);
    }
    return count;
}


/*
 * overload the assignment operator
 * parameters: the right multiset
 * return the multiset
 */
template<class T>
multiset<T> multiset<T>::operator=(const multiset<T>& right)
{
    clear();
    copy(right.RBTree<T>::root, RBTree<T>::root, RBTree<T>::NIL, right.RBTree<T>::NIL);
    return *this;
}

/*
 * return the size of the multiset
 */
template<class T>
int multiset<T>::size()
{
    int size = 0;

    InOrderNumElems(RBTree<T>::root, size);

    return size;
}

/*
 * return the frequency of a particular number
 */
template<class T>
int multiset<T>::count(T val)
{
    int count = 0;

    InOrderNumElemsType(RBTree<T>::root, count, val);

    return count;
}

/*
 * clear the multiset
 */
template<class T>
void multiset<T>::clear()
{
    RBTree<T>::destroySubTree(RBTree<T>::root);
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

// overload the == operator
template<class T>
bool multiset<T>::operator==(multiset<T>& right)
{
    return InOrderSubset(RBTree<T>::root, right) && InOrderSubset(right.RBTree<T>::root, right.RBTree<T>::NIL);
}

// overload the != operator
template<class T>
bool multiset<T>::operator!=(multiset<T>& right)
{
    return !(InOrderSubset(RBTree<T>::root, right) && InOrderSubset(right.RBTree<T>::root, right.RBTree<T>::NIL));
}

// overload the < operator
template<class T>
bool multiset<T>::operator<(multiset<T>& right)
{
    return InOrderSubset(RBTree<T>::root, right) && !(InOrderSubset(right.RBTree<T>::root, right.RBTree<T>::NIL));
}

// overload the > operator
template<class T>
bool multiset<T>::operator>(multiset<T>& right)
{
    return InOrderSubset(right.RBTree<T>::root, right.RBTree<T>::NIL) && !(InOrderSubset(RBTree<T>::root, right));
}

// overload the <= operator
template<class T>
bool multiset<T>::operator<=(multiset<T>& right)
{
    return InOrderSubset(RBTree<T>::root, right);
}

// overload the >= operator
template<class T>
bool multiset<T>::operator>=(multiset<T>& right)
{
    return InOrderSubset(right.RBTree<T>::root, right.RBTree<T>::NIL);
}

// overload the + operator
template<class T>
multiset<T> multiset<T>::operator+(multiset<T> right)
{
    multiset<T> temp(*this);
    right.InOrderInsert(right.RBTree<T>::root, temp);
    return temp;
}

// overload the - operator
template<class T>
multiset<T> multiset<T>::operator-(multiset<T> right)
{
    multiset<T> temp(*this);

    right.InOrderErase(right.RBTree<T>::root, temp);

    return temp;
}

// overload the * operator
template<class T>
multiset<T> multiset<T>::operator*(multiset<T> right)
{
    multiset<T> temp((*this + right) - ((*this - right)+(right - *this)));
    return temp;
}

// overload the << operator
template<class T>
ostream& operator<<(ostream& os, multiset<T>& obj)
{
    os<<"{ ";
    int count = 0;
    // call in order display with the count var
    obj.InOrderDisplay(obj.RBTree<T>::root, os, count);
    os<<" }\n";
    return os;
}


#endif // end of the declaration and implementation of multimultiset class
    
