#ifndef CROSSREF_H
#define CROSSREF_H

#include <iostream>
#include "BST.h"
#include <fstream>
#include <string>

using namespace std;

class crossref : public BST<crossrefNode<int>> {
public: 
	crossref(string FileName);
	virtual ~crossref();
	void printDataBase();
};

#endif  
