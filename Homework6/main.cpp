/*
 * Author: Cole Barbes and Harrison Colborne
 * Creation date: 10/18/23
 * Last Edited: 10/18/23
 * Desciption: utilizes the set class and the functions created in Lab07
 */
#include <iostream>
#include <ctime>
#include <vector>
#include "set.h"

using namespace std;

int main()
{
    
    srand(time(0)); // seed the rand
    
    set<int> dataSet; // create the set
    
    // create needed container vars
    int setSize = 0;
    int randNum = 0;
    
    // take in the set size
    cout<<"Please enter the size of the set: ";
    cin>>setSize;
    
    if(dataSet.empty()){
        cout<<"The set is empty { }"<<endl;
    }
    // insert random values into the tree
    for(int i = 0; i<setSize; i++){
        randNum = rand()%1000+1;
        while(dataSet.find(randNum))
            randNum = rand()%1000+1;
        dataSet.insert(randNum);
    }

    cout<<dataSet<<endl;

    set<int> newData = dataSet;

    if(dataSet.empty()){
        cout<<"The set is empty { }"<<endl;
    }else{
        cout<<"NOT EMPTY"<<endl;
    }

    cout<<"----------------------------------------"<<endl;

    vector<int> stuff;

    newData.toVector(stuff);

    int *array = new int[setSize];

    dataSet.toArray(array, setSize);

    for(int i = 0; i<setSize; i++){
        cout<<stuff[i]<<" ";
       // cout<<array[i]<<" ";
    }
    cout<<endl;
    cout<<newData;

    cout<<"----------------------------------------"<<endl;

    for(int i = 0; i<setSize; i++){
       // cout<<stuff[i]<<" ";
       cout<<array[i]<<" ";
    }
    cout<<endl;
    cout<<dataSet<<endl;

    cout<<"----------------------------------------"<<endl;

    if(newData == dataSet)
        cout<<"The sets are equivalent"<<endl;

    if(newData < dataSet)
        cout<<"The second set is strict subset of the first"<<endl;
    else
        cout<<"Not a strict subset of the other"<<endl;

    cout<<"----------------------------------------"<<endl;
    // get a random value to find in the tree
    randNum = (rand()%setSize+1);
    bool tester = dataSet.find(randNum);
    newData.erase(randNum);

    if(newData < dataSet)
        cout<<"The second set is strict subset of the first"<<endl;
    else
        cout<<"Not a subset of the other"<<endl;

    set<int> hello = dataSet + newData;
    cout<<hello<<endl;

    set<int> intersection = dataSet*newData;
    cout<<intersection<<endl;

    set<int> difference = dataSet-newData;

    return 0;
}
