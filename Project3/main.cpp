/* Author: Dr. Spickler 
 * Last Edited by : Harrison Colborne and Cole Barbes
 * Last Date Edited: 10/17/23
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

template<class T>
class wedge {
public:
	T from, to;
	double weight;

	wedge(T f, T t, double w = 0) {
		from = f;
		to = t;
		weight = w;
	}

	friend ostream& operator <<(ostream &strm, const wedge &obj) {
		strm << obj.from << " -> " << obj.to << " : " << obj.weight;
		return strm;
	}
};

template<class T>
class wnode {
public:
	T name;
	double weight;

	wnode(T t, double w = 0) {
		name = t;
		weight = w;
	}

	friend ostream& operator <<(ostream &strm, const wnode &obj) {
		strm << obj.name << " : " << obj.weight;
		return strm;
	}

};

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

void cycleDFS(ListOfLists<int> G, vector<int> &num, int pos, int &count, bool &cycle);

vector<int> KruskalAlgorithm(ListOfLists<int> G);

ListOfLists<int> findMinEdge(ListOfLists<int> G);

void div(){
	cout << "\n---------------------------------\n\n";
}

int main() {

	int type = 0;
	cout<<"Please enter what algorithm to run: (0: Depth First, 1: Breadth First, 3: Dijkstras, 4: Ford's, 5: Cycle Detection, )";
	cin>>type;

	ListOfLists<int> graphAdj;
	loadMatrix(graphAdj);
	cout<<"  ";

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
	}else if(type == 3){
		vector<double> weightVect = DijkstraAlgorithm(graphAdj, 3);

		for(unsigned int i = 0; i<weightVect.size(); i++){
			cout<<static_cast<char>('a'+i)<<" : "<<weightVect[i]<<endl;
		}

		vector<int> path1 = findPath(graphAdj, 3, 6, weightVect[6]);

		for(unsigned int i = 0; i<path1.size(); i++)
			cout<<static_cast<char>('a'+path1[i])<<" ";
		cout<<endl;
		
		vector<int> path2 = findPath(graphAdj, 3, 2, weightVect[2]);

		for(unsigned int i = 0; i<path2.size(); i++)
			cout<<static_cast<char>('a'+path2[i])<<" ";
		cout<<endl;
	}else if(type == 4){
		int startingNode = 0;
		int toNode1 = 0;
		int toNode2 = 0;
		cout<<"Enter a node to start from: ";
		cin>>startingNode;
		vector<double> weightVect = FordAlgorithm(graphAdj, startingNode);

		for(unsigned int i = 0; i<weightVect.size(); i++){
			cout<<static_cast<char>('a'+i)<<" : "<<weightVect[i]<<endl;
		}
	}else if(type == 5){
		if(detectCycles(graphAdj)){
			cout<<"Cycle Detected in the graph"<<endl;
		}else{
			cout<<"No Cycle Detected"<<endl;
		}
	}else if(type == 6){

	}else if(type == 7){

	}else if(type==8){

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


vector<double> FordAlgorithm(ListOfLists<int> G, int start) {
	vector<double> nodes;

	int min = 0;
	double max = 1E100; // DBL_MAX;
	int v = 0;

	for(unsigned int i = 0; i<G.size(); i++)
		nodes.push_back(max);

	nodes[start] = 0;

	bool finished = false;
	while (!finished) {
		finished = true;

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

vector<double> DijkstraAlgorithm(ListOfLists<int> adjMatrix, int start) {
	vector<double> nodes;
	vector<int> tobechecked;
	int min = 0;
	double max = 1E100; // DBL_MAX;
	int v = 0;

	for(unsigned int i = 0; i<adjMatrix.size(); i++)
		nodes.push_back(max);

	nodes[start] = 0;

	for (unsigned int i = 0; i < adjMatrix.size(); i++)
		tobechecked.push_back(i);

	
	while (!tobechecked.empty()) {
		v = findMinWnodePos(nodes, tobechecked);
		int tmp = tobechecked[v];
		tobechecked.erase(tobechecked.begin() + v);
		v = tmp;
		double node = nodes[v];

		for (int j = 0; j < adjMatrix.size(); j++){
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

	for (int i = 0; i < G.size(); i++)
		num.push_back(0);

	while (find(num.begin(), num.end(), 0) < num.end()) {
		int pos = find(num.begin(), num.end(), 0) - num.begin();
		cycleDFS(G, num, pos, count, cycle);
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

void cycleDFS(ListOfLists<int> G, vector<int> &num, int pos, int &count, bool &cycle) {
	vector<int> Adj = G[pos];
	num[pos] = count++;
	int inf = 1000000000;

	for (int i = 0; i < Adj.size(); i++) {
		int vert = Adj[i];
		if (vert!=0 && num[i] == 0) {
			cycleDFS(G, num, i, count, cycle);
		}else if (vert!=0 && num[i] != inf)
			cycle = true;
	}
	
	num[pos] = inf;
}

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

vector<int> findPath(ListOfLists<int> G, int start, int end,
		double totalcost) {
	vector<int> path;
	vector<int> solpath;
	findPathRec(G, start, end, 0, totalcost, path, solpath);
	return solpath;
}


vector<int> KruskalAlgorithm(ListOfLists<int> G) {
	ListOfLists<int> MST(G.size(), G.size());
	ListOfLists<int> MST_test(G.size(), G.size());
	ListOfLists<int> H = G;
	int vcount = G.size();

	for (int i = 0; i < H.size() && MST.size() < vcount - 1; i++) {
		 e = getMinNode;
		MST_test = MST;
		MST_test.push_back(e);

		if (!detectCycles(MST_test)) {
			MST = MST_test;
		}
	}
	return MST;
}

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
		while(getline(InFile1, line)){
			numVect++;
		}
		InFile1.close();
		ifstream InFile1(filename1);// open the file for input
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

pair<int, int> findMinEdge(ListOfLists<int> G)
{
	pair<int, int> min(0, 0);
	for(int i = 0; i<G.size(); i++){
		for(int j = 0; j<G.size(); j++)
			if(G[i][j]<G[min.first][min.second]){
				min.first = i;
				min.second = j;
			}
	}
	return min;
}