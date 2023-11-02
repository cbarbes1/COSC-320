/******************************************************************************************************
 * Authors: Cole Barbes
 * Creation Date: 10/18/23
 * Last Edited: 10/31/23
 * Description: implementation of a multimap class similar to the stl multimap
******************************************************************************************************/
#ifndef MULTIMAP_H
#define MULTIMAP_H

#include <iostream>
#include <vector>
#include <exception>
#include <utility>
#include "RBTree.h"
#include "RBT.h"

using namespace std;

// multimap class declaration
template<class T, class V>
class multimap : public RBTree<T, RBT<V>>{
private:
    // below are all recursive private functions for use by the other functions
    void copy(RBTreeNode<T, RBT<V>>*, RBTreeNode<T, RBT<V>>*&, RBTreeNode<T, RBT<V>>*, RBTreeNode<T, RBT<V>> *NilPtr);

    // in order recursive functions
    ostream& InOrderDisplay(RBTreeNode<T, RBT<V>> *, ostream&, int&);
    bool InOrderSubset(RBTreeNode<T, RBT<V>>*, multimap<T, RBT<V>>&);
    bool InOrderSubset(RBTreeNode<T, RBT<V>>*, RBTreeNode<T, RBT<V>>*);
    int InOrderNumPairs(RBTreeNode<T, RBT<V>> *, int&);
    
public:
    multimap();
    multimap(const multimap<T, RBT<V>>&);
    virtual ~multimap();

    // insert a value into the multimap
    void insert(T, RBT<V>);
    // find a value
    bool find(T);
    //erase a value from the multimap
    void erase(T);
    // empty function to check if empty
    bool empty();

    RBT<V> get(T key);

    void set(T key, RBT<V> value);

    int size(); // return the size
    void clear(); // clear the multimap

    // overloaded assignment operator
    multimap<T, RBT<V>> operator=(const multimap<T, RBT<V>>& right);
    // overloaded operators
    bool operator==(multimap<T, RBT<V>>& right);
    bool operator!=(multimap<T, RBT<V>>& right);
    template<class c, class m>
    friend ostream& operator<<(ostream& os, multimap<c, m>& obj);
};

/*
 * empty constructor
 */
template<class T, class V>
multimap<T, RBT<V>>::multimap()
{
}

/*
 * destructor which has no purpose
 */
template<class T, class V>
multimap<T, RBT<V>>::~multimap()
{
}

/*
 * copy constructor for the multimap
 * parameters: the right multimap
 */
template<class T, class V>
multimap<T, RBT<V>>::multimap(const multimap<T, RBT<V>> &right)
{
    copy(right.RBTree<T, RBT<V>>::root, RBTree<T, RBT<V>>::root, RBTree<T, RBT<V>>::NIL, right.RBTree<T, RBT<V>>::NIL);
}

/*
 * copy each node recursively in a sub tree pointed to by nodePtr
 * parameters: the node of the other subtree, the next node of the next subtree, the parent of this subtree, the nil of the other tree
 */
template<class T, class V>
void multimap<T, RBT<V>>::copy(RBTreeNode<T, RBT<V>> *nodePtr, RBTreeNode<T, RBT<V>> *&next, RBTreeNode<T, RBT<V>> *parent, RBTreeNode<T, RBT<V>> *NilPtr)
{
    if(nodePtr != NilPtr){
        next = new RBTreeNode<T, RBT<V>>(nodePtr->key, nodePtr->value, nodePtr->color, RBTree<T, RBT<V>>::NIL, RBTree<T, RBT<V>>::NIL, parent);
        copy(nodePtr->left, next->left, next, NilPtr);
        copy(nodePtr->right, next->right, next, NilPtr);
    }
}

/*
 * display the multimap in InOrder
 * parameters: the subtree pointer, the outstream var by reference
 * return the stream
 */
template<class T, class V>
ostream& multimap<T, RBT<V>>::InOrderDisplay(RBTreeNode<T, RBT<V>> *nodePtr, ostream &strm, int &count)
{
    if(nodePtr != RBTree<T, RBT<V>>::NIL){
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
 * check if A is a submultimap of B
 * parameters: node of the subtree, the other multimap which is being compared to
 * return whether this is a submultimap of the other
 */
template<class T, class V>
bool multimap<T, RBT<V>>::InOrderSubset(RBTreeNode<T, RBT<V>> *nodePtr, multimap<T, RBT<V>> &other)
{
    if(nodePtr != RBTree<T, RBT<V>>::NIL){
        bool left = InOrderSubset(nodePtr->left, other);
        bool right = InOrderSubset(nodePtr->right, other);
        return (other.RBTree<T, RBT<V>>::find(nodePtr->key) && left && right);
    }
    return true;
}

/*
 * check if A is a submultimap of B
 * parameters: the pointer to the other multimap node, and the nil of that multimap
 * return whether this A is a submultimap of B
 */
template<class T, class V>
bool multimap<T, RBT<V>>::InOrderSubset(RBTreeNode<T, RBT<V>> *nodePtr, RBTreeNode<T, RBT<V>> *nilPtr)
{
    if(nodePtr != nilPtr){
        bool left = InOrderSubset(nodePtr->left, nilPtr);
        bool right = InOrderSubset(nodePtr->right, nilPtr);
        return (RBTree<T, RBT<V>>::find(nodePtr->value) && left && right);
    }
    return true;
}

/*
 * count number of elements
 * parameters: the subtree pointer, the count variable
 * return the count of the multimap
 */
template<class T, class V>
int multimap<T, RBT<V>>::InOrderNumPairs(RBTreeNode<T, RBT<V>> *nodePtr, int &count)
{
    if(nodePtr != RBTree<T, RBT<V>>::NIL){
        InOrderNumPairs(nodePtr->left, count);
        count++;
        InOrderNumPairs(nodePtr->right, count);
    }
    return count;
}

/*
 * overload the assignment operator
 * parameters: the right multimap
 * return the multimap
 */
template<class T, class V>
multimap<T, RBT<V>> multimap<T, RBT<V>>::operator=(const multimap<T, RBT<V>>& right)
{
    clear();
    copy(right.RBTree<T, RBT<V>>::root, RBTree<T, RBT<V>>::root, RBTree<T, RBT<V>>::NIL, right.RBTree<T, RBT<V>>::NIL);
    return *this;
}

/*
 * return the size of the multimap
 */
template<class T, class V>
int multimap<T, RBT<V>>::size()
{
    int size = 0;
    
    InOrderNumPairs(RBTree<T, RBT<V>>::root, size);

    return size;
}

/*
 * clear the multimap
 */
template<class T, class V>
void multimap<T, RBT<V>>::clear()
{
    RBTree<T, RBT<V>>::destroySubTree(RBTree<T, RBT<V>>::root);
}


/*
 * Description: Insert function which calls the addElement function and only adds a non copy function
 * Parameters: item to be added
*/
template<class T, class V>
void multimap<T, RBT<V>>::insert(T key, V val)
{
    RBT<V> newValSet;
    newValSet.insert(val);
    RBTreeNode<T, RBT<V>> *newnode = new RBTreeNode<T, RBT<V>>(key, newValSet, RED, RBTree<T, RBT<V>>::NIL, RBTree<T, RBT<V>>::NIL, RBTree<T, RBT<V>>::NIL);
	RBTreeNode<T, RBT<V>> *y = RBTree<T, RBT<V>>::NIL;
	RBTreeNode<T, RBT<V>> *x = RBTree<T, RBT<V>>::root;

	while (x != RBTree<T, RBT<V>>::NIL) {
		y = x;
		if (key < x->key)
			x = x->left;
		else if(key > x->key)
			x = x->right;
        else{
            x->value.set(val);
            delete newnode;
            return;
        }
	}

    newnode->parent = y;
    if (y == RBTree<T, RBT<V>>::NIL)
        RBTree<T, RBT<V>>::root = newnode;
    else if (newnode->key < y->key)
        y->left = newnode;
    else if(newnode->key > y->key)
        y->right = newnode;

    //  Adjust the RB tree to retain the properties.
    // if the value is not in the tree insert it
    RBTree<T, RBT<V>>::insertFix(newnode);
}



/*
 * Find a value in the multimap
 */
template<class T, class V>
bool multimap<T, RBT<V>>::find(T key)
{
    return RBTree<T, RBT<V>>::find(key);
}


/*
 * Erase a value from the tree
 */
template<class T, class V>
void multimap<T, RBT<V>>::erase(T key)
{
    RBTreeNode<T, RBT<V>> *z = RBTree<T, RBT<V>>::findNode(key);
	if (z == RBTree<T, RBT<V>>::NIL)
		return;

	RBTreeNode<T, RBT<V>> *y = z;
	RBTreeNode<T, RBT<V>> *x = RBTree<T, RBT<V>>::NIL;
	color_t yorigcol = y->color;

	if (z->left == RBTree<T, RBT<V>>::NIL) {
		x = z->right;
		RBTree<T, RBT<V>>::transplant(z, z->right);
	} else if (z->right == RBTree<T, RBT<V>>::NIL) {
		x = z->left;
		RBTree<T, RBT<V>>::transplant(z, z->left);
	} else {
		y = RBTree<T, RBT<V>>::getMinNode(z->right);
		yorigcol = y->color;
		x = y->right;
		if (y->parent == z)
			x->parent = y;
		else {
			RBTree<T, RBT<V>>::transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		RBTree<T, RBT<V>>::transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	(z->value).clear();
	delete z;
	if (yorigcol == BLACK)
		RBTree<T, RBT<V>>::deleteFix(x);
}

// empty function to check if empty
template<class T, class V>
bool multimap<T, RBT<V>>::empty()
{
    bool checker = false;

    if(RBTree<T, RBT<V>>::root == RBTree<T, RBT<V>>::NIL)
        checker = true;

    return checker;
}

template<class T, class V>
RBT<V> multimap<T, RBT<V>>::get(T key)
{
    if(!find(key))
        throw std::runtime_error("Pair not in the set");
    return RBTree<T, RBT<V>>::findNode(key)->value;
}

template<class T, class V>
void multimap<T, RBT<V>>::set(T key, RBT<V> value)
{
    insert(key, value);
}

// overload the == operator
template<class T, class V>
bool multimap<T, RBT<V>>::operator==(multimap<T, RBT<V>>& right)
{
    return InOrderSubset(RBTree<T, RBT<V>>::root, right) && InOrderSubset(right.RBTree<T, RBT<V>>::root, right.RBTree<T, RBT<V>>::NIL);
}

// overload the != operator
template<class T, class V>
bool multimap<T, RBT<V>>::operator!=(multimap<T, RBT<V>>& right)
{
    return !(InOrderSubset(RBTree<T, RBT<V>>::root, right) && InOrderSubset(right.RBTree<T, RBT<V>>::root, right.RBTree<T, RBT<V>>::NIL));
}

// overload the << operator
template<class T, class V>
ostream& operator<<(ostream& os, multimap<T, RBT<V>>& obj)
{
    os<<"{ ";
    int count = 0;
    obj.InOrderDisplay(obj.RBTree<T, RBT<V>>::root, os, count);
    os<<" }\n";
    return os;
}

#endif
