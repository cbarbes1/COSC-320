//***************************************************************
// Harrison Colborne and Cole Barbes
// Date Created 9/20/2023
//***************************************************************
#include <iostream>
#include "BinaryTree.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{
    srand(time(0)); // seed the rand
    
    int numNodes = 0; // create number of node var
    
    BinaryTree<long> Tree; // create a binary tree
    
    // ask the user for the desired number of nodes
    cout<<"How many nodes would you like to place in the tree? ";
    cin>>numNodes;
     
    // loop through and set the nodes to rand numbers
    for(int i = 0; i<numNodes; i++)
        Tree.insertNode(rand());
 
    // time the increment in order
    auto start = high_resolution_clock::now();
	Tree.incrementInOrder();
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
     
    // output the time
    cout << "Time to Increment In Order recursively: " << duration.count() / 1000000.0 << " seconds"
			<< endl;
    
    // time the Post order recursive algorithm
    start = high_resolution_clock::now();
	Tree.incrementPostOrder();
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
    
    // output the time
    cout << "Time to Increment Post Order recursively: " << duration.count() / 1000000.0 << " seconds"
			<< endl;
    
    // time the pre order recursive function
    start = high_resolution_clock::now();
	Tree.incrementPreOrder();
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
    
    // output the time
    cout << "Time to Increment Pre Order recursively: " << duration.count() / 1000000.0 << " seconds"
			<< endl;
    
    // time the pre order iterative function
    start = high_resolution_clock::now();
	Tree.incrIterativePreorder();
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
    
    // output the time
    cout << "Time to Increment Pre Order iteratively: " << duration.count() / 1000000.0 << " seconds"
			<< endl;
    
    // time the post order 2 stacks iterative function
    start = high_resolution_clock::now();
	Tree.incrIterativePostorder2Stacks();
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
    
    // output the time
    cout << "Time to Increment Post Order 2 stacks iteratively: " << duration.count() / 1000000.0 << " seconds"
			<< endl;
    
    // time the post order iterative function
    start = high_resolution_clock::now();
	Tree.incrIterativePostorder();
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
    
    // output the time
    cout << "Time to Increment Post Order iteratively: " << duration.count() / 1000000.0 << " seconds"
			<< endl;
    
    // time the In order iterative function
    start = high_resolution_clock::now();
	Tree.incrIterativeInorder();
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
    
    // output the time
    cout << "Time to Increment In Order iteratively: " << duration.count() / 1000000.0 << " seconds"
			<< endl;
    
    return 0;
}
