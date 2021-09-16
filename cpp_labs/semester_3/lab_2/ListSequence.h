#ifndef LIST_SEQUENCE_H
#define LIST_SEQUENCE_H

#include <iostream>
#include "Sequence.h"
#include "Exceptions.h"

template <typename T>
struct Node {
	T data;
	Node<T> * next;
	Node<T> * prev;
};

template <typename T>
class ListSequence : public Sequence<T> {
private:
	Node<T> * first;
	Node<T> * last;
public:
	ListSequence();
	~ListSequence();
	ListSequence(const ListSequence<T> &obj);
	T Get(int index);
	T GetFirst();
	T GetLast();
	ListSequence <T> GetSubsequence(int startIndex, int endIndex);
	void Append(T item);
	void Prepend(T item);
	void InsertAt(int index, T item);
	void Remove(T item);
	void printAll();
	void Swap(int, int);
};

template <typename T>
ListSequence<T>::ListSequence(const ListSequence<T> &obj) {
	Node<T> * node = new Node<T>;
	node->next = nullptr;
	node->prev = nullptr;
	this->first = node;
	this->last = node;
	Node<T> *ptr = obj.first;
	for (int i = 0; i < obj.length; i++) {
		Append(ptr->data);
		ptr = ptr->next;
	}
}

template <typename T>
ListSequence<T>::ListSequence() {
	Node<T> * node = new Node<T>;
	node->next = nullptr;
	node->prev = nullptr;
	this->first = node;
	this->last = node;
}

template <typename T>
ListSequence<T>::~ListSequence() {
	for (int i = 0; i < this->length; i++) {
		Node<T> *ptr = this->last;
		this->last = this->last->prev;
		delete ptr;
	}
}

template <typename T>
T ListSequence<T>::Get(int index) {
	if (index >= this->length || index < 0)
		throw(SequenceException(index));
	else {
		Node<T> *ptr = this->first;
		for (int j = 0; j < index; j++)
			ptr = ptr->next;
		return ptr->data;
	}
}

template <typename T>
T ListSequence<T>::GetFirst() {
	if (this->isEmpty)
		throw (SequenceException(0));
	else
		return this->first->data;
}

template <typename T>
T ListSequence<T>::GetLast() {
	if (this->isEmpty)
		throw (SequenceException(0));
	else
		return this->last->data;
}

template <typename T>
void ListSequence<T>::Prepend(T item) {
	if (this->length == 0) {
		this->isEmpty = false;
		this->length++;
		this->first->data = item;
	}
	else {
		this->length++;
		Node<T> * node = new Node<T>;
		node->data = item;
		node->prev = nullptr;
		node->next = this->first;
		this->first = node;
		this->first->next->prev = node;
	}
}

template <typename T>
void ListSequence<T>::Append(T item) {
	if (this->length == 0) {
		this->length++;
		this->isEmpty = false;
		this->first->data = item;
	}
	else if (this->length > 0) {
		this->length++;
		Node<T> * node = new Node<T>;
		node->data = item;
		node->next = nullptr;
		node->prev = this->last;
		this->last = node;
		this->last->prev->next = this->last;
	}
}

template <typename T>
ListSequence<T> ListSequence<T>::GetSubsequence(int startIndex, int endIndex) {
	if (startIndex < 0 || startIndex >= this->length)
		throw(SequenceException(startIndex));
	if (endIndex < 0 || endIndex >= this->length)
		throw(SequenceException(endIndex));
	if (startIndex > endIndex)
		throw (SequenceException(startIndex));
	else {
		ListSequence<T> List;
		Node<T> *ptr = this->first;
		for (int i = 0; i < startIndex; i++)
			ptr = ptr->next;
		for (int i = startIndex; i <= endIndex; i++) {
			List.Append(ptr->data);
			ptr = ptr->next;
		}
		return List;
	}
}

template <typename T>
void ListSequence<T>::InsertAt(int index, T item) {
	bool flag = false;
	if (index<0 || index>this->length)
		throw (SequenceException(index));
	else {
		if (this->isEmpty) {
			this->first->data = item;
			this->isEmpty = false;
			this->length++;
			flag = true;
		}
		if (index == this->length && !this->isEmpty && !flag) {
			Node<T> *node = new Node<T>;
			node->data = item;
			node->next = nullptr;
			node->prev = this->last;
			this->last->next = node;
			this->last = node;
			this->length++;
			flag = true;
		}
		if (index == 0 && !this->isEmpty && !flag) {
			Node<T> *node = new Node<T>;
			node->data = item;
			node->prev = nullptr;
			node->next = this->first;
			this->first->prev = node;
			this->first = node;
			this->length++;
			flag = true;
		}
		else if (!flag) {
			Node<T> *node = new Node<T>;
			node->data = item;
			Node<T> *ptr = this->first;
			for (int i = 0; i < index - 1; i++)
				ptr = ptr->next;
			ptr->next->prev = node;
			node->next = ptr->next;
			ptr->next = node;
			node->prev = ptr;
			this->length++;
			flag = true;
		}
	}
}

template <typename T>
void ListSequence<T>::Remove(T item) {
	if (this->isEmpty)
		throw (SequenceException(0));
	else {
		Node<T> *ptr = this->first;
		for (int j = 0; j < this->length; j++) {
			if (ptr->data == item && ptr != this->first && ptr != this->last) {
				this->length--;
				ptr->prev->next = ptr->next;
				ptr->next->prev = ptr->prev;
				Node<T> *ptr1 = ptr->prev;
				delete ptr;
				ptr = ptr1;
				j--;
			}
			else if (ptr->data == item && ptr == this->first && ptr != this->last) {
				this->length--;
				ptr->next->prev = nullptr;
				this->first = ptr->next;
				Node<T> *ptr1 = ptr->next;
				delete ptr;
				ptr = ptr1;
				j--;
			}
			else if (ptr->data == item && ptr != this->first && ptr == this->last) {
				this->length--;
				ptr->prev->next = nullptr;
				this->last = ptr->prev;
				Node<T> *ptr1 = ptr->prev;
				delete ptr;
				ptr = ptr1;
				j--;
			}
			else if (ptr->data == item && ptr == this->first && ptr == this->last) {
				this->length--;
				this->first = this->last = nullptr;
				delete ptr;
				j--;
			}
			else {
				Node<T> *ptr1 = ptr->next;
				ptr = ptr1;
			}
		}
	}
}

template <typename T>
void ListSequence<T>::printAll() {
	if (this->isEmpty)
		throw (SequenceException(0));
	else {
		Node<T> *ptr = this->first;
		int i;
		for (i = 0; ptr != this->last; i++) {
			cout << "Элемент " << i << " : " << ptr->data << endl;
			ptr = ptr->next;
		}
		cout << "Элемент " << i << " : " << this->last->data << endl << endl;
	}
}

template <typename T>
void ListSequence<T>::Swap(int ind1, int ind2) {
	Node<T> * ptr1 = this->first, *ptr2 = this->first;
	T first = Get(ind1);
	T second = Get(ind2);
	for (int i = 0; i < ind1; i++)
		ptr1 = ptr1->next;
	ptr1->data = second;
	for (int i = 0; i < ind2; i++)
		ptr2 = ptr2->next;
	ptr2->data = first;
}

#endif /* LIST_SEQUENCE_H */