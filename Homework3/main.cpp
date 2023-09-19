#include <iostream>
#include "IntBinaryTree.h"

using namespace std;

int main()
{
	int *A = new int[8];

	for(int i = 0; i<8; i++)
		A[i] = (i+1);

	IntBinaryTree HelloWorld;

	HelloWorld.LoadArray(A, 8);

	HelloWorld.PrintTree();

	return 0;

}

