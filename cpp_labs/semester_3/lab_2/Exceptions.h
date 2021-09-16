#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
using namespace std;

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

template <typename TKey>
class KeyUsedException : public exception {
	TKey ex_key;
public:
	KeyUsedException(TKey key) {
		ex_key = key;
	}
	void what() {
		cout << "ERROR. This key (" << ex_key << ") is already used." << std::endl;
	}
};

template <typename TKey>
class KeyIsNotExistException : public exception {
	TKey ex_key;
public:
	KeyIsNotExistException(TKey key) {
		ex_key = key;
	}
	void what() {
		cout << "ERROR. This key (" << ex_key << ") is not exist." << endl;
	}
};

template <typename TElem>
class ElementNotFoundException : public exception {
	TElem ex_element;
public:
	ElementNotFoundException(TElem elem) {
		ex_element = elem;
	}
	void what() {
		cout << "ERROR 404. Element (" << ex_element << ") not found." << endl;
	};
};

class EmptySequenceException : public exception {
public:
	void what() {
		cout << "ERROR. Последовательность пуста" << endl;
	}
};

class NoMeaningFibException : public std::exception {
public:
	void what() {
		cout << "ERROR. Бессмысленная пропорция деления" << endl;
	}
};

#endif /* EXCEPTIONS_H */
