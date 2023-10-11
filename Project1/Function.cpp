#include "Function.h"

/*
 * Nifty trick to convert a numeric looking string to a numeric data type.
 * Examples:
 * from_string<double>(dval, str, dec)
 * from_string<int>(ival, str, dec)
 */
template<class T>
bool from_string(T &t, const string &s, ios_base& (*f)(ios_base&)) {
	istringstream iss(s);
	return !(iss >> f >> t).fail();
}

/*
 * ostream friend function for the ExpData data type.
 */
ostream& operator<<(ostream &ostr, ExpData &item) {
	string TempStr;

	if (item.op == '#')
		ostr << item.num;
	else if ((FunctionStr.find(item.op) != string::npos)
			|| (ConstStr.find(item.op) != string::npos))
		ostr << Function::FunctionCrossRef(item.op);
	else
		ostr << item.op;
	return ostr;
}

/*
 * Function constructor.
 */
Function::Function() {
	root = nullptr;
	InputString = "";
	pos = 0;
}

/*
 * Function copy constructor.
 */
Function::Function(const Function &f) {
	root = CopyTree(f.root);
}

/*
 * Function that corresponds the mathematical expression for a function
 * to our single character coding. If StdFncToCode is true it converts
 * the function name to the coding (e.g. SIN -> S). If StdFncToCode is
 * false the conversion is in the opposite direction.
 */
string Function::FunctionCrossRef(string strtest, bool StdFncToCode) {
	int fctsize = FunctionListStr.length();

	strtest = Ucase(strtest);

	if (StdFncToCode) {
		int pos = 0;
		while (pos < fctsize && FunctionList[pos] != strtest)
			pos++;

		if (pos < fctsize)
			return FunctionListStr.substr(pos, 1);
		else
			return "";
	} else {
		unsigned long pos = FunctionListStr.find(strtest);
		if (pos != string::npos)
			return FunctionList[pos];
		else
			return "";
	}
}

/*
 * Function destructor.
 */
Function::~Function() {
	DeleteTree(root);
	root = nullptr;
}

/*
 * Overloaded assignment statement.
 */
Function& Function::operator=(const Function &rhs) {
	if (root)
		this->ClearFunction();

	root = CopyTree(rhs.root);
	return *this;
}

/*
 * Simply a string converter to all uppercase.
 */
string Function::Ucase(string str) {
	for (unsigned long i = 0; i < str.length(); i++)
		str[i] = toupper(str[i]);
	return str;
}

/*
 * Code to function cross reference with character input.
 * Simply calls the string cross reference function.
 */
string Function::FunctionCrossRef(char chartest) {
	chartest = toupper(chartest);
	string teststr = "Q";
	teststr[0] = chartest;
	return FunctionCrossRef(teststr, false);
}

/*
 * Clears all dynamically allocated memory stored in the expression tree.
 * Simply calls the recursive DeleteTree function on the root.
 */
void Function::ClearFunction() {
	DeleteTree(root);
	root = nullptr;
}

/*
 * Creates a new tree node with the parameter information and child links.
 * If the allocation fails the program is halted.
 */
ExpTreeNode* Function::MakeTreeNode(ExpData item, ExpTreeNode *lptr,
		ExpTreeNode *rptr) {
	ExpTreeNode *p = new ExpTreeNode(item, lptr, rptr);
	if (p == nullptr) {
		cerr << "Memory Allocation Error!";
		exit(1);
	}

	return p;
}

/*
 * Recursive function to copy a tree or subtree.
 */
ExpTreeNode* Function::CopyTree(ExpTreeNode *t) {
	ExpTreeNode *newlptr, *newrptr, *newnode;

	if (!t)
		return nullptr;

	if (t->left)
		newlptr = CopyTree(t->left);
	else
		newlptr = nullptr;

	if (t->right)
		newrptr = CopyTree(t->right);
	else
		newrptr = nullptr;

	newnode = MakeTreeNode(t->data, newlptr, newrptr);
	return newnode;
}

/*
 * Recursive function to clear all memory of a binary tree.
 */
void Function::DeleteTree(ExpTreeNode *t) {
	if (t) {
		DeleteTree(t->left);
		DeleteTree(t->right);
		delete t;
	}
}

/*
 * Retrieves the next token from the input string.
 */
ExpData Function::GetToken() {
	char testchar;
	string NumStr, TempStr;
	ExpData ReturnVal;
	int startpos;
	double numval;
	NumStr = "1234567890.";

	testchar = InputString[pos];

	if (NumStr.find(testchar) != string::npos) {
		startpos = pos;
		while (NumStr.find(InputString[pos]) != string::npos)
			pos++;
		TempStr = InputString.substr(startpos, pos - startpos);
		ReturnVal.op = '#';
		if (from_string<double>(numval, TempStr, dec))
			ReturnVal.num = numval;
		else
			ReturnVal.num = 0;
	} else {
		pos++;
		ReturnVal.op = testchar;
		ReturnVal.num = 0;
	}
	return ReturnVal;
}

/*
 * Function to load a new expression string into the tree.
 */
void Function::LoadFunction(string str) {
	ConvertExpression(str);
}

/*
 * Function to load a new expression string into the tree.
 * Removes standard white space, converts to function coding
 * then calls the functions to build the tree.
 */
void Function::ConvertExpression(string str) {
	ExpData Token;
	string tstr, altstr;
	char ch;
	str = Ucase(str);

	altstr = "";
	for (unsigned int i = 0; i < str.length(); i++) {
		ch = str[i];
		if (ch != ' ' && ch != '\n' && ch != '\t')
			altstr += str.substr(i, 1);
	}
	str = altstr;

	for (unsigned int i = 0; i < str.length(); i++)
		for (int j = 4; j >= 1; j--) {
			tstr = str.substr(i, j);
			if (FunctionCrossRef(tstr) != "") {
				str.erase(i, j);
				str.insert(i, FunctionCrossRef(tstr));
			}
		}

	pos = 0;
	InputString = str + "==";

	Token = GetToken();
	ClearFunction();
	root = Expression(Token);
}

/*
 * BNF-ish
 * Expression := {-} Term {+ / - Term}
 * Term := Factor {* / / Factor}
 * Factor := Power {^ Power}
 * Power := Terminal | (Expression) | Function(Expression)
 */

/*
 * Function to process an expression.
 */
ExpTreeNode* Function::Expression(ExpData &Token) {
	ExpData ThisToken;
	ExpTreeNode *temp = nullptr, *temp2 = nullptr;

	if (Token.op == '-') {
		ThisToken = Token;
		Token = GetToken();
		temp = Term(Token);
		ThisToken.op = '~';
		temp = MakeTreeNode(ThisToken, nullptr, temp);
	} else
		temp = Term(Token);

	while ((Token.op == '+') || (Token.op == '-')) {
		ThisToken = Token;
		Token = GetToken();
		temp2 = Term(Token);
		temp = MakeTreeNode(ThisToken, temp, temp2);
	}
	return temp;
}

/*
 * Function to process a term.
 */
ExpTreeNode* Function::Term(ExpData &Token) {
	ExpData ThisToken;
	ExpTreeNode *temp = nullptr, *temp2 = nullptr;

	temp = Factor(Token);

	while ((Token.op == '*') || (Token.op == '/')) {
		ThisToken = Token;
		Token = GetToken();
		temp2 = Factor(Token);
		temp = MakeTreeNode(ThisToken, temp, temp2);
	}
	return temp;
}

/*
 * Function to process a factor.
 */
ExpTreeNode* Function::Factor(ExpData &Token) {
	ExpData ThisToken;
	ExpTreeNode *temp = nullptr, *temp2 = nullptr;

	temp = Power(Token);

	while (Token.op == '^') {
		ThisToken = Token;
		Token = GetToken();
		temp2 = Power(Token);
		temp = MakeTreeNode(ThisToken, temp, temp2);
	}
	return temp;
}

/*
 * Function to process a power.
 */
ExpTreeNode* Function::Power(ExpData &Token) {
	ExpTreeNode *temp = nullptr;
	ExpData ThisToken;

	if (TerminalsStr.find(Token.op) != string::npos) {
		temp = MakeTreeNode(Token);
		Token = GetToken();
	} else if (Token.op == '(') {
		Token = GetToken();
		temp = Expression(Token);
		if (Token.op == ')')
			Token = GetToken();
		else
			cout << "Right Parenthesis Expected.\n";
	} else if (FunctionStr.find(Token.op) != string::npos) {
		ThisToken = Token;
		Token = GetToken();
		if (Token.op == '(') {
			Token = GetToken();
			temp = Expression(Token);
			temp = MakeTreeNode(ThisToken, nullptr, temp);
			if (Token.op == ')')
				Token = GetToken();
			else
				cout << "Right Parenthesis Expected.\n";
		} else
			cout << "Left Parenthesis Expected.\n";
	} else
		cout << "Operand or Left Parenthesis Expected.\n";
	return temp;
}

/*
 * Convenience function to evaluate a function with variable x.
 */
double Function::Evaluate(double xval, int &error) {
	error = 0;
	return Eval(root, xval, 0, 0, 0, 0, error);
}

/*
 * Convenience function to evaluate a function with variable x.
 */
double Function::EvaluateX(double xval, int &error) {
	error = 0;
	return Eval(root, xval, 0, 0, 0, 0, error);
}

/*
 * Convenience function to evaluate a function with variables x and y.
 */
double Function::EvaluateXY(double xval, double yval, int &error) {
	error = 0;
	return Eval(root, xval, yval, 0, 0, 0, error);
}

/*
 * Convenience function to evaluate a function with variables x, y, and z.
 */
double Function::EvaluateXYZ(double xval, double yval, double zval,
		int &error) {
	error = 0;
	return Eval(root, xval, yval, zval, 0, 0, error);
}

/*
 * Convenience function to evaluate a function with variables u and v.
 */
double Function::EvaluateUV(double uval, double vval, int &error) {
	error = 0;
	return Eval(root, 0, 0, 0, uval, vval, error);
}

/*
 * General recursive evaluation function. Parameters for values of x, y, z, u, and v.
 * Returns the value of the expression with the values substituted and an error
 * code if there was a numeric error in the evaluation.
 */
double Function::Eval(ExpTreeNode *fct, double xval, double yval, double zval,
		double uval, double vval, int &error) {
	double ans, lans, rans;
	char opch;

	opch = (fct->data).op;

	if (error)
		return 0;

	if (FunctionStr.find(opch) != string::npos) {
		rans = Eval(fct->right, xval, yval, zval, uval, vval, error);

		if (opch == 'A') {
			if (fabs(tan(rans)) < tol) {
				error = 1;
				ans = 0;
			} else
				ans = 1 / tan(rans);
		}

		if (opch == 'B') {
			if (fabs(cos(rans)) < tol) {
				error = 1;
				ans = 0;
			} else
				ans = 1 / cos(rans);
		}

		if (opch == 'C')
			ans = cos(rans);

		if (opch == 'D') {
			if (fabs(sin(rans)) < tol) {
				error = 1;
				ans = 0;
			} else
				ans = 1 / sin(rans);
		}

		if (opch == 'F')
			ans = exp(rans);

		if (opch == 'G') {
			if (rans < tol) {
				error = 1;
				ans = 0;
			} else
				ans = log(rans) / log(10);
		}

		if (opch == 'H')
			ans = sinh(rans);
		if (opch == 'I')
			ans = cosh(rans);
		if (opch == 'J')
			ans = tanh(rans);

		if (opch == 'K') {
			if ((rans > 1) || (rans < -1)) {
				error = 1;
				ans = 0;
			} else
				ans = asin(rans);
		}

		if (opch == 'L') {
			if (rans < tol) {
				error = 1;
				ans = 0;
			} else
				ans = log(rans);
		}

		if (opch == 'M') {
			if ((rans > 1) || (rans < -1)) {
				error = 1;
				ans = 0;
			} else
				ans = acos(rans);
		}

		if (opch == 'N')
			ans = atan(rans);

		if (opch == 'S')
			ans = sin(rans);
		if (opch == 'T')
			ans = tan(rans);

		return ans;
	} else if (TerminalsStr.find(opch) != string::npos) {
		if (opch == 'X')
			return xval;
		if (opch == 'Y')
			return yval;
		if (opch == 'Z')
			return zval;
		if (opch == 'U')
			return uval;
		if (opch == 'V')
			return vval;
		if (opch == '#')
			return (fct->data).num;
		if (opch == 'P')
			return PI;
		if (opch == 'E')
			return E;
	} else {
		if (opch == '~') {
			rans = Eval(fct->right, xval, yval, zval, uval, vval, error);
			if (error)
				return 0;
			else
				return -rans;
		} else {
			rans = Eval(fct->right, xval, yval, zval, uval, vval, error);
			lans = Eval(fct->left, xval, yval, zval, uval, vval, error);
			if (opch == '+')
				ans = lans + rans;
			if (opch == '-')
				ans = lans - rans;
			if (opch == '*')
				ans = lans * rans;

			if (opch == '/') {
				if (fabs(rans) < tol) {
					error = 1;
					ans = 0;
				} else
					ans = lans / rans;
			}

			if (opch == '^') {
				if (lans < tol) {
					if (fabs(lans) < tol) {
						if (rans < tol) {
							error = 1;
							ans = 0;
						} else
							ans = 0;
					} else {
						if (fabs(rans - int(rans + .5)) > tol) {
							error = 1;
							ans = 0;
						} else {
							if (int(rans + .5) == 0) {
								ans = 1;
							} else {
								if (rans < 0) {
									lans = 1 / lans;
									rans = -rans;
								}
								ans = 1;
								for (int i = 0; i < int(rans + .5); i++)
									ans *= lans;
							}
						}
					}
				} else
					ans = exp(rans * log(lans));
			}

			if (error)
				return 0;
			else
				return ans;
		}
	}
	error = 1;
	return 0;
}

/*
 * Function to start the creation of a new function that is the derivative
 * (partial derivative) of the current function with respect to the variable
 * that is input as a parameter.
 */
Function Function::differentiate(char var) {
	Function tempfct;
	tempfct.root = diff(var);
	return tempfct;
}

/*
 * Recursive differentiation function for taking the derivative of the function
 * with respect to the variable that is input as a parameter.
 */
ExpTreeNode* Function::diff(const char var) {
	ExpTreeNode *ansder, *leftder, *rightder, *copyfctl, *copyfctr,
			*tempnodeptrl, *tempnodeptrr, *tempnodeptr;
	ExpData tempnode;
	Function tempfct;

	char testchar = root->data.op;

	switch (testchar) {
	case '+':
	case '-':
		tempfct.root = CopyTree(root->left);
		leftder = tempfct.diff(var);
		tempfct.ClearFunction();
		tempfct.root = CopyTree(root->right);
		rightder = tempfct.diff(var);
		tempfct.ClearFunction();
		tempnode.op = root->data.op;
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, leftder, rightder);
		break;
	case '~':
		tempfct.root = CopyTree(root->right);
		rightder = tempfct.diff(var);
		tempfct.ClearFunction();
		tempnode.op = '~';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, nullptr, rightder);
		break;
	case '*':
		tempfct.root = CopyTree(root->left);
		copyfctl = CopyTree(root->left);
		leftder = tempfct.diff(var);
		tempfct.ClearFunction();
		tempfct.root = CopyTree(root->right);
		copyfctr = CopyTree(root->right);
		rightder = tempfct.diff(var);
		tempfct.ClearFunction();

		tempnode.op = '*';
		tempnode.num = 0;
		tempnodeptrl = MakeTreeNode(tempnode, copyfctl, rightder);
		tempnodeptrr = MakeTreeNode(tempnode, leftder, copyfctr);

		tempnode.op = '+';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, tempnodeptrl, tempnodeptrr);
		break;
	case '/':
		tempfct.root = CopyTree(root->left);
		copyfctl = CopyTree(root->left);
		leftder = tempfct.diff(var);
		tempfct.ClearFunction();
		tempfct.root = CopyTree(root->right);
		copyfctr = CopyTree(root->right);
		rightder = tempfct.diff(var);
		tempfct.ClearFunction();

		tempnode.op = '*';
		tempnode.num = 0;
		tempnodeptrr = MakeTreeNode(tempnode, copyfctl, rightder);
		tempnodeptrl = MakeTreeNode(tempnode, leftder, copyfctr);

		tempnode.op = '-';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, tempnodeptrl, tempnodeptrr); // numerator

		tempnode.op = '#';
		tempnode.num = 2;
		tempnodeptrr = MakeTreeNode(tempnode);

		tempnode.op = '^';
		tempnode.num = 0;
		tempnodeptrl = CopyTree(root->right);
		tempnodeptrl = MakeTreeNode(tempnode, tempnodeptrl, tempnodeptrr);

		tempnode.op = '/';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, ansder, tempnodeptrl);
		break;

	case '^':
		if (IsNumber(root->left) && IsNumber(root->right)) {
			tempnode.op = '#';
			tempnode.num = 0;
			ansder = MakeTreeNode(tempnode);
		} else if (IsNumber(root->left) && !IsNumber(root->right)) {
			tempfct.root = CopyTree(root->right);
			rightder = tempfct.diff(var);
			copyfctl = CopyTree(root->left);
			tempnodeptrl = CopyTree(root);
			tempfct.ClearFunction();

			tempnode.op = '*';
			tempnode.num = 0;
			ansder = MakeTreeNode(tempnode, tempnodeptrl, rightder);

			tempnode.op = 'L';
			tempnode.num = 0;
			tempnodeptrr = MakeTreeNode(tempnode, nullptr, copyfctl);

			tempnode.op = '*';
			tempnode.num = 0;
			ansder = MakeTreeNode(tempnode, ansder, tempnodeptrr);
		} else if (!IsNumber(root->left) && IsNumber(root->right)) {
			tempfct.root = CopyTree(root->left);
			leftder = tempfct.diff(var);
			copyfctl = CopyTree(root->left);
			copyfctr = CopyTree(root->right);
			tempnodeptrr = CopyTree(root->right);
			tempfct.ClearFunction();

			tempnode.op = '#';
			tempnode.num = 1;
			ansder = MakeTreeNode(tempnode);

			tempnode.op = '-';
			tempnode.num = 0;
			ansder = MakeTreeNode(tempnode, copyfctr, ansder);

			tempnode.op = '^';
			tempnode.num = 0;
			ansder = MakeTreeNode(tempnode, copyfctl, ansder);

			tempnode.op = '*';
			tempnode.num = 0;
			ansder = MakeTreeNode(tempnode, ansder, tempnodeptrr);

			tempnode.op = '*';
			tempnode.num = 0;
			ansder = MakeTreeNode(tempnode, ansder, leftder);
		} else {
			tempfct.root = CopyTree(root->right);
			rightder = tempfct.diff(var);
			tempfct.ClearFunction();
			tempfct.root = CopyTree(root->left);
			leftder = tempfct.diff(var);
			tempfct.ClearFunction();
			copyfctl = CopyTree(root->left);
			tempnodeptrl = CopyTree(root->left);
			copyfctr = CopyTree(root->left);
			tempnodeptrr = CopyTree(root);

			tempnode.op = '/';
			tempnode.num = 0;
			ansder = MakeTreeNode(tempnode, leftder, copyfctl);

			tempnode.op = '*';
			tempnode.num = 0;
			ansder = MakeTreeNode(tempnode, copyfctr, ansder);

			tempnode.op = 'L';
			tempnode.num = 0;
			tempnodeptr = MakeTreeNode(tempnode, nullptr, tempnodeptrl);

			tempnode.op = '*';
			tempnode.num = 0;
			tempnodeptr = MakeTreeNode(tempnode, tempnodeptr, rightder);

			tempnode.op = '+';
			tempnode.num = 0;
			ansder = MakeTreeNode(tempnode, ansder, tempnodeptr);

			tempnode.op = '*';
			tempnode.num = 0;
			ansder = MakeTreeNode(tempnode, ansder, tempnodeptrr);
		}
		break;

	case 'L':
		tempfct.root = CopyTree(root->right);
		copyfctr = CopyTree(root->right);
		rightder = tempfct.diff(var);
		tempfct.ClearFunction();
		tempnode.op = '/';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, rightder, copyfctr);
		break;

	case 'G':
		tempfct.root = CopyTree(root->right);
		copyfctr = CopyTree(root->right);
		rightder = tempfct.diff(var);
		tempfct.ClearFunction();
		tempnode.op = '/';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, rightder, copyfctr);

		tempnode.op = '#';
		tempnode.num = log(10);
		tempnodeptrr = MakeTreeNode(tempnode);

		tempnode.op = '/';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, ansder, tempnodeptrr);
		break;

	case 'S':
		tempfct.root = CopyTree(root->right);
		copyfctr = CopyTree(root->right);
		rightder = tempfct.diff(var);
		tempfct.ClearFunction();

		tempnode.op = 'C';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, nullptr, copyfctr);

		tempnode.op = '*';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, ansder, rightder);
		break;

	case 'C':
		tempfct.root = CopyTree(root->right);
		copyfctr = CopyTree(root->right);
		rightder = tempfct.diff(var);
		tempfct.ClearFunction();

		tempnode.op = 'S';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, nullptr, copyfctr);

		tempnode.op = '~';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, nullptr, ansder);

		tempnode.op = '*';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, ansder, rightder);
		break;

	case 'T':
		tempfct.root = CopyTree(root->right);
		copyfctr = CopyTree(root->right);
		rightder = tempfct.diff(var);
		tempfct.ClearFunction();

		tempnode.op = 'B';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, nullptr, copyfctr);

		tempnode.op = '#';
		tempnode.num = 2;
		tempnodeptrr = MakeTreeNode(tempnode);

		tempnode.op = '^';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, ansder, tempnodeptrr);

		tempnode.op = '*';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, ansder, rightder);
		break;

	case 'A':
		tempfct.root = CopyTree(root->right);
		copyfctr = CopyTree(root->right);
		rightder = tempfct.diff(var);
		tempfct.ClearFunction();

		tempnode.op = 'D';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, nullptr, copyfctr);

		tempnode.op = '#';
		tempnode.num = 2;
		tempnodeptrr = MakeTreeNode(tempnode);

		tempnode.op = '^';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, ansder, tempnodeptrr);

		tempnode.op = '~';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, nullptr, ansder);

		tempnode.op = '*';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, ansder, rightder);
		break;

	case 'B':
		tempfct.root = CopyTree(root->right);
		copyfctr = CopyTree(root->right);
		tempnodeptrr = CopyTree(root->right);
		rightder = tempfct.diff(var);
		tempfct.ClearFunction();

		tempnode.op = 'B';
		tempnode.num = 0;
		tempnodeptrl = MakeTreeNode(tempnode, nullptr, copyfctr);

		tempnode.op = 'T';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, nullptr, tempnodeptrr);

		tempnode.op = '*';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, tempnodeptrl, ansder);

		tempnode.op = '*';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, ansder, rightder);
		break;

	case 'D':
		tempfct.root = CopyTree(root->right);
		copyfctr = CopyTree(root->right);
		tempnodeptrr = CopyTree(root->right);
		rightder = tempfct.diff(var);
		tempfct.ClearFunction();

		tempnode.op = 'D';
		tempnode.num = 0;
		tempnodeptrl = MakeTreeNode(tempnode, nullptr, copyfctr);

		tempnode.op = 'A';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, nullptr, tempnodeptrr);

		tempnode.op = '*';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, tempnodeptrl, ansder);

		tempnode.op = '~';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, nullptr, ansder);

		tempnode.op = '*';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, ansder, rightder);
		break;

	case 'F':
		tempfct.root = CopyTree(root->right);
		copyfctr = CopyTree(root->right);
		rightder = tempfct.diff(var);
		tempfct.ClearFunction();

		tempnode.op = 'F';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, nullptr, copyfctr);

		tempnode.op = '*';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, ansder, rightder);
		break;

	case 'H':
		tempfct.root = CopyTree(root->right);
		copyfctr = CopyTree(root->right);
		rightder = tempfct.diff(var);
		tempfct.ClearFunction();

		tempnode.op = 'I';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, nullptr, copyfctr);

		tempnode.op = '*';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, ansder, rightder);
		break;

	case 'I':
		tempfct.root = CopyTree(root->right);
		copyfctr = CopyTree(root->right);
		rightder = tempfct.diff(var);
		tempfct.ClearFunction();

		tempnode.op = 'H';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, nullptr, copyfctr);

		tempnode.op = '*';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, ansder, rightder);
		break;

	case 'J':
		tempfct.root = CopyTree(root->right);
		copyfctr = CopyTree(root->right);
		rightder = tempfct.diff(var);
		tempfct.ClearFunction();

		tempnode.op = 'I';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, nullptr, copyfctr);

		tempnode.op = '#';
		tempnode.num = 2;
		tempnodeptrr = MakeTreeNode(tempnode);

		tempnode.op = '^';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, ansder, tempnodeptrr);

		tempnode.op = '/';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, rightder, ansder);
		break;

	case 'K':
		tempfct.root = CopyTree(root->right);
		copyfctr = CopyTree(root->right);
		rightder = tempfct.diff(var);
		tempfct.ClearFunction();

		tempnode.op = '#';
		tempnode.num = 2;
		tempnodeptrr = MakeTreeNode(tempnode);

		tempnode.op = '^';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, copyfctr, tempnodeptrr);

		tempnode.op = '#';
		tempnode.num = 1;
		tempnodeptrl = MakeTreeNode(tempnode);

		tempnode.op = '-';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, tempnodeptrl, ansder);

		tempnode.op = '#';
		tempnode.num = 0.5;
		tempnodeptrr = MakeTreeNode(tempnode);

		tempnode.op = '^';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, ansder, tempnodeptrr);

		tempnode.op = '/';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, rightder, ansder);
		break;

	case 'M':
		tempfct.root = CopyTree(root->right);
		copyfctr = CopyTree(root->right);
		rightder = tempfct.diff(var);
		tempfct.ClearFunction();

		tempnode.op = '#';
		tempnode.num = 2;
		tempnodeptrr = MakeTreeNode(tempnode);

		tempnode.op = '^';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, copyfctr, tempnodeptrr);

		tempnode.op = '#';
		tempnode.num = 1;
		tempnodeptrl = MakeTreeNode(tempnode);

		tempnode.op = '-';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, tempnodeptrl, ansder);

		tempnode.op = '#';
		tempnode.num = 0.5;
		tempnodeptrr = MakeTreeNode(tempnode);

		tempnode.op = '^';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, ansder, tempnodeptrr);

		tempnode.op = '/';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, rightder, ansder);

		tempnode.op = '~';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, nullptr, ansder);
		break;

	case 'N':
		tempfct.root = CopyTree(root->right);
		copyfctr = CopyTree(root->right);
		rightder = tempfct.diff(var);
		tempfct.ClearFunction();

		tempnode.op = '#';
		tempnode.num = 2;
		tempnodeptrr = MakeTreeNode(tempnode);

		tempnode.op = '^';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, copyfctr, tempnodeptrr);

		tempnode.op = '#';
		tempnode.num = 1;
		tempnodeptrl = MakeTreeNode(tempnode);

		tempnode.op = '+';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, tempnodeptrl, ansder);

		tempnode.op = '/';
		tempnode.num = 0;
		ansder = MakeTreeNode(tempnode, rightder, ansder);
		break;

	default:   //  Variables and Constants
		if (testchar == var) {
			tempnode.op = '#';
			tempnode.num = 1;
			ansder = MakeTreeNode(tempnode);
		} else {
			tempnode.op = '#';
			tempnode.num = 0;
			ansder = MakeTreeNode(tempnode);
		}
		break;
	}

	return ansder;
}

/*
 * Determines if the node is a leaf.
 */
bool Function::IsLeaf(ExpTreeNode *t) {
	return (!t->left && !t->right);
}

/*
 * Determines if the subtree would evaluate to a number.
 */
bool Function::IsNumber(ExpTreeNode *t) {
	if (!t)
		return true;

	return ((VariablesStr.find(t->data.op) == string::npos) && IsNumber(t->left)
			&& IsNumber(t->right));
}

/*
 * Stream in operator to a function.  Since this is streaming into a
 * string before conversion the user should not include any whitespace
 * during input.
 */
istream& operator>>(istream &istr, Function &fx) {
	string InputString;
	istr >> InputString;
	fx.ConvertExpression(InputString);
	return istr;
}

/*
 * Recursive function to convert an expression subtree to a string.
 */
string Function::toString(ExpTreeNode *t) {
	stringstream ss;
	ss.str("");

	if (t) {
		ss << "(";
		ss << toString(t->left);
		ss << t->data;
		ss << toString(t->right);
		ss << ")";
	}
	return ss.str();
}

/*
 * Function to convert an expression to a string.
 */
string Function::toString() {
	if (root)
		return toString(root);

	return "";
}

/*
 * Overloaded stream out operator.
 */
ostream& operator<<(ostream &ostr, Function &fx) {
	ostr << fx.toString();
	return ostr;
}

/*
 * Indentation helper function for tree printing.
 */
void Function::IndentBlock(int num) {
	for (int i = 0; i < num; i++)
		cout << " ";
}

/*
 * Recursive function for printing an expression tree in tree form.
 */
void Function::PrintFunctionTree(ExpTreeNode *t, int Indent, int Level) {
	if (t) {
		PrintFunctionTree(t->right, Indent, Level + 1);
		IndentBlock(Indent * Level);
		cout << t->data << "\n";
		PrintFunctionTree(t->left, Indent, Level + 1);
	}
}

/*
 * Function for printing an expression tree in tree form.
 */
void Function::PrintFunctionTree(int Indent, int Level) {
	if (root)
		PrintFunctionTree(root, Indent, Level);
}

/*
 * Recursive function for printing an expression to standard out.
 */
void Function::PrintFunction(ExpTreeNode *t) {
	if (t) {
		cout << "(";
		PrintFunction(t->left);
		cout << t->data;
		PrintFunction(t->right);
		cout << ")";
	}
}

/*
 * Function for printing an expression to standard out.
 */
void Function::PrintFunction(void) {
	if (root)
		PrintFunction(root);
}

/*
 * Recursive function for printing an expression in postfix form to standard out.
 */
void Function::PrintFunctionPostfix(ExpTreeNode *t) {
	if (t) {
		PrintFunctionPostfix(t->left);
		PrintFunctionPostfix(t->right);
		cout << t->data << " ";
	}
}

/*
 * Function for printing an expression in postfix form to standard out.
 */
void Function::PrintFunctionPostfix(void) {
	if (root)
		PrintFunctionPostfix(root);
}
