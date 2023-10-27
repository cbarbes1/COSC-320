/*
 * Author: Cole Barbes
 * Creation Date: 10/18/23
 * Last Edited: 10/19/23
 * Description: Implement a arbitrary integer calculator
 */
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "Function.h"
#include "tinyfiledialogs.h"
#include <stdexcept>

using namespace std;

// prototype functions
void HelpMenu();
void Header();
string IOreplace(string, vector<Function>);

int main() {

    // create needed vars
	string exp = "";
	string line = "";
	Function f;
	vector<Function> ExpTreeList;

    Header();
    // for loop to run the simulator
	for(int IOTracker = 1; exp!="exit"; IOTracker++){
        
        // output the input terminal and take in the line
		cout<<"i"<<IOTracker<<" > ";
		getline(cin, exp);

        // if the selection is a help command print the help screen and decrement the Tracker
		if(exp=="H"||exp=="h"||exp=="-h"){
			HelpMenu();
			IOTracker--;
		}
		else if(exp=="open"){ //  if "open" open the file and read it in
            
            // grab the needed info for the file opening using the tiny file dialog gui thing
			char const *lFilterPatterns[2] = { "*.iwf", "*"};
			char const *filename = tinyfd_openFileDialog("Open Arbitrary Precision Integer Calculator Workspace File", NULL, 1, lFilterPatterns, "Workspace File", 0);

			if (filename) { // if the file name was recieved
				cout<<"Opening "<<filename<<endl;
				ifstream InFile(filename);// open the file for input 
				if(InFile.is_open()){ // if the file is open
                    vector<Function> tmpList; // create the temporary list to remove the inputs and outputs incase this is an externally created input file
					while(InFile){ // while not pointing at the eof
						getline(InFile, line, '\n'); // get the line from the file
						if(line[0] == 'i'){
							line = line.substr(line.find('>')+1); // substring the io setup part
							cout<<"i"<<IOTracker<<" > "<<line<<endl;
                            line = IOreplace(line, tmpList); // replace the lines io 
							cout<<"o"<<IOTracker<<" > "; // create the output starter
                            // try to convert and catch the exceptions
							try{
								f.ConvertExpression(line);
								tmpList.push_back(f);
                                ExpTreeList.push_back(f);
								cout<<f.Eval()<<endl;
							}catch(const exception& e){
								cout<<"Error: "<<e.what()<<endl;
							}
							cout<<endl;
							IOTracker++;
						}

					}
					tmpList.clear();
				}
				InFile.close();
			}else {
				cerr<<"Failed to open the file for writing\n";
			}
			IOTracker--;
		}
		else if(exp=="save"){ // if "save" then save the input and output to a file

			char const *lFilterPatterns[2] = { "*.iwf" , "*"};

			char const *filename = tinyfd_saveFileDialog("Save Arbitrary Precision Integer Calculator Workspace File", NULL, 1, lFilterPatterns, "Workspace File");
			if (filename) { // if the file name was valid and not canceled
				cout<<"Saving Workspace to "<<filename<<endl; // print prompt
				ofstream outputFile(filename); // open file
				if(outputFile.is_open()){ // check to see if the file opened properly
					int pos = 1;
					for(Function t : ExpTreeList){ // for each value in the list save the io to the file
						outputFile<<"i"<<pos<<" > "<<t<<endl;
						outputFile<<"o"<<pos++<<" > ";
						try{ // try to evaluate the expression
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
		else if(exp=="exit"){ // print exit screen 
			cout<<"Have a nice day!"<<endl;
			cout<<"Below are the run stats: "<<endl;
			cout<<"Number of computations: "<<(IOTracker-1)<<endl;
			cout<<"Summary: "<<endl;
			int temp = 0;
			for(Function t : ExpTreeList){ // for each loop through the list and print the IO
				temp++;
				cout<<"i"<<temp<<" > "<<t<<endl;
				cout<<"o"<<temp<<" > "<<" ";
				try{ // try to evaluate the expression and throw exceptions if needed
					cout<<t.Eval()<<endl;
				}catch(const exception& e){
					cout<<"Error: "<<e.what()<<endl;
				}
			}
			cout<<endl;
		}
		else { // take in the input into the expression tree and evaluate the expression outputting the result as an output line
			cout<<"o"<<IOTracker<<" > ";
			exp = IOreplace(exp, ExpTreeList);
			try{ // attempt to do the actions and throw an exception if there is one
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

/*
 * Simple replace function to pull the input and output out of the line and replacing them with the needed io from the list
 * Parameters: a string x and a list of the IO
 * return a string that is the new complete output
 */
string IOreplace(string x, vector<Function> list)
{
    // create the needed vars 
	int pos = 0;
	int IONum = 0;
	string tmp;

    // while an i is found in the string replace it and the subsequent numbers with an io
	while(x.find('i', pos)!=string::npos)
	{
		pos = x.find('i', pos); // grab the position
        // if it a digit replace
		if(isdigit(x[(pos+1)])){
			pos++;
			int startpos = pos;
            // while its a digit increment the position until it reaches the end
			while(isdigit(x[pos])) 
				pos++;
            // grab the substr and send it to an int
			tmp = x.substr(startpos, pos-1);
			IONum = stoi(tmp);
			x.replace((startpos-1), (pos-startpos+1), (list[(IONum-1)]).toString()); //replace the input 
		}
		else { //  if no number after i then it must be a word so skip up 3 and continue through the string
			pos+=3;
			continue;
		}
	}

	pos = 0;
	IONum = 0;
    
    // while an i is found in the string replace it and the subsequent numbers with an io
	while(x.find('o', pos)!=string::npos)
	{
		pos = x.find('o', pos);// grab the position
		// if it a digit replace
		if(isdigit(x[(pos+1)])){
			pos++;
			int startpos = pos;
            // while its a digit increment the position until it reaches the end
			while(isdigit(x[pos])) 
				pos++;
            // grab the substr and send it to an int
			tmp = x.substr(startpos, pos-1);
			IONum = stoi(tmp);
			x.replace((startpos-1), (pos-startpos+1), (list[(IONum-1)]).toString()); //replace the output 
		}
		else { //  if no number after i then it must be a word so skip up 3 and continue through the string
			pos+=3;
			continue;
		}
	}


	return x;
}
