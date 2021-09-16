#ifndef ARRAY_SEQUENCE_H
#define ARRAY_SEQUENCE_H

#include <iostream>
#include "Sequence.h"

template <typename T>
class ArraySequence : public Sequence<T> {
private:
	T * ptr;
public:
	ArraySequence();
	~ArraySequence();
	ArraySequence(const ArraySequence<T> &obj);
	T Get(int);
	T GetFirst();
	T GetLast();
	ArraySequence <T> GetSubsequence(int, int);
	void Append(T);
	void Prepend(T);
	void InsertAt(int, T);
	void Remove(T);
	void Swap(int, int);
	void printAll();
};

template <typename T>
ArraySequence<T>::ArraySequence() {
	ptr = new T;
}

template <typename T>
ArraySequence<T>::ArraySequence(const ArraySequence<T> &obj) {
	ptr = new T;
	for (int i = 0; i < obj.length; i++)
		Append(obj.ptr[i]);
}

template <typename T>
ArraySequence<T>::~ArraySequence() {
	delete[] ptr;
}

template <typename T>
T ArraySequence<T>::Get(int index) {
	if (index >= this->length || index < 0)
		throw(SequenceException(index));
	else
		return ptr[index];
}

template <typename T>
T ArraySequence<T>::GetFirst() {
	if (this->isEmpty)
		throw (SequenceException(0));
	else
		return ptr[0];
}

template <typename T>
T ArraySequence<T>::GetLast() {
	if (this->isEmpty)
		throw (SequenceException(0));
	else
		return ptr[this->length - 1];
}

template <typename T>
void ArraySequence<T>::Prepend(T item) {
	if (this->length == 0) {
		this->length++;
		this->isEmpty = false;
		ptr[0] = item;
	}
	else if (this->length > 0) {
		T * ptr1 = new T[this->length + 1];
		for (int i = 0; i < this->length; i++)
			ptr1[i + 1] = ptr[i];
		delete[] ptr;
		ptr1[0] = item;
		ptr = ptr1;
		this->length++;
	}
}

template <typename T>
void ArraySequence<T>::Append(T item) {
	if (this->length == 0) {
		this->length++;
		this->isEmpty = false;
		ptr[0] = item;
	}
	else if (this->length > 0) {
		T * ptr1 = new T[this->length + 1];
		for (int i = 0; i < this->length; i++)
			ptr1[i] = ptr[i];
		delete[] ptr;
		ptr1[this->length] = item;
		ptr = ptr1;
		this->length++;
	}
}

template <typename T>
ArraySequence<T> ArraySequence<T>::GetSubsequence(int startIndex, int endIndex) {
	if (startIndex < 0 || startIndex >= this->length)
		throw(SequenceException(startIndex));
	if (endIndex < 0 || endIndex >= this->length)
		throw(SequenceException(endIndex));
	if (startIndex > endIndex)
		throw (SequenceException(startIndex));
	else {
		ArraySequence<T> Array;
		for (int i = startIndex; i <= endIndex; i++)
			Array.Append(ptr[i]);
		return Array;
	}
}

template <typename T>
void ArraySequence<T>::InsertAt(int index, T item) {
	if (index<0 || index>this->length)
		throw (SequenceException(index));
	else {
		this->length++;
		this->isEmpty = false;
		T *ptr1 = new T[this->length];
		for (int i = 0; i < index; i++)
			ptr1[i] = ptr[i];
		ptr1[index] = item;
		for (int i = index + 1; i < this->length; i++)
			ptr1[i] = ptr[i - 1];
		delete[] ptr;
		ptr = ptr1;
	}
}

template <typename T>
void ArraySequence<T>::Remove(T item) {
	if (this->isEmpty)
		throw (SequenceException(0));
	else {
		for (int j = 0; j < this->length; j++) {
			if (ptr[j] == item) {
				this->length--;
				T *ptr1 = new T[this->length];
				for (int i = 0; i < j; i++)
					ptr1[i] = ptr[i];
				for (int i = j + 1; i < this->length + 1; i++)
					ptr1[i - 1] = ptr[i];
				delete[] ptr;
				ptr = ptr1;
				j--;
			}
			else
				;
		}
	}
}

template <typename T>
void ArraySequence<T>::printAll() {
	if (this->isEmpty)
		throw (SequenceException(0));
	else {
		for (int i = 0; i < this->length; i++)
			cout << "Элемент " << i << ": " << ptr[i] << endl;
	}
	cout << '\n';
}

template <typename T>
void ArraySequence<T>::Swap(int ind1, int ind2) {
	T a = Get(ind1);
	this->ptr[ind1] = Get(ind2);
	this->ptr[ind2] = a;
}


#endif /* ARRAY_SEQUENCE_H */