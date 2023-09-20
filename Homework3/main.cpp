#include <iostream>
#include "IntBinaryTree.h"

using namespace std;

int main()
{
	srand(time(0));
	int size = 0;

	cout<<"Input Array Size: ";
	cin>>size;

	int *A = new int[size];

	for(int i = 0; i<size; i++)
		A[i] = (rand()%100)+1;
	
	IntBinaryTree HelloWorld;
	HelloWorld.LoadArray(A, size);

	HelloWorld.PrintTree();

	HelloWorld.ReturnSortedArray(A, size);
	
	HelloWorld.PrintTree();

	for(int i = 0; i<size; i++)
		cout<<A[i]<<endl;
	
	return 0;

}

