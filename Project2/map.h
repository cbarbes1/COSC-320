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
#include <exception>
#include <utility>
#include <queue>
#include "RBTree.h"

using namespace std;

// map class declaration
template<class T, class V>
class map : public RBTree<T, V>{
private:
    // below are all recursive private functions for use by the other functions
    void copy(RBTreeNode<T, V>*, RBTreeNode<T, V>*&, RBTreeNode<T, V>*, RBTreeNode<T, V> *NilPtr);

    // in order recursive functions
    ostream& InOrderDisplay(RBTreeNode<T, V> *, ostream&, int&);
    bool InOrderSubset(RBTreeNode<T, V>*, map<T, V>&);
    bool InOrderSubset(RBTreeNode<T, V>*, RBTreeNode<T, V>*);
    int InOrderNumPairs(RBTreeNode<T, V> *, int&);
    void InOrderAct(RBTreeNode<T, V> *, void (*)(T&, V&, V), V);
    void InOrderVector(RBTreeNode<T, V> *, vector<pair<T, V>>&);
public:
    map();
    map(const map<T, V>&);
    virtual ~map();

    // insert a value into the map
    void insert(T, V);
    // find a value
    bool find(T);
    //erase a value from the map
    void erase(T);
    // empty function to check if empty
    bool empty();

    V get(T key);

    void set(T key, V value);

    int size(); // return the size
    void clear(); // clear the map

    // overloaded assignment operator
    map<T, V> operator=(const map<T, V>& right);
    // overloaded operators
    bool operator==(map<T, V>& right);
    bool operator!=(map<T, V>& right);
    template<class c, class m>
    friend ostream& operator<<(ostream& os, map<c, m>& obj);

    void InOrderAct(void (*func)(T &key, V &var, V app), V app){
        return InOrderAct(RBTree<T, V>::root, func, app);
    }

    void toVector(vector<pair<T, V>> &vect){
        InOrderVector(RBTree<T, V>::root, vect);
    }
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
        next = new RBTreeNode<T, V>(nodePtr->key, nodePtr->value, nodePtr->color, RBTree<T, V>::NIL, RBTree<T, V>::NIL, parent);
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
ostream& map<T, V>::InOrderDisplay(RBTreeNode<T, V> *nodePtr, ostream &strm, int &count)
{
    if(nodePtr != RBTree<T, V>::NIL){
        InOrderDisplay(nodePtr->left, strm, count);
        strm<<"("<<nodePtr->key<<", "<<nodePtr->value<<")";
        if(count!=(size()-1)){
            strm<<", ";
            count++;
        }
        InOrderDisplay(nodePtr->right, strm, count);
    }
    return strm;
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
        return ((other.RBTree<T, V>::findNode(nodePtr->key) == nodePtr->value) && left && right);
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
        return ((RBTree<T, V>::findNode(nodePtr->key) == nodePtr->value) && left && right);
    }
    return true;
}

/*
 * count number of elements
 * parameters: the subtree pointer, the count variable
 * return the count of the map
 */
template<class T, class V>
int map<T, V>::InOrderNumPairs(RBTreeNode<T, V> *nodePtr, int &count)
{
    if(nodePtr != RBTree<T, V>::NIL){
        InOrderNumPairs(nodePtr->left, count);
        count++;
        InOrderNumPairs(nodePtr->right, count);
    }
    return count;
}

/*
 * do an action on a node with the given key if the action was successful return true
 * parameters: the subtree pointer, the key, and the function pointer to the specified action function
 * return true or false: true if the node is found and the action is completed
 */
template<class T, class V>
void map<T, V>::InOrderAct(RBTreeNode<T, V> *nodePtr, void (*func)(T &key, V &var, V app), V applyAgent)
{
    // if the node is nil then return false
    if(nodePtr != RBTree<T, V>::NIL){
        // if the left finds the value then return true
        InOrderAct(nodePtr->left, func, applyAgent);
        // if the value is indeed found then do the action and return true
        func(nodePtr->key, nodePtr->value, applyAgent);
        // if right is reached return whatever it may be
        InOrderAct(nodePtr->right, func, applyAgent);
    }
}

/*
 * In order traversal to place all of the values into a vector
 * parameters: the treenode and the queue
 * return nothing
 */
template<class T, class V>
void map<T, V>::InOrderVector(RBTreeNode<T, V> *nodePtr, vector<pair<T, V>> &list)
{
    if(nodePtr != RBTree<T, V>::NIL){
        InOrderVector(nodePtr->left, list);
        list.push_back(make_pair(nodePtr->key, nodePtr->value));// push the value into the vector
        InOrderVector(nodePtr->right, list);
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
    return *this;
}

/*
 * return the size of the map
 */
template<class T, class V>
int map<T, V>::size()
{
    int size = 0;
    
    InOrderNumPairs(RBTree<T, V>::root, size);

    return size;
}

/*
 * clear the map
 */
template<class T, class V>
void map<T, V>::clear()
{
    RBTree<T, V>::destroySubTree(RBTree<T, V>::root);
}


/*
 * Description: Insert function which calls the addElement function and only adds a non copy function
 * Parameters: item to be added
*/
template<class T, class V>
void map<T, V>::insert(T key, V val)
{
    
	RBTreeNode<T, V> *y = RBTree<T, V>::NIL;
	RBTreeNode<T, V> *x = RBTree<T, V>::root;

	while (x != RBTree<T, V>::NIL) {
		y = x;
		if (key < x->key)
			x = x->left;
		else if(key > x->key)
			x = x->right;
        else{
            x->value = val;
            return;
        }
	}
	
	RBTreeNode<T, V> *newnode = new RBTreeNode<T, V>(key, val, RED, RBTree<T, V>::NIL, RBTree<T, V>::NIL, RBTree<T, V>::NIL);
    newnode->parent = y;
    if (y == RBTree<T, V>::NIL)
        RBTree<T, V>::root = newnode;
    else if (newnode->key < y->key)
        y->left = newnode;
    else if(newnode->key > y->key)
        y->right = newnode;

    //  Adjust the RB tree to retain the properties.
    // if the value is not in the tree insert it
    RBTree<T, V>::insertFix(newnode);
}



/*
 * Find a value in the map
 */
template<class T, class V>
bool map<T, V>::find(T key)
{
    return RBTree<T, V>::find(key);
}


/*
 * Erase a value from the tree
 */
template<class T, class V>
void map<T, V>::erase(T key)
{
    RBTreeNode<T, V> *z = RBTree<T, V>::findNode(key);
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
    if(!find(key))
        throw std::runtime_error("Pair not in the set");

    return RBTree<T, V>::findNode(key)->value;
}

template<class T, class V>
void map<T, V>::set(T key, V value)
{
    insert(key, value);
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

// overload the << operator
template<class T, class V>
ostream& operator<<(ostream& os, map<T, V>& obj)
{
    os<<"{ ";
    int count = 0;
    obj.InOrderDisplay(obj.RBTree<T, V>::root, os, count);
    os<<" }\n";
    return os;
}

#endif
