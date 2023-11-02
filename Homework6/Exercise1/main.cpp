/*
 * Author: Cole Barbes
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
    
    set<int> dataSet1, dataSet2; // create the set
    int signal = 0;

    // get size of the set from command line
    cout<<"How many values would you like to enter?";
    cin>> signal;

    // loop to the size and insert random values that are within
    // the size of the array to keep the set uniform enough to view
    for(int i = 0; i<signal; i++){
        int num = rand()%signal+1;
        dataSet1.insert(num);
    }

    // print data set 1
    cout<<"Data Set 1: "<<dataSet1<<endl;

    // loop to the size and insert random values that are within
    // the size of the array to keep the set uniform enough to view
    for(int i = 0; i<signal; i++){
        int num = rand()%signal+1;
        dataSet2.insert(num);
    }

    // print random data set 2
    cout<<"Data Set 2: "<<dataSet2<<endl;

    // grab the integer to test
    int num = 0;
    cout<<"Please enter an integer to test the set: ";
    cin>>num;

    // test if in the data set and then erase it
    if(dataSet1.find(num)){
        cout<<"value was found"<<endl;
        dataSet1.erase(num);
    }else {
        cout<<"Value not in the set"<<endl;
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

//  get the union of the 2 sets
    set<int> hello = dataSet1 + dataSet2;
    cout<<hello<<endl;

    // test if the data set is a strict subset of the union
    if(dataSet1 < hello)
        cout<<"First data set is a strict subset of the union!"<<endl;

    // check if the set is a subset of itself which should be true
    if(dataSet1 <= dataSet1)
        cout<<"First data Set is a subset of itself!"<<endl;

    // check if its equal to itself
    if(dataSet1 == dataSet1)
        cout<<"First is equal to itself"<<endl;
    
    // get the difference of A - B
    set<int> difference = dataSet2-dataSet1;
    cout<<difference<<endl;

    // get the set of same elements between sets
    set<int> intersection = dataSet1*dataSet2;
    cout<<intersection<<endl;
    
    // get the size of the set
    cout<<dataSet1.size()<<endl;

    // test the equals operator
    set<int> equalTester;
    equalTester = dataSet1;

    // print the set from the equals set
    cout<<equalTester<<endl;

    return 0;
}
