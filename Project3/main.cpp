/* Author: Cole Barbes
 * Last Date Edited: 11/1/23
 * Description: This is a main file to create and implement a graph algorithm library
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <sstream>
#include "tinyfiledialogs.h"
#include <fstream>
#include <string>

#include "ListOfLists.h"

using namespace std;

template<class T>
class edge {
public:
	T f, t;

	edge(T from, T to) {
		f = from;
		t = to;
	}
};

// Prototypes of each function
int findMinWnodePos(vector<double> &);

template<class T>
void Print(ListOfLists<T>);

template<class T>
void depthFirstSearch(ListOfLists<T>);

template<class T>
void DFS(ListOfLists<T>, vector<int>&, int, int&, vector<edge<T>>&);

template<class T>
void breadthFirstSearch(ListOfLists<T> G);

vector<double> DijkstraAlgorithm(ListOfLists<int> adj, int start);

vector<double> FordAlgorithm(ListOfLists<int> adj, int start);

void findPathRec(ListOfLists<int> G, int start, int end, double cost, double totalcost, vector<int> path, vector<int> &solpath);

vector<int> findPath(ListOfLists<int> G, int start, int end, double totalcost);

void loadMatrix(ListOfLists<int>&);

bool detectCycles(ListOfLists<int> G);

void cycleDFS(ListOfLists<int> G, vector<int> &num, int pos, int &count, bool &cycle, int parent);

ListOfLists<int> KruskalAlgorithm(ListOfLists<int> G);

/*
ListOfLists<int> BoruvkaAlgorithm(ListOfLists<int> G);

ListOfLists<int> JarnikPrimAlgorithm(ListOfLists<int> G);
*/

void div(){
	cout << "\n---------------------------------\n\n";
}

int main() {

	// ask the user for which algorithm to run
	int type = 0;
	cout<<"Please enter what algorithm to run: (0: Depth First, 1: Breadth First, 2: Dijkstras, 3: Ford's, 4: Cycle Detection, 5: Kruskals Min spanning tree)";
	cin>>type;

	// create the graph using the load function which asks the user for which file to use using tiny file dialogs
	ListOfLists<int> graphAdj;
	loadMatrix(graphAdj);
	cout<<"  ";

	// Print the adjacency matrix
	for(int i = 0; i<graphAdj.size(); i++)
		cout<<static_cast<char>('a'+i)<<" ";
	cout<<endl;
	for(int i = 0; i<graphAdj.size(); i++){
		cout<<static_cast<char>('a'+i)<<" ";
		for(int j = 0; j<graphAdj.size(); j++)
			cout<<graphAdj[i][j]<<" ";
		cout<<endl;
	}

	if(type == 0){
		depthFirstSearch(graphAdj);
		cout << endl;
	}else if(type == 1){
		breadthFirstSearch(graphAdj);
		cout << endl;
	}else if(type == 2){
		// graph weight vector from dijkstras
		vector<double> weightVect = DijkstraAlgorithm(graphAdj, 3);

		// print the weights
		for(unsigned int i = 0; i<weightVect.size(); i++){
			cout<<static_cast<char>('a'+i)<<" : "<<weightVect[i]<<endl;
		}

		// find the path given the start
		vector<int> path1 = findPath(graphAdj, 3, 6, weightVect[6]);

		for(unsigned int i = 0; i<path1.size(); i++)
			cout<<static_cast<char>('a'+path1[i])<<" ";
		cout<<endl;
		
		// print path of different start
		vector<int> path2 = findPath(graphAdj, 3, 2, weightVect[2]);

		for(unsigned int i = 0; i<path2.size(); i++)
			cout<<static_cast<char>('a'+path2[i])<<" ";
		cout<<endl;
	}else if(type == 3){
		int startingNode = 0;
		int toNode1 = 0;
		int toNode2 = 0;
		cout<<"Enter a node to start from: 0-n numerical node names!";
		cin>>startingNode;
		// start the fords algorithm from
		vector<double> weightVect = FordAlgorithm(graphAdj, startingNode);

		// print the weights
		for(unsigned int i = 0; i<weightVect.size(); i++){
			cout<<static_cast<char>('a'+i)<<" : "<<weightVect[i]<<endl;
		}
	}else if(type == 4){
		// detect whether the graph has a cycle
		if(detectCycles(graphAdj)){
			cout<<"Cycle Detected in the graph"<<endl;
		}else{
			cout<<"No Cycle Detected"<<endl;
		}
	}else if(type == 5){
		// use the requested algorithm to find min spanning tree
		ListOfLists<int> tree = KruskalAlgorithm(graphAdj);
		depthFirstSearch(tree);
		Print(tree);
	}else if(type == 6){

	}else if(type==7){

	}else{
		cout<<"Invalid Selection"<<endl;
	}
	

	return 0;
}

//does the first step of the depthFirstSearch
template<class T>
void depthFirstSearch(ListOfLists<T> G) {
	vector<int> num;
	vector<edge<T>> E;
	int count = 1;

	// create number vector
	for (int i = 0; i < G.size(); i++)
		num.push_back(0);

	while (find(num.begin(), num.end(), 0) < num.end()) {
		int pos = find(num.begin(), num.end(), 0) - num.begin();
		DFS(G, num, pos, count, E);
	}

	for (edge<T> e : E)
		cout << static_cast<char>(e.f +'a') << " - " << static_cast<char>(e.t+'a') << endl;
}

//does the recursive step of the depthFirstSearch
// below we changed how the for loop executes so it does a depth first breadth first
// 
template<class T>
void DFS(ListOfLists<T> G, vector<int> &num, int pos, int &count, vector<edge<T>> &E) {
	vector<T> Adj = G[pos]; // save the row into adj 
    
	num[pos] = count++;

	for (int i = 0; i < G.size(); i++) {
		T vert = Adj[i]; // save the value in the adjacent node list

		if (vert && num[i] == 0) { // if there is a node and we either reached the end or num has no value in this position
			E.push_back( {pos, i});
			DFS(G, num, i, count, E);
		}
	}
	
}

// Does the breadthFirstSearch
template<class T>
void breadthFirstSearch(ListOfLists<T> G) {
	vector<int> num;
	vector<edge<T>> E;
	deque<T> queue;
	int count = 1;

	for (int i = 0; i < G.size(); i++) {
		num.push_back(0); 
	}

	while (find(num.begin(), num.end(), 0) < num.end()) {
		int pos = find(num.begin(), num.end(), 0) - num.begin();
		num[pos] = count++; // save in the num vector the position we have reached
		queue.push_back(pos); // save the first node in the queue to start algorithm
		while (!queue.empty()) {
			T vert = queue.front(); // pop off the front 
			queue.pop_front();
			vector<T> Adj = G[vert]; // save the vector at this vertex position
			for (int i = 0; i < Adj.size(); i++) {
				if (num[i] == 0 && Adj[i]) {
					num[i] = count++;
					queue.push_back(i);
					E.push_back( { vert , i});
				}
			}
		}
		
	}

	for (edge<T> e : E)
		cout << static_cast<char>(e.f +'a') << " - " << static_cast<char>(e.t+'a') << endl;
}

int findMinWnodePos(vector<double> &nodes, vector<int> &check) {
	int minnodepos = 0;
	for (int j = 0; j < check.size(); j++)
		if (nodes[check[j]] < nodes[check[minnodepos]])
			minnodepos = j;

	return minnodepos;
}

/*
 * Fords algorithm to find the minimum path cost
 * Parameters: The graph as an adjacency matrix, and the start
 * Return: the vector of the weights at each node
 */
vector<double> FordAlgorithm(ListOfLists<int> G, int start) {
	vector<double> nodes;

	int min = 0;
	double max = 1E100; // DBL_MAX;
	int v = 0;

	// fill the array with infinity
	for(unsigned int i = 0; i<G.size(); i++)
		nodes.push_back(max);

	// set the starting node to 0
	nodes[start] = 0;

	bool finished = false;
	while (!finished) {
		finished = true;

		// traverse through the graph and if there is a node then check if the weight is minimum
		for (int j = 0; j < G.size(); j++) {
			for(int k = 0; k < G.size(); k++){
				if (G[j][k] != 0 && nodes[k] > nodes[j] + G[j][k]) {
					nodes[k] = nodes[j] + G[j][k];
					finished = false;
				}
			}
		}
	}

	return nodes;
}

/*
 * Dijkstras algorithm to find the minimum path
 * Paramters: The graph as an adjacency matrix and the start
 * return the vector of weights
 */
vector<double> DijkstraAlgorithm(ListOfLists<int> adjMatrix, int start) {
	vector<double> nodes;
	vector<int> tobechecked;
	int min = 0;
	double max = 1E100; // DBL_MAX;
	int v = 0;

	// fill with max
	for(unsigned int i = 0; i<adjMatrix.size(); i++)
		nodes.push_back(max);

	// set the start
	nodes[start] = 0;

	// fill to be checked with all nodes
	for (unsigned int i = 0; i < adjMatrix.size(); i++)
		tobechecked.push_back(i);

	
	while (!tobechecked.empty()) {
		v = findMinWnodePos(nodes, tobechecked); // find the minimum node position
		int tmp = tobechecked[v]; // save from to be checked
		tobechecked.erase(tobechecked.begin() + v); // erase the node from to be checked
		v = tmp;
		double node = nodes[v];

		for (int j = 0; j < adjMatrix.size(); j++){// traverse the matrix at the given node and look for cheapest path
				if (adjMatrix[v][j] != 0 && find(tobechecked.begin(), tobechecked.end(), j)!=tobechecked.end()){
					if(nodes[j] > node + adjMatrix[v][j]) {
						nodes[j] = node + adjMatrix[v][j];
					}
				}
		}
	}

	return nodes;
}

//  Assumes the graph is given as adjacency lists.
bool detectCycles(ListOfLists<int> G) {
	vector<int> num;
	int count = 1;
	bool cycle = false;

	// fill check array with 0s indicating that that node has been used
	for (int i = 0; i < G.size(); i++){
		num.push_back(0);
	}

	// while there is a node with the value of 0 keep calling DFS
	while (find(num.begin(), num.end(), 0) < num.end()) {
		int pos = find(num.begin(), num.end(), 0) - num.begin();
		cycleDFS(G, num, pos, count, cycle, -1);
	}

// Probably overkill but have seen this in print.
// Simply checks every starting vertex.
//	for (int i = 0; i < G.size(); i++) {
//		for (int j = 0; j < num.size(); j++)
//			num[j] = 0;
//
//		cycleDFS(G, num, i, count, cycle);
//	}

	return cycle;
}

/*
 * recursively loop for a cycle in the given graph
 * Parameters: the graph, the num vector, the position, the count of step, the cycle checker, and the parent node
 * return: none
 */
void cycleDFS(ListOfLists<int> G, vector<int> &num, int pos, int &count, bool &cycle, int parent) {
	vector<int> Adj = G[pos];
	num[pos] = count++;
	int inf = 1000000000;

	// find a node which has made it out of the DFS that is not the parent
	for (int i = 0; i < Adj.size(); i++) {
		int vert = Adj[i];
		if (vert!=0 && num[i] == 0){
			cycleDFS(G, num, i, count, cycle, pos);
		}else if (vert!=0 && num[i] != inf && parent!=i)
			cycle = true;
	}
	
	num[pos] = inf;
}

/*
 * go through the matrix recursively and find the next node that satsfies the cost
 */
void findPathRec(ListOfLists<int> G, int start, int end, double cost, double totalcost, vector<int> path, vector<int> &solpath) {
	double tol = 0.000001; // For roundoff error.
	path.push_back(start);
	if (start == end) {
		solpath = path;
	}

	for (int j = 0; j < G[start].size(); j++)
			if (G[start][j] != 0 && cost + G[start][j] <= totalcost + tol)
				findPathRec(G, j, end, cost + G[start][j], totalcost, path, solpath);
}

/*
 * setup the recursive call for the find path function
 */
vector<int> findPath(ListOfLists<int> G, int start, int end,
		double totalcost) {
	vector<int> path;
	vector<int> solpath;
	findPathRec(G, start, end, 0, totalcost, path, solpath);
	return solpath;
}

/*
 * Kruskals algorithm to find the minimum spanning tree
 * parameters: the graph
 * return the MST tree
 */
ListOfLists<int> KruskalAlgorithm(ListOfLists<int> G) {
	ListOfLists<int> MST(G.size(), G.size());
	ListOfLists<int> MST_test(G.size(), G.size());
	vector<pair<int, pair<int, int>>> H;

	// setup the needed trees and the list of each edge
	for(int i = 0; i<G.size(); i++){
		for(int j = i; j<G.size(); j++){
			MST[i][j] = 0;
			MST_test[i][j] = 0;
			MST[j][i] = 0;
			MST_test[j][i] = 0;
			if(G[i][j]!=0){
				pair<int, int> tmp;
				tmp.first = i;
				tmp.second = j;
				H.push_back({G[i][j], tmp});
			}
		}
	}
	int treeSize = 0; // set the size of the tree to 0

	sort(H.begin(), H.end()); // sort the list of edges

	// loop through the list until the end or the tree is large enough
	for (int i = 0; i < H.size() && treeSize < G.size() - 1; i++) {
		// get the min node
		pair<int, int> e = H[i].second;
		// set the test tree
		MST_test = MST;
		// save the new node into the tree
		MST_test[e.first][e.second] = G[e.first][e.second];
		MST_test[e.second][e.first] = G[e.first][e.second];

		if (!detectCycles(MST_test)) { // if no cycle then add to the tree
			MST = MST_test;
			treeSize++;
		}
	}
	return MST;
}
/*
ListOfLists<int> BoruvkaAlgorithm(ListOfLists<int> G)
{
	vector<ListOfLists<int>> trees;
	for(int i = 0; i<G.size(); i++){
		ListOfLists<int> tmp;
		tmp.addRow();
		trees.push_back(tmp);
	}

	while(trees.size() > 1){
		for(ListOfLists<int> t : trees){

		}
	}
}

ListOfLists<int> JarnikPrimAlgorithm(ListOfLists<int> G)
{

}
*/

//Prints the ListOfLists
template<class T>
void Print(ListOfLists<T> L) {
	if (L.size() == 0)
		return;

	for (int i = 0; i < L.size(); i++) {
		for (int j = 0; j < L[i].size(); j++)
			cout << L[i][j] << " ";
		cout << endl;
	}
}

/*
 * Load the files of the given type
 * Parameters: the list to save it into
 */
void loadMatrix(ListOfLists<int> &list)
{
	// get a file to use in n gram key calculation
    char const *lFilterPatterns[2] = { "*.txt", "*"};
    char const *filename1 = tinyfd_openFileDialog("Open Adjacency Matrix File", NULL, 1, lFilterPatterns, "Adjacency Matrix File", 0);
    cout<<"Opening "<<filename1<<endl;
    ifstream InFile1(filename1);// open the file for input
    if(InFile1){
		vector<int> tempL;
		string line = "";
		int temp = 0;
		int numVect = 0;
		// get the line number
		while(getline(InFile1, line)){
			numVect++;
		}
		InFile1.close();
		ifstream InFile1(filename1);// open the file for input
		// go through each line and fill the adjacency matrix with values
		for(int i = 0; i<numVect && !InFile1.eof(); i++){
			for(int j = 0; j<numVect; j++){
				InFile1>>temp;
				tempL.push_back(temp);
			}
			InFile1.ignore(256, '\n');
			list.push_back(tempL);
			tempL.clear();
		}
    }else{
        cerr<<"Adjacency Matrix file is needed to proceed, exiting\n";
    }
    InFile1.close();
}
