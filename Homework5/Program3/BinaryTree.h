/*
 * code sourced from Dr. Spicklers 320 data structures and algorithms course 
 * last edited 10/05/23 by Cole Barbes
 */
#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>

using namespace std;

template<class T>
class TreeNode {
public:
	T value;
	TreeNode *left;
	TreeNode *right;

	TreeNode() {
		left = nullptr;
		right = nullptr;
	}
};

template<class T, class Node = TreeNode<T>>
class BinaryTree {
protected:
	Node *root;
	void destroySubTree(Node*);
	void InOrderRec(Node*, void (*fct)(T&)) const;
	void PreOrderRec(Node*, void (*fct)(T&)) const;
	void PostOrderRec(Node*, void (*fct)(T&)) const;
	void IndentBlock(int num);
	void PrintTreeRec(Node *t, int Indent, int Level);
    
    void copyTree(Node *&nodePtr, Node *rootOldNode);

public:
	BinaryTree() {
		root = nullptr;
	}

	virtual ~BinaryTree() {
		destroySubTree(root);
	}

	virtual void insert(T) = 0;
	virtual void remove(T) = 0;
    
     
    // copy constructor
    BinaryTree(BinaryTree&);

    // equals operator
    void operator=(BinaryTree&);

	void InOrder(void (*fct)(T&)) const {
		InOrderRec(root, fct);
	}

	void PreOrder(void (*fct)(T&)) const {
		PreOrderRec(root, fct);
	}

	void PostOrder(void (*fct)(T&)) const {
		PostOrderRec(root, fct);
	}

	void PrintTree(int Indent = 4, int Level = 0);
};

//***************************************************
// destroySubTree is called by the destructor. It   *
// deletes all nodes in the tree.                   *
//***************************************************
template<class T, class Node>
void BinaryTree<T, Node>::destroySubTree(Node *nodePtr) {
	if (nodePtr) {
		if (nodePtr->left)
			destroySubTree(nodePtr->left);
		if (nodePtr->right)
			destroySubTree(nodePtr->right);
		delete nodePtr;
	}
}

/*
 * The InOrderRec member function displays the values in the subtree
 * pointed to by nodePtr, via recursive inorder traversal.
 */
template<class T, class Node> void BinaryTree<T, Node>::InOrderRec(
		Node *nodePtr, void (*fct)(T&)) const {
	if (nodePtr) {
		InOrderRec(nodePtr->left, fct);
		fct(nodePtr->value);
		InOrderRec(nodePtr->right, fct);
	}
}
/*
 * The PreOrderRec member function displays the values in the subtree
 * pointed to by nodePtr, via recursive preorder traversal.
 */
template<class T, class Node> void BinaryTree<T, Node>::PreOrderRec(
		Node *nodePtr, void (*fct)(T&)) const {
	if (nodePtr) {
		fct(nodePtr->value);
		PreOrderRec(nodePtr->left, fct);
		PreOrderRec(nodePtr->right, fct);
	}
}
/*
 * The PostOrderRec member function displays the values in the subtree
 * pointed to by nodePtr, via recursive postorder traversal.
 */
template<class T, class Node> void BinaryTree<T, Node>::PostOrderRec(
		Node *nodePtr, void (*fct)(T&)) const {
	if (nodePtr) {
		PostOrderRec(nodePtr->left, fct);
		PostOrderRec(nodePtr->right, fct);
		fct(nodePtr->value);
	}
}
//****************************************************************
// Simple helper function to do the indentations for the tree
// printing algorithm.
//****************************************************************
template<class T, class Node> void BinaryTree<T, Node>::IndentBlock(int num) {
	for (int i = 0; i < num; i++)
		cout << " ";
}
//****************************************************************
// This function recursively prints the tree contents to the
// console using a reverse inorder traversal with indenting.
//****************************************************************
template<class T, class Node>
void BinaryTree<T, Node>::PrintTreeRec(Node *t, int Indent, int Level) {
	if (t) {
		PrintTreeRec(t->right, Indent, Level + 1);
		IndentBlock(Indent * Level);
		cout << t->value << "\n";
		PrintTreeRec(t->left, Indent, Level + 1);
	}
}
//****************************************************************
// This function initiates the recursive printing function to
// print the contents of the tree in tree form sideways with the
// root at the far left.
//****************************************************************
template<class T, class Node> void BinaryTree<T, Node>::PrintTree(int Indent,
		int Level) {
	if (root)
		PrintTreeRec(root, Indent, Level);
}

/*
Description: This function copies a given tree
Parameters: the root and the nodeptr
*/
template<class T, class Node>
void BinaryTree<T, Node>::copyTree(Node*& nodePtr, Node *rootOther)
{
    if(rootOther){ // if the tree is valid continue
        Node* newNode = new Node; // create the node
        newNode->value = rootOther->value; // set the value
        newNode->left = newNode->right = nullptr; 
        nodePtr = newNode;// set the pointer to the new node
        copyTree(nodePtr->left, rootOther->left); // recurse to left subtree
        copyTree(nodePtr->right, rootOther->right);// recurse to right subtree
    }
    return;
}

/*
Description: The binary tree copy constructor 
Parameters: The binary tree to be copied 
*/
template<class T, class Node>
BinaryTree<T, Node>::BinaryTree(BinaryTree& obj)
{
    if(obj.root){ // check if the root exists
        copyTree(root, obj.root);
    }
}

/*
Description: The equals operator overload
Parameters: The other binary tree
Return the binary tree
*/
template<class T, class Node>
void BinaryTree<T, Node>::operator=(BinaryTree& other){
    destroySubTree(root);
    if(other.root){
        copyTree(root, other.root);
    }
}



#endif
