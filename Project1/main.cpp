#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "Function.h"
#include "tinyfiledialogs.h"
#include <stdexcept>

using namespace std;

void HelpMenu();
void Header();
string IOreplace(string, vector<Function>);

int main() {

	string exp;
	string line;
	Function f;
	vector<Function> ExpTreeList;


	for(int IOTracker = 1; exp!="exit"; IOTracker++){
		cout<<"i"<<IOTracker<<" > ";
		getline(cin, exp);

		if(exp=="H"||exp=="h"||exp=="-h"){
			HelpMenu();
			IOTracker--;
		}
		else if(exp=="open"){
			char const *lFilterPatterns[2] = { "*.iwf", "*"};

			char const *filename = tinyfd_openFileDialog("Open Arbitrary Precision Integer Calculator Workspace File", NULL, 1, lFilterPatterns, "Workspace File", 0);

			if (filename) {
				cout<<"Opening "<<filename<<endl;
				ifstream InFile(filename);
				if(InFile.is_open()){
					while(InFile){
						getline(InFile, line, '\n');
						if(line[0] == 'i'){
							line = line.substr(4);
							cout<<"i"<<IOTracker<<" > "<<line<<endl;
							cout<<"o"<<IOTracker<<" > ";
							try{
								f.ConvertExpression(line);
								ExpTreeList.push_back(f);
								cout<<f.Eval()<<endl;
							}catch(const exception& e){
								cout<<"Error: "<<e.what()<<endl;
							}
							cout<<endl;
							IOTracker++;
						}

					}
				}
				InFile.close();
			}else {
				cerr<<"Failed to open the file for writing\n";
			}
			IOTracker--;
		}
		else if(exp=="save"){

			char const *lFilterPatterns[2] = { "*.iwf" , "*"};

			char const *filename = tinyfd_saveFileDialog("Save Arbitrary Precision Integer Calculator Workspace File", NULL, 1, lFilterPatterns, "Workspace File");
			if (filename) {
				cout<<"Saving Workspace to "<<filename<<endl;
				ofstream outputFile(filename);
				if(outputFile.is_open()){
					int pos = 1;
					for(Function t : ExpTreeList){
						outputFile<<"i"<<pos<<" > "<<t<<endl;
						outputFile<<"o"<<pos++<<" > ";
						try{
							outputFile<<t.Eval()<<endl;
						}catch(const exception& e){
							outputFile<<"Error: "<<e.what()<<endl;
						}
					}
				}
				outputFile.close();
			}else {
				cerr<<"Failed to open the file for writing\n";
			}
			IOTracker--;
		}
		else if(exp=="exit"){
			cout<<"Have a nice day!"<<endl;
			cout<<"Below are the run stats: "<<endl;
			cout<<"Number of computations: "<<(IOTracker-1)<<endl;
			cout<<"Summary: "<<endl;
			int temp = 0;
			for(Function t : ExpTreeList){
				temp++;
				cout<<"i"<<temp<<" > "<<t<<endl;
				cout<<"o"<<temp<<" > "<<" ";
				try{
					cout<<t.Eval()<<endl;
				}catch(const exception& e){
					cout<<"Error: "<<e.what()<<endl;
				}
			}
			cout<<endl;
		}
		else {
			cout<<"o"<<IOTracker<<" > ";
			exp = IOreplace(exp, ExpTreeList);
			try{
				f.ConvertExpression(exp);
				ExpTreeList.push_back(f);
				cout<<f.Eval()<<endl;
			}catch(const exception& e){
				cout<<"Error: "<<e.what()<<endl;
			}
		}

	}

	return 0;
}

/*
 * Simple print function to print the header
 */
void Header()
{
    cout<<"Arbitrary Precision Integer Calculator\n";
    cout<<"Standard arithmetic expression evaluator but with unlimited integer size.\n";
    cout<<"by Cole Barbes\n\n";
    cout<<"Type 'H' for help\n";
    cout<<"Type 'exit' to quit.\n";
    cout<<"Type 'open' to open a workspace file.\n";
    cout<<"Type 'save' to save a workspace file.\n\n\n";
}

/*
 * Simple print funtion to print the help HelpMenu
 */
void HelpMenu()
{
	cout<<"=== Arbitrary Precision Integer Calculator Help ===\n";
	cout<<"Type ’H’ for help\n";
	cout<<"Type ’exit’ to quit.\n";
	cout<<"Type ’open’ to open a workspace file.\n";
	cout<<"Type ’save’ to save a workspace file.\n";
	cout<<"\n";
	cout<<"Supported Operations and Functions:\n";
	cout<<"+: addition, Ex: 123 + 432\n";
	cout<<"-: subtraction, Ex: 123 - 432\n";
	cout<<"*: multiplication, Ex: 123 * 432\n";
	cout<<"/: integer division, Ex: 123 / 432\n";
	cout<<"%: modulus, Ex: 123 % 432\n";
	cout<<"ˆ: power, Ex: 123 ˆ 432 --- exponent must be of integer size.\n";
	cout<<"(): parentheses for expression delimitation.\n";
	cout<<"fact: factorial, Ex: fact(1000) --- operand must be of integer size.\n";
	cout<<"fib: Fibonacci number , Ex: fib(1000) --- operand must be of integer size.\n";
	cout<<"sqrt: integer square root, Ex: sqrt(1000)\n";
	cout<<"You can also use previous inputs and outputs by using their designations,\n";
	cout<<"for example, i4 * 2345 will take the input number 4 and multiply it by 2345.\n";
	cout<<"Similarly, i4 * o7 will multiply input 4 by output 7.\n\n";
}

string IOreplace(string x, vector<Function> list)
{
	int pos = 0;
	int IONum = 0;
	string tmp;

	while(x.find('i', pos)!=string::npos)
	{
		pos = x.find('i', pos);
		if(isdigit(x[(pos+1)])){
			pos++;
			int startpos = pos;
			while(isdigit(x[pos]))
				pos++;
			tmp = x.substr(startpos, pos-1);
			IONum = stoi(tmp);
			x.replace((startpos-1), (pos-startpos+1), (list[(IONum-1)]).toString());
		}
		else {
			pos+=3;
			continue;
		}
	}

	while(x.find('o', pos)!=string::npos)
	{
		pos = x.find('o', pos);
		pos++;
		int startpos = pos;
		while(isdigit(x[pos]))
			pos++;
		tmp = x.substr(startpos, pos-1);
		IONum = stoi(tmp);
		x.replace((startpos-1), (pos-startpos+1), (list[(IONum-1)]).toString());
	}


	return x;
}
