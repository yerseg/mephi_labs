#ifndef HELP_FUNC_H
#define HELP_FUNC_H

#include <iostream>
#include <chrono>
#include <locale>
#include "Sequence.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include "Sorters.h"

using namespace std;

template <typename T>
void Rand_Seq_Gen(Sequence<T> * seq, int length) {
	srand(static_cast<unsigned int>(time(NULL)));
	for (int i = 0; i < length; i++)
		seq->Append(rand());
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

#endif /* HELP_FUNC_H */