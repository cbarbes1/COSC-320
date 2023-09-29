/* Created By: Cole Barbes
 * Creation Date: 09/29/23
 */
#include "crossref.h"
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

/*
 *
 */
crossref::crossref(string fileName)
{
    ifstream DataFile;

    DataFile.open(fileName);

    if(DataFile){

        string line = "";
        string word = "";
        int lineNumber = 0;

        while(getline(DataFile, line)){
            lineNumber++;
            istringstream var(line);
            while(var>>word){
                string newWord="";
                for(unsigned int i = 0; i<word.length(); i++){
                    if((word[i]>='A'&&word[i]<='Z')||(word[i]>='a'&&word[i]<='z'))
                        newWord+=tolower(word[i]);
                }

                crossrefNode<int> *p;
                if(this->find(newWord)){
                    p = this->findNode(newWord);
                    p->appendNode(lineNumber);
                }
                else{
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

crossref::~crossref(){
}

/*
 * The InOrderRec member function displays the values in the subtree
 * pointed to by nodePtr, via recursive inorder traversal.
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

/*
 *
 */
void crossref::insert(string word, int lineNumber)
{
    crossrefNode<int> *Node = new crossrefNode<int>;
    Node->setWord(word);
    Node->appendNode(lineNumber);
    BST<string, crossrefNode<int>>::insert(BST<string, crossrefNode<int>>::root, Node);
}


