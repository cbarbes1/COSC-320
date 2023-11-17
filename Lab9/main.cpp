/* Author: Dr. Spickler 
 * Last Edited by : Harrison Colborne and Cole Barbes
 * Last Date Edited: 10/17/23
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

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
void Print(ListOfLists<T>);

template<class T>
void AddNode(ListOfLists<T>&, T);

template<class T>
void AddEdge(ListOfLists<T>&, T, T);

template<class T>
void AddEdges(ListOfLists<T> &G, T f, vector<T> tv);

template<class T>
void depthFirstSearch(ListOfLists<T>);

template<class T>
void DFS(ListOfLists<T>, vector<int>&, int, int&, vector<edge<T>>&);

template<class T>
int findVertexPos(ListOfLists<T> G, T vert);

template<class T>
int findVertexPos(vector<T> G, T vert);

template<class T>
void breadthFirstSearch(ListOfLists<T> G);

void div(){
	cout << "\n---------------------------------\n\n";
}

int main() {
	ListOfLists<int> adjMatrix(6, 6);
    ListOfLists<int> adjMatrix2(10, 10);

    // create an adjacency matrix for a undirected graph
    adjMatrix[0] = { 0, 0, 1, 1, 0, 1};
	adjMatrix[1] = { 0, 0, 0, 1, 1, 0};
	adjMatrix[2] = { 1, 0, 0, 0, 0, 1};
	adjMatrix[3] = { 1, 1, 0, 0, 1, 1};
	adjMatrix[4] = { 0, 1, 0, 1, 0, 0};
	adjMatrix[5] = { 1, 0, 1, 1, 0, 0};
    //
    
    // create an adjacency matrix for a directed graph
    adjMatrix2[0] = { 0, 0, 0, 0, 1, 0, 0, 1, 0, 0};
	adjMatrix2[1] = { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0};
	adjMatrix2[2] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	adjMatrix2[3] = { 1, 0, 0, 0, 0, 0, 0, 1, 0, 0};
	adjMatrix2[4] = { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
	adjMatrix2[5] = { 0, 1, 1, 0, 0, 0, 1, 0, 1, 0};
	adjMatrix2[6] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    adjMatrix2[7] = { 0, 0, 0, 0, 1, 0, 0, 0, 1, 0};
    adjMatrix2[8] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
    adjMatrix2[9] = { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0};
    //
    
    cout<<"Undirected Graph: "<<endl;
	Print(adjMatrix);
	cout << endl;

	depthFirstSearch(adjMatrix);
	cout << endl;

	breadthFirstSearch(adjMatrix);
	cout << endl;

    cout<<"Directed Graph: "<<endl;
    Print(adjMatrix2);
	cout << endl;

	depthFirstSearch(adjMatrix2);
	cout << endl;

	breadthFirstSearch(adjMatrix2);
	cout << endl;
    
    
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

		if (vert == 1 && (num[i] == 0 || num[i] == (i+1))) { // if there is a node and we either reached the end or num has no value in this position
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
				if ((num[i] == 0 || num[i] == (i+1)) && Adj[i] == 1) {
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
