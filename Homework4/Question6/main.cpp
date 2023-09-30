/* Author: Cole Barbes
 * Creation Date: 09/29/23
 * Last Edited: 09/29/23
 */
#include <iostream>
#include <ctime>
#include <cmath>
#include <chrono>
#include "BST.h"

using namespace std;
using namespace std::chrono;

//function to simulate a given experiment with the parameter number of variables
void simulate(string, BST<int>&, int, int);

int main()
{
    srand(time(0)); // seed the rand

    const int ITER_CONST = 1000; // constant to keep experiment stream line

    // loop to step through the heights
    for(int i = 500; i<=2000; i+=500){

        BST<int> ThisGuy1; // Tree Named ThisGuy to help run this simulation
        BST<int> ThisGuy2; // Tree Named ThisGuy to help run this simulation

        while(ThisGuy1.height() < i){ // create the trees
            int randNum = (rand()%100)+1;
            ThisGuy1.insert(randNum);
            ThisGuy2.insert(randNum);
        }

        //get the heights
        int n1 = ThisGuy1.height();
        int n2 = ThisGuy2.height();

        //print the heights
        cout<<"Height of Tree 1: "<<n1<<" Height of Tree 2: "<<n2<<endl;

        cout<<"-----------------------------------------------------------------------------------------------------------------------"<<endl;
        // time a the sorting process
        auto start = high_resolution_clock::now();
        //Process to be timed.
        simulate("Symmetric", ThisGuy1, i, ITER_CONST);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        // output the needed information needed
        cout << "Time to insert and delete Symmetrically for an "<<i<< " Height Tree is :" << duration.count() / 1000000.0 << " seconds" << endl;
        cout<<"Average IPL length of Tree 1: "<<ThisGuy1.AverageIPL()<<endl;
        cout<<"Ending Height Tree 1: "<<ThisGuy1.height()<<endl;
        cout<<"Number Of Nodes Tree 1: "<<ThisGuy1.numNodes()<<endl;
        cout<<"Expected IPL of Tree 1: "<<((1.386)*(log2(ThisGuy1.numNodes())))<<endl;

        cout<<"-----------------------------------------------------------------------------------------------------------------------"<<endl;
        start = high_resolution_clock::now();
        //Process to be timed.
        simulate("Asymmetric", ThisGuy2, i, ITER_CONST);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);

        // output the needed information
        cout <<"Time to insert and delete Asymmetrically for an "<<i<< " Height Tree is :"<< duration.count() / 1000000.0 << " seconds" << endl;

        cout<<"Average IPL length of Tree 2: "<<ThisGuy2.AverageIPL()<<endl;
        cout<<"Ending Height Tree 2: "<<ThisGuy2.height()<<endl;
        cout<<"Number Of Nodes Tree 2: "<<ThisGuy2.numNodes()<<endl;
        cout<<"Expected IPL of Tree 2: "<<((1.386)*(log2(ThisGuy1.numNodes())))<<endl;


    }



    return 0;
}

/*
 * Simulate the Symmetric and asymmetric deletions
 * Parameters: a type, a tree, the height, and the length of the sim
 */
void simulate(string type, BST<int> &Tree, int height, int lengthOfSim)
{
    srand(time(0));

    if(type == "Symmetric"){
        int numIterations = 0;
        while(numIterations != (lengthOfSim)){ // do the insertion and deletion length of sim number of times
            Tree.insert((rand()%100)+1);
            int randDelete = (rand()%100)+1;
            if(!Tree.find(randDelete))
                randDelete = (rand()%100)+1;

            Tree.remove(randDelete);

            numIterations++;

        }
    }
    else{
        int numIterations = 0;
        while(numIterations != (lengthOfSim)){// do the insertion and deletion length of sim number of times
            Tree.insert((rand()%100)+1);
            int randDelete = (rand()%100)+1;
            if(!Tree.find(randDelete))
                randDelete = (rand()%100)+1;

            Tree.deleteValue(randDelete);

            numIterations++;

        }
    }
}

// EOF
