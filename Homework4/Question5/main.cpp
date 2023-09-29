#include <iostream>
#include "crossref.h"

using namespace std;

int main(){

    string fileName = "";
    cout<<"Please enter the name of the file to cross reference from: ";
    cin>>fileName;

    crossref CrossRef(fileName);

    CrossRef.printDataBase();

    return 0;

}
