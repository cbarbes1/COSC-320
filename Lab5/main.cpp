//*********************************************************************************
// Authors: Cole Barbes and Harrison Colborne
// Date Created: 10/4/2023
// Description: This program will create Binary search trees, and 
//            : one AVL tree, and time the insertions and balancing of each tree.
//*********************************************************************************
#include <iostream>
#include <chrono>
#include <ctime>
#include "BinaryTree.h"
#include "AVLTree.h"

using namespace std;
using namespace std::chrono;

int main()
{
    srand(time(0)); // seed the rand
    
    // create the 2 binary trees
    BinaryTree<int> BST1;
    BinaryTree<int> BST2;
    
    AVLTree<int> AVL1; // avl declaration
    
    int n = 0, m = 0, b = 0; // init vars
    
    // user input
    cout<<"Enter the number of nodes to insert into the trees: ";
    cin>>n;
    
    cout<<"Enter the max of the integers to enter into the tree: [0, m) ";
    cin>>m;
    
    cout<<"Enter the number of insertions between balances: ";
    cin>>b;
    //
    
    // time a the avl insertion process
    auto start = high_resolution_clock::now();
    //Process to be timed.
    for(int i = 0; i<n; i++)
        AVL1.insertNode(rand()%m+1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    
    // output the needed information
    cout <<"Time to insert into AVL Tree is : "<< duration.count() / 1000000.0 << " seconds" << endl;
    
    // time a the insertion and 1 balance process
    start = high_resolution_clock::now();
    //Process to be timed.
    for(int i = 0; i<n; i++)
        BST1.insertNode(rand()%m+1);
    BST1.balance();
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    
    // output the needed information
    cout <<"Time to insert and Balance once in BST Tree 1 is : "<< duration.count() / 1000000.0 << " seconds" << endl;
    
    // time the insertion and balance every b time then 1 after process
    start = high_resolution_clock::now();
    //Process to be timed.
    for(int i = 0; i<n; i++){
        BST2.insertNode(rand()%m+1);
        if(i%b == 0)
            BST2.balance();
    }
    BST2.balance();
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    
    // output the needed information
    cout <<"Time to insert and Balance at every insert into a BST Tree 2 is : "<< duration.count() / 1000000.0 << " seconds" << endl<<endl;
    
}
