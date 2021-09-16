#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "Graph.h"
#include "Test.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");

	srand(static_cast<unsigned int>(time(0)));

	Test_Find_Shortest_Path();

	while (1) {
		int section;

		do {
			cout << "Выберите алгоритм:" << endl;
			cout << "1 - Поиск кратчайшего пути\n2 - Выход\nОтвет:   ";
			while (!(cin >> section)) {
				cin.clear();
				cout << "ERROR: введите число--> " << endl;
				while (cin.get() != '\n') continue;
			}
			if (section != 1 && section != 2 && section != 3)
				cout << "ОШИБКА: повторите ввод->";
		} while (section != 1 && section != 2 && section != 3);

		if (section == 1) {
			int number, u, v;
			do {
				cout << "Введите количество вершин неориентированного графа: " << endl;
				while (!(cin >> number)) {
					cin.clear();
					cout << "ERROR: введите число--> " << endl;
					while (cin.get() != '\n') continue;
				}
				if (number < 1)
					cout << "ОШИБКА: повторите ввод->";
			} while (number < 1);

			Graph<int> G = Graph<int>(number);

			vector<vector<int> *> vect = G.FindShortestPath();

			G.printMatrix();

			cout << "Кратчайшие расстояния между всеми вершинами графа G представлены в матрице:\n " << endl;

			for (int i = 0; i < number; i++) {
				cout << " ";
				for (int j = 0; j < number; j++) {
					cout << "    " << vect[0][i][j] << "    ";
				}
				cout << endl;
			}

			bool f = 1;

			do {
				cout << "Введите две вершины графа между которыми необходимо восстановить кратчайший путь: " << endl;
				do {
					cout << "Введите 1 вершину: " << endl;
					while (!(cin >> u)) {
						cin.clear();
						cout << "ERROR: введите число--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (u < 0)
						cout << "ОШИБКА: повторите ввод->";
				} while (u < 0);

				do {
					cout << "Введите 2 вершину: " << endl;
					while (!(cin >> v)) {
						cin.clear();
						cout << "ERROR: введите число--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (v < 0)
						cout << "ОШИБКА: повторите ввод->";
				} while (v < 0);

				cout << "Кратчайший путь: \n";
				try {
					G.ConstructPath(vect[1], u, v);
				}
				catch (BadIndex ex1) {
					ex1.what();
				}

				do {
					cout << "Продолжить?\n 1 - ДА\n 0 - НЕТ\n Ответ: ";
					while (!(cin >> f)) {
						cin.clear();
						cout << "ERROR: введите число--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (f != 0 && f != 1)
						cout << "ОШИБКА: повторите ввод->";
				} while (f != 0 && f != 1);

			} while (f == 1);
		}

		else if (section == 2)
			return -1;

		system("pause");
	
	}
}

