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

int main() {
	// Building graph structures from the ListOfLists structure.
	ListOfLists<int> G;
	ListOfLists<char> G1;
	ListOfLists<int> GI2(7, 7);

	for (int i = 1; i <= 7; i++)
		AddNode(G, i);

	AddEdges(G, 1, { 2, 3, 7, 5 });
	AddEdges(G, 2, { 4, 2, 5 });
	AddEdges(G, 3, { 1, 2, 6, 7 });
	AddEdges(G, 4, { 6, 7 });
	AddEdges(G, 5, { 1, 4, 6 });
	AddEdges(G, 6, { 1, 5 });
	AddEdges(G, 7, { 2, 4 });

	Print(G);
	cout << endl;

	AddNode(G1, 'A');
	AddNode(G1, 'B');
	AddNode(G1, 'C');
	AddNode(G1, 'D');
	AddNode(G1, 'E');
	AddNode(G1, 'F');

	AddEdges(G1, 'A', { 'B', 'E', 'F' });
	AddEdges(G1, 'B', { 'A', 'C', 'D', 'F' });
	AddEdges(G1, 'C', { 'E' });
	AddEdges(G1, 'D', { 'A', 'B', 'E' });
	AddEdges(G1, 'E', { 'C', 'E', 'D' });
	AddEdges(G1, 'F', { 'B', 'D', 'C', 'E' });

	Print(G1);
	cout << endl;

	GI2[0] = { 0, 1, 1, 0, 1, 0, 1 };
	GI2[1] = { 0, 1, 0, 1, 1, 0, 0 };
	GI2[2] = { 1, 1, 0, 0, 0, 1, 1 };
	GI2[3] = { 0, 0, 0, 0, 0, 1, 1 };
	GI2[4] = { 1, 0, 0, 1, 0, 1, 0 };
	GI2[5] = { 1, 0, 0, 0, 1, 0, 0 };
	GI2[6] = { 0, 1, 0, 1, 0, 0, 0 };

	Print(GI2);
	cout << endl;

	return 0;
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
