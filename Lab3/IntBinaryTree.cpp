// Harrison Colborne and Cole Barbes
// Implementation file for the IntBinaryTree class
#include <iostream>
#include "IntBinaryTree.h"
#include <vector>
using namespace std;

//*************************************************************
// insert accepts a TreeNode pointer and a pointer to a node. *
// The function inserts the node into the tree pointed to by  *
// the TreeNode pointer. This function is called recursively. *
//*************************************************************

void IntBinaryTree::insert(TreeNode *&nodePtr, TreeNode *&newNode) {
	if (nodePtr == nullptr)
		nodePtr = newNode;                  // Insert the node.
	else if (newNode->value < nodePtr->value)
		insert(nodePtr->left, newNode);     // Search the left branch
	else
		insert(nodePtr->right, newNode);    // Search the right branch
}

//**********************************************************
// insertNode creates a new node to hold num as its value, *
// and passes it to the insert function.                   *
//**********************************************************

void IntBinaryTree::insertNode(int num) {
	TreeNode *newNode = nullptr;	// Pointer to a new node.

	// Create a new node and store num in it.
	newNode = new TreeNode;
	newNode->value = num;
	newNode->left = newNode->right = nullptr;

	// Insert the node.
	insert(root, newNode);
}

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

//***************************************************
// searchNode determines if a value is present in   *
// the tree. If so, the function returns true.      *
// Otherwise, it returns false.                     *
//***************************************************

bool IntBinaryTree::searchNode(int num) {
	TreeNode *nodePtr = root;

	while (nodePtr) {
		if (nodePtr->value == num)
			return true;
		else if (num < nodePtr->value)
			nodePtr = nodePtr->left;
		else
			nodePtr = nodePtr->right;
	}
	return false;
}

//**********************************************
// remove calls deleteNode to delete the       *
// node whose value member is the same as num. *
//**********************************************

void IntBinaryTree::remove(int num) {
	deleteNode(num, root);
}

//********************************************
// deleteNode deletes the node whose value   *
// member is the same as num.                *
//********************************************

void IntBinaryTree::deleteNode(int num, TreeNode *&nodePtr) {
	if (num < nodePtr->value)
		deleteNode(num, nodePtr->left);
	else if (num > nodePtr->value)
		deleteNode(num, nodePtr->right);
	else
		makeDeletion(nodePtr);
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

// count number of nodes
int IntBinaryTree::numNodes(TreeNode *nodePtr) const{
	if(nodePtr){
		return numNodes(nodePtr->left) + numNodes(nodePtr->right) + 1;
	}
	return 0;
}

// count number of leaves meaning the number of nodes with null left and right children
int IntBinaryTree::numLeaves(TreeNode *nodePtr) const{
	if(nodePtr){
		if(!nodePtr->left && !nodePtr->right){
			return 1;
		}
		else{
			return numLeaves(nodePtr->right) + numLeaves(nodePtr->left);
		}
	}
	return 0;
}

// count the height of the longest leg of the tree
int IntBinaryTree::height(TreeNode* nodePtr) const{
	if(nodePtr){
		int left = height(nodePtr->left); 
		int right = height(nodePtr->right); 
		if(left > right){
			return left+1;
		}
		else if(right > left){
			return right+1;
		}
		else{
			return left+1;
		}
	}
	return 0;
}

// print the path of all of the longest legs that are the same length as the height
void IntBinaryTree::PrintHeightPaths(TreeNode *nodePtr, vector<int> nums) const{
	if(nodePtr){
		nums.push_back(nodePtr->value);
		PrintHeightPaths(nodePtr->left, nums);
		PrintHeightPaths(nodePtr->right, nums);
		if(nums.size()==height(root)){
			for(int i = 0; i<nums.size(); i++)
				cout<<nums[i]<<" ";
			cout<<endl;
		}
		
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

