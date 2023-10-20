/*
 * Author: Don Spickler, Edited By: Cole Barbes
 * ** This file is used for COSC 320 purposes only **
 * Last Edited: 10/19/23
 */
#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include "InfInt.h"
#include <stdexcept>


using namespace std;
const string operators = "+-*/%";
const string FunctionList[] = {"fact", "fib","sqrt" };


class ExpData {
public:
	string op;
	InfInt num;

	ExpData() {
		op = "";
		num = 0;
	}

	friend ostream& operator<<(ostream &ostr, ExpData &item);
};

class ExpTreeNode {
public:
	ExpData data;
	ExpTreeNode *left;
	ExpTreeNode *right;

	ExpTreeNode(ExpData val, ExpTreeNode *lptr = nullptr, ExpTreeNode *rptr =
			nullptr) {
		data = val;
		left = lptr;
		right = rptr;
	}
};

class Function {
private:
	ExpTreeNode *root;

	ExpTreeNode* MakeTreeNode(ExpData item, ExpTreeNode *lptr = nullptr,
			ExpTreeNode *rptr = nullptr);
	void DeleteTree(ExpTreeNode *t);
	ExpTreeNode* CopyTree(ExpTreeNode *t);

	ExpData GetToken();
	ExpTreeNode* Expression(ExpData &Token);
	ExpTreeNode* Term(ExpData &Token);
	ExpTreeNode* Factor(ExpData &Token);
	ExpTreeNode* Power(ExpData &Token);

	InfInt Eval(ExpTreeNode *fct);

	bool IsLeaf(ExpTreeNode *t);
	void IndentBlock(int num = 4);
    // simple factorial function
	InfInt factorial(int);
    // simple fibonacci funtion
	InfInt fibonacci(int);

	string InputString;
	int pos;

public:
	Function();
	Function(const Function &f);
	~Function();
	Function& operator=(const Function &rhs);

	void ConvertExpression(string str);
	void LoadFunction(string str);

	InfInt Eval();

	friend istream& operator>>(istream &istr, Function &fx);
	friend ostream& operator<<(ostream &ostr, Function &fx);

	string toString(ExpTreeNode *t);
	string toString();

	void PrintFunctionTree(ExpTreeNode *t, int Indent = 6, int Level = 0);
	void PrintFunctionTree(int Indent = 6, int Level = 0);
	void PrintFunction();
	void PrintFunction(ExpTreeNode *t);
	void PrintFunctionPostfix();
	void PrintFunctionPostfix(ExpTreeNode *t);
	void ClearFunction();
};


#endif /* FUNCTION_H_ */
