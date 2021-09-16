#ifndef TEST_H
#define TEST_H

#include "Graph.h"
#include <assert.h>
#include <iostream>

using namespace std;

void Test_Find_Shortest_Path() {
	Graph<int> G;
	G.TestGraph();
	vector<vector<int> *> vect = G.FindShortestPath();
	assert(vect[0][0][0] == 3 && vect[0][0][1] == 6 && vect[0][0][2] == 4 && vect[0][0][3] == 14 && vect[0][1][1] == 0 && vect[0][1][2] == 2 && vect[0][1][3] == 8 && vect[0][2][2] == 0 && vect[0][2][3] == 10 && vect[0][3][3] == 5);

	cout << "Автоматическое тестирование поиска кратчайшего пути.....:  пройдено без ошибок" << endl;
}



#endif /* TEST_H */