#pragma once

using namespace std;

template <typename T>
class Sequence {
protected:
	int length;
	bool isEmpty;
public:
	Sequence();
	~Sequence();
	int GetLength();
	bool IsEmpty();
	virtual T Get(int) = 0;
	virtual T GetFirst() = 0;
	virtual T GetLast() = 0;
	virtual void Append(T) = 0;
	virtual void Prepend(T) = 0;
	virtual void InsertAt(int, T) = 0;
	virtual void Remove(T) = 0;
	virtual void Swap(int, int) = 0;
	virtual void printAll() = 0;
};

class SequenceException : public exception {
private:
	int ex_index;
public:
	SequenceException(int index) {
		ex_index = index;
	};
	void what() {
		cout << "ERROR. Index:" << ex_index << " Out of sequence bounds." << endl;
	};
};

template <typename T>
Sequence<T>::Sequence() {
	length = 0;
	isEmpty = true;
}

template <typename T>
Sequence<T>::~Sequence() {}

template <typename T>
int Sequence<T>::GetLength() {
	return length;
}

template <typename T>
bool Sequence<T>::IsEmpty() {
	return isEmpty;
}