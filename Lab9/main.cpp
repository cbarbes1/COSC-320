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
	ListOfLists<int> adjMatrix(7, 7);

    adjMatrix[0] = { 0, 0, 1, 1, 0, 1, 0 };
	adjMatrix[1] = { 0, 0, 0, 1, 1, 0, 0 };
	adjMatrix[2] = { 1, 0, 0, 0, 0, 1, 0 };
	adjMatrix[3] = { 1, 1, 0, 0, 1, 1, 0 };
	adjMatrix[4] = { 0, 1, 0, 1, 0, 0, 0 };
	adjMatrix[5] = { 1, 0, 1, 1, 0, 0, 0 };
	adjMatrix[6] = { 0, 0, 0, 0, 0, 0, 0 };

	Print(adjMatrix);
	cout << endl;

	depthFirstSearch(adjMatrix);
	cout << endl;

	breadthFirstSearch(adjMatrix);
	cout << endl;

	return 0;
}

template<class T>
int findVertexPos(ListOfLists<T> G, T vert) {
	int vPos = -1;
	for (int j = 0; j < G.size(); j++) {
		if (G[j][0] == vert)
			vPos = j;
	}
	return vPos;
}

template<class T>
int findVertexPos(vector<T> L, T vert) {
	int vPos = -1;
	for (int j = 0; j < L.size(); j++) {
		if (L[j] == vert)
			vPos = j;
	}
	return vPos;
}

//  Assumes the graph is given as adjacency lists.
template<class T>
void depthFirstSearch(ListOfLists<T> G) {
	vector<int> num;
	vector<edge<T>> E;
	int count = 1;

	for (int i = 0; i < G.size(); i++)
		num.push_back(0);

	while (find(num.begin(), num.end(), 0) < num.end()) {
		int pos = find(num.begin(), num.end(), 0) - num.begin();
        cout<<"Before DFS"<<endl;
		DFS(G, num, pos, count, E);
	}

	for (edge<T> e : E)
		cout << static_cast<char>(e.f +'a') << " - " << static_cast<char>(e.t+'a') << endl;
}

template<class T>
void DFS(ListOfLists<T> G, vector<int> &num, int pos, int &count,
		vector<edge<T>> &E) {
	vector<T> Adj = G[pos];
	num[pos] = count++;

	for (int i = 0; i < Adj.size(); i++) {
		T vert = Adj[i];

		if (vert == 1 && num[i] == 0) {
			E.push_back( {pos, i});
            DFS(G, num, ++pos, count, E);
		}
		
	}
	
}

template<class T>
void breadthFirstSearch(ListOfLists<T> G) {
	vector<int> num;
	vector<T> V;
	vector<edge<T>> E;
	deque<T> queue;
	int count = 1;

	for (int i = 0; i < G.size(); i++) {
		num.push_back(0);
		V.push_back(G[i][0]);
	}

	while (find(num.begin(), num.end(), 0) < num.end()) {
		int pos = find(num.begin(), num.end(), 0) - num.begin();
		num[pos] = count++;
		queue.push_back(G[pos][0]);
		while (!queue.empty()) {
			T vert = queue.front();
			queue.pop_front();
			int vPos = findVertexPos(G, vert);
			vector<T> Adj = G[vPos];
			for (int i = 1; i < Adj.size(); i++) {
				int AdjvPos = findVertexPos(G, Adj[i]);
				if (num[AdjvPos] == 0) {
					num[AdjvPos] = count++;
					queue.push_back(Adj[i]);
					E.push_back( { vert, Adj[i] });
				}
			}
		}
	}

	for (edge<T> e : E)
		cout << e.f << " - " << e.t << endl;
}

template<class T>
void AddNode(ListOfLists<T> &G, T n) {
	bool found = false;
	for (int i = 0; i < G.size(); i++) {
		if (G[i].size() > 0 && G[i][0] == n)
			found = true;
	}

	if (!found) {
		G.addRow();
		G[G.size() - 1].push_back(n);
	}
}

template<class T>
void AddEdge(ListOfLists<T> &G, T f, T t) {
	int index = -1;
	for (int i = 0; i < G.size(); i++) {
		if (G[i].size() > 0 && G[i][0] == f)
			index = i;
	}

	bool found = false;
	if (index >= 0) {
		for (int i = 1; i < G[index].size(); i++) {
			if (G[index][i] == t)
				found = true;
		}
	} else
		return;

	if (!found) {
		G[index].push_back(t);
	}
}

template<class T>
void AddEdges(ListOfLists<T> &G, T f, vector<T> tv) {
	int index = -1;
	for (int i = 0; i < G.size(); i++) {
		if (G[i].size() > 0 && G[i][0] == f)
			index = i;
	}

	if (index == -1)
		return;

	for (int j = 0; j < tv.size(); j++) {
		bool found = false;
		for (int i = 1; i < G[index].size(); i++) {
			if (G[index][i] == tv[j])
				found = true;
		}
		if (!found)
			G[index].push_back(tv[j]);
	}
}

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
