#include <iostream>
#include <ctime>
#include "BST.h"

using namespace std;

int main()
{

    BST<int> Ted;
    int num = 0;
    for(int i = 0; i<10; i++)
        Ted.insert(rand()%10+1);


    Ted.PrintTree();

    cin>>num;
    Ted.rDelete(num);


    Ted.PrintTree();
    return 0;
}
