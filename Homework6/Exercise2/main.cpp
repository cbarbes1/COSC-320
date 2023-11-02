/*
 * Author: Cole Barbes
 * Creation date: 10/18/23
 * Last Edited: 10/18/23
 * Desciption: utilizes the multiset class and the functions created in Lab07
 */
#include <iostream>
#include <ctime>
#include <vector>
#include "multiset.h"

using namespace std;

int main()
{

    srand(time(0)); // seed the rand

    multiset<int> dataSet1, dataSet2; // create the multiset
    int signal = 0;

    // get size of the multiset from command line
    cout<<"How many values would you like to enter?";
    cin>> signal;

    // loop to the size and insert random values that are within
    // the size of the array to keep the multiset uniform enough to view
    for(int i = 0; i<signal; i++){
        int num = rand()%signal+1;
        dataSet1.insert(num);
    }

    // print data multiset 1
    cout<<"Data Set 1: "<<dataSet1<<endl;

    // loop to the size and insert random values that are within
    // the size of the array to keep the multiset uniform enough to view
    for(int i = 0; i<signal; i++){
        int num = rand()%signal+1;
        dataSet2.insert(num);
    }

    // print random data multiset 2
    cout<<"Data Set 2: "<<dataSet2<<endl;

    // grab the integer to test
    int num = 0;
    cout<<"Please enter an integer to test the multiset: ";
    cin>>num;

    // test if in the data multiset and then erase it
    if(dataSet1.find(num)){
        cout<<"value was found"<<endl;
        dataSet1.erase(num);
    }else {
        cout<<"Value not in the multiset"<<endl;
    }

    // create test vector and array
    vector<int> testVect;
    int *arr = new int[dataSet1.size()];

    // send them to vectors or array
    dataSet1.toVector(testVect);
    dataSet1.toArray(arr, dataSet1.size());

    cout<<"As a vector: ";
    // print the vector
    for(unsigned int i = 0; i<testVect.size(); i++){
        cout<<testVect[i]<<" ";
    }
    cout<<endl;

    cout<<"As an array: ";
    // print the array
    for(int i = 0; i<dataSet1.size(); i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;

//  get the union of the 2 multisets
    multiset<int> hello = dataSet1 + dataSet2;
    cout<<hello<<endl;

    // test if the data multiset is a strict submultiset of the union
    if(dataSet1 < hello)
        cout<<"First data multiset is a strict subset of the union!"<<endl;

    // check if the multiset is a submultiset of itself which should be true
    if(dataSet1 <= dataSet1)
        cout<<"First data Set is a subset of itself!"<<endl;

    // check if its equal to itself
    if(dataSet1 == dataSet1)
        cout<<"First is equal to itself"<<endl;

    // get the difference of A - B
    multiset<int> difference = dataSet2-dataSet1;
    cout<<difference<<endl;

    // get the multiset of same elements between multisets
    multiset<int> intersection = dataSet1*dataSet2;
    cout<<intersection<<endl;

    // get the size of the multiset
    cout<<dataSet1.size()<<endl;

    // test the equals operator
    multiset<int> equalTester;
    equalTester = dataSet1;

    // print the multiset from the equals multiset
    cout<<equalTester<<endl;

    return 0;
}

