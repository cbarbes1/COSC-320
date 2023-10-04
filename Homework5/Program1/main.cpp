#include <iostream>
#include <ctime>
#include "BST.h"

using namespace std;

int main()
{
    srand(0);

    BST<int> Ted;

    for(int i = 0; i<10; i++)
        Ted.insert(rand()%10+1);

    Ted.rDelete(9);
    Ted.rDelete(7);
    Ted.rDelete(3);
    Ted.rDelete(2);

    return 0;
}
