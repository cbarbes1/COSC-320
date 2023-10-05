#ifndef BST_H_
#define BST_H_

#include "BinaryTree.h"

template<class T>
class BST: public BinaryTree<T> {
protected:
	void insert(TreeNode<T>*&, TreeNode<T>*&);
	void deleteNode(T, TreeNode<T>*&);
	void makeDeletion(TreeNode<T>*&);

	void findAndDeleteByCopy(T item, TreeNode<T> *&nodePtr);
	void deleteByCopying(TreeNode<T> *&node);

	int numNodes(TreeNode<T>*) const;
	int numLeaves(TreeNode<T>*) const;
	int height(TreeNode<T>*) const;

	void leftRotate(TreeNode<T>*&);
	void rightRotate(TreeNode<T>*&);

	void findAndDeleteByRotate(T item, TreeNode<T> *&nodePtr);
	void rotateDelete(TreeNode<T>*&);

public:
	BST();
	virtual ~BST();

	void insert(T);
	void remove(T);

	void deleteValue(T);

	void rDelete(T val);

	int numNodes() const {
		return numNodes(BinaryTree<T>::root);
	}

	int numLeaves() const {
		return numLeaves(BinaryTree<T>::root);
	}

	int height() const {
		return height(BinaryTree<T>::root);
	}

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

/*
 * Nonrecursive start to deleting a tree node.
 */
template<class T> void BST<T>::deleteValue(T item) {
	findAndDeleteByCopy(item, BinaryTree<T>::root);
}

/*
 * Recursive find for deleting a node.  Once the value is found the
 * deleteByCopying function s called on the node.
 */
template<class T> void BST<T>::findAndDeleteByCopy(T item, TreeNode<T> *&nodePtr) {
	if (!nodePtr)
		return;

	if (item < nodePtr->value)
		deleteNode(item, nodePtr->left);
	else if (item > nodePtr->value)
		deleteNode(item, nodePtr->right);
	else
		deleteByCopying(nodePtr);
}

/*
 * Deletes a node using the copy algorithm.  Copies the node's
 * predecessor to the position of deletion. Then deletes the leaf
 * or adjusts the child node pointer and deletes the old predecessor
 * position.
 */
template<class T>
void BST<T>::deleteByCopying(TreeNode<T> *&node) {
	TreeNode<T> *previous, *tmp = node;
	// node has no right child
	if (!node->right)
		node = node->left;
	// node has no left child
	else if (node->left == 0)
		node = node->right;
	else {
		// node has both children.
		tmp = node->left;
		previous = node;
		while (tmp->right != 0) {
			previous = tmp;
			tmp = tmp->right;
		}
		node->value = tmp->value;
		if (previous == node)
			previous->left = tmp->left;
		else
			previous->right = tmp->left;
	}
	delete tmp;
}



// count number of nodes
template<class T>
int BST<T>::numNodes(TreeNode<T> *nodePtr) const{
	if(nodePtr){
		return numNodes(nodePtr->left) + numNodes(nodePtr->right) + 1;
	}
	return 0;
}

// count number of leaves meaning the number of nodes with null left and right children
template<class T>
int BST<T>::numLeaves(TreeNode<T> *nodePtr) const{
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
template<class T>
int BST<T>::height(TreeNode<T>* nodePtr) const{
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

/*
 * Rotate right function to rotate the given node
 */
template<class T>
void BST<T>::leftRotate( TreeNode<T>*& nodePtr)
{
	TreeNode<T> *p = nodePtr->right;
	TreeNode<T> *temp = p->left;
	p->left = nodePtr;
	nodePtr->right = temp;
}

/*
 * Rotate left function to rotate the given node
 */
template<class T>
void BST<T>::rightRotate(TreeNode<T>*& nodePtr)
{
	TreeNode<T> *p = nodePtr->left;
	TreeNode<T> *temp = p->right;
	p->right = nodePtr;
	nodePtr->left = temp;
}

/*
 * Recursive find for deleting a node.  Once the value is found the
 * deleteByrotate function s called on the node.
 */
template<class T> void BST<T>::findAndDeleteByRotate(T item, TreeNode<T> *&nodePtr) {
	if (!nodePtr)
		return;

	if (item < nodePtr->value)
		findAndDeleteByRotate(item, nodePtr->left);
	else if (item > nodePtr->value)
		findAndDeleteByRotate(item, nodePtr->right);
	else
		rotateDelete(nodePtr);
}

template<class T>
void BST<T>::rDelete(T var)
{
	if(find(var))
		findAndDeleteByRotate(var, this->root);
	else
		cout<<"Node not in the tree"<<endl;
}


template<class T>
void BST<T>::rotateDelete(TreeNode<T>*& nodePtr)
{
	TreeNode<T> *p = nodePtr;
	if(!nodePtr->left){
		nodePtr = nodePtr->right;
	}
	else if(!nodePtr->right){
		nodePtr = nodePtr->left;
	}
	else{
		int leftHeight = 0, rightHeight = 0;

		leftHeight = height(p->left);
		rightHeight = height(p->right);

		if(leftHeight > rightHeight){
			rightRotate(p);

		}
		else if(rightHeight >= leftHeight){
			leftRotate(p);
		}
		this->PrintTree();

		rotateDelete(p);
	}
	delete p;
}

#endif /* BST_H_ */
