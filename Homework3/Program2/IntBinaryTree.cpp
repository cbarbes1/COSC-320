/* 
 * Edited by: Cole Barbes on 09/20/2023
 * This code is example code that was edited to perform a sort using a tree
 */

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
	cout<<root->value<<endl;
	if (root != NULL)
		PrintTree(root, Indent, Level);
}

/*
 * This funcion finds the max value in an array and returns the max+1
 * return: the max+1 in an array
 * Parameters: A dynamically allocated array and its size
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
 * Parameters: A tree node pointer, a stl queue, the height at which the function is, the max of the array, and the desired height 
 */
void IntBinaryTree::buildTree(TreeNode *&nodePtr, queue<int> &varList, int height, int maxVar, int h)
{
	height++;
	if(height == h){ // if depth is reached then setup nodes accordingly
		if(!varList.empty()){ // if the queue is not empty place value
			nodePtr = new TreeNode();
			nodePtr->value = varList.front();
			varList.pop();
		}
		else { // when queue is empty set to the max var
			nodePtr = new TreeNode();
			nodePtr->value = maxVar;
		}
	}
	else if(height != h){ // if still in null nodes recurse
		nodePtr = new TreeNode();
		nodePtr->value = -1;
		buildTree(nodePtr->left, varList, height, maxVar, h); // left recursive step
		buildTree(nodePtr->right, varList, height, maxVar, h); // right recursive step
	}
}

/*
 * Take an array of integers of size sz and create a tree with all the values at the bottom
 * 2 parameters: the array and the size
 */
void IntBinaryTree::LoadArray(int *A, int sz)
{	
	queue<int> varList;
	for(int i = 0; i<sz; i++){ // loop to push element into the queue
		varList.push(A[i]);
	}
	// start the recursion
	buildTree(root, varList, 0, maxValue(A, sz), ceil(log2(sz))+1);
}


/* 
 * Recurse through a given tree, setting the minimum of the 2 branched leaves through the whole tree
 * Parameters: the tree node, the max value
 * Return: The value of the sub trees minimum
 */
int IntBinaryTree::minTree(TreeNode *&nodePtr, int maxVar)
{
	if(nodePtr->left && nodePtr->right){ // if there are leaves to this node 
		// recurse left and right saving the value of the previous recursive step
		int lvar = minTree(nodePtr->left, maxVar);
		int rvar = minTree(nodePtr->right, maxVar);
		
		if(lvar<rvar){ // if left is less than the right set the nodes value to the left
			nodePtr->value = lvar;
		}
		else{ // if equal or greater, set the nodes value to the right
			nodePtr->value = rvar;
		}
	}
	return nodePtr->value; // return the value in the node
}

/* Clear the minimum values from the list
 * Parameters: A tree node pointer, the minimum, and the max
 * return: a boolean value for recursive steps 
 */
bool IntBinaryTree::clearMin(TreeNode *&nodePtr, int emin, int maxVar)
{
	if(!nodePtr->left && !nodePtr->right){ // if the node is a leaf 
		if(nodePtr->value == emin){ // if leaf is the emin 
			//set the value to the maxvar and return true
			nodePtr->value = maxVar;
			return true;
		}
		return false; // if not emin then false
	}
	else{// if not then recurse and check if there was a minimum in the leaf
		bool left = false;
		bool right = false;

		if(nodePtr->left->value == emin)
			left = clearMin(nodePtr->left, emin, maxVar);
		else
			right = clearMin(nodePtr->right, emin, maxVar);

		if(left || right)
			nodePtr->value = maxVar;

		return (left || right); // return whether there was a leaf in this step
	}
}
			
/*
 * grab the sorted array out of the tree 
 * Parameters: The array to save the values in and the size
 */
void IntBinaryTree::ReturnSortedArray(int *A, int sz)
{

	int max = maxValue(A, sz);
	int count = 0;
	int emin = 0;
	
	// while not the max and the count doesnt equal the size
	while(emin != max && sz != count){
		emin = minTree(root, max);
		A[count++] = emin; 
		clearMin(root, emin, max);
		emin = minTree(root, max);
	}
}

//EOF
//
////
////
////
////
