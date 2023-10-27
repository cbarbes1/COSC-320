#ifndef MAP_H
#define MAP_H

#include <iostream>
using namespace std;

// map class declaration
template<class T, class V>
class map : public RBTree<T, V>{
private:
    void copy(RBTreeNode<T, V>*, RBTreeNode<T, V>*&, RBTreeNode<T, V>*, RBTreeNode<T, V> *NilPtr);
    ostream& InOrderDisplay(RBTreeNode<T, V> *, ostream&);
    void InOrderVector(RBTreeNode<T, V>*, vector<T, V>&);
    void InOrderArray(RBTreeNode<T, V>*, T [], int &n, const int);

    bool InOrderSubset(RBTreeNode<T, V>*, map<T, V>&);
    bool InOrderSubset(RBTreeNode<T, V>*, RBTreeNode<T, V>*);
public:
    map();
    map(const map<T, V>&);
    ~map();
    
    // insert a value into the map
    void insert(T, V);
    // find a value 
    bool find(T, V);
    //erase a value from the map
    void erase(T, V);
    // empty function to check if empty
    bool empty();
    
    int size();
    
    void clear();

    // overloaded assignment operator
    map<T, V> operator=(const map<T, V>& right);

    bool operator==(map<T, V>& right);

    bool operator!=(map<T, V>& right);

    template<class c>
    friend ostream& operator<<(ostream& os, map<c>& obj);
};
    
template<class T, class V>
map<T, V>::map()
{
}

/*
 * copy each node recursively in a sub tree pointed to by nodePtr
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

template<class T, class V>
void map<T, V>::InOrderVector(RBTreeNode<T, V> *nodePtr, vector<T, V>& vect)
{
    if(nodePtr != RBTree<T, V>::NIL){
        InOrderVector(nodePtr->left, vect);
        vect.push_back(nodePtr->value);
        InOrderVector(nodePtr->right, vect);
    }
}

template<class T, class V>
void map<T, V>::InOrderArray(RBTreeNode<T, V> *nodePtr, T arr[], int &n, const int size)
{
    if(nodePtr != RBTree<T, V>::NIL && n<size){
        InOrderArray(nodePtr->left, arr, n, size);
        arr[n++] = nodePtr->value;
        InOrderArray(nodePtr->right, arr, n, size);
    }
}

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
 * overload the assignment operator
 */
template<class T, class V>
map<T, V> map<T, V>::operator=(const map<T, V>& right)
{
    RBTree<T, V>::destroySubTree(RBTree<T, V>::root);
    copy(right.RBTree<T, V>::root, RBTree<T, V>::root, RBTree<T, V>::NIL, right.RBTree<T, V>::NIL);
}

template<class T, class V>
int map<T, V>::size()
{
    vector<T, V> V;
    toVector(V);
    
    int size = V.size();
    
    return size;
}

template<class T, class V>
void map<T, V>::clear()
{
    vector<T, V> V;
    toVector(V);
    
    for(unsigned int i = 0; i<V.size(); i++)
        erase(V[i]);
}

template<class T, class V>
map<T, V>::map(const map<T, V> &right)
{
    copy(right.RBTree<T, V>::root, RBTree<T, V>::root, RBTree<T, V>::NIL, right.RBTree<T, V>::NIL);
}

template<class T, class V>
map<T, V>::~map()
{
}

/*
 * Description: Insert function which calls the addElement function and only adds a non copy function
 * Parameters: item to be added
 */
template<class T, class V>
void map<T, V>::insert(T key, V value)
{
    RBTreeNode<T, V> *newnode = new RBTreeNode<T, V>(key, value, RED, RBTree<T, V>::NIL, RBTree<T, V>::NIL, RBTree<T, V>::NIL);
	RBTreeNode<T, V> *y = RBTree<T, V>::NIL;
	RBTreeNode<T, V> *x = RBTree<T, V>::root;

	while (x != RBTree<T, V>::NIL) {
		y = x;
		if (val < x->value)
			x = x->left;
		else
			x = x->right;
	}

	if(newnode->value == y->value){
        delete newnode;
        return;
    }

	newnode->parent = y;
	if (y == RBTree<T, V>::NIL)
		RBTree<T, V>::root = newnode;
	else if (newnode->key < y->value)
		y->left = newnode;
	else if(newnode->key > y->value)
		y->right = newnode;

	//  Adjust the RB tree to retain the properties.
    // if the value is not in the tree insert it
    RBTree<T, V>::insertFix(newnode);
}


/*
 * Find a value in the map
 */
template<class T, class V>
bool map<T, V>::find(T key, V value)
{
    return RBTree<T, V>::find(key, value);
}


/*
 * Erase a value from the tree
 */
template<class T, class V>
void map<T, V>::erase(T key, V value)
{
    RBTreeNode<T, V> *z = RBTree<T, V>::findNode(key, value);
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
bool map<T, V>::operator==(map<T, V>& right)
{
    return InOrderSubset(RBTree<T, V>::root, right) && InOrderSubset(right.RBTree<T, V>::root, right.RBTree<T, V>::NIL);
}

template<class T, class V>
bool map<T, V>::operator!=(map<T, V>& right)
{
    return !(InOrderSubset(RBTree<T, V>::root, right) && InOrderSubset(right.RBTree<T, V>::root, right.RBTree<T, V>::NIL));
}

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
