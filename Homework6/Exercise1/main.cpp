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
    
    set<int> dataSet1, dataSet2; // create the set
    int signal = 0;

    cout<<"How many values would you like to enter?";
    cin>> signal;

    for(int i = 0; i<signal; i++){
        int num = rand()%signal+1;
        dataSet1.insert(num);
    }
    cout<<dataSet1<<endl;

    for(int i = 0; i<signal; i++){
        int num = rand()%signal+1;
        dataSet2.insert(num);
    }

    cout<<dataSet2<<endl;

    int num = 0;
    cout<<"Please enter an integer to test the set: ";
    cin>>num;

    if(dataSet1.find(num)){
        cout<<"value was found"<<endl;
        dataSet1.erase(num);
    }

    cout<<"Please enter values to erase from the set: ";
    cin>>num;

    dataSet1.erase(num);

    vector<int> testVect;

    dataSet1.toVector(testVect);

    for(unsigned int i = 0; i<testVect.size(); i++){
        cout<<testVect[i]<<" ";
    }
    cout<<endl;


    set<int> hello = dataSet1 + dataSet2;
    cout<<hello<<endl;

    if(dataSet1 < hello)
        cout<<"First data set is a strict subset of the union!"<<endl;

    if(dataSet1 <= dataSet1)
        cout<<"First data Set is a subset of itself!"<<endl;

    if(dataSet1 == dataSet1)
        cout<<"First is equal to itself"<<endl;
    
    set<int> difference = dataSet2-dataSet1;
    cout<<difference<<endl;

    set<int> intersection = dataSet1*dataSet2;
    cout<<intersection<<endl;
    
    cout<<dataSet1.size()<<endl;

    return 0;
}
