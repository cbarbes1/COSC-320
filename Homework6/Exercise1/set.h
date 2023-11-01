/******************************************************************************************************
 * Authors: Cole Barbes and Harrison Colborne
 * Creation Date: 10/18/23
 * Last Edited: 10/31/23
 * Description: implementation of a set class similar to the stl set 
******************************************************************************************************/
#ifndef SET_H
#define SET_H

#include <iostream>
#include <vector>
#include "RBTree.h"

using namespace std;

// set class declaration
template<class T>
class set : public RBTree<T>{
private:
    // below are all recursive private functions for use by the other functions
    void copy(RBTreeNode<T>*, RBTreeNode<T>*&, RBTreeNode<T>*, RBTreeNode<T> *NilPtr);

    // in order recursive functions
    ostream& InOrderDisplay(RBTreeNode<T> *, ostream&);
    void InOrderVector(RBTreeNode<T>*, vector<T>&);
    void InOrderArray(RBTreeNode<T>*, T [], int &n, const int);
    bool InOrderSubset(RBTreeNode<T>*, set<T>&);
    bool InOrderSubset(RBTreeNode<T>*, RBTreeNode<T>*);
    void InOrderInsert(RBTreeNode<T>*, set<T> &other);
    void InOrderErase(RBTreeNode<T>*, set<T> &other);
public:
    set();
    set(const set<T>&);
    virtual ~set();
    
    // insert a value into the set
    void insert(T);
    // find a value 
    bool find(T);
    //erase a value from the set
    void erase(T);
    // empty function to check if empty
    bool empty();
    // convert the set to a vector
    void toVector(vector<T>&);
    // convert the set to an array
    void toArray(T arr[], const int size);
    int size(); // return the size
    void clear(); // clear the set

    // overloaded assignment operator
    set<T> operator=(const set<T>& right);
    // overloaded operators
    bool operator==(set<T>& right);
    bool operator!=(set<T>& right);
    bool operator<(set<T>& right);
    bool operator>(set<T>& right);
    bool operator<=(set<T>& right);
    bool operator>=(set<T>& right);
    set<T> operator+(set<T> right);
    set<T> operator-(set<T> right);
    set<T> operator*(set<T> right);
    template<class c>
    friend ostream& operator<<(ostream& os, set<c>& obj);
};

/*
 * empty constructor
 */
template<class T>
set<T>::set()
{
}

/*
 * destructor which has no purpose
 */
template<class T>
set<T>::~set()
{
}

/*
 * copy constructor for the set
 * parameters: the right set
 */
template<class T>
set<T>::set(const set<T> &right)
{
    copy(right.RBTree<T>::root, RBTree<T>::root, RBTree<T>::NIL, right.RBTree<T>::NIL);
}

/*
 * copy each node recursively in a sub tree pointed to by nodePtr
 * parameters: the node of the other subtree, the next node of the next subtree, the parent of this subtree, the nil of the other tree
 */
template<class T>
void set<T>::copy(RBTreeNode<T> *nodePtr, RBTreeNode<T> *&next, RBTreeNode<T> *parent, RBTreeNode<T> *NilPtr)
{
    if(nodePtr != NilPtr){
        next = new RBTreeNode<T>(nodePtr->value, nodePtr->color, RBTree<T>::NIL, RBTree<T>::NIL, parent);
        copy(nodePtr->left, next->left, next, NilPtr);
        copy(nodePtr->right, next->right, next, NilPtr);
    }
}

/*
 * display the set in InOrder
 * parameters: the subtree pointer, the outstream var by reference
 * return the stream
 */
template<class T>
ostream& set<T>::InOrderDisplay(RBTreeNode<T> *nodePtr, ostream &strm)
{
    if(nodePtr != RBTree<T>::NIL){
        InOrderDisplay(nodePtr->left, strm);
        strm<<nodePtr->value;
        InOrderDisplay(nodePtr->right, strm);
    }
    return strm;
}

/*
 * insert the set into a vector using an in order traversal
 * paremeters: the node of the subtree, the vector
 */
template<class T>
void set<T>::InOrderVector(RBTreeNode<T> *nodePtr, vector<T>& vect)
{
    if(nodePtr != RBTree<T>::NIL){
        InOrderVector(nodePtr->left, vect);
        vect.push_back(nodePtr->value);
        InOrderVector(nodePtr->right, vect);
    }
}

/*
 * insert the set into an array using an in order traversal
 * parameters: the node of the subtree, the array, the number of elements that have been inserted, the size of the array
 */
template<class T>
void set<T>::InOrderArray(RBTreeNode<T> *nodePtr, T arr[], int &n, const int size)
{
    if(nodePtr != RBTree<T>::NIL && n<size){
        InOrderArray(nodePtr->left, arr, n, size);
        arr[n++] = nodePtr->value;
        InOrderArray(nodePtr->right, arr, n, size);
    }
}

/*
 * check if A is a subset of B
 * parameters: node of the subtree, the other set which is being compared to
 * return whether this is a subset of the other
 */
template<class T>
bool set<T>::InOrderSubset(RBTreeNode<T> *nodePtr, set<T> &other)
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
 * parameters: the pointer to the other set node, and the nil of that set
 * return whether this A is a subset of B
 */
template<class T>
bool set<T>::InOrderSubset(RBTreeNode<T> *nodePtr, RBTreeNode<T> *nilPtr)
{
    if(nodePtr != nilPtr){
        bool left = InOrderSubset(nodePtr->left, nilPtr);
        bool right = InOrderSubset(nodePtr->right, nilPtr);
        return (RBTree<T>::find(nodePtr->value) && left && right);
    }
    return true;
}

/*
 * insert the set into a another using an in order traversal
 * parameters: the node and the other set
 */
template<class T>
void set<T>::InOrderInsert(RBTreeNode<T> *nodePtr, set<T> &other)
{
    if(nodePtr != RBTree<T>::NIL){
        InOrderInsert(nodePtr->left, other);
        other.insert(nodePtr->value);
        InOrderInsert(nodePtr->right, other);
    }
}

/*
 * insert the set into a vector using an in order traversal
 * parameters: the node of this set and the other set being erased from
 */
template<class T>
void set<T>::InOrderErase(RBTreeNode<T> *nodePtr, set<T> &other)
{
    if(nodePtr != RBTree<T>::NIL){
        InOrderErase(nodePtr->left, other);
        other.erase(nodePtr->value);
        InOrderErase(nodePtr->right, other);
    }
}


/*
 * overload the assignment operator
 * parameters: the right set
 * return the set
 */
template<class T>
set<T> set<T>::operator=(const set<T>& right)
{
    clear();
    copy(right.RBTree<T>::root, RBTree<T>::root, RBTree<T>::NIL, right.RBTree<T>::NIL);
}

/*
 * return the size of the set
 */
template<class T>
int set<T>::size()
{
    vector<T> V;
    toVector(V);
    
    int size = V.size();
    
    return size;
}

/*
 * clear the set
 */
template<class T>
void set<T>::clear()
{
    RBTree<T>::destroySubTree(RBTree<T>::root);
    delete RBTree<T>::NIL;
}


/*
 * Description: Insert function which calls the addElement function and only adds a non copy function
 * Parameters: item to be added
*/
template<class T>
void set<T>::insert(T val)
{
    RBTreeNode<T> *newnode = new RBTreeNode<T>(val, RED, RBTree<T>::NIL, RBTree<T>::NIL, RBTree<T>::NIL);
	RBTreeNode<T> *y = RBTree<T>::NIL;
	RBTreeNode<T> *x = RBTree<T>::root;

	while (x != RBTree<T>::NIL) {
		y = x;
		if (val < x->value)
			x = x->left;
		else if(val > x->value)
			x = x->right;
        else{
            delete newnode;
            return;
        }
	}

    newnode->parent = y;
    if (y == RBTree<T>::NIL)
        RBTree<T>::root = newnode;
    else if (newnode->value < y->value)
        y->left = newnode;
    else if(newnode->value > y->value)
        y->right = newnode;

    //  Adjust the RB tree to retain the properties.
    // if the value is not in the tree insert it
    RBTree<T>::insertFix(newnode);
}



/*
 * Find a value in the set
 */
template<class T>
bool set<T>::find(T item)
{
    return RBTree<T>::find(item);
}


/*
 * Erase a value from the tree
 */
template<class T>
void set<T>::erase(T val)
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
bool set<T>::empty()
{
    bool checker = false;

    if(RBTree<T>::root == RBTree<T>::NIL)
        checker = true;

    return checker;
}

// convert the set to a vector
template<class T>
void set<T>::toVector(vector<T>& vect)
{
    InOrderVector(RBTree<T>::root, vect);
}

// convert the set to an array
template<class T>
void set<T>::toArray(T arr[], const int size)
{
    int n = 0;
    InOrderArray(RBTree<T>::root, arr, n,  size);
}

// overload the == operator
template<class T>
bool set<T>::operator==(set<T>& right)
{
    return InOrderSubset(RBTree<T>::root, right) && InOrderSubset(right.RBTree<T>::root, right.RBTree<T>::NIL);
}

// overload the != operator
template<class T>
bool set<T>::operator!=(set<T>& right)
{
    return !(InOrderSubset(RBTree<T>::root, right) && InOrderSubset(right.RBTree<T>::root, right.RBTree<T>::NIL));
}

// overload the < operator
template<class T>
bool set<T>::operator<(set<T>& right)
{
    return InOrderSubset(RBTree<T>::root, right) && !(InOrderSubset(right.RBTree<T>::root, right.RBTree<T>::NIL));
}

// overload the > operator
template<class T>
bool set<T>::operator>(set<T>& right)
{
    return InOrderSubset(right.RBTree<T>::root, right.RBTree<T>::NIL) && !(InOrderSubset(RBTree<T>::root, right));
}

// overload the <= operator
template<class T>
bool set<T>::operator<=(set<T>& right)
{
    return InOrderSubset(RBTree<T>::root, right);
}

// overload the >= operator
template<class T>
bool set<T>::operator>=(set<T>& right)
{
    return InOrderSubset(right.RBTree<T>::root, right.RBTree<T>::NIL);
}

// overload the + operator
template<class T>
set<T> set<T>::operator+(set<T> right)
{
    set<T> temp(*this);
    right.InOrderInsert(right.RBTree<T>::root, temp);
    return temp;
}

// overload the - operator
template<class T>
set<T> set<T>::operator-(set<T> right)
{
    set<T> temp(*this);

    right.InOrderErase(right.RBTree<T>::root, temp);

    return temp;
}

// overload the * operator
template<class T>
set<T> set<T>::operator*(set<T> right)
{
    set<T> temp((*this + right) - ((*this - right)+(right - *this)));
    return temp;
}

// overload the << operator
template<class T>
ostream& operator<<(ostream& os, set<T>& obj)
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

#endif // end of the declaration and implementation of set class
    
