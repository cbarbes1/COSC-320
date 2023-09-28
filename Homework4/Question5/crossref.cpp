#include "crossref.h"


crossref::crossref(string fileName)
{
    ifstream DataFile;

    DataFile.open(fileName);

    if(DataFile){

        string line = "";
        string word = "";
        int lineNumber = 0;

        if(DataFile){
            lineNumber++;
			while(getline(DataFile, word, ' ')||getline(DataFile, word, '\n')){
                crossrefNode<int> Node;
                Node.setWord(word);
                crossrefNode<int> *p;
                if(BST<int>::find(Node)){
                    p=findNode(Node);
                    p->appendNode(lineNumber);
                }
                else{
                    insert(Node);
                }
            }
        }
    }
    else{
        cout<<"File does not exist"<<endl;
    }

    DataFile.close();

}

void crossref::printDataBase()
{
    InOrderRec(std::cout);
    cout<<endl;
}
