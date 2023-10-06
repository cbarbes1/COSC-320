/*
 * Test main for the  newly constructed function to delete a value via rotation out of the tree
 * Author: Cole Barbes
 * Created: 10/05/23
 * last edited: 10/05/23
 */
#include <iostream>
#include <ctime>
#include "BST.h"

using namespace std;

int main()
{
    srand(time(0)); // seed the rand
    BST<int> Ted;
    
    // generate the tree
    int num = 0;
    for(int i = 0; i<25; i++)
        Ted.insert(rand()%25+1);


    //print the tree
    Ted.PrintTree();
    
    // ask the user for input regarding the delete
    cout<<"Please enter a number to delete from the tree using rotate delete by height"<<endl;
    cin>>num;
    
    //delete by rotate using height
    Ted.rDeleteByHeight(num);
    
    cout<<"After Deleting "<<num<<" from the tree."<<endl;
    
    Ted.PrintTree();
    
    cout<<"Please enter a number to delete from the tree using rotate delete by number of nodes"<<endl;
    cin>>num;
     
    // delete by rotate using number of nodes
    
    Ted.rDeleteByNumNodes(num);
    
    cout<<"After Deleting "<<num<<" from the tree."<<endl;
    
    Ted.PrintTree();
    
    return 0;
}
