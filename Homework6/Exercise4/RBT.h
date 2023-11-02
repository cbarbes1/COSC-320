#ifndef RBT_H_
#define RBT_H_

#include <string>
#include <sstream>

using namespace std;

enum ccolor_t {
	RRED, BBLACK
// Red = 0, Black = 1
};

template<class T>
class RBTNode {
public:
	T value;
	ccolor_t color;
	RBTNode *left;
	RBTNode *right;
	RBTNode *parent;

	RBTNode() {
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		color = RRED;
	}

	RBTNode(T val, ccolor_t col, RBTNode *l, RBTNode *r,
			RBTNode *p) {
		value = val;
		left = l;
		right = r;
		parent = p;
		color = col;
	}
};

template<class T>
class RBT {
protected:
	RBTNode<T> *root;
	RBTNode<T> *NIL;
	void IndentBlock(int num);
	void PrintTree(RBTNode<T>*, int, int);

	void LeftRotation(RBTNode<T>*);
	void RightRotation(RBTNode<T>*);
	void insertFix(RBTNode<T>*);

	void transplant(RBTNode<T>*, RBTNode<T>*);
	void deleteFix(RBTNode<T>*);
	RBTNode<T>* getMinNode(RBTNode<T>*);

	void destroySubTree(RBTNode<T>*);
    
    int InOrdercount(RBTNode<T> *, int &);
    
    string InOrderDisplay(RBTNode<T> *, string&, int &);
    
    void InOrderVector(RBTNode<T>*, vector<T>&);

public:
	RBT();
	virtual ~RBT();

	virtual void insert(T);
	void remove(T);
    
    int size(); // return the size

	bool find(const T &item);
	RBTNode<T>* findNode(const T&);

	void PrintTree(int Indent = 4, int Level = 0);
    
    string toString();
    
    vector<T> toVector(vector<T> &vect);
};

template<class T>
RBT<T>::RBT() {
	NIL = new RBTNode<T>(T(), BBLACK, nullptr, nullptr, nullptr);
	root = NIL;
}

template<class T>
RBT<T>::~RBT() {
	destroySubTree(root);
	delete NIL;
}

/*
 * Recursively frees the memory of the subtree pointed to by nodePtr.
 */
template<class T>
void RBT<T>::destroySubTree(RBTNode<T> *nodePtr) {
	if (nodePtr != NIL) {
		if (nodePtr->left != NIL)
			destroySubTree(nodePtr->left);
		if (nodePtr->right != NIL)
			destroySubTree(nodePtr->right);
		delete nodePtr;
	}
}

/*
 * count number of elements
 * parameters: the subtree pointer, the count variable
 * return the count of the multimap
 */
template<class T>
int RBT<T>::InOrdercount(RBTNode<T> *nodePtr, int &count)
{
    if(nodePtr != NIL){
        InOrdercount(nodePtr->left, count);
        count++;
        InOrdercount(nodePtr->right, count);
    }
    return count;
}

/*
 * insert the set into a vector using an in order traversal
 * paremeters: the node of the subtree, the vector
 */
template<class T>
void RBT<T>::InOrderVector(RBTNode<T> *nodePtr, vector<T>& vect)
{
    // if nil is encountered then stop
    if(nodePtr != NIL){
        InOrderVector(nodePtr->left, vect);
        vect.push_back(nodePtr->value);
        InOrderVector(nodePtr->right, vect);
    }
}

// convert the set to a vector
template<class T>
void set<T>::toVector(vector<T>& vect)
{
    InOrderVector(RBTree<T>::root, vect);
}

/*
 * return the size of the multimap
 */
template<class T>
int RBT<T>::size()
{
    int size = 0;
    
    InOrdercount(root, size);

    return size;
}

/*
 * Inserts a new node into the RB-Tree as with a standard BST but then calls the
 * insertFix function to adjust the tree back to an RB tree.
 */
template<class T>
void RBT<T>::insert(T val) {
	RBTNode<T> *newnode = new RBTNode<T>(val, RRED, NIL, NIL, NIL);
	RBTNode<T> *y = NIL;
	RBTNode<T> *x = root;

	while (x != NIL) {
		y = x;
		if (val < x->value)
			x = x->left;
		else
			x = x->right;
	}

	newnode->parent = y;
	if (y == NIL)
		root = newnode;
	else if (newnode->value < y->value)
		y->left = newnode;
	else if(newnode->value >= y->value)
		y->right = newnode;

	//  Adjust the RB tree to retain the properties.
	insertFix(newnode);
}

/*
 * Adjusts the tree back to an RB tree after insertion of a new node.
 */
template<class T>
void RBT<T>::insertFix(RBTNode<T> *z) {
	RBTNode<T> *y = NIL;

	while (z->parent->color == RRED) {
		if (z->parent == z->parent->parent->left) {
			y = z->parent->parent->right;
			if (y->color == RRED) {
				z->parent->color = BBLACK;
				y->color = BBLACK;
				z->parent->parent->color = RRED;
				z = z->parent->parent;
			} else {
				if (z == z->parent->right) {
					z = z->parent;
					LeftRotation(z);
				}
				z->parent->color = BBLACK;
				z->parent->parent->color = RRED;
				RightRotation(z->parent->parent);
			}
		} else {
			y = z->parent->parent->left;
			if (y->color == RRED) {
				z->parent->color = BBLACK;
				y->color = BBLACK;
				z->parent->parent->color = RRED;
				z = z->parent->parent;
			} else {
				if (z == z->parent->left) {
					z = z->parent;
					RightRotation(z);
				}
				z->parent->color = BBLACK;
				z->parent->parent->color = RRED;
				LeftRotation(z->parent->parent);
			}
		}
	}
	root->color = BBLACK;
}

/*
 * This is a helper function to the node deletion process.
 */
template<class T>
void RBT<T>::transplant(RBTNode<T> *u, RBTNode<T> *v) {
	if (u->parent == NIL)
		root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	v->parent = u->parent;
}

/*
 * Finds the smallest node in the subtree pointed to by x.  As usual
 * we traverse down the left branch as far as possible.  The node y
 * tracks x's parent so that when x == NIL, y is the minimum valued
 * node.
 */
template<class T>
RBTNode<T>* RBT<T>::getMinNode(RBTNode<T> *x) {
	if (x == NIL)
		return NIL;

	RBTNode<T> *y = NIL;
	while (x != NIL) {
		y = x;
		x = x->left;
	}
	return y;
}

/*
 * Finds and deletes the node whose value is val.  Calls the deleteFix function
 * to readjust the tree back to RB format.
 */
template<class T>
void RBT<T>::remove(T val) {
	RBTNode<T> *z = findNode(val);
	if (z == NIL)
		return;

	RBTNode<T> *y = z;
	RBTNode<T> *x = NIL;
	ccolor_t yorigcol = y->color;

	if (z->left == NIL) {
		x = z->right;
		transplant(z, z->right);
	} else if (z->right == NIL) {
		x = z->left;
		transplant(z, z->left);
	} else {
		y = getMinNode(z->right);
		yorigcol = y->color;
		x = y->right;
		if (y->parent == z)
			x->parent = y;
		else {
			transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	delete z;
	if (yorigcol == BBLACK)
		deleteFix(x);
}

/*
 * Readjusts the RB tree to fix any violated properties after the deletion of a
 * node.
 */
template<class T>
void RBT<T>::deleteFix(RBTNode<T> *x) {
	RBTNode<T> *w = NIL;

	while (x != root && x->color == BBLACK) {
		if (x == x->parent->left) {
			w = x->parent->right;
			if (w->color == RRED) {
				w->color = BBLACK;
				x->parent->color = RRED;
				LeftRotation(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == BBLACK && w->right->color == BBLACK) {
				w->color = RRED;
				x = x->parent;
			} else {
				if (w->right->color == BBLACK) {
					w->left->color = BBLACK;
					w->color = RRED;
					RightRotation(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BBLACK;
				w->right->color = BBLACK;
				LeftRotation(x->parent);
				x = root;
			}
		} else {
			w = x->parent->left;
			if (w->color == RRED) {
				w->color = BBLACK;
				x->parent->color = RRED;
				RightRotation(x->parent);
				w = x->parent->left;
			}
			if (w->left->color == BBLACK && w->right->color == BBLACK) {
				w->color = RRED;
				x = x->parent;
			} else {
				if (w->left->color == BBLACK) {
					w->right->color = BBLACK;
					w->color = RRED;
					LeftRotation(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BBLACK;
				w->left->color = BBLACK;
				RightRotation(x->parent);
				x = root;
			}
		}
	}
	x->color = BBLACK;
}

/*
 * This returns true if the item is in the RB-tree and false otherwise.
 * It simply calls the node based recursive version and checks the result
 * against the NIL object.
 */
template<class T>
bool RBT<T>::find(const T &item) {
	return findNode(item) != NIL;
}

/*
 Does a right rotation at the input node.
 The function also updates the height values for the nodes.

 Parameters
 x --- pointer to the node to rotate right around.
 */

template<class T>
void RBT<T>::RightRotation(RBTNode<T> *x) {
	RBTNode<T> *y = x->left;
	x->left = y->right;

	if (y->right != NIL)
		y->right->parent = x;

	y->parent = x->parent;

	if (x->parent == NIL)
		root = y;
	else if (x == x->parent->right)
		x->parent->right = y;
	else
		x->parent->left = y;

	y->right = x;
	x->parent = y;
}

/*
 Does a left rotation at the input node.
 The function also updates the height values for the nodes.

 Parameters
 nodePtr --- pointer to the node to rotate right around.
 */

template<class T>
void RBT<T>::LeftRotation(RBTNode<T> *x) {
	RBTNode<T> *y = x->right;
	x->right = y->left;

	if (y->left != NIL)
		y->left->parent = x;

	y->parent = x->parent;

	if (x->parent == NIL)
		root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;

	y->left = x;
	x->parent = y;
}

/*
 * Recursive find function that finds the first node containing the value item.
 */
template<class T>
RBTNode<T>* RBT<T>::findNode(const T &item) {
	RBTNode<T> *nodePtr = root;

	while (nodePtr != NIL) {
		if (nodePtr->value == item)
			return nodePtr;
		else if (item < nodePtr->value)
			nodePtr = nodePtr->left;
		else
			nodePtr = nodePtr->right;
	}
	return NIL;
}

//****************************************************************
// Simple helper function to do the indentations for the tree
// printing algorithm.
//****************************************************************
template<class T>
void RBT<T>::IndentBlock(int num) {
	for (int i = 0; i < num; i++)
		cout << " ";
}

//****************************************************************
// This function recursively prints the tree contents to the
// console using a reverse inorder traversal with indenting.
// This includes the height and balance factor of each node.
//****************************************************************

template<class T>
void RBT<T>::PrintTree(RBTNode<T> *t, int Indent, int Level) {
	if (t != NIL) {
		PrintTree(t->right, Indent, Level + 1);
		string RBstr;
		if (t->color == RRED)
			RBstr = "R";
		else
			RBstr = "B";


		IndentBlock(Indent * Level);
		cout << t->value << " (" << RBstr << ")" << endl;

		PrintTree(t->left, Indent, Level + 1);
	}
}

//****************************************************************
// This function initiates the recursive printing function to
// print the contents of the tree in tree form sideways with the
// root at the far left. This includes the height and balance
// factor of each node.
//****************************************************************

template<class T>
void RBT<T>::PrintTree(int Indent, int Level) {
	if (root)
		PrintTree(root, Indent, Level);
}

template<class T>
string RBT<T>::toString() {
    string strng = "";
    string divider = " \\ ";
    stringstream s;
    vector<T> vect;
    InOrderVector(root, vect);
    for(unsigned int i = 0; i<vect.size(); i++){
        s>>vect[i];
        if(i < (vect.size()-1))
            s>>divider;
    }
    strng = s.str();
    return strng;
}

#endif /* RBTREE_H_ */
