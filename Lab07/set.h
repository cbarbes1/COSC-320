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
class set{
private:
    RBTree<T> key; // tree for faster access and find of set values
public:
    set();
    ~set();
    
    // insert a value into the set
    void insert(T);
    // find a value 
    bool find(T);
    //erase a value from the set
    void erase(T);
};
    
template<class T>
set<T>::set()
{
}

template<class T>
set<T>::~set()
{
}

/*
 * Description: Insert function which calls the addElement function and only adds a non copy function
 * Parameters: item to be added
 */
template<class T>
void set<T>::insert(T item)
{
    key.addElement(item);
}

/*
 * Find a value in the set
 */
template<class T>
bool set<T>::find(T item)
{
    return key.find(item);
}

/*
 * Erase a value from the tree
 */
template<class T>
void set<T>::erase(T item)
{
    key.remove(item);
}

#endif // end of the declaration and implementation of set class
    
