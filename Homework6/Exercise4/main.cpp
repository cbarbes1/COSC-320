/*
 * Author: Cole Barbes
 * Creation date: 10/18/23
 * Last Edited: 11/1/23
 * Desciption: utilizes the red black tree class to create a set
 */
#include <iostream>
#include <ctime>
#include <vector>

#include "multimap.h"

using namespace std;

int main()
{
    // create empty set
    multimap<int, string> tester;

    int signal = 0;

    // get the size from command line
    cout<<"Enter number of data items to enter into the multimap:";
    cin>>signal;

    // get the key value pairs
    for(int i = 0; i<signal; i++){
        int key = 0;
        cout<<"Please enter a key to enter in to the multimap: ";
        cin>>key;

        string value = "";
        cout<<"Please enter a value to enter into the multimap: ";
        cin>>value;

        tester.set(key, value);

    }

    cout<<tester<<endl;

    multimap<int, string> newTester = tester;

    multimap<int, string> newGuy;

    newGuy = tester;

    cout<<"Copy constructed multimap: "<<newTester<<endl;

    if(newGuy.empty()){
        cout<<"The multimap is empty"<<endl;
    }

    cout<<"Equal operator multimap: "<<newGuy<<endl;

    if(!tester.empty()){
        cout<<"The multimap is not empty"<<endl;
    }

    int tmp = 0;
    cout<<"enter a key in the multimap"<<endl;
    cin>>tmp;

    vector<string> newVect = newGuy.get(tmp);
    
    for(unsigned int i = 0; i<newVect.size(); i++){
        cout<<newVect[i];
    }
    cout<<endl;
    
    return 0;
}
