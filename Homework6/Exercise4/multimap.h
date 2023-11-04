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

using namespace std;

// multimap class declaration
template<class T, class V>
class multimap : public RBTree<T, vector<V>>{
private:
    // below are all recursive private functions for use by the other functions
    void copy(RBTreeNode<T, vector<V>>*, RBTreeNode<T, vector<V>>*&, RBTreeNode<T, vector<V>>*, RBTreeNode<T, vector<V>> *NilPtr);

    // in order recursive functions
    ostream& InOrderDisplay(RBTreeNode<T, vector<V>> *, ostream&, int&);
    bool InOrderSubset(RBTreeNode<T, vector<V>>*, multimap<T, V>&);
    bool InOrderSubset(RBTreeNode<T, vector<V>>*, RBTreeNode<T, vector<V>>*);
    int InOrderNumPairs(RBTreeNode<T, vector<V>> *, int&);
   
    
public:
    multimap();
    multimap(const multimap<T, V>&);
    virtual ~multimap();

    // insert a value into the multimap
    void insert(T, V);
    // find a value
    bool find(T);
    //erase a value from the multimap
    void erase(T, V);
    // empty function to check if empty
    bool empty();

    vector<V> get(T key);

    void set(T key, V value);

    int size(); // return the size
    void clear(); // clear the multimap

    // overloaded assignment operator
    multimap<T, V> operator=(const multimap<T, V>& right);
    // overloaded operators
    bool operator==(multimap<T, V>& right);
    bool operator!=(multimap<T, V>& right);
    template<class c, class m>
    friend ostream& operator<<(ostream& os, multimap<c, m>& obj);
};

/*
 * empty constructor
 */
template<class T, class V>
multimap<T, V>::multimap()
{
}

/*
 * destructor which has no purpose
 */
template<class T, class V>
multimap<T, V>::~multimap()
{
}

/*
 * copy constructor for the multimap
 * parameters: the right multimap
 */
template<class T, class V>
multimap<T, V>::multimap(const multimap<T, V> &right)
{
    copy(right.RBTree<T, vector<V>>::root, RBTree<T, vector<V>>::root, RBTree<T, vector<V>>::NIL, right.RBTree<T, vector<V>>::NIL);
}

/*
 * copy each node recursively in a sub tree pointed to by nodePtr
 * parameters: the node of the other subtree, the next node of the next subtree, the parent of this subtree, the nil of the other tree
 */
template<class T, class V>
void multimap<T, V>::copy(RBTreeNode<T, vector<V>> *nodePtr, RBTreeNode<T, vector<V>> *&next, RBTreeNode<T, vector<V>> *parent, RBTreeNode<T, vector<V>> *NilPtr)
{
    if(nodePtr != NilPtr){
        next = new RBTreeNode<T, vector<V>>(nodePtr->key, nodePtr->value, nodePtr->color, RBTree<T, vector<V>>::NIL, RBTree<T, vector<V>>::NIL, parent);
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
ostream& multimap<T, V>::InOrderDisplay(RBTreeNode<T, vector<V>> *nodePtr, ostream &strm, int &count)
{
    if(nodePtr != RBTree<T, vector<V>>::NIL){
        InOrderDisplay(nodePtr->left, strm, count);
        strm<<"("<<nodePtr->key<<", ";
        for(unsigned int i = 0; i<(nodePtr->value).size(); i++){
            strm<<(nodePtr->value)[i];
            if(i<((nodePtr->value).size()-1))
                strm<<" \\ ";
        }
        strm<<")";
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
bool multimap<T, V>::InOrderSubset(RBTreeNode<T, vector<V>> *nodePtr, multimap<T, V> &other)
{
    if(nodePtr != RBTree<T, vector<V>>::NIL){
        bool left = InOrderSubset(nodePtr->left, other);
        bool right = InOrderSubset(nodePtr->right, other);
        return (other.RBTree<T, vector<V>>::find(nodePtr->key) && left && right);
    }
    return true;
}

/*
 * check if A is a submultimap of B
 * parameters: the pointer to the other multimap node, and the nil of that multimap
 * return whether this A is a submultimap of B
 */
template<class T, class V>
bool multimap<T, V>::InOrderSubset(RBTreeNode<T, vector<V>> *nodePtr, RBTreeNode<T, vector<V>> *nilPtr)
{
    if(nodePtr != nilPtr){
        bool left = InOrderSubset(nodePtr->left, nilPtr);
        bool right = InOrderSubset(nodePtr->right, nilPtr);
        return (RBTree<T, vector<V>>::find(nodePtr->key) && left && right);
    }
    return true;
}

/*
 * count number of elements
 * parameters: the subtree pointer, the count variable
 * return the count of the multimap
 */
template<class T, class V>
int multimap<T, V>::InOrderNumPairs(RBTreeNode<T, vector<V>> *nodePtr, int &count)
{
    if(nodePtr != RBTree<T, vector<V>>::NIL){
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
multimap<T, V> multimap<T, V>::operator=(const multimap<T, V>& right)
{
    clear();
    copy(right.RBTree<T, vector<V>>::root, RBTree<T, vector<V>>::root, RBTree<T, vector<V>>::NIL, right.RBTree<T, vector<V>>::NIL);
    return *this;
}

/*
 * return the size of the multimap
 */
template<class T, class V>
int multimap<T, V>::size()
{
    int size = 0;
    
    InOrderNumPairs(RBTree<T, vector<V>>::root, size);

    return size;
}

/*
 * clear the multimap
 */
template<class T, class V>
void multimap<T, V>::clear()
{
    RBTree<T, vector<V>>::destroySubTree(RBTree<T, vector<V>>::root);
}


/*
 * Description: Insert function which calls the addElement function and only adds a non copy function
 * Parameters: item to be added
 * alteration: changed the function so that the additional value of the node is inserted all other cases stay the same
*/
template<class T, class V>
void multimap<T, V>::insert(T key, V val)
{
    vector<V> newValSet;
    newValSet.push_back(val);
    RBTreeNode<T, vector<V>> *newnode = new RBTreeNode<T, vector<V>>(key, newValSet, RED, RBTree<T, vector<V>>::NIL, RBTree<T, vector<V>>::NIL, RBTree<T, vector<V>>::NIL);
	RBTreeNode<T, vector<V>> *y = RBTree<T, vector<V>>::NIL;
	RBTreeNode<T, vector<V>> *x = RBTree<T, vector<V>>::root;

	while (x != RBTree<T, vector<V>>::NIL) {
		y = x;
		if (key < x->key)
			x = x->left;
		else if(key > x->key)
			x = x->right;
        else{ // alter the loop to push a value into the associated keys vector
            x->value.push_back(val);
            delete newnode;
            return;
        }
	}

    newnode->parent = y;
    if (y == RBTree<T, vector<V>>::NIL)
        RBTree<T, vector<V>>::root = newnode;
    else if (newnode->key < y->key)
        y->left = newnode;
    else
        y->right = newnode;

    //  Adjust the RB tree to retain the properties.
    // if the value is not in the tree insert it
    RBTree<T, vector<V>>::insertFix(newnode);
}



/*
 * Find a value in the multimap
 */
template<class T, class V>
bool multimap<T, V>::find(T key)
{
    return RBTree<T, vector<V>>::find(key);
}


/*
 * Erase a value from the tree
 */
template<class T, class V>
void multimap<T, V>::erase(T key, V val)
{
    RBTreeNode<T, vector<V>> *z = RBTree<T, vector<V>>::findNode(key);
	if (z == RBTree<T, vector<V>>::NIL)
		return;

    // if there is values in the vector other than one than we must erase the entry in the list
    if(z->value.size() > 1){
        for(unsigned int i = 0; i<z->value.size(); i++){
            if((z->value)[i] == val)
                (z->value).erase((z->value).begin() + static_cast<int>(i));
        }
        return;
    }

	RBTreeNode<T, vector<V>> *y = z;
	RBTreeNode<T, vector<V>> *x = RBTree<T, vector<V>>::NIL;
	color_t yorigcol = y->color;

	if (z->left == RBTree<T, vector<V>>::NIL) {
		x = z->right;
		RBTree<T, vector<V>>::transplant(z, z->right);
	} else if (z->right == RBTree<T, vector<V>>::NIL) {
		x = z->left;
		RBTree<T, vector<V>>::transplant(z, z->left);
	} else {
		y = RBTree<T, vector<V>>::getMinNode(z->right);
		yorigcol = y->color;
		x = y->right;
		if (y->parent == z)
			x->parent = y;
		else {
			RBTree<T, vector<V>>::transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		RBTree<T, vector<V>>::transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
    delete z;
    if (yorigcol == BLACK)
        RBTree<T, vector<V>>::deleteFix(x);
}

// empty function to check if empty
template<class T, class V>
bool multimap<T, V>::empty()
{
    bool checker = false;

    if(RBTree<T, vector<V>>::root == RBTree<T, vector<V>>::NIL)
        checker = true;

    return checker;
}

template<class T, class V>
vector<V> multimap<T, V>::get(T key)
{
    if(!find(key))
        throw std::runtime_error("Pair not in the set");
    // find the node an return the vector
    return RBTree<T, vector<V>>::findNode(key)->value;
}

// simple set function to set a pair into the multimap structure
template<class T, class V>
void multimap<T, V>::set(T key, V value)
{
    insert(key, value);
}

// overload the == operator
template<class T, class V>
bool multimap<T, V>::operator==(multimap<T, V>& right)
{
    return InOrderSubset(RBTree<T, vector<V>>::root, right) && InOrderSubset(right.RBTree<T, vector<V>>::root, right.RBTree<T, vector<V>>::NIL);
}

// overload the != operator
template<class T, class V>
bool multimap<T, V>::operator!=(multimap<T, V>& right)
{
    return !(InOrderSubset(RBTree<T, vector<V>>::root, right) && InOrderSubset(right.RBTree<T, vector<V>>::root, right.RBTree<T, vector<V>>::NIL));
}

// overload the << operator
template<class T, class V>
ostream& operator<<(ostream& os, multimap<T, V>& obj)
{
    os<<"{ ";
    int count = 0;
    obj.InOrderDisplay(obj.RBTree<T, vector<V>>::root, os, count);
    os<<" }\n";
    return os;
}

#endif
