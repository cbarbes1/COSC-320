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

	if (item.op == "#")
		ostr << item.num;
    else if(item.op == "~")
        ostr << "-";
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
	char testchr;
	string NumStr, TempStr;
	ExpData ReturnVal;
	int startpos;
	InfInt numval;

	testchr = InputString[pos];

	if (isdigit(testchr)) {
		startpos = pos;
		while (isdigit(InputString[pos]))
			pos++;
		TempStr = InputString.substr(startpos, pos - startpos);
		ReturnVal.op = "#";
		if (from_string<InfInt>(numval, TempStr, dec))
			ReturnVal.num = numval;
		else
			ReturnVal.num = 0;
	} else {
		if(isalpha(testchr)){
			startpos = pos;
			while (isalpha(InputString[pos]))
				pos++;
			TempStr = InputString.substr(startpos, pos - startpos);
			ReturnVal.op = TempStr;
		}
		else {
			pos++;
			ReturnVal.op += testchr;
			ReturnVal.num = 0;
		}
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

	altstr = "";
	for (unsigned int i = 0; i < str.length(); i++) {
		ch = str[i];
		if (ch != ' ' && ch != '\n' && ch != '\t')
			altstr += str.substr(i, 1);
	}
	str = altstr;

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

	if (Token.op == "-") {
		ThisToken = Token;
		Token = GetToken();
		temp = Term(Token);
		ThisToken.op = "~";
		temp = MakeTreeNode(ThisToken, nullptr, temp);
	} else
		temp = Term(Token);

	while ((Token.op == "+") || (Token.op == "-")) {
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

	while ((Token.op == "*") || (Token.op == "/") || (Token.op == "%")) {
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

	while (Token.op == "^") {
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

	if (Token.op == "#") {
		temp = MakeTreeNode(Token);
		Token = GetToken();
	} else if (Token.op == "(") {
		Token = GetToken();
		temp = Expression(Token);
		if (Token.op == ")"){
			Token = GetToken();
		}else{
			throw std::runtime_error("Right Parenthesis Expected.\n");
		}
	} else if (Token.op.length() > 1 ) {
		ThisToken = Token;
		Token = GetToken();
		if (Token.op == "(") {
			Token = GetToken();
			temp = Expression(Token);
			temp = MakeTreeNode(ThisToken, nullptr, temp);
			if (Token.op == ")")
				Token = GetToken();
			else
				throw std::runtime_error("Right Parenthesis Expected.\n");
		} else
			throw std::runtime_error("Left Parenthesis Expected.\n");
	} else
		throw std::runtime_error("Operand or Left Parenthesis Expected.\n");
	return temp;
}

/*
 * set up recursive evaluate function
 */
InfInt Function::Eval()
{
	if(root){
		return Eval(root);
	}
	return 0;
}

/*
 * Evaluate an expression tree recurively and check for errors
 */
InfInt Function::Eval(ExpTreeNode *fct) {
	if(fct){
		string opstr = (fct->data).op;
		InfInt ans = 0;
		InfInt lans, rans;
		if(opstr == "#"){
			ans = (fct->data).num;
		}
		else if(opstr == "~"){
			ans = -(Eval(fct->right));
		}
		else if(opstr == "^"){
			rans = Eval(fct->right);
			if(rans < 0){
				throw std::runtime_error("Exponent must be non-negative.");
			}
			lans = Eval(fct->left);
			int ransI = rans.toInt();
			ans = lans;
			for(int i = 2; i<=ransI; i++){
				ans*=lans;
			}
		}
		else if(opstr=="fact"){
			rans = Eval(fct->right);
			if(rans < 0){
				throw std::runtime_error("Factorial value must be non-negative.");
			}
			ans = factorial(rans.toInt());
		}
		else if(opstr=="fib"){
			rans = Eval(fct->right);
			if(rans < 0){
				throw std::runtime_error("Fibonacci value must be non-negative.");
			}
			ans = fibonacci(rans.toInt());
		}
		else if(opstr=="sqrt"){
			rans = Eval(fct->right);
			if(rans < 0){
				throw std::runtime_error("Square root value must be non-negative.");
			}
			ans = rans.intSqrt();
		}
		else if(operators.find(opstr)!= string::npos){
			lans = Eval(fct->left);
			rans = Eval(fct->right);
			if (opstr == "+")
				ans = lans + rans;
			if (opstr == "-")
				ans = lans - rans;
			if (opstr == "*")
				ans = lans * rans;
			if (opstr == "/"){
				if(rans ==0)
					throw std::runtime_error("Cannot divide by zero!");
				ans = lans / rans;
			}
			if (opstr == "%"){
				if(rans ==0)
					throw std::runtime_error("Cannot divide by zero!");
				ans = lans % rans;
			}
		}
		else{
			throw runtime_error("Function not found.");
		}
		return ans;
	}
}

/*
 * Determines if the node is a leaf.
 */
bool Function::IsLeaf(ExpTreeNode *t) {
	return (!t->left && !t->right);
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

/*
 * recursive Factorial function
 */
InfInt Function::factorial(int num)
{
	if(num >1){
		return factorial(num-1)*num;
	}
	return 1;
}

/*
 * Iterative fibonacci function
 */
InfInt Function::fibonacci(int num)
{
	if(num ==1 || num ==2)
		return 1;
	InfInt fib1 = 1;
	InfInt fib2 = 1;
	InfInt fibp = fib2;
	InfInt fibn = fib1+fib2;
	for(int i = 4; i<=num; i++){
		InfInt nth = fibn;
		fibn = fibp+fibn;
		fibp = nth;
	}

	return fibn;
}


