#include <iostream>

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
	virtual T Get(int index) = 0;
	virtual T GetFirst() = 0;
	virtual T GetLast() = 0;
	virtual void Append(T item) = 0;
	virtual void Prepend(T item) = 0;
	virtual void InsertAt(int index, T item) = 0;
	virtual void Remove(T item) = 0;
};

template <typename T>
class ArraySequence : public Sequence<T> {
private:
	T * ptr;
public:
	ArraySequence();
	~ArraySequence();
	ArraySequence(const ArraySequence<T> &obj);
	T Get(int index);
	T GetFirst();
	T GetLast();
	ArraySequence <T> GetSubsequence(int startIndex, int endIndex);
	void Append(T item);
	void Prepend(T item);
	void InsertAt(int index, T item);
	void Remove(T item);
	void printAll();
};

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
	if (endIndex<0 || endIndex >= this->length)
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
			cout << ptr[i] << ' ';
	}
	cout << '\n';
}

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
	if (endIndex<0 || endIndex >= this->length)
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
		for (int i = 0; ptr != this->last; i++) {
			cout << ptr->data << ' ';
			ptr = ptr->next;
		}
		cout << this->last->data << ' ' << '\n';
	}
}

void TestListSequence() {
	cout << "_____BEGIN_TEST_LIST_____" << endl;
	ListSequence<int> list;

	if (list.GetLength() == 0) cout << "_TEST 1 - OK" << endl;
	else cout << "_TEST 1 - ERROR!" << endl;

	list.Append(23);
	list.printAll();

	if (list.GetLength() == 1) cout << "_TEST 2 - OK" << endl;
	else cout << "_TEST 2 - ERROR!" << endl;

	if (list.GetFirst() == 23) cout << "_TEST 3 - OK" << endl;
	else cout << "_TEST 3 - ERROR!" << endl;

	if (list.GetLast() == 23) cout << "_TEST 4 - OK" << endl;
	else cout << "_TEST 4 - ERROR!" << endl;

	try {
		if (list.Get(0) == 23) cout << "_TEST 5 - OK" << endl;
		else cout << "_TEST 5 - ERROR!" << endl;
	}
	catch (SequenceException ex) {
		ex.what();
	}

	try {
		cout << list.Get(-1) << endl;
	}
	catch (SequenceException ex) {
		ex.what();
	}

	try {
		list.Get(1);
	}
	catch (SequenceException ex) {
		ex.what();
	}

	list.Append(43);

	if (list.GetLength() == 2) cout << "_TEST 6 - OK" << endl;
	else cout << "_TEST 6 - ERROR!" << endl;

	if (list.GetFirst() == 23) cout << "_TEST 7 - OK" << endl;
	else cout << "_TEST 7 - ERROR!" << endl;

	if (list.GetLast() == 43) cout << "_TEST 8 - OK" << endl;
	else cout << "_TEST 8 - ERROR!" << endl;

	try {
		if (list.Get(0) == 23) cout << "_TEST 9 - OK" << endl;
		else cout << "_TEST 9 - ERROR!" << endl;
	}
	catch (SequenceException ex) {
		ex.what();
	}

	try {
		if (list.Get(1) == 43) cout << "_TEST 10 - OK" << endl;
		else cout << "_TEST 10 - ERROR!" << endl;
	}
	catch (SequenceException ex) {
		ex.what();
	}

	try {
		list.Get(-1);
	}
	catch (SequenceException ex) {
		ex.what();
	}

	try {
		list.Get(2);
	}
	catch (SequenceException ex) {
		ex.what();
	}

	list.Prepend(53);

	if (list.GetLength() == 3) cout << "_TEST 11 - OK" << endl;
	else cout << "_TEST 11 - ERROR!" << endl;

	if (list.GetFirst() == 53) cout << "_TEST 12 - OK" << endl;
	else cout << "_TEST 12 - ERROR!" << endl;

	if (list.GetLast() == 43) cout << "_TEST 13 - OK" << endl;
	else cout << "_TEST 13 - ERROR!" << endl;

	try {
		if (list.Get(0) == 53) cout << "_TEST 14 - OK" << endl;
		else cout << "_TEST 14 - ERROR!" << endl;
	}
	catch (SequenceException ex) {
		ex.what();
	}

	try {
		if (list.Get(1) == 23) cout << "_TEST 15 - OK" << endl;
		else cout << "_TEST 15 - ERROR!" << endl;
	}
	catch (SequenceException ex) {
		ex.what();
	}

	try {
		list.Get(-1);
	}
	catch (SequenceException ex) {
		ex.what();
	}

	try {
		list.Get(3);
	}
	catch (SequenceException ex) {
		ex.what();
	}


	ListSequence<int> subList = list.GetSubsequence(1, 1);

	if (subList.GetLength() == 1) cout << "_TEST 16 - OK" << endl;
	else cout << "_TEST 16 - ERROR!" << endl;

	if (subList.GetFirst() == 23) cout << "_TEST 17 - OK" << endl;
	else cout << "_TEST 17 - ERROR!" << endl;

	if (subList.GetLast() == 23) cout << "_TEST 18 - OK" << endl;
	else cout << "_TEST 18 - ERROR!" << endl;

	subList.InsertAt(0, 1);
	subList.InsertAt(2, 3);
	subList.InsertAt(2, 5);
	subList.printAll();

	subList.Remove(3);
	subList.printAll();

	if (subList.GetLength() == 3) cout << "_TEST 19 - OK" << endl;
	else cout << "_TEST 19 - ERROR!" << endl;

	cout << "____END_TEST_ARRAY____" << endl;

}

void TestArraySequence() {
	cout << "_____BEGIN_TEST_ARRAY_____" << endl;
	ArraySequence<int> arr;

	if (arr.GetLength() == 0) cout << "_TEST 1 - OK" << endl;
	else cout << "_TEST 1 - ERROR!" << endl;

	arr.Append(23);

	if (arr.GetLength() == 1) cout << "_TEST 2 - OK" << endl;
	else cout << "_TEST 2 - ERROR!" << endl;

	if (arr.GetFirst() == 23) cout << "_TEST 3 - OK" << endl;
	else cout << "_TEST 3 - ERROR!" << endl;

	if (arr.GetLast() == 23) cout << "_TEST 4 - OK" << endl;
	else cout << "_TEST 4 - ERROR!" << endl;

	try {
		if (arr.Get(0) == 23) cout << "_TEST 5 - OK" << endl;
		else cout << "_TEST 5 - ERROR!" << endl;
	}
	catch (SequenceException ex) {
		ex.what();
	}

	try {
		cout << arr.Get(-1) << endl;
	}
	catch (SequenceException ex) {
		ex.what();
	}

	try {
		arr.Get(1);
	}
	catch (SequenceException ex) {
		ex.what();
	}

	arr.Append(43);

	if (arr.GetLength() == 2) cout << "_TEST 6 - OK" << endl;
	else cout << "_TEST 6 - ERROR!" << endl;

	if (arr.GetFirst() == 23) cout << "_TEST 7 - OK" << endl;
	else cout << "_TEST 7 - ERROR!" << endl;

	if (arr.GetLast() == 43) cout << "_TEST 8 - OK" << endl;
	else cout << "_TEST 8 - ERROR!" << endl;

	try {
		if (arr.Get(0) == 23) cout << "_TEST 9 - OK" << endl;
		else cout << "_TEST 9 - ERROR!" << endl;
	}
	catch (SequenceException ex) {
		ex.what();
	}

	try {
		if (arr.Get(1) == 43) cout << "_TEST 10 - OK" << endl;
		else cout << "_TEST 10 - ERROR!" << endl;
	}
	catch (SequenceException ex) {
		ex.what();
	}

	try {
		arr.Get(-1);
	}
	catch (SequenceException ex) {
		ex.what();
	}

	try {
		arr.Get(2);
	}
	catch (SequenceException ex) {
		ex.what();
	}

	arr.Prepend(53);

	if (arr.GetLength() == 3) cout << "_TEST 11 - OK" << endl;
	else cout << "_TEST 11 - ERROR!" << endl;

	if (arr.GetFirst() == 53) cout << "_TEST 12 - OK" << endl;
	else cout << "_TEST 12 - ERROR!" << endl;

	if (arr.GetLast() == 43) cout << "_TEST 13 - OK" << endl;
	else cout << "_TEST 13 - ERROR!" << endl;

	try {
		if (arr.Get(0) == 53) cout << "_TEST 14 - OK" << endl;
		else cout << "_TEST 14 - ERROR!" << endl;
	}
	catch (SequenceException ex) {
		ex.what();
	}

	try {
		if (arr.Get(1) == 23) cout << "_TEST 15 - OK" << endl;
		else cout << "_TEST 15 - ERROR!" << endl;
	}
	catch (SequenceException ex) {
		ex.what();
	}

	try {
		arr.Get(-1);
	}
	catch (SequenceException ex) {
		ex.what();
	}

	try {
		arr.Get(3);
	}
	catch (SequenceException ex) {
		ex.what();
	}

	ArraySequence<int> subArr = arr.GetSubsequence(1, 1);

	if (subArr.GetLength() == 1) cout << "_TEST 16 - OK" << endl;
	else cout << "_TEST 16 - ERROR!" << endl;

	if (subArr.GetFirst() == 23) cout << "_TEST 17 - OK" << endl;
	else cout << "_TEST 17 - ERROR!" << endl;

	if (subArr.GetLast() == 23) cout << "_TEST 18 - OK" << endl;
	else cout << "_TEST 18 - ERROR!" << endl;

	subArr.InsertAt(0, 1);
	subArr.InsertAt(2, 3);
	subArr.InsertAt(2, 5);
	subArr.printAll();

	subArr.Remove(5);
	subArr.printAll();


	
	if (subArr.GetLength() == 3) cout << "_TEST 19 - OK" << endl;
	else cout << "_TEST 19 - ERROR!" << endl;

	cout << "____END_TEST_ARRAY____" << endl;

}

int main() {
	ArraySequence<int> list;
	list.Append(0); list.Append(1); list.Append(2); list.Append(3); list.Append(4);
	list.printAll();
	list.Remove(5);
	list.printAll();
	//TestArraySequence();
	//TestListSequence();
	system("PAUSE");
	return 0;
}
