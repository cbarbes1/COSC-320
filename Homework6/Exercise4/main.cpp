/*
 * Author: Cole Barbes
 * Creation date: 10/18/23
 * Last Edited: 11/1/23
 * Desciption: utilizes the red black tree class to create a set
 */
#include <iostream>
#include <ctime>
#include <vector>

#include "map.h"

using namespace std;

int main()
{
    // create empty set
    map<int, string> tester;

    int signal = 0;

    // get the size from command line
    cout<<"Enter number of data items to enter into the map:";
    cin>>signal;

    // get the key value pairs
    for(int i = 0; i<signal; i++){
        int key = 0;
        cout<<"Please enter a key to enter in to the map: ";
        cin>>key;

        string value = "";
        cout<<"Please enter a value to enter into the map: ";
        cin>>value;

        tester.set(key, value);

    }

    cout<<tester<<endl;

    map<int, string> newTester = tester;

    map<int, string> newGuy;

    newGuy = tester;

    cout<<"Copy constructed map: "<<newTester<<endl;

    if(newGuy.empty()){
        cout<<"The map is empty"<<endl;
    }

    cout<<"Equal operator map: "<<newGuy<<endl;

    if(!tester.empty()){
        cout<<"The map is not empty"<<endl;
    }

    int tmp = 0;
    cout<<"enter a key in the map"<<endl;
    cin>>tmp;

    cout<<newGuy.get(tmp)<<endl;
    
    return 0;
}
