#include <iostream>
#include <chrono>
#include <ctime>
#include "RBTree.h"
#include "AVLTree.h"

using namespace std;
using namespace std::chrono;

int main()
{
    srand(time(0));
    AVLTree<int> AVL;
    RBTree<int> RBT;
    
    int n = 0;
    int m = 0;
    int randomVal = 0;
    
    int cycles = 0;
    
    cout<<"Please enter the number of nodes to place into the Trees ";
    cin>>n;
    
    cout<<"Please enter the max value of the range for example: [0, m) ";
    cin>>m;
    
    cout<<"Please enter the number of cycles for the insertion and deletion simulation ";
    cin>>cycles;
    
    // time a the avl insertion process
    auto start = high_resolution_clock::now();
    //Process to be timed.
    for(int i = 0; i<n; i++)
        AVL.insertNode(rand()%m+1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    
    // output the needed information
    cout <<"\nTime to insert into AVL Tree is : "<< duration.count() / 1000000.0 << " seconds" << endl;
    
    // time a the avl insertion process
    start = high_resolution_clock::now();
    //Process to be timed.
    for(int i = 0; i<n; i++)
        RBT.insert(rand()%m+1);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    
    // output the needed information
    cout <<"Time to insert into RB Tree is : "<< duration.count() / 1000000.0 << " seconds" << endl;
    
    double IPL1 = 0, IPL2 = 0;
    int numNodes1= 0, numNodes2=0;
    double AIPL1=0, AIPL2=0;
    double AIPL3= 0, AIPL4=0;
    
    IPL1 = AVL.IPL();
    IPL2 = RBT.IPL();
    
    numNodes1=AVL.numNodes();
    numNodes2=RBT.numNodes();
    
    AIPL1=IPL1/numNodes1;
    AIPL2=IPL2/numNodes2;
    
    cout<<"The IPL for the AVL tree is "<<AIPL1<<" The IPL for the RB Tree is "<<AIPL2<<endl;
    
    // time the insertion and balance every b time then 1 after process
    start = high_resolution_clock::now();
    //Process to be timed.
    for(int i = 0; i<cycles; i++){
        AVL.insertNode(rand()%m+1);
        
        randomVal = (rand()%m+1);
        
        while(!AVL.searchNode(randomVal))
            randomVal = (rand()%m+1);
        
        AVL.remove(randomVal);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    
    // output the needed information
    cout <<"Time to insert and Delete from the AVL is : "<< duration.count() / 1000000.0 << " seconds" << endl;
    
    // time the insertion and balance every b time then 1 after process
    start = high_resolution_clock::now();
    //Process to be timed.
    for(int i = 0; i<cycles; i++){
        RBT.insert(rand()%m+1);
        
        randomVal = (rand()%m+1);
        
        while(!RBT.find(randomVal))
            randomVal = (rand()%m+1);
        
        RBT.remove(randomVal);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    
    // output the needed information
    cout <<"Time to insert and delete from the RBTree is : "<< duration.count() / 1000000.0 << " seconds" << endl<<endl;
    

    IPL1 = AVL.IPL();
    IPL2 = RBT.IPL();
    
    numNodes1=AVL.numNodes();
    numNodes2=RBT.numNodes();
    

    AIPL3=IPL1/numNodes1;
    AIPL4=IPL2/numNodes2;
    
    cout<<"The IPL for the AVL tree is "<<AIPL3<<" The IPL for the RB Tree is "<<AIPL4<<endl;
    
    
    cout<<"The ratio of the AVL Average Ipl between insertions and the insertions and deletion cycle "<<AIPL1/AIPL3<<endl;
    cout<<"The ratio of the RB Tree average ipl between insertions and the insertions and deletion cycle "<<AIPL2/AIPL4<<endl;
    return 0;
    
}
