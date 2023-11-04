/*
 * Author: Cole Barbes
 * Creation date: 10/18/23
 * Last Edited: 11/1/23
 * Desciption: utilizes the red black tree class to create a set
 */
#include <iostream>
#include <ctime>
#include <vector>
#include <exception>

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

    // print the map
    cout<<tester<<endl;

    // copy constructor test
    map<int, string> newTester = tester;

    // create empty map
    map<int, string> newGuy;

    // test the equals operator
    newGuy = tester;

    // test the copy constructed map with a print
    cout<<"Copy constructed map: "<<newTester<<endl;

    // test if the map is empty
    if(newGuy.empty()){
        cout<<"The map is empty"<<endl;
    }

    // print the equals operator test
    cout<<"Equal operator map: "<<newGuy<<endl;

    // test if the map is not empty
    if(!tester.empty()){
        cout<<"The map is not empty"<<endl;
    }

    // get test key form user
    int tmp = 0;
    cout<<"enter a key in the map"<<endl;
    cin>>tmp;

    // try to get the value at the specified key
    try{
        cout<<newGuy.get(tmp)<<endl;
    }catch(exception &e){
        cout<<e.what()<<endl;
    }

    if(tester == newGuy)
        cout<<"equal"<<endl;

    cout<<"Enter a key to remove from the map:";
    cin>>tmp;

    tester.erase(tmp);
    cout<<tester<<endl;
    
    return 0;
}
