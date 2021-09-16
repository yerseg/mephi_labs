#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <iostream>
#include <vector>
#include "Sequence.h"
#include "Exceptions.h"

template <typename T>
int Search_Binary_Prop(Sequence<T> * seq, T element, int a, int b) {
	return Search_Binary_Helper(seq, element, 0, seq->GetLength(), a, b);
}

template <typename T>
int Search_Binary_Helper(Sequence<T> * seq, T element, int begin, int end, int a, int b) {
	Sorter<T> sort;
	sort.QuickSort(seq);
	int midd = 0;
	while (1) {
		midd = begin + a * (end - begin) / (a + b);
		if (element < seq->Get(midd))
			end = midd - 1;
		else if (element > seq->Get(midd))
			begin = midd + 1;
		else
			return midd;
		if (begin > end)
			throw ElementNotFoundException<T>(element);
	}
}

template <typename T>
int Search_Binary_Base(Sequence<T> * seq, T element) {
	int midd = 0;
	int length = seq->GetLength();
	if (length == 0) 
		throw EmptySequenceException();
	else 
		return Search_Binary_Helper(seq, element, 0, length, 1, 1);
}

template <typename T>
int Search_Binary_Golden_Ratio(Sequence<T> * seq, T element) {
	int midd = 0;
	double phi = 0.5 * (1 + sqrt(5));
	int length = seq->GetLength();
	if (length == 0) 
		throw EmptySequenceException();
	else 
		return Search_Binary_Helper(seq, element, 0, length, phi - 1, phi);
}

template <typename T>
int Search_Binary_Fibonacci(Sequence<T> * seq, T element, int n) {
	int midd = 0;
	double phi = 0.5 * (1 + sqrt(5));
	int length = seq->GetLength();
	if (n <= 2)
		throw NoMeaningFibException();
	if (length == 0)
		throw EmptySequenceException();
	else {
		double a = (pow(phi, n) - pow(phi * (-1), n * (-1))) / (2 * phi - 1);
		double b = (pow(phi, n + 1) - pow(phi * (-1), (n + 1)* (-1))) / (2 * phi - 1);
		return Search_Binary_Helper(seq, element, 0, length, a, b);
	}
}

#endif /* BINARY_SEARCH_H */
