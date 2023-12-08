#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <iostream>
#include "ListOfLists.h"
#include <algorithm>

using namespace std;

template<class T>
class HashTable {
protected:
	ListOfLists<T> tab;
	int (*hf)(T&);

public:
	HashTable(int sz, int (*hashfct)(T&));
	virtual ~HashTable();
	void insert(T);
	void remove(T);
	bool find(T);
	void rehash(int sz);
	void print();
};

template<class T>
HashTable<T>::HashTable(int sz, int (*hashfct)(T&)) {
	tab.addRows(sz, 0);
	hf = hashfct;
}

template<class T>
HashTable<T>::~HashTable() {
}

template<class T>
void HashTable<T>::insert(T item) {
	int pos = hf(item) % tab.size();

	tab[pos].push_back(item);
}

template<class T>
void HashTable<T>::remove(T item) {
	int pos = hf(item) % tab.size();
    
    if(std::find(tab[pos].begin(), tab[pos].end(), item) != tab[pos].end()){
        tab[pos].erase(std::find(tab[pos].begin(), tab[pos].end(), item));
    }
}

template<class T>
bool HashTable<T>::find(T item) {
	int pos = hf(item) % tab.size();
	int initpos = pos;
    bool checker = false;
    
    if(std::find(tab[pos].begin(), tab[pos].end(), item) < tab[pos].end())
        checker = true;

	return checker;
}

template<class T>
void HashTable<T>::rehash(int sz) {
    HashTable<T> temp(sz, hf);
	for (int i = 0; i < tab.size(); i++) {
		for(int j = 0; j< tab[i].size(); j++){
            temp.insert(tab[i][j]);
        }
	}

	tab = temp.tab;
}

template<class T>
void HashTable<T>::print() {
	for (int i = 0; i < tab.size(); i++){
        cout << i << ": ";
		for(int j = 0; j < tab[i].size(); j++)
            cout << tab[i][j] << " ";
        cout << endl;
    }
}

#endif /* HASHTABLE_H_ */
