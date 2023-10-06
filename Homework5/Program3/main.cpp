/*
 * Author: Cole Barbes
 * Creation Date: 10/05/23
 * last edited: 10/05/23
 * Use: This program was created to test different types of deletions methods in a binary tree
 * General consensus: The rotation deletion method left the trees closer to their original state and the merge and copy create too many changes
 */
#include <iostream>
#include <ctime>
#include "BST.h"

using namespace std; 

// simple divider function for cleaner output
void div(){
    cout<<"---------------------------------------------------------------------------------"<<endl;
}

int main()
{

    srand(time(0));
    
    // variable initialization
    BST<int> Ted;
    BST<int> PrisonerZero;
    BST<int> Rory;
    BST<int> TheDoctor;
    int numNodes = 0;
    int min = 0;
    int Max = 0;
    int NumInsertDelete = 0;
    int randomNumber = 0;
    int randomDelete = 0;
    int ogHeight = 0;
    
    int firstHeight = 0;
    int secondHeight = 0;
    int thirdHeight = 0;
    int fourthHeight = 0;
    
    
    // take input from user on the structure of the new tree
    cout<<"Please enter the number of nodes to exist in the tree: ";
    cin>>numNodes;
    
    cout<<"Please enter the min of the random numbers range [min, Max] : ";
    cin>>min;
    
    
    cout<<"Please enter the max of random numbers range [min, Max) :";
    cin>>Max;
    //
    
    // fill the tree with random data
    for(int i = 0; i<numNodes; i++)
        Ted.insert(rand()%(Max-min+1)+min);
    
    ogHeight = Ted.height();

    // set all trees to be the same
    PrisonerZero = Ted;
    Rory = Ted;
    TheDoctor = Ted;
    
    // ask user for the number of insertions and deletions to perform
    cout<<"Please enter the number of insertions and deletions:";
    cin>>NumInsertDelete;
    
    for(int i = 0; i<NumInsertDelete; i++){
        // create random number
        randomNumber = rand()%(Max-min+1)+min;
        
        // insert values into the tree
        Ted.insert(randomNumber);
        PrisonerZero.insert(randomNumber);
        Rory.insert(randomNumber);
        TheDoctor.insert(randomNumber);
        
        // find a delete - able random value
        randomDelete=rand()%(Max-min+1)+min;
        while(randomNumber != randomDelete && !Ted.find(randomDelete))
            randomDelete=rand()%(Max-min+1)+min;
        
        // delete values from the trees 
        Ted.remove(randomDelete); // merge delete
        PrisonerZero.deleteValue(randomDelete); // delete by copy
        Rory.rDeleteByHeight(randomDelete); // delete by rotate using the heights
        TheDoctor.rDeleteByNumNodes(randomDelete); // delete by rotate using the number of nodes
        
    
    }
    
    div();
    
    // get the heights after the insertions and deletions
    firstHeight = Ted.height();
    secondHeight = PrisonerZero.height();
    thirdHeight = Rory.height();
    fourthHeight = TheDoctor.height();
    
    
    
    // create output of needed info about the above trees
    cout<<"Height of the original tree: "<<ogHeight<<endl;
    cout<<"Height of tree 1: "<<firstHeight<<endl;
    cout<<"Height of tree 2: "<<secondHeight<<endl;
    cout<<"Height of tree 3: "<<thirdHeight<<endl;
    cout<<"Height of Tree 4: "<<fourthHeight<<endl;
    div();
    cout<<"Ratio of tree 1 and original: "<<(static_cast<double>(firstHeight)/ogHeight)<<endl;
    cout<<"Ratio of tree 2 and original: "<<(static_cast<double>(secondHeight)/ogHeight)<<endl;
    cout<<"Ratio of tree 3 and original: "<<(static_cast<double>(thirdHeight)/ogHeight)<<endl;
    cout<<"Ratio of tree 4 and original: "<<(static_cast<double>(fourthHeight)/ogHeight)<<endl;
    
    div();
    
    
    return 0;
}
