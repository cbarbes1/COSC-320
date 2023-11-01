/*
 * Author: Cole Barbes and Harrison Colborne
 * Creation date: 10/18/23
 * Last Edited: 10/18/23
 * Desciption: utilizes the set class and the functions created in Lab07
 */
#include <iostream>
#include <ctime>
#include <vector>
#include "map.h"

using namespace std;

int main()
{
    map<int, string> tester;

    int signal = 0;

    cout<<"Enter number of data items to enter into the map:";
    cin>>signal;

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

    cout<<newTester<<endl;

    if(newGuy.empty()){
        cout<<"The map is empty"<<endl;
    }

    cout<<newGuy<<endl;

    if(!newGuy.empty()){
        cout<<"The map is not empty"<<endl;
    }

    int tmp = 0;
    cout<<"enter a key in the map"<<endl;
    cin>>tmp;

    cout<<newGuy.get(tmp)<<endl;
    
    return 0;
}
