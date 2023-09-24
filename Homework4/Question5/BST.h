#ifndef BST_H_
#define BST_H_

#include "BinaryTree.h"

template<class T>
class BST: public BinaryTree<T> {
protected:
	void insert(TreeNode<T>*&, TreeNode<T>*&);
	void deleteNode(T, TreeNode<T>*&);
	void makeDeletion(TreeNode<T>*&);

public:
	BST();
	virtual ~BST();

    void insert(T);
	void remove(T);

	virtual bool find(const T&);
	virtual TreeNode<T>* findNode(const T&);
};

template<class T>
BST<T>::BST() {
}

template<class T>
BST<T>::~BST() {
}

template<class T>
void BST<T>::insert(TreeNode<T> *&nodePtr, TreeNode<T> *&newNode) {
	if (nodePtr == nullptr)
		nodePtr = newNode;
	else if (newNode->value < nodePtr->value)
		insert(nodePtr->left, newNode);
	else
		insert(nodePtr->right, newNode);
}

template<class T>
void BST<T>::insert(T item) {
	TreeNode<T> *newNode = new TreeNode<T>;
	newNode->value = item;
	insert(BinaryTree<T>::root, newNode);
}

template<class T>
bool BST<T>::find(const T &item) {
	return findNode(item) != nullptr;
}

template<class T>
TreeNode<T>* BST<T>::findNode(const T &item) {
	TreeNode<T> *nodePtr = BinaryTree<T>::root;

	while (nodePtr) {
		if (nodePtr->value == item)
			return nodePtr;
		else if (item < nodePtr->value)
			nodePtr = nodePtr->left;
		else
			nodePtr = nodePtr->right;
	}
	return nullptr;
}

template<class T> void BST<T>::remove(T item) {
	deleteNode(item, BinaryTree<T>::root);
}

template<class T> void BST<T>::deleteNode(T item, TreeNode<T> *&nodePtr) {
	if (!nodePtr)
		return;

	if (item < nodePtr->value)
		deleteNode(item, nodePtr->left);
	else if (item > nodePtr->value)
		deleteNode(item, nodePtr->right);
	else
		makeDeletion(nodePtr);
}

template<class T> void BST<T>::makeDeletion(TreeNode<T> *&nodePtr) {
	TreeNode<T> *tempNodePtr = nullptr;

	if (!nodePtr)
		cout << "Cannot delete empty node.\n";
	else if (!nodePtr->right) {
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->left;
		delete tempNodePtr;
	} else if (!nodePtr->left) {
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->right;
		delete tempNodePtr;
	} else {
		tempNodePtr = nodePtr->right;
		while (tempNodePtr->left)
			tempNodePtr = tempNodePtr->left;
		tempNodePtr->left = nodePtr->left;
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->right;
		delete tempNodePtr;
	}
}

#endif /* BST_H_ */
