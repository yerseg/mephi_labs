#include <iostream>
#include <assert.h>
#include "Sequence.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include "Sorters.h"
#include "Binary_Search.h"
#include "BTree.h"
#include "Exceptions.h"
#include "Student.h"
#include "IDictionary.h"
#include "Test.h"
#include "Help_Func.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");

	Test_Binary_Search(); Test_Dictionary(); Test_BTree();

	srand(static_cast<unsigned int>(time(0)));

	while (1) {
		int section;

		do {
			cout << "Выберите раздел:" << endl;
			cout << "1 - Бинарный поиск\n2 - Хеш-таблица\n3 - B/В+-дерево\n4 - Закончить работу\nОтвет:   ";
			while (!(cin >> section)) {
				cin.clear();
				cout << "ERROR: введите число--> " << endl;
				while (cin.get() != '\n') continue;
			}
			if (section < 1 or section > 4)
				cout << "ОШИБКА: повторите ввод->";
		} while (section != 1 && section != 2 && section != 3 && section != 4);

		if (section == 1) {
			int vvod;

			do {
				cout << "Выберете режим работы:\n1 - ручной ввод\n2 - автоматический ввод\nОтвет:    ";
				while (!(cin >> vvod)) {
					cin.clear();
					cout << "ERROR: введите число--> " << endl;
					while (cin.get() != '\n') continue;
				}
				if (vvod != 1 && vvod != 2)
					cout << "ОШИБКА: повторите ввод->";
			} while (vvod != 1 && vvod != 2);
			
			if (vvod == 1) {
				ArraySequence<Student> ArraySeq;
				int amount_of_el;
				do {
					cout << "Введите количество студентов в последовательности: ";
					while (!(cin >> amount_of_el)) {
						cin.clear();
						cout << "ERROR: введите число--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (amount_of_el < 1)
						cout << "ОШИБКА: повторите ввод->";
				} while (amount_of_el < 1);

				cout << "Вводите фамилии и даты рождения" << endl;
				for (int i = 0; i < amount_of_el; i++) {
					cout << "Cтудент " << i << ":" << endl;
					cout << "Имя:  ";
					string name; cin >> name;
					cout << "Дата рождения (через пробел):\n";
					int d; int m; int g;
					do {
						cout << "Введите день: ";
						while (!(cin >> d)) {
							cin.clear();
							cout << "ERROR: введите число--> " << endl;
							while (cin.get() != '\n') continue;
						}
						if (d > 31 || d < 1)
							cout << "ОШИБКА: повторите ввод->";
					} while (d > 31 || d < 1);
					do {
						cout << "Введите месяц: ";
						while (!(cin >> m)) {
							cin.clear();
							cout << "ERROR: введите число--> " << endl;
							while (cin.get() != '\n') continue;
						}
						if (m > 12 || m < 1)
							cout << "ОШИБКА: повторите ввод->";
					} while (m > 12 || m < 1);
					do {
						cout << "Введите год: ";
						while (!(cin >> g)) {
							cin.clear();
							cout << "ERROR: введите число--> " << endl;
							while (cin.get() != '\n') continue;
						}
						if (g > 2018 || g < 1900)
							cout << "ОШИБКА: повторите ввод->";
					} while (g > 2018 || g < 1900);
					
					Student stud = Student(name, d, m, g);
					ArraySeq.Append(stud);
				}

				Sorter<Student> sort;
				ArraySequence<Student> arr1;
				arr1 = ArraySeq;
				sort.QuickSort(&arr1);
				ArraySeq.printAll();
				arr1.printAll();

				cout << "Введите элемент, который хотите найти:\n";
				cout << "Cтудент: " << endl;
				cout << "Имя:  ";
				string name; cin >> name;
				cout << "Дата рождения:\n";
				int d; int m; int g;
				do {
					cout << "Введите день: ";
					while (!(cin >> d)) {
						cin.clear();
						cout << "ERROR: введите число--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (d > 31 || d < 1)
						cout << "ОШИБКА: повторите ввод->";
				} while (d > 31 || d < 1);
				do {
					cout << "Введите месяц: ";
					while (!(cin >> m)) {
						cin.clear();
						cout << "ERROR: введите число--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (m > 12 || m < 1)
						cout << "ОШИБКА: повторите ввод->";
				} while (m > 12 || m < 1);
				do {
					cout << "Введите год: ";
					while (!(cin >> g)) {
						cin.clear();
						cout << "ERROR: введите число--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (g > 2018 || g < 1900)
						cout << "ОШИБКА: повторите ввод->";
				} while (g > 2018 || g < 1900);

				int fib_n;
				do {
					cout << "Для бинарного поиска с делением числом Фибоначчи введите номер числа Фибоначчи: ";
					while (!(cin >> fib_n)) {
						cin.clear();
						cout << "ERROR: введите число--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (fib_n < 2 || fib_n > 15)
						cout << "ОШИБКА: повторите ввод->";
				} while (fib_n < 2 || fib_n > 15);

				int prop1; int prop2;
				cout << "Для бинарного поиска с делением отрезком введите пропорции в формате X:Y\n";
				do {
					cout << "Введите X: ";
					while (!(cin >> prop1)) {
						cin.clear();
						cout << "ERROR: введите число--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (prop1 < 1)
						cout << "ОШИБКА: повторите ввод->";
				} while (prop1 < 1);
				do {
					cout << "Введите Y: ";
					while (!(cin >> prop2)) {
						cin.clear();
						cout << "ERROR: введите число--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (prop2 < 1)
						cout << "ОШИБКА: повторите ввод->";
				} while (prop2 < 1);
				
				int atr;
				do {
					cout << "Выберите атрибут поиска:\n1 - имя, 2 - дата рождения, 3 - оба атрибута ";
					while (!(cin >> atr)) {
						cin.clear();
						cout << "ERROR: введите число--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (atr != 1 && atr != 2 && atr != 3 && atr != 4)
						cout << "ОШИБКА: повторите ввод->";
				} while (atr != 1 && atr != 2 && atr != 3 && atr != 4);
				
				Student stud_ = Student(name, d, m, g);

				if (atr == 1) {
					for (int i = 0; i < amount_of_el; i++) {
						ArraySeq.GetPointer(i)->set_flag(1);
					}
					stud_.set_flag(1);
				}
				else if (atr == 2) {
					for (int i = 0; i < amount_of_el; i++) {
						ArraySeq.GetPointer(i)->set_flag(2);
					}
					stud_.set_flag(2);
				}
				else if (atr == 3) {
					for (int i = 0; i < amount_of_el; i++) {
						ArraySeq.GetPointer(i)->set_flag(0);
					}
					stud_.set_flag(0);
				}
				else
					;

				try {
					int index = Search_Binary_Base(&ArraySeq, stud_);
					cout << "Индекс искомого студента в отсортированной последовательности: " << index << endl;
					Student res_stud = ArraySeq.Get(index);
					cout << "Искомый студент: " << res_stud << endl;
				}
				catch (ElementNotFoundException<Student> ex1) {
					ex1.what();
				}
				catch (EmptySequenceException ex2) {
					ex2.what();
				}
				catch (NoMeaningFibException ex3) {
					ex3.what();
				}
				try {
					cout << "Время для базового бинарного поиска: " << Time_For_Search_Binary_Base(&ArraySeq, stud_)[1] << " нс" << endl;
				}
				catch (ElementNotFoundException<Student> ex1) {
					ex1.what();
				}
				catch (EmptySequenceException ex2) {
					ex2.what();
				}
				catch (NoMeaningFibException ex3) {
					ex3.what();
				}
				try {
					cout << "Время для бинарного поиска с делением золотым сечением: " << Time_For_Search_Binary_Golden_Ratio(&ArraySeq, stud_)[1] << " нс" << endl;
				}
				catch (ElementNotFoundException<Student> ex1) {
					ex1.what();
				}
				catch (EmptySequenceException ex2) {
					ex2.what();
				}
				catch (NoMeaningFibException ex3) {
					ex3.what();
				}
				try {
					cout << "Время для бинарного поиска с делением числом Фибоначчи: " << Time_For_Search_Binary_Fibonacci(&ArraySeq, stud_, fib_n)[1] << " нс" << endl;
				}
				catch (ElementNotFoundException<Student> ex1) {
					ex1.what();
				}
				catch (EmptySequenceException ex2) {
					ex2.what();
				}
				catch (NoMeaningFibException ex3) {
					ex3.what();
				}
				try {
					cout << "Время для бинарного поиска с делением отрезком: " << Time_For_Search_Binary_Own_Pair(&ArraySeq, stud_, prop1, prop2)[1] << " нс" << endl;
				}
				catch (ElementNotFoundException<Student> ex1) {
					ex1.what();
				}
				catch (EmptySequenceException ex2) {
					ex2.what();
				}
				catch (NoMeaningFibException ex3) {
					ex3.what();
				}
			}
			else if (vvod == 2) {
				ArraySequence<Student> ArraySeq;
				int amount_of_el;
				do {
					cout << "Введите количество студентов в последовательности: ";
					while (!(cin >> amount_of_el)) {
						cin.clear();
						cout << "ERROR: введите число--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (amount_of_el < 1)
						cout << "ОШИБКА: повторите ввод->";
				} while (amount_of_el < 1);

				Rand_Stud_Seq_Gen(&ArraySeq, amount_of_el);

				ArraySeq.printAll();

				cout << "Введите элемент, который хотите найти:\n";
				cout << "Cтудент: " << endl;
				cout << "Имя: ";
				string name; cin >> name;
				cout << "Дата рождения (через пробел):\n";
				int d; int m; int g;
				do {
					cout << "Введите день: ";
					while (!(cin >> d)) {
						cin.clear();
						cout << "ERROR: введите число--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (d > 31 || d < 1)
						cout << "ОШИБКА: повторите ввод->";
				} while (d > 31 || d < 1);
				do {
					cout << "Введите месяц: ";
					while (!(cin >> m)) {
						cin.clear();
						cout << "ERROR: введите число--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (m > 12 || m < 1)
						cout << "ОШИБКА: повторите ввод->";
				} while (m > 12 || m < 1);
				do {
					cout << "Введите год: ";
					while (!(cin >> g)) {
						cin.clear();
						cout << "ERROR: введите число--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (g > 2018 || g < 1900)
						cout << "ОШИБКА: повторите ввод->";
				} while (g > 2018 || g < 1900);

				int fib_n;
				do {
					cout << "Для бинарного поиска с делением числом Фибоначчи введите номер числа Фибоначчи: ";
					while (!(cin >> fib_n)) {
						cin.clear();
						cout << "ERROR: введите число--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (fib_n < 2 || fib_n > 15)
						cout << "ОШИБКА: повторите ввод->";
				} while (fib_n < 2 || fib_n > 15);

				int prop1; int prop2;
				cout << "Для бинарного поиска с делением отрезком введите пропорции в формате X:Y\n";
				do {
					cout << "Введите X: ";
					while (!(cin >> prop1)) {
						cin.clear();
						cout << "ERROR: введите число--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (prop1 < 1)
						cout << "ОШИБКА: повторите ввод->";
				} while (prop1 < 1);
				do {
					cout << "Введите Y: ";
					while (!(cin >> prop2)) {
						cin.clear();
						cout << "ERROR: введите число--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (prop2 < 1)
						cout << "ОШИБКА: повторите ввод->";
				} while (prop2 < 1);

				Student stud_ = Student(name, d, m, g);

				int atr;
				do {
					cout << "Выберите атрибут поиска:\n1 - имя, 2 - дата рождения, 3 - оба атрибута ";
					while (!(cin >> atr)) {
						cin.clear();
						cout << "ERROR: введите число--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (atr != 1 && atr != 2 && atr != 3 && atr != 4)
						cout << "ОШИБКА: повторите ввод->";
				} while (atr != 1 && atr != 2 && atr != 3 && atr != 4);

				if (atr == 1) {
					for (int i = 0; i < amount_of_el; i++) {
						ArraySeq.GetPointer(i)->set_flag(1);
					}
					stud_.set_flag(1);
				}
				else if (atr == 2) {
					for (int i = 0; i < amount_of_el; i++) {
						ArraySeq.GetPointer(i)->set_flag(2);
					}
					stud_.set_flag(2);
				}
				else if (atr == 3) {
					for (int i = 0; i < amount_of_el; i++) {
						ArraySeq.GetPointer(i)->set_flag(0);
					}
					stud_.set_flag(0);
				}
				else
					;

				try {
					int index = Search_Binary_Base(&ArraySeq, stud_);
					cout << "Индекс искомого студента в отсортированной последовательности: " << index << endl;
					Student res_stud = ArraySeq.Get(index);
					cout << "Искомый студент: " << res_stud << endl;
				}
				catch (ElementNotFoundException<Student> ex1) {
					ex1.what();
				}
				catch (EmptySequenceException ex2) {
					ex2.what();
				}
				catch (NoMeaningFibException ex3) {
					ex3.what();
				}
				try {
					cout << "Время для базового бинарного поиска: " << Time_For_Search_Binary_Base(&ArraySeq, stud_)[1] << " нс" << endl;
				}
				catch (ElementNotFoundException<Student> ex1) {
					ex1.what();
				}
				catch (EmptySequenceException ex2) {
					ex2.what();
				}
				catch (NoMeaningFibException ex3) {
					ex3.what();
				}
				try {
					cout << "Время для бинарного поиска с делением золотым сечением: " << Time_For_Search_Binary_Golden_Ratio(&ArraySeq, stud_)[1] << " нс" << endl;
				}
				catch (ElementNotFoundException<Student> ex1) {
					ex1.what();
				}
				catch (EmptySequenceException ex2) {
					ex2.what();
				}
				catch (NoMeaningFibException ex3) {
					ex3.what();
				}
				try {
					cout << "Время для бинарного поиска с делением числом Фибоначчи: " << Time_For_Search_Binary_Fibonacci(&ArraySeq, stud_, fib_n)[1] << " нс" << endl;
				}
				catch (ElementNotFoundException<Student> ex1) {
					ex1.what();
				}
				catch (EmptySequenceException ex2) {
					ex2.what();
				}
				catch (NoMeaningFibException ex3) {
					ex3.what();
				}
				try {
					cout << "Время для бинарного поиска с делением отрезком: " << Time_For_Search_Binary_Own_Pair(&ArraySeq, stud_, prop1, prop2)[1] << " нс" << endl;
				}
				catch (ElementNotFoundException<Student> ex1) {
					ex1.what();
				}
				catch (EmptySequenceException ex2) {
					ex2.what();
				}
				catch (NoMeaningFibException ex3) {
					ex3.what();
				}
			}
		}
		else if (section == 2) {
			IDictionary<string, Student> dict;
			int f = 1;
			while(f == 1) {
				int act;
				do {
					cout << "Выберите действие:  \n1 - Добавить элемент\n2 - Удалить элемент\n3 - Получение элемента по ключу\n4 - Проверка, что в таблице уже есть элемент с заданным ключом\n5 - Выйти\nОтвет: ";
					while (!(cin >> act)) {
						cin.clear();
						cout << "ERROR: введите число--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (act != 1 && act != 2 && act != 3 && act != 4 && act != 5)
						cout << "ОШИБКА: Введите корректное значение(от 1 до 5):  ";
				} while (act != 1 && act != 2 && act != 3 && act != 4 && act != 5);
				
				if (act == 1) {
					
					int act1;
					do {
						cout << "Выберите действие:  \n1 - Заполнить случайными элементами\n2 - Ввести вручную\nОтвет:  ";
						while (!(cin >> act1)) {
							cin.clear();
							cout << "ERROR: введите число--> " << endl;
							while (cin.get() != '\n') continue;
						}
						if (act1 != 1 && act1 != 2 && act1 != 3 && act1 != 4 && act1 != 5)
							cout << "ОШИБКА: Введите корректное значение:  ";
					} while (act1 != 1 && act1 != 2 && act1 != 3 && act1 != 4 && act1 != 5);

					if (act1 == 1) {
						int amount_of_elem;
						do {
							cout << "Введите количество студентов в последовательности: ";
							while (!(cin >> amount_of_elem)) {
								cin.clear();
								cout << "ERROR: введите число--> " << endl;
								while (cin.get() != '\n') continue;
							}
							if (amount_of_elem < 1)
								cout << "ОШИБКА: повторите ввод->";
						} while (amount_of_elem < 1);

						ArraySequence<Student> Stud_Arr;
						Rand_Stud_Seq_Gen(&Stud_Arr, amount_of_elem);
						for (int i = 0; i < amount_of_elem; i++)
							dict.Add(Stud_Arr.Get(i).GetName(), Stud_Arr.Get(i));
						cout << "Получившаяся Хеш-таблица:" << endl;
						dict.printAll();
						cout << "Capacity: " << dict.GetCapacity() << endl;
						cout << "Count: " << dict.GetCount() << endl;
					}

					else if (act1 == 2) {
						int amount_of_elem;
						do {
							cout << "Введите количество студентов в последовательности: ";
							while (!(cin >> amount_of_elem)) {
								cin.clear();
								cout << "ERROR: введите число--> " << endl;
								while (cin.get() != '\n') continue;
							}
							if (amount_of_elem < 1)
								cout << "ОШИБКА: повторите ввод->";
						} while (amount_of_elem < 1);
						while (amount_of_elem < 1) {
							cout << "Введите корректное значение:  ";
							cin >> amount_of_elem;
						}
						string name;
						int d, m, g;
						cout << "Вводите фамилии и даты рождения" << endl;
						for (int i = 0; i < amount_of_elem; i++) {
							cout << "Cтудент " << i << ":" << endl;
							cout << "Имя:  ";
							string name; cin >> name;
							cout << "Дата рождения (через пробел):\n";
							int d; int m; int g;
							do {
								cout << "Введите день: ";
								while (!(cin >> d)) {
									cin.clear();
									cout << "ERROR: введите число--> " << endl;
									while (cin.get() != '\n') continue;
								}
								if (d > 31 || d < 1)
									cout << "ОШИБКА: повторите ввод->";
							} while (d > 31 || d < 1);
							do {
								cout << "Введите месяц: ";
								while (!(cin >> m)) {
									cin.clear();
									cout << "ERROR: введите число--> " << endl;
									while (cin.get() != '\n') continue;
								}
								if (m > 12 || m < 1)
									cout << "ОШИБКА: повторите ввод->";
							} while (m > 12 || m < 1);
							do {
								cout << "Введите год: ";
								while (!(cin >> g)) {
									cin.clear();
									cout << "ERROR: введите число--> " << endl;
									while (cin.get() != '\n') continue;
								}
								if (g > 2018 || g < 1900)
									cout << "ОШИБКА: повторите ввод->";
							} while (g > 2018 || g < 1900);

							Student stud = Student(name, d, m, g);
							dict.Add(stud.GetName(), stud);
						}
						dict.printAll();
						cout << "Capacity: " << dict.GetCapacity() << endl;
						cout << "Count: " << dict.GetCount() << endl;
					}
				}

				else if (act == 2) {
					if (dict.GetCount() == 0) {
						cout << "Сначала добавьте элемент в последовательность\n";
						act = 1;
					}
					else {
						cout << "Введите ключ элемента, который хотите удалить:  ";
						string k;
						cin >> k;

						try {
							dict.Remove(k);
						}
						catch (KeyIsNotExistException<string> ex1) {
							ex1.what();
						}
						cout << "Получившаяся Хеш-таблица:" << endl;
						dict.printAll();
						cout << "Capacity: " << dict.GetCapacity() << endl;
						cout << "Count: " << dict.GetCount() << endl;
					}
					
				}
				else if (act == 3) {
					if (dict.GetCount() == 0) {
						cout << "Сначала добавьте элемент в последовательность\n";
						act = 1;
					}
					else {
						cout << "Введите ключ для получения элемента ";
						string key;
						cin >> key;

						Student stud;
						try {
							stud = dict.Get(key);
						}
						catch (ElementNotFoundException<Student> ex1) {
							ex1.what();
						}
						cout << endl << stud;
					}
				}
				else if (act == 4) {
					if (dict.GetCount() == 0) {
						cout << "Сначала добавьте элемент в последовательность\n";
						act = 1;
					}
					else {
						cout << "Введите ключ для поиска элемента ";
						string key;
						cin >> key;

						bool flag = false;
						try {
							flag = dict.ContainsKey(key);
						}
						catch (ElementNotFoundException<Student> ex1) {
							ex1.what();
						}
	
						if (flag)
							cout << endl << "True";
						else if (!flag)
							cout << endl << "False";
					}
				}
				else if (act == 5) {
					f = -1;
				}
			}
		}

		else if (section == 3) {
			ArraySequence<Student> Stud_Arr;
			int t, f = 1;

			do {
				cout << "Введите t - минимальную степень B-дерева: ";
				while (!(cin >> t)) {
					cin.clear();
					cout << "ERROR: введите число--> " << endl;
					while (cin.get() != '\n') continue;
				}
				if (t > 10 || t < 1)
					cout << "ОШИБКА: повторите ввод->";
			} while (t > 10 || t < 1);
			
			BTreeBuilder<Student> builder = BTreeBuilder<Student>(t);

			int atr;
			do {
				cout << "Выберите атрибут поиска:\n1 - имя, 2 - дата рождения, 3 - оба атрибута ";
				while (!(cin >> atr)) {
					cin.clear();
					cout << "ERROR: введите число--> " << endl;
					while (cin.get() != '\n') continue;
				}
				if (atr != 1 && atr != 2 && atr != 3 && atr != 4)
					cout << "ОШИБКА: повторите ввод->";
			} while (atr != 1 && atr != 2 && atr != 3 && atr != 4);

			cout << "Добавьте элементы для первичного построения B-дерева" << endl;

			int vvod;
			do {
				cout << "Выберете режим работы:\n1 - ручной ввод\n2 - автоматический ввод\nОтвет:    ";
				while (!(cin >> vvod)) {
					cin.clear();
					cout << "ERROR: введите число--> " << endl;
					while (cin.get() != '\n') continue;
				}
				if (vvod != 1 && vvod != 2)
					cout << "ОШИБКА: Введите корректное значение(1 или 2): ";
			} while (vvod != 1 && vvod != 2);

			if (vvod == 1) {

				int amount_of_el;
				do {
					cout << "Введите количество студентов в последовательности: ";
					while (!(cin >> amount_of_el)) {
						cin.clear();
						cout << "ERROR: введите число--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (amount_of_el < 1)
						cout << "ОШИБКА: повторите ввод->";
				} while (amount_of_el < 1);

				cout << "Вводите фамилии и даты рождения" << endl;
				for (int i = 0; i < amount_of_el; i++) {
					cout << "Cтудент " << i << ":" << endl;
					cout << "Имя:  ";
					string name; cin >> name;
					cout << "Дата рождения (через пробел):\n";
					int d; int m; int g;
					do {
						cout << "Введите день: ";
						while (!(cin >> d)) {
							cin.clear();
							cout << "ERROR: введите число--> " << endl;
							while (cin.get() != '\n') continue;
						}
						if (d > 31 || d < 1)
							cout << "ОШИБКА: повторите ввод->";
					} while (d > 31 || d < 1);
					do {
						cout << "Введите месяц: ";
						while (!(cin >> m)) {
							cin.clear();
							cout << "ERROR: введите число--> " << endl;
							while (cin.get() != '\n') continue;
						}
						if (m > 12 || m < 1)
							cout << "ОШИБКА: повторите ввод->";
					} while (m > 12 || m < 1);
					do {
						cout << "Введите год: ";
						while (!(cin >> g)) {
							cin.clear();
							cout << "ERROR: введите число--> " << endl;
							while (cin.get() != '\n') continue;
						}
						if (g > 2018 || g < 1900)
							cout << "ОШИБКА: повторите ввод->";
					} while (g > 2018 || g < 1900);

					Student stud = Student(name, d, m, g);
					Stud_Arr.Append(stud);
				}
			}

			else if (vvod == 2) {
				int amount_of_el;
				do {
					cout << "Введите количество студентов в последовательности: ";
					while (!(cin >> amount_of_el)) {
						cin.clear();
						cout << "ERROR: введите число--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (amount_of_el < 1)
						cout << "ОШИБКА: повторите ввод->";
				} while (amount_of_el < 1);
				Rand_Stud_Seq_Gen(&Stud_Arr, amount_of_el);
			}

			for (int k = 0; k < Stud_Arr.GetLength(); k++) {
				if (atr == 1)
					Stud_Arr.Get(k).set_flag(1);
				else if (atr == 2)
					Stud_Arr.Get(k).set_flag(2);
				else if (atr == 3)
					Stud_Arr.Get(k).set_flag(0);
			}
			
			BTree<Student> btree = builder.build(&Stud_Arr, Stud_Arr.GetLength());

			cout << "Получившееся B-дерево\n";
			btree.traverse();

			while (f == 1) {
				ArraySequence<Student> Stud_Arr1;

				int act;
				do {
					cout << "Выберите действие:  \n1 - Добавить элемент\n2 - Поиск элемента\n3 - Выйти\nОтвет: ";
					while (!(cin >> act)) {
						cin.clear();
						cout << "ERROR: введите число--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (act != 1 && act != 2 && act != 3)
						cout << "ОШИБКА: Введите корректное значение(от 1 до 5):  ";
				} while (act != 1 && act != 2 && act != 3);

				if (act == 1) {
					int vvod;
					do {
						cout << "Выберете режим работы:\n1 - ручной ввод\n2 - автоматический ввод\nОтвет:    ";
						while (!(cin >> vvod)) {
							cin.clear();
							cout << "ERROR: введите число--> " << endl;
							while (cin.get() != '\n') continue;
						}
						if (vvod != 1 && vvod != 2)
							cout << "ОШИБКА: повторите ввод->";
					} while (vvod != 1 && vvod != 2);

					if (vvod == 1) {

						int amount_of_el;
						do {
							cout << "Введите количество студентов в последовательности: ";
							while (!(cin >> amount_of_el)) {
								cin.clear();
								cout << "ERROR: введите число--> " << endl;
								while (cin.get() != '\n') continue;
							}
							if (amount_of_el < 1)
								cout << "ОШИБКА: повторите ввод->";
						} while (amount_of_el < 1);

						cout << "Вводите фамилии и даты рождения" << endl;
						for (int i = 0; i < amount_of_el; i++) {
							cout << "Cтудент " << i << ":" << endl;
							cout << "Имя:  ";
							string name; cin >> name;
							cout << "Дата рождения (через пробел):\n";
							int d; int m; int g;
							do {
								cout << "Введите день: ";
								while (!(cin >> d)) {
									cin.clear();
									cout << "ERROR: введите число--> " << endl;
									while (cin.get() != '\n') continue;
								}
								if (d > 31 || d < 1)
									cout << "ОШИБКА: повторите ввод->";
							} while (d > 31 || d < 1);
							do {
								cout << "Введите месяц: ";
								while (!(cin >> m)) {
									cin.clear();
									cout << "ERROR: введите число--> " << endl;
									while (cin.get() != '\n') continue;
								}
								if (m > 12 || m < 1)
									cout << "ОШИБКА: повторите ввод->";
							} while (m > 12 || m < 1);
							do {
								cout << "Введите год: ";
								while (!(cin >> g)) {
									cin.clear();
									cout << "ERROR: введите число--> " << endl;
									while (cin.get() != '\n') continue;
								}
								if (g > 2018 || g < 1900)
									cout << "ОШИБКА: повторите ввод->";
							} while (g > 2018 || g < 1900);

							Student stud = Student(name, d, m, g);
							Stud_Arr1.Append(stud);
						}
					}

					else if (vvod == 2) {
						int amount_of_el;
						do {
							cout << "Введите количество студентов в последовательности: ";
							while (!(cin >> amount_of_el)) {
								cin.clear();
								cout << "ERROR: введите число--> " << endl;
								while (cin.get() != '\n') continue;
							}
							if (amount_of_el < 1)
								cout << "ОШИБКА: повторите ввод->";
						} while (amount_of_el < 1);
						Rand_Stud_Seq_Gen(&Stud_Arr1, amount_of_el);
					}

					for (int k = 0; k < Stud_Arr1.GetLength(); k++) {
						if (atr == 1)
							Stud_Arr1.Get(k).set_flag(1);
						else if (atr == 2)
							Stud_Arr1.Get(k).set_flag(2);
						else if (atr == 3)
							Stud_Arr1.Get(k).set_flag(0);
					}

					for (int j = 0; j < Stud_Arr1.GetLength(); j++)
						btree.insert(Stud_Arr1.Get(j));

					cout << "Получившееся B-дерево\n";
					btree.traverse();
				}
				else if (act == 2) {
					cout << "\nВведите студента для поиска в B-дереве " << endl;
					cout << "Cтудент: " << endl;
					cout << "Имя:  ";
					string name; cin >> name;
					cout << "Дата рождения (через пробел):\n";
					int d; int m; int g;
					do {
						cout << "Введите день: ";
						while (!(cin >> d)) {
							cin.clear();
							cout << "ERROR: введите число--> " << endl;
							while (cin.get() != '\n') continue;
						}
						if (d > 31 || d < 1)
							cout << "ОШИБКА: повторите ввод->";
					} while (d > 31 || d < 1);
					do {
						cout << "Введите месяц: ";
						while (!(cin >> m)) {
							cin.clear();
							cout << "ERROR: введите число--> " << endl;
							while (cin.get() != '\n') continue;
						}
						if (m > 12 || m < 1)
							cout << "ОШИБКА: повторите ввод->";
					} while (m > 12 || m < 1);
					do {
						cout << "Введите год: ";
						while (!(cin >> g)) {
							cin.clear();
							cout << "ERROR: введите число--> " << endl;
							while (cin.get() != '\n') continue;
						}
						if (g > 2018 || g < 1900)
							cout << "ОШИБКА: повторите ввод->";
					} while (g > 2018 || g < 1900);

					Student stud = Student(name, d, m, g);
					if (atr == 1)
						stud.set_flag(1);
					else if (atr == 2)
						stud.set_flag(2);
					else if (atr == 3)
						stud.set_flag(0);

					auto begin = chrono::high_resolution_clock::now();
					try {
						cout << "Результат: " << btree.search(stud).index;
					}
					catch (ElementNotFoundException<Student> ex) {
						ex.what();
					}
					auto end = chrono::high_resolution_clock::now();
					auto res = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
					cout << " Время: " << res << " нс" << endl;
				}
				else if (act == 3)
					f = -1;
			}
		}
		else if (section == 4) 
			return -1;

		system("pause");
	}
}
