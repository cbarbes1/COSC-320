/* Created By: Cole Barbes
 * Creation Date: 09/29/23
 */
#include "crossref.h"
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

/* Constructor: Create the tree using the given FILE
 * Parameters: the file name
 */
crossref::crossref(string fileName)
{
    ifstream DataFile;

    DataFile.open(fileName);

    if(DataFile){// if the data file is open

        string line = "";
        string word = "";
        int lineNumber = 0;

        while(getline(DataFile, line)){ // get the line until the eof bit is reached
            lineNumber++;
            istringstream var(line); // parse the string to a stream
            while(var>>word){ //parse in the words form the stream
                string newWord="";

                for(unsigned int i = 0; i<word.length(); i++){
                    if((word[i]>='A'&&word[i]<='Z')||(word[i]>='a'&&word[i]<='z'))
                        newWord+=tolower(word[i]);
                }

                crossrefNode<int> *p;
                if(this->find(newWord)){ // if the node is found then add to the list rather than insert
                    p = this->findNode(newWord);
                    p->appendNode(lineNumber);
                }
                else{ // insert into the list
                    insert(newWord, lineNumber);
                }
            }
        }
    }
    else{
        cout<<"File does not exist"<<endl;
    }

    DataFile.close();

}

// destructor
crossref::~crossref(){
}

/*
 * Print the data recursively in order displaying the list after each
 * parameters: the node of the subtree
 */
void crossref::printDataBaseRec(crossrefNode<int> *nodePtr){
	if (nodePtr) {
		printDataBaseRec(nodePtr->left);
		cout<<nodePtr->getWord()<<"\t\t Page Numbers: ";
        nodePtr->displayList();
        cout<<endl;
		printDataBaseRec(nodePtr->right);
	}
}

/* override the insert so it inserts the crossreference node correctly
 * Parameters: a word, and the line number it was found on
 */
void crossref::insert(string word, int lineNumber)
{
    crossrefNode<int> *Node = new crossrefNode<int>;
    Node->setWord(word);
    Node->appendNode(lineNumber);
    BST<string, crossrefNode<int>>::insert(BST<string, crossrefNode<int>>::root, Node);
}


