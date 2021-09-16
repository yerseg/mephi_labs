#ifndef TEST_H
#define TEST_H

#include <assert.h>
#include "Exceptions.h"
#include "Sequence.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include "Student.h"
#include "IDictionary.h"
#include "BTree.h"
#include "Binary_Search.h"


void Test_Dictionary() {
	cout << "Запуск автоматического тестирования словаря (hash-таблицы).....";

	bool Remove = false;
	IDictionary<string, int> test_dict;

	Student student1 = Student("Maksim", 19, 10, 2000); student1.set_flag(1); 
	Student student2 = Student("Dasha", 20, 1, 1997); student2.set_flag(1); 
	Student student3 = Student("Alexey", 23, 11, 1995); student3.set_flag(1); 
	Student student4 = Student("Vanya", 5, 6, 1999); student4.set_flag(1); 
	Student student5 = Student("Slava", 18, 11, 1998); student5.set_flag(1); 
	Student student6 = Student("Egor", 1, 2, 1993); student6.set_flag(1); 
	Student student7 = Student("Nastya", 10, 11, 1994); student7.set_flag(1); 
	Student student8 = Student("Semyon", 10, 12, 1996); student8.set_flag(1); 
	Student student9 = Student("Andrey", 15, 12, 1999); student9.set_flag(1); 
	Student student10 = Student("Kirill", 29, 01, 1999); student10.set_flag(1);

	test_dict.Add("0", 0); 
	test_dict.Add("1", 25); 
	test_dict.Add("2", 79); 
	test_dict.Add("3", 239); 
	test_dict.Add("4", 477); 
	test_dict.Add("5", 0); 
	
	assert(test_dict.Get("0") == 0 && test_dict.Get("1") == 25 && test_dict.Get("2") == 79 && test_dict.Get("3") == 239 && test_dict.Get("4") == 477 && test_dict.Get("5") == 0);
	assert(test_dict.GetCount() == 6);	
	assert(test_dict.GetCapacity() == 7);
	assert(test_dict.ContainsKey("0") && test_dict.ContainsKey("1") && test_dict.ContainsKey("2") && test_dict.ContainsKey("3") && test_dict.ContainsKey("4") && test_dict.ContainsKey("5") && !(test_dict.ContainsKey("6")));
	test_dict.Remove("3");

	try {
		test_dict.Get("3");
	}
	catch (KeyIsNotExistException<string> ex) {
		Remove = true;
	}

	if (Remove)
		cout << "Автоматическое тестирование пройдено без ошибок" << endl;
}

void Test_BTree() {
	cout << "Запуск тестирования B-дерева.....";

	ArraySequence<Student> test_arr;
	Student student1 = Student("Maksim", 19, 10, 2000); student1.set_flag(2); test_arr.Append(student1);
	Student student2 = Student("Dasha", 20, 1, 1997); student2.set_flag(2); test_arr.Append(student2);
	Student student3 = Student("Alexey", 23, 11, 1995); student3.set_flag(2); test_arr.Append(student3);
	Student student4 = Student("Vanya", 5, 6, 1999); student4.set_flag(2); test_arr.Append(student4);
	Student student5 = Student("Slava", 18, 11, 1998); student5.set_flag(2); test_arr.Append(student5);
	Student student6 = Student("Egor", 1, 2, 1993); student6.set_flag(2); test_arr.Append(student6);
	Student student7 = Student("Nastya", 10, 11, 1994); student7.set_flag(2); test_arr.Append(student7);
	Student student8 = Student("Semyon", 10, 12, 1996); student8.set_flag(2); test_arr.Append(student8);
	Student student9 = Student("Andrey", 15, 12, 1999); student9.set_flag(2); test_arr.Append(student9);
	Student student10 = Student("Kirill", 29, 01, 1999); student10.set_flag(2); test_arr.Append(student10);

	BTreeBuilder<Student> builder = BTreeBuilder<Student>(2);
	BTree<Student> btree = builder.build(&test_arr, test_arr.GetLength());

	assert(btree.search(student1).index == 1);
	assert(btree.search(student2).index == 0);
	assert(btree.search(student3).index == 0);
	assert(btree.search(student4).index == 0);
	assert(btree.search(student5).index == 0);
	assert(btree.search(student6).index == 0);
	assert(btree.search(student7).index == 0);
	assert(btree.search(student8).index == 1);
	assert(btree.search(student9).index == 0);
	assert(btree.search(student10).index == 1);

	for (int i = 0; i < 10; i++)
		test_arr.Get(i).set_flag(1);

	assert(btree.search(student1).index == 1);
	assert(btree.search(student2).index == 0);
	assert(btree.search(student3).index == 0);
	assert(btree.search(student4).index == 0);
	assert(btree.search(student5).index == 0);
	assert(btree.search(student6).index == 0);
	assert(btree.search(student7).index == 0);
	assert(btree.search(student8).index == 1);
	assert(btree.search(student9).index == 0);
	assert(btree.search(student10).index == 1);

	cout << "Автоматическое тестирование пройдено без ошибок" << endl;
}

void Test_Binary_Search() {
	cout << "Запуск тестирования бинарного поиска.....";

	ArraySequence<Student> test_arr;
	Student student1 = Student("Maksim", 19, 10, 2000); student1.set_flag(1); test_arr.Append(student1);
	Student student2 = Student("Dasha", 20, 1, 1997); student2.set_flag(1); test_arr.Append(student2);
	Student student3 = Student("Alexey", 23, 11, 1995); student3.set_flag(1); test_arr.Append(student3);
	Student student4 = Student("Vanya", 5, 6, 1999); student4.set_flag(1); test_arr.Append(student4);
	Student student5 = Student("Slava", 18, 11, 1998); student5.set_flag(1); test_arr.Append(student5);
	Student student6 = Student("Egor", 1, 2, 1993); student6.set_flag(1); test_arr.Append(student6);
	Student student7 = Student("Nastya", 10, 11, 1994); student7.set_flag(1); test_arr.Append(student7);
	Student student8 = Student("Semyon", 10, 12, 1996); student8.set_flag(1); test_arr.Append(student8);
	Student student9 = Student("Andrey", 15, 12, 1999); student9.set_flag(1); test_arr.Append(student9);
	Student student10 = Student("Kirill", 29, 01, 1999); student10.set_flag(1); test_arr.Append(student10);

	assert(test_arr.Get(Search_Binary_Base(&test_arr, student1)) == student1);
	assert(test_arr.Get(Search_Binary_Base(&test_arr, student2)) == student2);
	assert(test_arr.Get(Search_Binary_Base(&test_arr, student3)) == student3);
	assert(test_arr.Get(Search_Binary_Base(&test_arr, student4)) == student4);
	assert(test_arr.Get(Search_Binary_Base(&test_arr, student5)) == student5);
	assert(test_arr.Get(Search_Binary_Base(&test_arr, student6)) == student6);
	assert(test_arr.Get(Search_Binary_Base(&test_arr, student7)) == student7);
	assert(test_arr.Get(Search_Binary_Base(&test_arr, student8)) == student8);
	assert(test_arr.Get(Search_Binary_Base(&test_arr, student9)) == student9);
	assert(test_arr.Get(Search_Binary_Base(&test_arr, student10)) == student10);

	assert(test_arr.Get(Search_Binary_Prop(&test_arr, student1, 1, 8)) == student1);
	assert(test_arr.Get(Search_Binary_Prop(&test_arr, student2, 2, 3)) == student2);
	assert(test_arr.Get(Search_Binary_Prop(&test_arr, student3, 3, 4)) == student3);
	assert(test_arr.Get(Search_Binary_Prop(&test_arr, student4, 1, 6)) == student4);
	assert(test_arr.Get(Search_Binary_Prop(&test_arr, student5, 1, 8)) == student5);
	assert(test_arr.Get(Search_Binary_Prop(&test_arr, student6, 1, 10)) == student6);
	assert(test_arr.Get(Search_Binary_Prop(&test_arr, student7, 10, 6)) == student7);
	assert(test_arr.Get(Search_Binary_Prop(&test_arr, student8, 10, 3)) == student8);
	assert(test_arr.Get(Search_Binary_Prop(&test_arr, student9, 3, 4)) == student9);
	assert(test_arr.Get(Search_Binary_Prop(&test_arr, student10, 150, 234)) == student10);
	
	assert(test_arr.Get(Search_Binary_Fibonacci(&test_arr, student1, 4)) == student1);
	assert(test_arr.Get(Search_Binary_Fibonacci(&test_arr, student2, 3)) == student2);
	assert(test_arr.Get(Search_Binary_Fibonacci(&test_arr, student3, 4)) == student3);
	assert(test_arr.Get(Search_Binary_Fibonacci(&test_arr, student4, 6)) == student4);
	assert(test_arr.Get(Search_Binary_Fibonacci(&test_arr, student5, 8)) == student5);
	assert(test_arr.Get(Search_Binary_Fibonacci(&test_arr, student6, 10)) == student6);
	assert(test_arr.Get(Search_Binary_Fibonacci(&test_arr, student7, 7)) == student7);
	assert(test_arr.Get(Search_Binary_Fibonacci(&test_arr, student8, 9)) == student8);
	assert(test_arr.Get(Search_Binary_Fibonacci(&test_arr, student9, 3)) == student9);
	assert(test_arr.Get(Search_Binary_Fibonacci(&test_arr, student10, 5)) == student10);

	assert(test_arr.Get(Search_Binary_Golden_Ratio(&test_arr, student1)) == student1);
	assert(test_arr.Get(Search_Binary_Golden_Ratio(&test_arr, student2)) == student2);
	assert(test_arr.Get(Search_Binary_Golden_Ratio(&test_arr, student3)) == student3);
	assert(test_arr.Get(Search_Binary_Golden_Ratio(&test_arr, student4)) == student4);
	assert(test_arr.Get(Search_Binary_Golden_Ratio(&test_arr, student5)) == student5);
	assert(test_arr.Get(Search_Binary_Golden_Ratio(&test_arr, student6)) == student6);
	assert(test_arr.Get(Search_Binary_Golden_Ratio(&test_arr, student7)) == student7);
	assert(test_arr.Get(Search_Binary_Golden_Ratio(&test_arr, student8)) == student8);
	assert(test_arr.Get(Search_Binary_Golden_Ratio(&test_arr, student9)) == student9);
	assert(test_arr.Get(Search_Binary_Golden_Ratio(&test_arr, student10)) == student10);

	for (int i = 0; i < 10; i++)
		test_arr.Get(i).set_flag(2);

	assert(test_arr.Get(Search_Binary_Base(&test_arr, student1)) == student1);
	assert(test_arr.Get(Search_Binary_Base(&test_arr, student2)) == student2);
	assert(test_arr.Get(Search_Binary_Base(&test_arr, student3)) == student3);
	assert(test_arr.Get(Search_Binary_Base(&test_arr, student4)) == student4);
	assert(test_arr.Get(Search_Binary_Base(&test_arr, student5)) == student5);
	assert(test_arr.Get(Search_Binary_Base(&test_arr, student6)) == student6);
	assert(test_arr.Get(Search_Binary_Base(&test_arr, student7)) == student7);
	assert(test_arr.Get(Search_Binary_Base(&test_arr, student8)) == student8);
	assert(test_arr.Get(Search_Binary_Base(&test_arr, student9)) == student9);
	assert(test_arr.Get(Search_Binary_Base(&test_arr, student10)) == student10);

	assert(test_arr.Get(Search_Binary_Prop(&test_arr, student1, 1, 8)) == student1);
	assert(test_arr.Get(Search_Binary_Prop(&test_arr, student2, 2, 3)) == student2);
	assert(test_arr.Get(Search_Binary_Prop(&test_arr, student3, 3, 4)) == student3);
	assert(test_arr.Get(Search_Binary_Prop(&test_arr, student4, 1, 6)) == student4);
	assert(test_arr.Get(Search_Binary_Prop(&test_arr, student5, 1, 8)) == student5);
	assert(test_arr.Get(Search_Binary_Prop(&test_arr, student6, 1, 10)) == student6);
	assert(test_arr.Get(Search_Binary_Prop(&test_arr, student7, 10, 6)) == student7);
	assert(test_arr.Get(Search_Binary_Prop(&test_arr, student8, 10, 3)) == student8);
	assert(test_arr.Get(Search_Binary_Prop(&test_arr, student9, 3, 4)) == student9);
	assert(test_arr.Get(Search_Binary_Prop(&test_arr, student10, 150, 234)) == student10);

	assert(test_arr.Get(Search_Binary_Fibonacci(&test_arr, student1, 4)) == student1);
	assert(test_arr.Get(Search_Binary_Fibonacci(&test_arr, student2, 3)) == student2);
	assert(test_arr.Get(Search_Binary_Fibonacci(&test_arr, student3, 4)) == student3);
	assert(test_arr.Get(Search_Binary_Fibonacci(&test_arr, student4, 6)) == student4);
	assert(test_arr.Get(Search_Binary_Fibonacci(&test_arr, student5, 8)) == student5);
	assert(test_arr.Get(Search_Binary_Fibonacci(&test_arr, student6, 10)) == student6);
	assert(test_arr.Get(Search_Binary_Fibonacci(&test_arr, student7, 7)) == student7);
	assert(test_arr.Get(Search_Binary_Fibonacci(&test_arr, student8, 9)) == student8);
	assert(test_arr.Get(Search_Binary_Fibonacci(&test_arr, student9, 3)) == student9);
	assert(test_arr.Get(Search_Binary_Fibonacci(&test_arr, student10, 5)) == student10);

	assert(test_arr.Get(Search_Binary_Golden_Ratio(&test_arr, student1)) == student1);
	assert(test_arr.Get(Search_Binary_Golden_Ratio(&test_arr, student2)) == student2);
	assert(test_arr.Get(Search_Binary_Golden_Ratio(&test_arr, student3)) == student3);
	assert(test_arr.Get(Search_Binary_Golden_Ratio(&test_arr, student4)) == student4);
	assert(test_arr.Get(Search_Binary_Golden_Ratio(&test_arr, student5)) == student5);
	assert(test_arr.Get(Search_Binary_Golden_Ratio(&test_arr, student6)) == student6);
	assert(test_arr.Get(Search_Binary_Golden_Ratio(&test_arr, student7)) == student7);
	assert(test_arr.Get(Search_Binary_Golden_Ratio(&test_arr, student8)) == student8);
	assert(test_arr.Get(Search_Binary_Golden_Ratio(&test_arr, student9)) == student9);
	assert(test_arr.Get(Search_Binary_Golden_Ratio(&test_arr, student10)) == student10);

	cout << "Автоматическое тестирование пройдено без ошибок" << endl;
}

#endif /* TEST_H */
