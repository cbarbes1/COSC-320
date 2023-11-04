/*
 * Author: Cole Barbes
 * Creation date: 10/18/23
 * Last Edited: 11/2/23
 * Desciption: utilizes the red black tree class to create a multi map
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

    // print the multimap
    cout<<tester<<endl;

    // copy constructor test
    multimap<int, string> newTester = tester;

    // create empty multimap
    multimap<int, string> newGuy;

    // equals operator
    newGuy = tester;

    // test copy constructor by print
    cout<<"Copy constructed multimap: "<<newTester<<endl;

    // check if the set is empty
    if(newGuy.empty()){
        cout<<"The multimap is empty"<<endl;
    }

    // test equal with print
    cout<<"Equal operator multimap: "<<newGuy<<endl;

    // if the set is not empty print if it is
    if(!tester.empty()){
        cout<<"The multimap is not empty"<<endl;
    }

    // ask for a key to get in the multimap
    int tmp = 0;
    cout<<"enter a key in the multimap"<<endl;
    cin>>tmp;

    // grab the vector for this key
    vector<string> newVect = newGuy.get(tmp);
    
    for(unsigned int i = 0; i<newVect.size(); i++){
        cout<<newVect[i];
        if(i<(newVect.size()-1))
            cout<<", ";
    }
    cout<<endl;

    // check if the sets are equal
    if(tester == newGuy)
        cout<<"equal"<<endl;

    // get key value pair that needs to be deleted
    cout<<"Please enter a key to delete: ";
    cin>>tmp;
    string value = "";
    cout<<"Please enter the associated value to delete: ";
    cin>>value;

    // erase the value
    tester.erase(tmp, value);

    // print the multimap
    cout<<tester<<endl;
    
    return 0;
}
