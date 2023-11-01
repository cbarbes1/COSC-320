/******************************************************************************************************
 * Authors: Cole Barbes and Harrison Colborne
 * Creation Date: 10/18/23
 * Last Edited: 10/31/23
 * Description: implementation of a map class similar to the stl map
******************************************************************************************************/
#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include "RBTree.h"

using namespace std;

// map class declaration
template<class T, class V>
class map : public RBTree<T, V>{
private:
    // below are all recursive private functions for use by the other functions
    void copy(RBTreeNode<T, V>*, RBTreeNode<T, V>*&, RBTreeNode<T, V>*, RBTreeNode<T, V> *NilPtr);

    // in order recursive functions
    ostream& InOrderDisplay(RBTreeNode<T, V> *, ostream&);
    void InOrderVector(RBTreeNode<T, V>*, vector<T, V>&);
    void InOrderArray(RBTreeNode<T, V>*, T [], int &n, const int);
    bool InOrderSubset(RBTreeNode<T, V>*, map<T, V>&);
    bool InOrderSubset(RBTreeNode<T, V>*, RBTreeNode<T, V>*);
    void InOrderInsert(RBTreeNode<T, V>*, map<T, V> &other);
    void InOrderErase(RBTreeNode<T, V>*, map<T, V> &other);
public:
    map();
    map(const map<T, V>&);
    virtual ~map();

    // insert a value into the map
    void insert(T);
    // find a value
    bool find(T);
    //erase a value from the map
    void erase(T);
    // empty function to check if empty
    bool empty();

    V get(T key);

    void set(T key, V value);

    // convert the map to a vector
    void toVector(vector<T, V>&);
    int size(); // return the size
    void clear(); // clear the map

    // overloaded assignment operator
    map<T, V> operator=(const map<T, V>& right);
    // overloaded operators
    bool operator==(map<T, V>& right);
    bool operator!=(map<T, V>& right);
    template<class c, class m>
    friend ostream& operator<<(ostream& os, map<c, m>& obj);
};

/*
 * empty constructor
 */
template<class T, class V>
map<T, V>::map()
{
}

/*
 * destructor which has no purpose
 */
template<class T, class V>
map<T, V>::~map()
{
}

/*
 * copy constructor for the map
 * parameters: the right map
 */
template<class T, class V>
map<T, V>::map(const map<T, V> &right)
{
    copy(right.RBTree<T, V>::root, RBTree<T, V>::root, RBTree<T, V>::NIL, right.RBTree<T, V>::NIL);
}

/*
 * copy each node recursively in a sub tree pointed to by nodePtr
 * parameters: the node of the other subtree, the next node of the next subtree, the parent of this subtree, the nil of the other tree
 */
template<class T, class V>
void map<T, V>::copy(RBTreeNode<T, V> *nodePtr, RBTreeNode<T, V> *&next, RBTreeNode<T, V> *parent, RBTreeNode<T, V> *NilPtr)
{
    if(nodePtr != NilPtr){
        next = new RBTreeNode<T, V>(nodePtr->value, nodePtr->color, RBTree<T, V>::NIL, RBTree<T, V>::NIL, parent);
        copy(nodePtr->left, next->left, next, NilPtr);
        copy(nodePtr->right, next->right, next, NilPtr);
    }
}

/*
 * display the map in InOrder
 * parameters: the subtree pointer, the outstream var by reference
 * return the stream
 */
template<class T, class V>
ostream& map<T, V>::InOrderDisplay(RBTreeNode<T, V> *nodePtr, ostream &strm)
{
    if(nodePtr != RBTree<T, V>::NIL){
        InOrderDisplay(nodePtr->left, strm);
        strm<<nodePtr->value;
        InOrderDisplay(nodePtr->right, strm);
    }
    return strm;
}

/*
 * insert the map into a vector using an in order traversal
 * paremeters: the node of the subtree, the vector
 */
template<class T, class V>
void map<T, V>::InOrderVector(RBTreeNode<T, V> *nodePtr, vector<T, V>& vect)
{
    if(nodePtr != RBTree<T, V>::NIL){
        InOrderVector(nodePtr->left, vect);
        vect.push_back(nodePtr->value);
        InOrderVector(nodePtr->right, vect);
    }
}

/*
 * insert the map into an array using an in order traversal
 * parameters: the node of the subtree, the array, the number of elements that have been inserted, the size of the array
 */
template<class T, class V>
void map<T, V>::InOrderArray(RBTreeNode<T, V> *nodePtr, T arr[], int &n, const int size)
{
    if(nodePtr != RBTree<T, V>::NIL && n<size){
        InOrderArray(nodePtr->left, arr, n, size);
        arr[n++] = nodePtr->value;
        InOrderArray(nodePtr->right, arr, n, size);
    }
}

/*
 * check if A is a submap of B
 * parameters: node of the subtree, the other map which is being compared to
 * return whether this is a submap of the other
 */
template<class T, class V>
bool map<T, V>::InOrderSubset(RBTreeNode<T, V> *nodePtr, map<T, V> &other)
{
    if(nodePtr != RBTree<T, V>::NIL){
        bool left = InOrderSubset(nodePtr->left, other);
        bool right = InOrderSubset(nodePtr->right, other);
        return (other.RBTree<T, V>::find(nodePtr->value) && left && right);
    }
    return true;
}

/*
 * check if A is a submap of B
 * parameters: the pointer to the other map node, and the nil of that map
 * return whether this A is a submap of B
 */
template<class T, class V>
bool map<T, V>::InOrderSubset(RBTreeNode<T, V> *nodePtr, RBTreeNode<T, V> *nilPtr)
{
    if(nodePtr != nilPtr){
        bool left = InOrderSubset(nodePtr->left, nilPtr);
        bool right = InOrderSubset(nodePtr->right, nilPtr);
        return (RBTree<T, V>::find(nodePtr->value) && left && right);
    }
    return true;
}

/*
 * insert the map into a another using an in order traversal
 * parameters: the node and the other map
 */
template<class T, class V>
void map<T, V>::InOrderInsert(RBTreeNode<T, V> *nodePtr, map<T, V> &other)
{
    if(nodePtr != RBTree<T, V>::NIL){
        InOrderInsert(nodePtr->left, other);
        other.insert(nodePtr->value);
        InOrderInsert(nodePtr->right, other);
    }
}

/*
 * insert the map into a vector using an in order traversal
 * parameters: the node of this map and the other map being erased from
 */
template<class T, class V>
void map<T, V>::InOrderErase(RBTreeNode<T, V> *nodePtr, map<T, V> &other)
{
    if(nodePtr != RBTree<T, V>::NIL){
        InOrderErase(nodePtr->left, other);
        other.erase(nodePtr->value);
        InOrderErase(nodePtr->right, other);
    }
}


/*
 * overload the assignment operator
 * parameters: the right map
 * return the map
 */
template<class T, class V>
map<T, V> map<T, V>::operator=(const map<T, V>& right)
{
    clear();
    copy(right.RBTree<T, V>::root, RBTree<T, V>::root, RBTree<T, V>::NIL, right.RBTree<T, V>::NIL);
}

/*
 * return the size of the map
 */
template<class T, class V>
int map<T, V>::size()
{
    vector<T, V> vect;
    toVector(vect);

    int size = vect.size();

    return size;
}

/*
 * clear the map
 */
template<class T, class V>
void map<T, V>::clear()
{
    RBTree<T, V>::destroySubTree(RBTree<T, V>::root);
    delete RBTree<T, V>::NIL;
}


/*
 * Description: Insert function which calls the addElement function and only adds a non copy function
 * Parameters: item to be added
*/
template<class T, class V>
void map<T, V>::insert(T val)
{
    RBTreeNode<T, V> *newnode = new RBTreeNode<T, V>(val, RED, RBTree<T, V>::NIL, RBTree<T, V>::NIL, RBTree<T, V>::NIL);
	RBTreeNode<T, V> *y = RBTree<T, V>::NIL;
	RBTreeNode<T, V> *x = RBTree<T, V>::root;

	while (x != RBTree<T, V>::NIL) {
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
    if (y == RBTree<T, V>::NIL)
        RBTree<T, V>::root = newnode;
    else if (newnode->value < y->value)
        y->left = newnode;
    else if(newnode->value > y->value)
        y->right = newnode;

    //  Adjust the RB tree to retain the properties.
    // if the value is not in the tree insert it
    RBTree<T, V>::insertFix(newnode);
}



/*
 * Find a value in the map
 */
template<class T, class V>
bool map<T, V>::find(T item)
{
    return RBTree<T, V>::find(item);
}


/*
 * Erase a value from the tree
 */
template<class T, class V>
void map<T, V>::erase(T val)
{
    RBTreeNode<T, V> *z = RBTree<T, V>::findNode(val);
	if (z == RBTree<T, V>::NIL)
		return;

	RBTreeNode<T, V> *y = z;
	RBTreeNode<T, V> *x = RBTree<T, V>::NIL;
	color_t yorigcol = y->color;

	if (z->left == RBTree<T, V>::NIL) {
		x = z->right;
		RBTree<T, V>::transplant(z, z->right);
	} else if (z->right == RBTree<T, V>::NIL) {
		x = z->left;
		RBTree<T, V>::transplant(z, z->left);
	} else {
		y = RBTree<T, V>::getMinNode(z->right);
		yorigcol = y->color;
		x = y->right;
		if (y->parent == z)
			x->parent = y;
		else {
			RBTree<T, V>::transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		RBTree<T, V>::transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	delete z;
	if (yorigcol == BLACK)
		RBTree<T, V>::deleteFix(x);
}

// empty function to check if empty
template<class T, class V>
bool map<T, V>::empty()
{
    bool checker = false;

    if(RBTree<T, V>::root == RBTree<T, V>::NIL)
        checker = true;

    return checker;
}

template<class T, class V>
V map<T, V>::get(T key)
{
    return RBTree<T, V>::findNode(key)->value;
}

template<class T, class V>
void map<T, V>::set(T key, V value)
{
    insert(key, value);
}

// convert the map to a vector
template<class T, class V>
void map<T, V>::toVector(vector<T, V>& vect)
{
    InOrderVector(RBTree<T, V>::root, vect);
}

// overload the == operator
template<class T, class V>
bool map<T, V>::operator==(map<T, V>& right)
{
    return InOrderSubset(RBTree<T, V>::root, right) && InOrderSubset(right.RBTree<T, V>::root, right.RBTree<T, V>::NIL);
}

// overload the != operator
template<class T, class V>
bool map<T, V>::operator!=(map<T, V>& right)
{
    return !(InOrderSubset(RBTree<T, V>::root, right) && InOrderSubset(right.RBTree<T, V>::root, right.RBTree<T, V>::NIL));
}

// overload the < operator
template<class T, class V>
bool map<T, V>::operator<(map<T, V>& right)
{
    return InOrderSubset(RBTree<T, V>::root, right) && !(InOrderSubset(right.RBTree<T, V>::root, right.RBTree<T, V>::NIL));
}

// overload the > operator
template<class T, class V>
bool map<T, V>::operator>(map<T, V>& right)
{
    return InOrderSubset(right.RBTree<T, V>::root, right.RBTree<T, V>::NIL) && !(InOrderSubset(RBTree<T, V>::root, right));
}

// overload the <= operator
template<class T, class V>
bool map<T, V>::operator<=(map<T, V>& right)
{
    return InOrderSubset(RBTree<T, V>::root, right);
}

// overload the >= operator
template<class T, class V>
bool map<T, V>::operator>=(map<T, V>& right)
{
    return InOrderSubset(right.RBTree<T, V>::root, right.RBTree<T, V>::NIL);
}

// overload the + operator
template<class T, class V>
map<T, V> map<T, V>::operator+(map<T, V> right)
{
    map<T, V> temp(*this);
    right.InOrderInsert(right.RBTree<T, V>::root, temp);
    return temp;
}

// overload the - operator
template<class T, class V>
map<T, V> map<T, V>::operator-(map<T, V> right)
{
    map<T, V> temp(*this);

    right.InOrderErase(right.RBTree<T, V>::root, temp);

    return temp;
}

// overload the * operator
template<class T, class V>
map<T, V> map<T, V>::operator*(map<T, V> right)
{
    map<T, V> temp((*this + right) - ((*this - right)+(right - *this)));
    return temp;
}

// overload the << operator
template<class T, class V>
ostream& operator<<(ostream& os, map<T, V>& obj)
{
    os<<"{ ";
    vector<T, V> vect;
    obj.toVector(vect);
    for(unsigned int i = 0; i<vect.size(); i++){
        os<<vect[i];
        if(i != (vect.size() - 1))
            os<<", ";
    }
    os<<" }\n";
    return os;
}

#endif
