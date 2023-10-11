#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <iostream>
#include <sstream>
#include <cmath>
#include <string>

using namespace std;

const string FunctionStr = "ABCDFGHIJKLMNST";
const string TerminalsStr = "EPXYZUV#";
const string VariablesStr = "XYZUV";
const string ConstStr = "EP";
const string FunctionListStr = "ABCDFGHIJKLMNSTEP";
const string FunctionList[] = { "COT", "SEC", "COS", "CSC", "EXP", "LOG",
		"SINH", "COSH", "TANH", "ASIN", "LN", "ACOS", "ATAN", "SIN", "TAN",
		"E", "PI" };

const double PI = 3.141592658979324;
const double E = 2.718281828459045;
const double tol = 0.000000001;

class ExpData {
public:
	char op;
	double num;

	ExpData() {
		op = ' ';
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

	double Eval(ExpTreeNode *fct, double xval, double yval, double zval,
			double uval, double vval, int &error);

	ExpTreeNode* diff(char var);

	bool IsLeaf(ExpTreeNode *t);
	bool IsNumber(ExpTreeNode *t);
	void IndentBlock(int num = 4);

	string InputString;
	int pos;

public:
	Function();
	Function(const Function &f);
	~Function();
	Function& operator=(const Function &rhs);

	void ConvertExpression(string str);
	void LoadFunction(string str);

	double Evaluate(double xval, int &error);
	double EvaluateX(double xval, int &error);
	double EvaluateXY(double xval, double yval, int &error);
	double EvaluateXYZ(double xval, double yval, double zval, int &error);
	double EvaluateUV(double uval, double vval, int &error);
	Function differentiate(char var = 'X');

	static string FunctionCrossRef(char chartest);
	static string FunctionCrossRef(string strtest, bool StdFncToCode = true);
	static string Ucase(string str);

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
