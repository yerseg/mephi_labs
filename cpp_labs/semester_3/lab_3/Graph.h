#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

#define INF 9000000

using namespace std;

class BadIndex : public exception
{
	string str_;
public:
	BadIndex(string str)
	{
		str_ = str;
	}
	void what()
	{
		cout << str_ << endl;
	}
};

template <typename T>
class Graph {
private:
	vector<T> * matrix;
	int number;
public:
	Graph();
	Graph(int);
	~Graph();
	vector<vector<T> *> FindShortestPath();
	void ConstructPath(vector<int> *, int, int);
	void printMatrix();
	void TestGraph();
};

template <typename T>
Graph<T>::Graph() {
	number = 4;
	matrix = new vector<T>[number];
	for (int i = 0; i < number; i++)
		for (int j = 0; j < number; j++)
			matrix[i].push_back(0);
}

template <typename T>
Graph<T>::Graph(int n) {
	if (n == 0)
	{
		throw BadIndex("Error -- Matrix can not has 0 size");
	}

	number = n;
	matrix = new vector<T>[n];
	for (int i = 0; i < number; i++)
		for (int j = 0; j < number; j++)
			matrix[i].push_back(0);

	cout << "Введите матрицу смежности неориентированного графа G: " << endl;
	for (int i = 0; i < number; i++)
		for (int j = i; j < number; j++) {
			T weight;
			do {
				cout << "Вес ребра между " << i << " и " << j << " вершиной (в случае отсутствия ребра = 0): ";
				while (!(cin >> weight)) {
					cin.clear();
					cout << "ERROR: введите число--> " << endl;
					while (cin.get() != '\n') continue;
				}
				if (weight < 0)
					cout << "ОШИБКА: повторите ввод->";
			} while (weight < 0);
			matrix[i][j] = weight;
			cout << endl;
		}

	for (int i = 0; i < number; i++)
		for (int j = 0; j < number; j++)
			if (i != j) {
				matrix[j][i] = matrix[i][j];
			}
}

template <typename T>
Graph<T>::~Graph() {
	delete[] matrix;
}

template <typename T>
void Graph<T>::printMatrix() {
	cout << "Граф G задан следующей матрицой смежности: " << endl;
	for (int i = 0; i < number; i++) {
		cout << " ";
		for (int j = 0; j < number; j++) {
			cout << "    " << matrix[i][j] << "    ";
		}
		cout << endl;
	}
}

template <typename T>
vector<vector<T> *> Graph<T>::FindShortestPath() {

	vector<T> * ptr = new vector<T>[number], *path = new vector<T>[number];

	for (int i = 0; i < number; i++)
		for (int j = 0; j < number; j++)
			ptr[i].push_back(0);

	for (int i = 0; i < number; i++)
		for (int j = 0; j < number; j++) {
			path[i].push_back(i);
			if (i != j && matrix[i][j] == 0)
				path[i][j] = -INF;
		}

	for (int i = 0; i < number; i++)
		for (int j = 0; j < number; j++) {
			ptr[i][j] = matrix[i][j];
			if (i != j && matrix[i][j] == 0)
				ptr[i][j] = INF;
		}

	for (int i = 0; i < number; i++)
		for (int j = 0; j < number; j++)
			for (int k = 0; k < number; k++) {
				if (ptr[j][i] < INF && ptr[i][k] < INF) 
				{
					if (ptr[j][k] > ptr[j][i] + ptr[i][k]) {
						ptr[j][k] = ptr[j][i] + ptr[i][k];
						path[j][k] = path[i][k];
					}
				}
			}

	return { ptr, path };
}

template <typename T>
void Graph<T>::ConstructPath(vector<int> * path, int u, int v) {
	if (path[u][v] == -INF)
		throw BadIndex("Ошибка: между данными вершинами нет рёбер!\n");
	if (u == v)
		cout << u << endl;
	else {
		if (path[u][v] == -INF)
			cout << u << '-' << v << endl;
		else {
			ConstructPath(path, u, path[u][v]);
			cout << v << endl;
		}
	}
}

template <typename T>
void Graph<T>::TestGraph() {
	number = 4;
	matrix[0][0] = 3; matrix[0][1] = 9; matrix[0][2] = 4; matrix[0][3] = 0;
	matrix[1][1] = 0; matrix[1][2] = 2; matrix[1][3] = 8;
	matrix[2][2] = 0; matrix[2][3] = 0;
	matrix[3][3] = 5;

	for (int i = 0; i<number; i++)
		for (int j = 0; j < number; j++) 
			if (i != j) {
				matrix[j][i] = matrix[i][j];
			}
}


#endif /* GRAPH_H */

