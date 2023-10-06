/*
 * Author: Cole Barbes
 * Created on: 10/05/23
 * last edited: 10/05/23
 * created to test a function that rotates a node out of the  tree
 */
#include <iostream>
#include <ctime>
#include "BST.h"

using namespace std;

int main()
{

    srand(time(0)); // seed the rand
    BST<int> Ted;
    
    // create the tree
    int num = 0;
    for(int i = 0; i<50; i++)
        Ted.insert(rand()%100+1);


    // print the tree
    Ted.PrintTree();
    
    // ask for the node to delete
    cout<<"Please enter a number to delete from the tree"<<endl;
    cin>>num;
    
    // delete by rotate
    Ted.rDelete(num);
    
    cout<<"After Deleting "<<num<<" from the tree."<<endl;
    
    Ted.PrintTree();
    return 0;
}
