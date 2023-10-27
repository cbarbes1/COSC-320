/*
 * Author: Cole Barbes and Harrison Colborne
 * Creation date: 10/18/23
 * Last Edited: 10/18/23
 * Desciption: utilizes the set class and the functions created in Lab07
 */
#include <iostream>
#include <ctime>
#include <vector>
#include "multiset.h"

using namespace std;

int main()
{
    
    srand(time(0)); // seed the rand
    
    multiset<int> dataSet1; // create the set
    
    // create needed container vars
    int setSize1 = 0;
    int randNum = 0;
    
    // take in the set size
    cout<<"Please enter the size of the set: ";
    cin>>setSize1;
    
    // insert random values into the tree
    for(int i = 0; i<setSize1; i++){
        randNum = rand()%10+1;
        dataSet1.insert(randNum);
    }
    
    multiset<int> dataSet2; // create the set
    
    // create needed container vars
    int setSize2 = 0;
    
    // take in the set size
    cout<<"Please enter the size of the set: ";
    cin>>setSize2;
    
    // insert random values into the tree
    for(int i = 0; i<setSize2; i++){
        randNum = rand()%10+1;
        dataSet2.insert(randNum);
    }

    cout<<dataSet1<<endl;
    
    cout<<dataSet2<<endl;

    if(dataSet1 == dataSet2)
        cout<<"The sets are equivalent"<<endl;
    else 
        cout<<"The sets are not equivalent"<<endl;

    if(dataSet2 < dataSet1)
        cout<<"The second set is strict subset of the first"<<endl;
    else
        cout<<"Not a strict subset of the other"<<endl;

    cout<<"----------------------------------------"<<endl;

    if(dataSet1 < dataSet2)
        cout<<"The first set is strict subset of the second"<<endl;
    else
        cout<<"Not a subset of the other"<<endl;

    multiset<int> hello = dataSet1 + dataSet2;
    cout<<hello<<endl;
    
    multiset<int> difference = dataSet1-dataSet2;
    cout<<difference<<endl;

    multiset<int> intersection = dataSet1*dataSet2;
    cout<<intersection<<endl;
    
    cout<<dataSet1.count(10)<<endl;

    cout<<dataSet1.size()<<endl;
    dataSet1.clear();
    dataSet2.clear();
    
    

    return 0;
}
