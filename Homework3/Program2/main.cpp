/*
 * Author: Cole Barbes
 * Creation date: 09/20/23
 * last edited: 09/20/23
 * Description: main program to implement a weird binary tree sorting algorithm for COSC 320
 */
#include <iostream>
#include "IntBinaryTree.h"
#include <chrono>
#include <ctime>
#include <algorithm>

using namespace std;
using namespace std::chrono;

void treeSort(int *A, int size);
void AllSort(int *A, int size);

template<class T>
void bubble(T A[], int size);

template<class T>
void insertion(T A[], int size);


int main()
{
	srand(time(0)); // seed the rand

	int size = 0;// set size to 0 

	bool mode = false;

	// take the size in from the user
	cout<<"Input Array Size: ";
	cin>>size;

	cout<<"Please select whether you would like to Time the Tree sort or all of the sorts: Enter 0 For Tree sorts and 1 for All sorts";
	cin>>mode;

	int *A = new int[size]; // create the array
	
	for(int i = 0; i<size; i++)
        A[i] = (rand()%100)+1;

	if(!mode){ // if mode is the tree sort then call function
        	treeSort(A, size);
    	}
    	else{
        	AllSort(A, size);
    	}
	
	return 0;

}

/* This function uses the binary tree to sort and times it
 * Takes the array and size as a parameter
 *
 */
void treeSort(int *A, int size)
{
	int *cpA = new int[size];
	copy(A, A + size, cpA);
    IntBinaryTree HelloWorld; // create the tree
    
	auto start = high_resolution_clock::now();
	HelloWorld.LoadArray(cpA, size); // call the loading function to build the bushy tree
    HelloWorld.ReturnSortedArray(cpA, size); // grab the sorted array from the tree 
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Time to sort using the new tree sort: " << duration.count() / 1000000.0 << " seconds"<< endl;
}

/* This function uses 3 sorts, the binary tree sort, the insertion and the bubble
 * takes the array and size as a parameter
 */
void AllSort(int *A, int size)
{
    
	int *cpA = new int[size];
	copy(A, A + size, cpA);
    
	auto start = high_resolution_clock::now();
	insertion(cpA, size);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Time to sort using the insertion sort algorithm: " << duration.count() / 1000000.0 << " seconds"<< endl;
            
	copy(A, A + size, cpA);
    
	start = high_resolution_clock::now();
	bubble(cpA, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);

	cout << "Time to sort using the bubble sort: " << duration.count() / 1000000.0 << " seconds"<< endl;
            
    copy(A, A + size, cpA);
    
    start = high_resolution_clock::now();
    
	IntBinaryTree HelloWorld; // create the tree
	HelloWorld.LoadArray(cpA, size); // call the loading function to build the bushy tree
	HelloWorld.ReturnSortedArray(cpA, size); // grab the sorted array from the tree
    
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);

	cout << "Time to sort using the new Tree sort: " << duration.count() / 1000000.0 << " seconds"<< endl;
    
    
    delete [] cpA;
    
}

////////////////////////////////////////////////////////////

template<class T>
void bubble(T A[], int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (A[j] > A[j + 1]) {
				T temp = A[j];
				A[j] = A[j + 1];
				A[j + 1] = temp;
			}
		}
	}
}

///////////////////////////////////////////////////////////

template<class T>
void insertion(T A[], int size) {
	for (int i = 0; i < size; i++) {
		int j = 0;
		T val = A[i];
		for (j = i; j > 0 && A[j - 1] > val; j--)
			A[j] = A[j - 1];

		A[j] = val;
	}
}





