// Harrison Colborne and Cole Barbes
// Specification file for the IntBinaryTree class
#ifndef INTBINARYTREE_H
#define INTBINARYTREE_H

#include <vector>
#include <iostream>

using namespace std;

class IntBinaryTree {
private:
	struct TreeNode {
		int value;
		TreeNode *left;
		TreeNode *right;
	};

	TreeNode *root;

	// Private member functions
	void insert(TreeNode*&, TreeNode*&);
	void destroySubTree(TreeNode*);
	void deleteNode(int, TreeNode*&);
	void makeDeletion(TreeNode*&);
	void displayInOrder(TreeNode*) const;
	void displayPreOrder(TreeNode*) const;
	void displayPostOrder(TreeNode*) const;
	void IndentBlock(int);
	void PrintTree(TreeNode*, int, int);
	int numNodes(TreeNode*) const;
	int numLeaves(TreeNode*) const;
	int height(TreeNode*) const;
	void PrintHeightPaths(TreeNode*, vector<int>) const;
public:
	// Constructor
	IntBinaryTree() {
		root = nullptr;
	}

	// Destructor
	~IntBinaryTree() {
		destroySubTree(root);
	}

	// Binary tree operations
	void insertNode(int);
	bool searchNode(int);
	void remove(int);

	void displayInOrder() const {
		displayInOrder(root);
	}

	void displayPreOrder() const {
		displayPreOrder(root);
	}

	void displayPostOrder() const {
		displayPostOrder(root);
	}

	int numNodes() const {
		return numNodes(root);
	}

	int numLeaves() const {
		return numLeaves(root);
	}

	int height() const {
		return height(root);
	}

	void PrintHeightPaths() const{
		vector<int> nums;
		PrintHeightPaths(root, nums);
		nums.clear();
	}

	void PrintTree(int Indent = 4, int Level = 0);
};
#endif
