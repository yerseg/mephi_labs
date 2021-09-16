#ifndef HELP_FUNC_H
#define HELP_FUNC_H

#include <iostream>
#include <chrono>
#include <locale>
#include <vector>
#include "Sequence.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include "Sorters.h"
#include "Student.h"

using namespace std;

template <typename T>
void Rand_Seq_Gen(Sequence<T> * seq, const int length) {
	srand(static_cast<unsigned int>(time(NULL)));
	for (int i = 0; i < length; i++)
		seq->Append(rand());
}

string Rand_String_Gen (const int len) {
	string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	string s;
	for (int i = 0; i < len; ++i) {
		s += alphabet[rand() % (alphabet.size() - 1)];
	}
	return s;
}

void Rand_Stud_Seq_Gen(Sequence<Student> * seq, int length) {
	srand(static_cast<unsigned int>(time(NULL)));
	for (int i = 0; i < length; i++) {
		Student stud = Student(Rand_String_Gen(10), 1 + rand() % (31 - 1), 1 + rand() % (12 - 1), 1930 + rand() % (2018 - 1930));
		seq->Append(stud);
	}
}

template <typename T>
long int time_InsectionSort(Sequence<T> * seq, Sorter<T> sort) {
	auto begin = chrono::high_resolution_clock::now();
	sort.InsectionSort(seq);
	auto end = chrono::high_resolution_clock::now();
	return chrono::duration_cast<chrono::microseconds>(end - begin).count();
}

template <typename T>
long int time_QuickSort(Sequence<T> * seq, Sorter<T> sort) {
	auto begin = chrono::high_resolution_clock::now();
	sort.QuickSort(seq);
	auto end = chrono::high_resolution_clock::now();
	return chrono::duration_cast<chrono::microseconds>(end - begin).count();
}

template <typename T>
bool Test_After_Sort(Sequence<T>* seq) {
	bool isCorrect = true;
	for (int i = 0; i < seq->GetLength() - 1; i++)
		if (seq->Get(i) > seq->Get(i + 1))
			isCorrect = false;
	return isCorrect;
}

template <typename T>
void Sorts_Compare(Sequence<T> * seq1, Sequence<T> * seq2, Sorter<T> sort) {
	long int time_Q = time_QuickSort(seq2, sort);
	long int time_I = time_InsectionSort(seq1, sort);
	cout << "Cортировка вставками: " << time_I << " мкс" << endl << "Быстрая сортировка: " << time_Q << " мкс " << endl;
}

template <typename T>
void Invert_Seq(Sequence<T> * seq) {
	int len = seq->GetLength();
	for (int i = 0; i < len / 2; i++)
		seq->Swap(i, len - 1 - i);
}

template <typename TElement>
vector<long int> Time_For_Search_Binary_Base(Sequence<TElement> * seq, TElement element) {
	auto begin = chrono::high_resolution_clock::now();
	int idx = Search_Binary_Base(seq, element);
	auto end = chrono::high_resolution_clock::now();
	auto res = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
	/*vector<long int> v;
	v.push_back(idx);
	v.push_back(res);
	return v;*/
	return { idx, (long int)res };
}

template <typename TElement>
vector<long int> Time_For_Search_Binary_Golden_Ratio(Sequence<TElement>* seq, TElement element) {
	auto begin = chrono::high_resolution_clock::now();
	int idx = Search_Binary_Golden_Ratio(seq, element);
	auto end = chrono::high_resolution_clock::now();
	auto res = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
	/*vector<long int> v;
	v.push_back(idx);
	v.push_back(res);
	return v;*/
	return { idx, (long int)res };
}

template <typename TElement>
vector<long int> Time_For_Search_Binary_Fibonacci(Sequence<TElement>* seq, TElement element, int n) {
	auto begin = chrono::high_resolution_clock::now();
	int idx = Search_Binary_Fibonacci(seq, element, n);
	auto end = chrono::high_resolution_clock::now();
	auto res = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
	/*vector<long int> v;
	v.push_back(idx);
	v.push_back(res);
	return v;*/
	return { idx, (long int)res };
}

template <typename TElement>
vector<long int> Time_For_Search_Binary_Own_Pair(Sequence<TElement>* seq, TElement element, int a, int b) {
	auto begin = chrono::high_resolution_clock::now();
	int idx = Search_Binary_Prop(seq, element, a, b);
	auto end = chrono::high_resolution_clock::now();
	auto res = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
	/*vector<long int> v;
	v.push_back(idx);
	v.push_back(res);
	return v;*/
	return { idx, (long int)res };
}

#endif /* HELP_FUNC_H */