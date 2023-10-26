/******************************************************************************************************
 * Authors: Cole Barbes and Harrison Colborne
 * Creation Date: 10/18/23
 * Last Edited: 10/18/23
 * Description: implementation of a set class similar to the stl set 
******************************************************************************************************/
#ifndef SET_H
#define SET_H

#include <iostream>
#include "RBTree.h"

using namespace std;

// set class declaration
template<class T>
class set : public RBTree<T>{
private:
    void copy(RBTreeNode<T>*&, RBTreeNode<T>*);
    void InOrderAction(RBTreeNode<T>*&, void (*)(T&));
public:
    set();
    set(set<T>&);
    ~set();
    
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
    void toArray(T arr);

    // overloaded assignment operator
    set<T> operator=(set<T>& right);
};
    
template<class T>
set<T>::set()
{
}

/*
 * copy each node recursively in a sub tree pointed to by nodePtr
 */
void set<T>::copy(RBTreeNode<T> *&nodePtr, RBTreeNode<T> *&next)
{
    if(nodePtr){
        next = new RBTreeNode<T>(nodePtr->value, nodePtr->color, nullptr, nullptr, nullptr);
        copy(nodePtr->left, next->left);
        copy(nodePtr->right, next->right);
    }
}

void InOrderAction(RBTreeNode<T> *&nodePtr, void (*func)(T &value))
{
    if(nodePtr){
        InOrderAction(nodePtr->left);
        func(nodePtr->value);
        InOrderAction(nodePtr->right);
    }
}
/*
 * overload the assignment operator
 */
set<T> set<T>::operator=(set<T>& right)
{
    copy(RBTree::root, right.RBTree::root);
}

template<class T>
set<T>::set(set<T> &other)
{
    copy(RBTree::root, other.RBTree::root);
}

template<class T>
set<T>::~set()
{
    RBTree::~RBTree();
}

/*
 * Description: Insert function which calls the addElement function and only adds a non copy function
 * Parameters: item to be added
 */
template<class T>
void set<T>::insert(T item)
{
    RBTree::addElement(item);
}


/*
 * Find a value in the set
 */
/*
template<class T>
bool set<T>::find(T item)
{
    return find(item);
}
*/

/*
 * Erase a value from the tree
 */
template<class T>
void set<T>::erase(T item)
{
    RBTree::remove(item);
}

// empty function to check if empty
bool empty()
{
    bool checker = false;

    if(RBTree::root == RBTree::NIL)
        checker = true;

    return checker;
}

// convert the set to a vector
void toVector(vector<T>&)
{

}
// convert the set to an array
void toArray(T arr)
{

}



#endif // end of the declaration and implementation of set class
    
