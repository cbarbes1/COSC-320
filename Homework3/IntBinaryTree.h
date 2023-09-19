// Specification file for the IntBinaryTree class
#ifndef INTBINARYTREE_H
#define INTBINARYTREE_H

#include <iostream>
#include <queue>
#include <cmath>

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
	void destroySubTree(TreeNode*);
	void makeDeletion(TreeNode*&);
	void displayInOrder(TreeNode*) const;
	void displayPreOrder(TreeNode*) const;
	void displayPostOrder(TreeNode*) const;
	void IndentBlock(int);
	void PrintTree(TreeNode*, int, int);
	void buildTree(TreeNode*, queue<int> p, int, int, int);
public:
	// Constructor
	IntBinaryTree() {
		root = nullptr;
	}

	// Destructor
	~IntBinaryTree() {
		destroySubTree(root);
	}

	void displayInOrder() const {
		displayInOrder(root);
	}

	void displayPreOrder() const {
		displayPreOrder(root);
	}

	void displayPostOrder() const {
		displayPostOrder(root);
	}

	void PrintTree(int Indent = 4, int Level = 0);

	int maxValue(int *A, int sz);

	void LoadArray(int *A, int sz);

	//void ReturnSortedArray(int *A, int sz);
};
#endif
