// Implementation file for the IntBinaryTree class
#include <iostream>
#include "IntBinaryTree.h"
using namespace std;

//***************************************************
// destroySubTree is called by the destructor. It   *
// deletes all nodes in the tree.                   *
//***************************************************

void IntBinaryTree::destroySubTree(TreeNode *nodePtr) {
	if (nodePtr) {
		if (nodePtr->left)
			destroySubTree(nodePtr->left);
		if (nodePtr->right)
			destroySubTree(nodePtr->right);
		delete nodePtr;
	}
}

//***********************************************************
// makeDeletion takes a reference to a pointer to the node  *
// that is to be deleted. The node is removed and the       *
// branches of the tree below the node are reattached.      *
//***********************************************************

void IntBinaryTree::makeDeletion(TreeNode *&nodePtr) {
	// Define a temporary pointer to use in reattaching
	// the left subtree.
	TreeNode *tempNodePtr = nullptr;

	if (nodePtr == nullptr)
		cout << "Cannot delete empty node.\n";
	else if (nodePtr->right == nullptr) {
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->left;   // Reattach the left child
		delete tempNodePtr;
	} else if (nodePtr->left == nullptr) {
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->right;  // Reattach the right child
		delete tempNodePtr;
	}
	// If the node has two children.
	else {
		// Move one node the right.
		tempNodePtr = nodePtr->right;
		// Go to the end left node.
		while (tempNodePtr->left)
			tempNodePtr = tempNodePtr->left;
		// Reattach the left subtree.
		tempNodePtr->left = nodePtr->left;
		tempNodePtr = nodePtr;
		// Reattach the right subtree.
		nodePtr = nodePtr->right;
		delete tempNodePtr;
	}
}

//****************************************************************
// The displayInOrder member function displays the values        *
// in the subtree pointed to by nodePtr, via inorder traversal.  *
//****************************************************************

void IntBinaryTree::displayInOrder(TreeNode *nodePtr) const {
	if (nodePtr) {
		displayInOrder(nodePtr->left);
		cout << nodePtr->value << endl;
		displayInOrder(nodePtr->right);
	}
}

//****************************************************************
// The displayPreOrder member function displays the values       *
// in the subtree pointed to by nodePtr, via preorder traversal. *
//****************************************************************

void IntBinaryTree::displayPreOrder(TreeNode *nodePtr) const {
	if (nodePtr) {
		cout << nodePtr->value << endl;
		displayPreOrder(nodePtr->left);
		displayPreOrder(nodePtr->right);
	}
}

//****************************************************************
// The displayPostOrder member function displays the values      *
// in the subtree pointed to by nodePtr, via postorder traversal.*
//****************************************************************

void IntBinaryTree::displayPostOrder(TreeNode *nodePtr) const {
	if (nodePtr) {
		displayPostOrder(nodePtr->left);
		displayPostOrder(nodePtr->right);
		cout << nodePtr->value << endl;
	}
}

//****************************************************************
// Simple helper function to do the indentations for the tree
// printing algorithm.
//****************************************************************

void IntBinaryTree::IndentBlock(int num) {
	for (int i = 0; i < num; i++)
		cout << " ";
}

//****************************************************************
// This function recursively prints the tree contents to the
// console using a reverse inorder traversal with indenting.
//****************************************************************

void IntBinaryTree::PrintTree(TreeNode *t, int Indent, int Level) {
	if (t != NULL) {
		PrintTree(t->right, Indent, Level + 1);
		IndentBlock(Indent * Level);
		cout << t->value << "\n";
		PrintTree(t->left, Indent, Level + 1);
	}
}

//****************************************************************
// This function initiates the recursive printing function to
// print the contents of the tree in tree form sideways with the
// root at the far left.
//****************************************************************

void IntBinaryTree::PrintTree(int Indent, int Level) {
	if (root != NULL)
		PrintTree(root, Indent, Level);
}

/*
 * This funcion finds the max value in an array and returns the max+1 
 */
int IntBinaryTree::maxValue(int *A, int sz)
{
	//set max to the max value so far
	int max = A[0];

	// loop through changing the max if it is found
	for(int i = 1; i < sz; i++){
		if(max < A[i])
			max = A[i];
	}

	return (max+1);
}


/* Build the tree recursively
 *
 */
void IntBinaryTree::buildTree(TreeNode *nodePtr, queue<TreeNode*> varList, int height, int maxVar, int h)
{
	if(height == h){ // if depth is reached then setup nodes accordingly
		if(!varList.empty()){ // if the queue is not empty place value
			TreeNode *newNode = varList.front();
			varList.pop();
		}
		else { // when queue is empty set to the max var
			TreeNode *newNode = new TreeNode();
			newNode->value = maxVar;
		}
	}
	else if(height != h){ // if still in null nodes recurse
		nodePtr = new TreeNode();
		nodePtr->value = -1;
		height++;
		buildTree(nodePtr->left, varList, height++, maxVar, h); // left recursive step
		buildTree(nodePtr->right, varList, height++, maxVar, h); // right recursive step
	}
}

/*
 * Take an array of integers of size sz and create a tree with all the values at the bottom
 * 2 parameters: the array and the size
 */
void IntBinaryTree::LoadArray(int *A, int sz)
{	
	queue<TreeNode*> varList;
	for(int i = 0; i<sz; i++){
		TreeNode *node = new TreeNode();
		node->value = *(A+1);
		varList.push(node);
	}
	buildTree(root, varList, 0, maxValue(A, sz), ceil(log2(sz))+1);
}

//void IntBinaryTree::

/*void ReturnSortedArray(int *A, int sz)
{
	TreeNode *nodePtr = root;
	TreeNode *tmp = nodePtr->left;

	while(nodePtr->value == -1){
*/
//EOF
//
