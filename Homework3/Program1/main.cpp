/*
 * Author: Cole Barbes
 * Creation date: 09/20/23
 * last edited: 09/20/23
 * Description: main program to implement a weird binary tree sorting algorithm for COSC 320
 */
#include <iostream>
#include "IntBinaryTree.h"

using namespace std;

int main()
{
	srand(time(0)); // seed the rand

	int size = 0;// set size to 0 

	// take the size in from the user
	cout<<"Input Array Size: ";
	cin>>size;

	int *A = new int[size]; // create the array
	
	// loop through the array and fill it with randome values between [1 and 100]
	cout<<endl;
	for(int i = 0; i<size; i++){
		A[i] = (rand()%100)+1;
		cout<<A[i]<<" ";
	}
	cout<<endl;
	
	IntBinaryTree HelloWorld; // create the tree

	HelloWorld.LoadArray(A, size); // call the loading function to build the bushy tree

	HelloWorld.ReturnSortedArray(A, size); // grab the sorted array from the tree 

	// loop through the array and print
	cout<<endl;
	for(int i = 0; i<size; i++)
		cout<<A[i]<<" ";
	cout<<endl;
	
	return 0;

}

