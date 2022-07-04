/*	Jake Shoffner
	maze_solve.cpp
	04/02/22
*/
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

class Node {
  public:
	int id;
    vector <int> edges;
	bool visited;
};

class Graph {
  public:
	vector <Node *> nodes;
	vector <int> path;
    void DFS(int index);
	bool flag;
};

void Graph::DFS(int index) {
	Node *n;
	n = nodes[index];
	path.push_back(index);

	/* If the index is the last element in the maze, we know we have reached our goal, so we return */
	if ((unsigned int)index == nodes.size() - 1) {
		/* Flag to only print one valid path */
		if (flag) {
			for (unsigned int i = 0; i < path.size(); ++i) cout << "PATH " << path[i] << '\n';
		}
		flag = false;
		return;
	}

	/* If already visited, remove the node from the path and return */
	if (n->visited == true) {
		path.pop_back();
		return;
	}

	/* Setting NODE's visited field to true, and then going through its connections recursively, other than the NODE we just came from */
	n->visited = true;
	for (unsigned int i = 0; i < n->edges.size(); i++) {
		if (n->edges[i] != index) DFS(n->edges[i]);
	}

	/* Removing the node from the path */
	path.pop_back();
	
	return;
}

int main() {
	Graph g;
	Node *node;
	vector <int>::iterator vit;
	string temp;
	unsigned int rows, cols;
	int ind1, ind2;
	g.flag = true;

	/* Reading in the one time ROWS and COLS information, then outputting it */
	cin >> temp >> rows >> temp >> cols;
	cout << "ROWS " << rows << " COLS " << cols << '\n';

	/* Creating NODES and storing it into the graph for every cell of the maze, setting the visited field to initally be false */
	for (unsigned int i = 0; i < rows; ++i) {
		for (unsigned int j = 0; j < cols; ++j) {
			node = new Node;
			node->id = i * cols + j;
			node->visited = false;
			g.nodes.push_back(node);
		}
	}
	
	/* Connecting every cell on the board */
	for (unsigned int i = 0; i < rows; ++i) {
		for (unsigned int j = 0; j < cols; ++j) {
			if (j != cols - 1) {
				g.nodes[i * cols + j]->edges.push_back(i * cols + j + 1);
				g.nodes[i * cols + j + 1]->edges.push_back(i * cols + j);
			}
			if (i != rows - 1) {
				g.nodes[i * cols + j]->edges.push_back((i + 1) * cols + j);
				g.nodes[(i + 1) * cols + j]->edges.push_back(i * cols + j);
			}
		}
	}
	
	/* Reading in WALLS and removing connections between NODES accordingly */	
	while (cin >> temp) {
		/* After reading in, we need to output */
		cin >> ind1 >> ind2;
		cout << "WALL " << ind1 << ' ' << ind2 << '\n';

		/* If there exists an edge for specified NODE, we can find it and erase it. As well as removing the edge from the other NODE as well. */
		vit = find(g.nodes[ind1]->edges.begin(), g.nodes[ind1]->edges.end(), ind2);
		if (vit != g.nodes[ind1]->edges.end()) g.nodes[ind1]->edges.erase(vit);

		vit = find(g.nodes[ind2]->edges.begin(), g.nodes[ind2]->edges.end(), ind1);
		if (vit != g.nodes[ind2]->edges.end()) g.nodes[ind2]->edges.erase(vit);
	}
	
	/* Recursive call starting at cell 0 */
	g.DFS(0);
	
	/* Freeing up the allocated memory of NODEs in the graph */
	for (unsigned int i = 0; i < g.nodes.size(); ++i) delete g.nodes[i];

	return 0;
}
