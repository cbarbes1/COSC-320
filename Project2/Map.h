#ifndef MAP_H_
#define MAP_H_

#include <vector>

#include "RBTree.h"

using namespace std;

///////////////////////////////////////
//  Pair Class
///////////////////////////////////////

template<class K, class V>
class Pair {
protected:
	K key;
	V value;

public:
	Pair();
	Pair(K, V);

	bool operator<(const Pair<K, V>&) const;
	bool operator>(const Pair<K, V>&) const;
	bool operator==(const Pair<K, V>&) const;

	K& getKey() {
		return key;
	}

	V& getValue() {
		return value;
	}

	template<class Kp, class Vp>
	friend ostream& operator<<(ostream&, const Pair<Kp, Vp>&);
};

template<class K, class V>
Pair<K, V>::Pair() {
}

template<class K, class V>
Pair<K, V>::Pair(K k, V v) {
	key = k;
	value = v;
}

template<class K, class V>
bool Pair<K, V>::operator<(const Pair<K, V> &obj) const {
	return key < obj.key;
}

template<class K, class V>
bool Pair<K, V>::operator>(const Pair<K, V> &obj) const {
	return key > obj.key;
}

template<class K, class V>
bool Pair<K, V>::operator==(const Pair<K, V> &obj) const {
	return (key == obj.key);
}

template<class Kp, class Vp>
ostream& operator<<(ostream &os, const Pair<Kp, Vp> &obj) {
	os << "(" << obj.key << ", " << obj.value << ")";
	return os;
}

///////////////////////////////////////
//  Map Class
///////////////////////////////////////

template<class K, class V>
class Map: RBTree<Pair<K, V>> {
protected:
	void toVector(RBTreeNode<Pair<K, V>>*, vector<Pair<K, V>>&) const;
	unsigned long size(RBTreeNode<Pair<K, V>>*);
    
    void InOrderAct(RBTreeNode<Pair<K, V>> *, void (*)(K&, V&, V), V);

public:
	Map();
	virtual ~Map();
	Map(const Map<K, V>&);
	Map<K, V>& operator=(const Map<K, V>&);

	void insert(K, V);
	void clear();

	bool empty();
	unsigned long size();
	bool find(K);
	void erase(K);
	V get(K);
	void set(K, V);

	void printtree(int Indent = 4, int Level = 0);
	void toVector(vector<Pair<K, V>>&) const;

	bool operator==(Map<K, V> &obj);
	bool operator!=(Map<K, V> &obj);
    
    void InOrderAct(void (*func)(K &key, V &var, V app), V app){
        return InOrderAct(this->root, func, app);
    }

	template<class U>
	friend ostream& operator<<(ostream&, const Map<K, V>&);
};

template<class K, class V>
Map<K, V>::Map() {
}

template<class K, class V>
Map<K, V>::~Map() {
}

template<class K, class V>
void Map<K, V>::toVector(RBTreeNode<Pair<K, V>> *ptr,
		vector<Pair<K, V>> &v) const {
	if (ptr != this->NIL) {
		toVector(ptr->left, v);
		v.push_back(ptr->value);
		toVector(ptr->right, v);
	}
}

template<class K, class V>
void Map<K, V>::toVector(vector<Pair<K, V>> &v) const {
	toVector(this->root, v);
}

/*
 * do an action on a node with the given key if the action was successful return true
 * parameters: the subtree pointer, the key, and the function pointer to the specified action function
 * return true or false: true if the node is found and the action is completed
 */
template<class K, class V>
void Map<K, V>::InOrderAct(RBTreeNode<Pair<K, V>> *nodePtr, void (*func)(K &key, V &var, V app), V applyAgent)
{
    // if the node is nil then return false
    if(nodePtr != this->NIL){
        // if the left finds the value then return true
        InOrderAct(nodePtr->left, func, applyAgent);
        // if the value is indeed found then do the action and return true
        func(nodePtr->value.getKey(), nodePtr->value.getValue(), applyAgent);
        // if right is reached return whatever it may be
        InOrderAct(nodePtr->right, func, applyAgent);
    }
}

template<class K, class V>
Map<K, V>::Map(const Map<K, V> &obj) {
	vector<Pair<K, V>> v;
	obj.toVector(v);
	for (Pair<K, V> val : v)
		insert(val.getKey(), val.getValue());
}

template<class K, class V>
Map<K, V>& Map<K, V>::operator=(const Map<K, V> &obj) {
	if (this != &obj) {
		this->clear();
		vector<Pair<K, V>> v;
		obj.toVector(v);
		for (Pair<K, V> val : v)
			insert(val.getKey(), val.getValue());
	}
	return *this;
}

template<class K, class V>
bool Map<K, V>::empty() {
	return size() == 0;
}

template<class K, class V>
unsigned long Map<K, V>::size(RBTreeNode<Pair<K, V>> *ptr) {
	if (ptr == this->NIL)
		return 0;

	return size(ptr->left) + size(ptr->right) + 1;
}

template<class K, class V>
unsigned long Map<K, V>::size() {
	return size(this->root);
}

template<class K, class V>
void Map<K, V>::clear() {
	this->destroySubTree(this->root);
	this->root = this->NIL;
}

template<class K, class V>
bool Map<K, V>::find(K k) {
	Pair<K, V> val(k, V());
	return RBTree<Pair<K, V>>::find(val);
}

template<class K, class V>
void Map<K, V>::erase(K k) {
	Pair<K, V> val(k, V());
	this->remove(val);
}

template<class K, class V>
void Map<K, V>::insert(K k, V v) {
	Pair<K, V> val(k, v);
	RBTreeNode<Pair<K, V> > *nil = this->NIL;
	RBTreeNode<Pair<K, V> > *y = nil;
	RBTreeNode<Pair<K, V> > *x = this->root;

	while (x != this->NIL) {
		y = x;
		if (val < x->value)
			x = x->left;
		else if (val > x->value)
			x = x->right;
		else {
			x->value = val;
			return;
		}
	}

	RBTreeNode<Pair<K, V> > *newnode = new RBTreeNode<Pair<K, V> >(val, RED,
			nil, nil, nil);
	newnode->parent = y;
	if (y == this->NIL)
		this->root = newnode;
	else if (newnode->value < y->value)
		y->left = newnode;
	else if (newnode->value > y->value)
		y->right = newnode;

	this->insertFix(newnode);
}

template<class K, class V>
V Map<K, V>::get(K k) {
	Pair<K, V> p(k, V());
	RBTreeNode<Pair<K, V>> *ptr = this->findNode(p);
	if (ptr == this->NIL)
		throw out_of_range("Key not found.");
	else
		return ptr->value.getValue();
}

template<class K, class V>
void Map<K, V>::set(K k, V v) {
	insert(k, v);
}

template<class K, class V>
bool Map<K, V>::operator==(Map<K, V> &obj) {
	vector<Pair<K, V>> rv;
	obj.toVector(rv);
	vector<Pair<K, V>> lv;
	toVector(lv);
	if (lv.size() != rv.size())
		return false;

	for (unsigned long i = 0; i < rv.size(); i++)
		if ((lv[i].getKey() != rv[i].getKey())
				|| (lv[i].getValue() != rv[i].getValue()))
			return false;

	return true;
}

template<class K, class V>
bool Map<K, V>::operator!=(Map<K, V> &obj) {
	return !(*this == obj);
}

template<class Kp, class Vp>
ostream& operator<<(ostream &os, const Map<Kp, Vp> &obj) {
	vector<Pair<Kp, Vp>> v;
	obj.toVector(v);
	os << "{";
	for (unsigned long i = 0; i < v.size(); i++)
		os << v[i] << ((i < v.size() - 1) ? ", " : "");
	os << "}";

	return os;
}

template<class K, class V>
void Map<K, V>::printtree(int Indent, int Level) {
	this->PrintTree(Indent, Level);
}

#endif /* MAP_H_ */
