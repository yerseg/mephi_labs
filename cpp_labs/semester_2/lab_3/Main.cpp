#include <iostream>
#include <math.h>
#include <string>
#include "Template.h"
#include "Testing.h"
#define TRUE 1
#define FALSE 0

using namespace std;

int func1(int n) {
	return n * n;
}

int func2(int n) {
	if (n == 0 || n == 1)
		return 1;
	return n * func2(n - 1);
}

int func3(int n) {
	return n + 1;
}

int func4(int n) {
	return 2 * n;
}

int func5(int n) {
	if (n >= 0)
		return TRUE;
	if (n < 0)
		return FALSE;
	else
		return FALSE;
}

int func6(int n) {
	return n - n + 33;
}

void GoInterface(int type, int function) {
	if (type == 2) {
		cout << "СТРОКИ\n" << endl;
		if (function == 1) {
			cout << "MAP преобразует каждую строку дерева в введённую строку\n";
			Tree<string> *string_tree = new Tree<string>;
			string_tree->SetTree();
			cout << "Введите преобразующую строку: " << endl;
			string for_map; cin >> for_map;
			string_tree->map(for_map);
			string_tree->PrintByLevels();
			string_tree->RCLrootPrint();
			delete string_tree;
		}
		if (function == 2) {
			cout << "WHERE вернёт дерево, состоящее только из строк, количество символов в которых < 7\n\n";
			Tree<string> *string_tree = new Tree<string>;
			Tree<string> *res_string_tree = new Tree<string>;
			string_tree->SetTree();
			string_tree->where(res_string_tree);
			if (res_string_tree->GetRoot() == nullptr) cout << "ERROR 404: not found" << endl;
			else {
				res_string_tree->RCLrootPrint();
				res_string_tree->PrintByLevels();
			}
			delete string_tree;
			delete res_string_tree;
		}
		if (function == 3) {
			cout << "Первое дерево для слияния:" << endl;
			Tree<string> *first_string_tree = new Tree<string>;
			first_string_tree->SetTree();
			cout << "Второе дерево для слияния:" << endl;
			Tree<string> *second_string_tree = new Tree<string>;
			second_string_tree->SetTree();
			second_string_tree->MergeTrees(first_string_tree);
			cout << "Результат: " << endl;
			first_string_tree->RCLrootPrint();
			first_string_tree->PrintByLevels();
			delete first_string_tree;
			delete second_string_tree;
		}
		if (function == 4) {
			Tree<string> *string_tree = new Tree<string>;
			Tree<string> *res_string_tree = new Tree<string>;
			string_tree->SetTree();
			cout << "Введите строку: ";
			string str; cin >> str;
			string_tree->SubtreeExtraction(str, res_string_tree);
			cout << "Результат извлечения поддерева по заданному элементу: " << endl;
			if (res_string_tree->GetRoot() == nullptr) cout << "ERROR 404" << endl;
			else {
				res_string_tree->RCLrootPrint();
				res_string_tree->PrintByLevels();
			}
			delete string_tree;
		}

		if (function == 5) {
			Tree<string> *string_tree = new Tree<string>;
			cout << "Введите дерево " << endl;
			string_tree->SetTree();
			Tree<string> *string_subtree = new Tree<string>;
			cout << "Введите поддерево " << endl;
			string_subtree->SetTree();
			if (string_tree->IfTreeContain(string_subtree)) cout << "НАЙДЕНО" << endl;
			else cout << "ERROR 404: not found" << endl;
			delete string_tree;
			delete string_subtree;
		}

		if (function == 6) {
			Tree<string> *string_tree = new Tree<string>;
			string_tree->SetTree();
			cout << "Введите строку, для которой надо проверить, содержится ли она в дереве: ";
			string str; cin >> str;
			if (string_tree->IfElementContain(str)) cout << "СОДЕРЖИТСЯ" << endl;
			else cout << "ERROR 404: not found" << endl;
			delete string_tree;
		}
		else
			;
	}

	if (type == 1) {
		cout << "ФУНКЦИИ" << endl;
		void *ptr[] = { (void*)func1, (void*)func2, (void*)func3, (void*)func4, (void*)func5 };
			if (function == 1) {
				cout << "MAP преобразует каждую функцию дерева в введённую\n\n";
				Tree<void*> *func_tree = new Tree<void*>;
				func_tree->SetFunctionTree(ptr);
				cout << "Введите преобразующую функцию: " << endl;
				int func_number;

				do {
					cin >> func_number;
				} while (func_number != 1 && func_number != 2 && func_number != 3 && func_number != 4 && func_number != 5);
				void *for_map = ptr[func_number - 1];
				func_tree->map(for_map);
				func_tree->PrintByLevels();
				func_tree->PrintValueFunction();
				delete func_tree;
			}
			if (function == 2) {
				cout << "WHERE вернёт дерево, состоящее только из функций, f(5)<10\n";
				Tree<void*> *func_tree = new Tree<void*>;
				Tree<void*> *res_func_tree = new Tree<void*>;
				func_tree->SetFunctionTree(ptr);
				func_tree->where(res_func_tree);
				if (res_func_tree->GetRoot() == nullptr) cout << "ERROR 404: not found" << endl;
				else {
					res_func_tree->PrintByLevels();
					res_func_tree->PrintValueFunction();
				}
				delete func_tree;
				delete res_func_tree;
			}
			if (function == 3) {
				cout << "Первое дерево для слияния:" << endl;
				Tree<void*> *first_functional_tree = new Tree<void*>;
				first_functional_tree->SetFunctionTree(ptr);
				cout << "Второе дерево для слияния:" << endl;
				Tree<void*> *second_functional_tree = new Tree<void*>;
				second_functional_tree->SetFunctionTree(ptr);
				second_functional_tree->MergeTrees(first_functional_tree);
				cout << "Результат: " << endl;
				first_functional_tree->PrintByLevels();
				first_functional_tree->RCLrootPrint();
				first_functional_tree->PrintValueFunction();
				delete first_functional_tree;
				delete second_functional_tree;
			}
			if (function == 4) {
				Tree<void*> *functional_tree = new Tree<void*>;
				Tree<void*> *res_functional_tree = new Tree<void*>;
				functional_tree->SetFunctionTree(ptr);
				cout << "Выберите функцию для извлечения: " << endl;
				int func_number;
				do {
					cin >> func_number;
				} while (func_number != 1 && func_number != 2 && func_number != 3 && func_number != 4 && func_number != 5);
				void *func = ptr[func_number - 1];
				functional_tree->SubtreeExtraction(func, res_functional_tree);
				if (functional_tree->GetRoot() == nullptr) cout << "ERROR 404: not found" << endl;
				res_functional_tree->PrintByLevels();
				res_functional_tree->PrintValueFunction();
				delete functional_tree;
			}
			if (function == 5) {
				Tree<void*> *func_tree = new Tree<void*>;
				cout << "Введите дерево " << endl;
				func_tree->SetFunctionTree(ptr);
				Tree<void*> *func_subtree = new Tree<void*>;
				cout << "Введите поддерево " << endl;
				func_subtree->SetFunctionTree(ptr);
				if (func_tree->IfTreeContain(func_subtree)) cout << "СОДЕРЖИТСЯ" << endl;
				else cout << "ERROR 404: not found" << endl;
				delete func_tree;
				delete func_subtree;
			}
			if (function == 6) {
				Tree<void*> *func_tree = new Tree<void*>;
				func_tree->SetFunctionTree(ptr);
				cout << "Выберите функцию, для которой надо проверить, содержится ли она в дереве: ";
				int func_number;
				do {
					cin >> func_number;
				} while (func_number != 1 && func_number != 2 && func_number != 3 && func_number != 4 && func_number != 5);
				void *func = ptr[func_number - 1];
				if (func_tree->IfElementContain(func)) cout << "СОДЕРЖИТСЯ" << endl;
				else cout << "ERROR 404: not found" << endl;
				delete func_tree;
			}
			else
				;
	}
}

int main() {
	setlocale(LC_ALL, "Rus");
	int track2, stop, track1, stop1 = 0, con1 = FALSE, con2 = FALSE, flag1 = 0, flag = 0;
	cout << "Будем ли тестировать функции 0 - NO/1 - YES -->";
	do {
		scanf_s("%d", &stop);
		rewind(stdin);
		if (stop != 0 && stop != 1)
			printf("ОШИБКА: повторите ввод->");
	} while (stop != 0 && stop != 1);
	if (stop == TRUE)
		Testing();

	do {
		cout  << "Выберите с каким типом данных работаем: 1 - ФУНКЦИИ, 2 - СТРОКИ->\n";
		do {
			scanf_s("%d", &track1);
			rewind(stdin);
			if (track1 != 1 && track1 != 2)
				printf("ОШИБКА: повторите ввод->");
		} while (track1 != 1 && track1 != 2);
		cout << "\nВыберите функцию:\n 1 - map\n 2 - where\n 3 - слияние\n 4 - извлечение поддерева по заданному элементу\n 5 - поиск на вхождение поддерева\n 6 - поиск элемента на вхождение -->\n";
		do {
			scanf_s("%d", &track2);
			rewind(stdin);
			if (track2 != 1 && track2 != 2 && track2 != 3 && track2 != 4 && track2 != 5 && track2 != 6)
				printf("ОШИБКА: повторите ввод->");
		} while (track2 != 1 && track2 != 2 && track2 != 3 && track2 != 4 && track2 != 5 && track2 != 6);

		GoInterface(track1, track2);

		printf("\nРАБОТА ЗАВЕРШЕНА\n\nПРОДОЛЖИТЬ работу программы? (1 - да, 0 - нет)-->");
		do {
			scanf_s("%d", &stop);
			rewind(stdin);
			if (stop != TRUE && stop != FALSE)
				printf("ОШИБКА: повторите ввод->");
		} while (stop != TRUE && stop != FALSE);
	} while (stop == TRUE);

	system("PAUSE");
	return 0;
}
