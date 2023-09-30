/* Author: Cole Barbes
 * Creation Date: 09/29/23
 * Last Updated: 09/29/23
 */
#include <iostream>
#include "crossref.h"

using namespace std;

int main(){

    // ask the user for the file name
    string fileName = "";
    cout<<"Please enter the name of the file to cross reference from: ";
    cin>>fileName;

    // cross reference the file
    crossref CrossRef(fileName);

    // print the data
    CrossRef.printDataBase();

    return 0;

}
