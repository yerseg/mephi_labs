#ifndef BTREE_H
#define BTREE_H

#include "Student.h"

struct foundPare {
	int index;
	void *node;
};

template <typename T>
class BTreeNode {
private:
	T * keys;
	int t;
	BTreeNode<T> **C;
	int n;
	bool leaf;
public:
	BTreeNode(int _t, bool _leaf);
	void traverse();
	foundPare search(T k);
	int findKey(T k);
	void insertNonFull(T k);
	void splitChild(int i, BTreeNode<T> *y);
	
    template <typename>
	friend class BTree;
};

template <typename T>
class BTree {
private:
	BTreeNode<T> *root;
	int t;
public:
	BTree(int _t) {
		root = NULL;
		t = _t;
	}
	 
	void traverse() {
		if (root != NULL) root->traverse();
	}

	foundPare search(T k) {
		return root->search(k);
	}
    
	void insert(T k);
};

template <typename T>
BTreeNode<T>::BTreeNode(int t1, bool leaf1) {
	t = t1;
	leaf = leaf1;
	keys = new T[2 * t - 1];
	C = new BTreeNode<T> *[2 * t];
	n = 0;
}

template <typename T>
int BTreeNode<T>::findKey(T k) {
	int idx = 0;
	while (idx < n && keys[idx] < k)
		++idx;
	return idx;
}

template <typename T>
void BTree<T>::insert(T k) {
	if (root == NULL) {
		root = new BTreeNode<T>(t, true);
		root->keys[0] = k;
		root->n = 1;
	}
	else {
		if (root->n == 2 * t - 1) {
			BTreeNode<T> *s = new BTreeNode<T>(t, false);

			s->C[0] = root;

			s->splitChild(0, root);

			int i = 0;
			if (s->keys[0] < k)
				i++;
			s->C[i]->insertNonFull(k);

			root = s;
		}
		else
			root->insertNonFull(k);
	}
	return;
}


template <typename T>
void BTreeNode<T>::insertNonFull(T k) {
	int i = n - 1;
	if (leaf == true) {
		while (i >= 0 && keys[i] > k) {
			keys[i + 1] = keys[i];
			i--;
		}
		keys[i + 1] = k;
		n = n + 1;
	}
	else {
		while (i >= 0 && keys[i] > k)
			i--;

		if (C[i + 1]->n == 2 * t - 1) {
			splitChild(i + 1, C[i + 1]);

			if (keys[i + 1] < k)
				i++;
		}
		C[i + 1]->insertNonFull(k);
	}
}


template <typename T>
void BTreeNode<T>::splitChild(int i, BTreeNode *y) {
	BTreeNode *z = new BTreeNode(y->t, y->leaf);
	z->n = t - 1;

	for (int j = 0; j < t - 1; j++)
		z->keys[j] = y->keys[j + t];

	if (y->leaf == false) {
		for (int j = 0; j < t; j++)
			z->C[j] = y->C[j + t];
	}

	y->n = t - 1;

	for (int j = n; j >= i + 1; j--)
		C[j + 1] = C[j];

	C[i + 1] = z;

	for (int j = n - 1; j >= i; j--)
		keys[j + 1] = keys[j];

	keys[i] = y->keys[t - 1];

	n = n + 1;
}

template <typename T>
void BTreeNode<T>::traverse() {
	int i;
	for (i = 0; i < n; i++) {
		if (leaf == false)
			C[i]->traverse();
		cout <<  keys[i] << endl;
	}

	if (leaf == false)
		C[i]->traverse();
}

template <typename T>
foundPare BTreeNode<T>::search(T k) {
	int i = 0;
	while (i < n && k > keys[i])
		i++;

	if (keys[i] == k) {
		foundPare myPare;
		myPare.node = this;
		myPare.index = i;
		return myPare;
	}

	if (leaf == true) {
		throw ElementNotFoundException<T>(k);
	}

	return C[i]->search(k);
}

template <typename T>
class BTreeBuilder {
	int t;
public:
	BTreeBuilder(int _t) {
		t = _t;
	}
	~BTreeBuilder() {}

	BTree<Student> build(ArraySequence<Student> *array, int length) {
		BTree<Student> myBTree(t);
		Student *bufer;
		for (int i = 0; i < length; i++) {
			bufer = array->GetPointer(i);
			//bufer.set_flag(flag);
			myBTree.insert(*bufer);
		}
		return myBTree;
	}

	BTree<int> build(ArraySequence<int> *array, int length) {

		BTree<int> myBTree(t, NULL);
		int bufer;
		for (int i = 0; i < length; i++) {
			bufer = array->Get(i);
			myBTree.insert(bufer);
		}
		return myBTree;
	}

	BTree<T> build(T *array, int length) {

		BTree<T> myBTree(t);
		for (int i = 0; i < length; i++) {
			myBTree.insert(array[i]);
		}
		return myBTree;
	}
};


#endif /* BTREE_H */
