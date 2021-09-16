#ifndef SORTERS_H
#define SORTERS_H

#include "Sequence.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include <time.h>

template <typename T>
class ISorter {
public:
	ISorter() {};
	~ISorter() {};
	virtual Sequence<T> * QuickSort(Sequence<T> *) = 0;
	virtual Sequence<T> * InsectionSort(Sequence<T> *) = 0;
};

template <typename T>
class Sorter : public ISorter<T> {
public:
	Sorter() {};
	~Sorter() {};
	Sequence<T> * QuickSort(Sequence<T> *);
	Sequence<T> * InsectionSort(Sequence<T> *);
private:
	Sequence<T> * quicksort_tool(Sequence<T> *, int, int);
};

template <typename T>
Sequence<T> * Sorter<T>::quicksort_tool(Sequence<T> * seq, int first, int last) {
	if (!seq->IsEmpty() && first < last) {
		srand(static_cast<unsigned int>(time(0)));
		int ind = first + rand() % (last - first);
		int PivotPoint = first;
		T pivot = seq->Get(ind);
		seq->Swap(first, ind);
		for (int i = first + 1; i <= last; i++) {
			if (seq->Get(i) < pivot) {
				PivotPoint++;
				seq->Swap(i, PivotPoint);
			}
			else
				;
		}
		seq->Swap(first, PivotPoint);
		quicksort_tool(seq, first, PivotPoint - 1);
		quicksort_tool(seq, PivotPoint + 1, last);
	}
	else
		;
	return seq;
}

template <typename T>
Sequence<T> * Sorter<T>::QuickSort(Sequence<T> * seq) {
	return quicksort_tool(seq, 0, seq->GetLength() - 1);
}

template <typename T>
Sequence<T> * Sorter<T>::InsectionSort(Sequence<T> * seq) {
	int i, j;
	for (i = 0; i < seq->GetLength(); i++) {
		j = i;
		while (j > 0 && seq->Get(j) < seq->Get(j - 1)) {
			seq->Swap(j, j - 1);
			j--;
		}
	}
	return seq;
}

#endif /* SORTERS_H */