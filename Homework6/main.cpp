/*
 * Author: Cole Barbes and Harrison Colborne
 * Creation date: 10/18/23
 * Last Edited: 10/18/23
 * Desciption: utilizes the set class and the functions created in Lab07
 */
#include <iostream>
#include <ctime>
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
    
    // insert random values into the tree
    for(int i = 0; i<setSize; i++)
        dataSet.insert(rand()%setSize+1);
    
    // get a random value to find in the tree
    randNum = (rand()%setSize+1);
    bool tester = dataSet.find(randNum);
    
    // if the value was found remove it
    if(tester){
        cout<<randNum<<" is in the set "<<endl;
        dataSet.erase(randNum);
    }else 
        cout<<randNum<<" is not in the set"<<endl;
    
    return 0;
}
