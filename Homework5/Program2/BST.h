/*
 * Code Taken from Dr. Spickler's Example code 
 * Edited by: Cole Barbes 10/05/23
 * Used for a rotate delete exercise on a tree
 */
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

    // number of nodes
	int numNodes(TreeNode<T>*) const;
    // number of leaves
	int numLeaves(TreeNode<T>*) const;
    // height of the given tree 
	int height(TreeNode<T>*) const;
    
    // 2 rotate functions to aid the rotate delete functions

	void leftRotate(TreeNode<T>*&);
	void rightRotate(TreeNode<T>*&);
    
    // added 2 private functions to perform the rotate delete
    void rotateDeleteByHeight(TreeNode<T>*&);
    void rotateDeleteByNumNodes(TreeNode<T>*&);
	void findAndrDeleteByHeight(T item, TreeNode<T> *&nodePtr);
    void findAndrDeleteByNumNodes(T item, TreeNode<T> *&nodePtr);
	

public:
	BST();
	virtual ~BST();

	void insert(T);
	void remove(T);

	void deleteValue(T);

    // rotate delete set up function
	void rDeleteByHeight(T val);
    
    // rotate delete set up function
	void rDeleteByNumNodes(T val);

    // set up functions
	int numNodes() const {
		return numNodes(BinaryTree<T>::root);
	}

	int numLeaves() const {
		return numLeaves(BinaryTree<T>::root);
	}

	int height() const {
		return height(BinaryTree<T>::root);
	}
	//

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
void BST<T>::leftRotate(TreeNode<T>*& nodePtr)
{
	TreeNode<T> *p = nodePtr->right;// hold the right of the node
	TreeNode<T> *temp = p->left;//hold the left of the right
	p->left = nodePtr;// change the left of the right to the node 
	nodePtr->right = temp;// change the right of the node to the left of p
	nodePtr = p;// reset the nodes
}

/*
 * Rotate left function to rotate the given node
 */
template<class T>
void BST<T>::rightRotate(TreeNode<T>*& nodePtr)
{
	TreeNode<T> *p = nodePtr->left; // hold the left of the node
	TreeNode<T> *temp = p->right; //hold the right of the left 
	p->right = nodePtr; // change the right of the left to the node 
	nodePtr->left = temp; // change the left of the node to the right of p
	nodePtr = p; // reset the nodes
}

/*
 * Recursive find for deleting a node.  Once the value is found the
 * deleteByrotate function s called on the node.
 */
template<class T> void BST<T>::findAndrDeleteByHeight(T item, TreeNode<T> *&nodePtr) {
	if (!nodePtr)
		return;

	if (item < nodePtr->value)
		findAndrDeleteByHeight(item, nodePtr->left);
	else if (item > nodePtr->value)
		findAndrDeleteByHeight(item, nodePtr->right);
	else
		rotateDeleteByHeight(nodePtr);
}

/*
 * Recursive find for deleting a node.  Once the value is found the
 * deleteByrotate function s called on the node.
 */
template<class T> void BST<T>::findAndrDeleteByNumNodes(T item, TreeNode<T> *&nodePtr) {
	if (!nodePtr)
		return;

	if (item < nodePtr->value)
		findAndrDeleteByNumNodes(item, nodePtr->left);
	else if (item > nodePtr->value)
		findAndrDeleteByNumNodes(item, nodePtr->right);
	else
		rotateDeleteByNumNodes(nodePtr);
}

/*
 * set up the rotate delete function
 * variable of type T to find and delete
 */
template<class T>
void BST<T>::rDeleteByHeight(T var)
{
	if(find(var))
		findAndrDeleteByHeight(var, this->root);
	else
		cout<<"Node not in the tree"<<endl;
}


/*
 * set up the rotate delete function
 * variable of type T to find and delete
 */
template<class T>
void BST<T>::rDeleteByNumNodes(T var)
{
	if(find(var))
		findAndrDeleteByNumNodes(var, this->root);
	else
		cout<<"Node not in the tree"<<endl;
}

/*
 * Rotate a given root with deeper height until there is atleast less than 1 child
 * parameters: the node to be deleted
 */
template<class T>
void BST<T>::rotateDeleteByHeight(TreeNode<T>*& nodePtr)
{
	TreeNode<T> *p = nodePtr;
	if(!nodePtr->left){ // if no left delete the right node
		nodePtr = nodePtr->right;
		delete p;
	}
	else if(!nodePtr->right){ // if no right delete the left node
		nodePtr = nodePtr->left;
		delete p;
	}
	else{ // if both nodes
		int leftHeight = 0, rightHeight = 0;
		
        // grab the heights
		leftHeight = height(nodePtr->left);
		rightHeight = height(nodePtr->right);

		if(leftHeight > rightHeight){ // if the left is deeper rotate the left root about x
			rightRotate(nodePtr);
			rotateDeleteByHeight(nodePtr->right);
		}
		else if(rightHeight >= leftHeight){ // if the right is deeper rotate the right root about x
			leftRotate(nodePtr);
			rotateDeleteByHeight(nodePtr->left);
			
		}
	}
}

/*
 * Rotate a given root with more nodes in the subtree until there is atleast less than 1 child
 * parameters: the node to be deleted
 */
template<class T>
void BST<T>::rotateDeleteByNumNodes(TreeNode<T> *&nodePtr)
{
	TreeNode<T> *p = nodePtr;
	if(!nodePtr->left){ // if no left delete the right node
		nodePtr = nodePtr->right;
		delete p;
	}
	else if(!nodePtr->right){ // if no right delete the left node
		nodePtr = nodePtr->left;
		delete p;
	}
	else{ // if both nodes
		int leftNumNodes = 0, rightNumNodes = 0;
		
        // grab the number of nodes
		leftNumNodes = numNodes(nodePtr->left);
		rightNumNodes = numNodes(nodePtr->right);

		if(leftNumNodes > rightNumNodes){ // if the left has more nodes rotate the left root about x
			rightRotate(nodePtr);
			rotateDeleteByNumNodes(nodePtr->right);
		}
		else if(rightNumNodes >= leftNumNodes){ // if the right has more nodes rotate the right root about x
			leftRotate(nodePtr);
			rotateDeleteByNumNodes(nodePtr->left);
			
		}
	}
}

#endif /* BST_H_ */
