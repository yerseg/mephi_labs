#ifndef __TEMPLATE_IMPL__H__
#define __TEMPLATE_IMPL__H__
#include <string>
#include "Template.h"

using namespace std;

template <typename T>
void Tree<T>::insert(T data) {
	if (root == nullptr) {
		root = new TreeNode<T>;
		root->leftkid = nullptr;
		root->rightkid = nullptr;
		root->centrkid = nullptr;
		root->data = data;
		root->kids = 0;
	}
	else {
		TreeNode<T> *curr = root;
		int n(1), side(0), levelsize(0), range(1), number = root->kids + 2;

		while ((3 * n - 1) <= number) {
			n = 3 * n - 1;
			range = 3 * range;
		}
		levelsize = n;

		while (1) {
			if (number < (levelsize + range / 3)) {
				curr->kids++;
				if (range != 3) {
					curr = curr->leftkid;
					range = range / 3;
				}
				else {
					side = 0;
					break;
				}
			}
			else if ((number >= (levelsize + range / 3)) && (number<(levelsize + range * 2 / 3))) {
				curr->kids++;
				if (range != 3) {
					curr = curr->centrkid;
					range = range / 3;
					levelsize += range;
				}
				else {
					side = 1;
					break;
				}
			}
			else {
				curr->kids++;
				if (range != 3) {
					curr = curr->rightkid;
					range = range / 3;
					levelsize = levelsize + 2 * range;
				}
				else {
					side = 2;
					break;
				}
			}
		}
		TreeNode<T> *newnode = new TreeNode<T>;
		newnode->kids = 0;
		newnode->leftkid = nullptr;
		newnode->rightkid = nullptr;
		newnode->centrkid = nullptr;
		newnode->data = data;

		if (side == 0) {
			curr->leftkid = newnode;
		}
		else if (side == 1) {
			curr->centrkid = newnode;
		}
		else {
			curr->rightkid = newnode;
		}
	}
}

template <typename T>
void Tree<T>::destroyTree(TreeNode<T> *node) {
	if (node != nullptr) {
		destroyTree(node->leftkid);
		destroyTree(node->rightkid);
		destroyTree(node->centrkid);
		delete node;
	}
}

template <typename T>
void Tree<T>::RCLrootPrint(TreeNode<T> *node) { 
	if (node != nullptr) {
		RCLrootPrintKids(node->rightkid);
		RCLrootPrintKids(node->centrkid);
		RCLrootPrintKids(node->leftkid);
		cout << node->data;
	}
}

template <typename T>
void Tree<T>::RCLrootPrintKids(TreeNode<T> *node) {
	if (node != nullptr) {
		RCLrootPrintKids(node->rightkid);
		RCLrootPrintKids(node->centrkid);
		RCLrootPrintKids(node->leftkid);
		cout << "|" << node->data << "|";
	}
}

template <typename T>
int Tree<T>::GetValueFunction(TreeNode<void*> *node) {
	return ((int(*)(int))(node->data))(5);
}

template <typename T>
void Tree<T>::PrintValueFunction(TreeNode<void*> *node) {
	if (node != nullptr) {
		cout << GetValueFunction(node) << endl;;
		PrintValueFunction(node->leftkid);
		PrintValueFunction(node->centrkid);
		PrintValueFunction(node->rightkid);
	}
}

template <typename T>
void Tree<T>::map(TreeNode<T> *node, T value) {
	if (node != nullptr) {
		node->data = value;
		map(node->leftkid, value);
		map(node->centrkid, value);
		map(node->rightkid, value);
	}
}

template <typename T>
bool Tree<T>::check(TreeNode<string> *node) {
	if ((node->data).length() < 7) return true;
	else return false;
}

template <typename T>
bool Tree<T>::check(TreeNode<void*> *node) {
	if (GetValueFunction(node) < 10) return true;
	else return false;
}

template <typename T>
void Tree<T>::where(TreeNode<T> *node, Tree<T> *new_tree) { // УКАЗАТЕЛЬ на дерево
	if (node != nullptr) {
		if (check(node)) {
			T key = node->data;
			new_tree->insert(key);
		}
		where(node->leftkid, new_tree);
		where(node->centrkid, new_tree);
		where(node->rightkid, new_tree);
	}
}

template <typename T>
void Tree<T>::MergeTrees(TreeNode<T> *node_of_1st_tree, Tree<T> *second_tree) {
	if (node_of_1st_tree != nullptr) {
		second_tree->insert(node_of_1st_tree->data);
		MergeTrees(node_of_1st_tree->leftkid, second_tree);
		MergeTrees(node_of_1st_tree->rightkid, second_tree);
		MergeTrees(node_of_1st_tree->centrkid, second_tree);
	}
}

template <typename T>
void Tree<T>::SubtreeExtraction(TreeNode<T> *node, T value, Tree<T> *res_tree, int *flag) {
	if (node != nullptr && *flag == 0) {
		if (node->data == value) {
			res_tree->root = node;
			*flag = 1;
		}
		SubtreeExtraction(node->leftkid, value, res_tree, flag);
		SubtreeExtraction(node->rightkid, value, res_tree, flag);
		SubtreeExtraction(node->centrkid, value, res_tree, flag);
	}
}

template <typename T>
void Tree<T>::IfElementContain(TreeNode<T> *node, T value, bool* check_ptr) {
	if (node != nullptr && *check_ptr == false) {
		if (node->data == value) {
			*check_ptr = true;
		}
		IfElementContain(node->leftkid, value, check_ptr);
		IfElementContain(node->rightkid, value, check_ptr);
		IfElementContain(node->centrkid, value, check_ptr);
	}
}

template <typename T>
void Tree<T>::CompareTrees(TreeNode<T> *first, TreeNode<T> *second, bool* if_same) {
	if (second != nullptr) {
		if ((first == nullptr) || (first->data != second->data)) 
			*if_same = 0;

		if ((*if_same != 0) && (first != nullptr)) {
			CompareTrees(first->leftkid, second->leftkid, if_same);
			CompareTrees(first->rightkid, second->rightkid, if_same);
			CompareTrees(first->rightkid, second->centrkid, if_same);
		}
	}

}

template <typename T>
void Tree<T>::IfTreeContain(TreeNode<T> *big_node, TreeNode<T> *small_node, bool *check_ptr, bool *if_same) {
	if (big_node != nullptr) {
		if ((big_node->data == small_node->data) && (!(*check_ptr))) {
			CompareTrees(big_node, small_node, if_same);
			if (*if_same) {
				*check_ptr = 1;
			}
		}
		if (!(*check_ptr)) {
			IfTreeContain(big_node->leftkid, small_node, check_ptr, if_same);
			IfTreeContain(big_node->centrkid, small_node, check_ptr, if_same);
			IfTreeContain(big_node->rightkid, small_node, check_ptr, if_same);
		}
	}
}

template <typename T>
void Tree<T>::PrintMentionedLevel(TreeNode<T> *node, int level) {
	if (node != nullptr) {
		PrintMentionedLevel(node->leftkid, level - 1);
		if (level == 0) cout << node->data << " ";
		PrintMentionedLevel(node->centrkid, level - 1);
		if (level == 0) cout << node->data << " ";
		PrintMentionedLevel(node->rightkid, level - 1);
	}
}

template <typename T>
Tree<T>::Tree() {
	root = nullptr;
}

template <typename T>
Tree<T>::~Tree() {
	destroyTree(root);
}

template <typename T>
TreeNode<T>* Tree<T>::GetRoot() {
	return root;
}

template <typename T>
int Tree<T>::GetKids() {
	return root->kids;
}

template <typename T>
void Tree<T>::RCLrootPrint() { // КПЛ обход
	cout << "321K обход ->" << endl;
	RCLrootPrint(root);
	cout << endl;
	cout << endl;
}

template <typename T>
void Tree<T>::SetTree() {  // для строк
	cout << "Введите количество элементов в дереве: ";
	int amount_of_elements;
	do { 
		cin >> amount_of_elements; 
	} while (amount_of_elements < 1);
	cout << "Введите " << amount_of_elements << " строки: " << endl;
	for (int i = 0; i < amount_of_elements; i++) {
		cout << "  " << i + 1 << ": ";
		T key; cin >> key;
		this->insert(key);
	}
}

template <typename T>
void Tree<T>::SetFunctionTree(void **ptr) { // для функций
	cout << "Список функций: " << endl;
	cout << " 1: x * 2\n 2: x^3\n 3: x + 1\n 4: x^2\n 5: x + 2\n";
	cout << "Введите количество элементов в дереве: ";
	int amount_of_elements;
	do { cin >> amount_of_elements; } while (amount_of_elements < 1);
	cout << "Выберите " << amount_of_elements << " функций из списка выше " << endl;
	for (int i = 0; i < amount_of_elements; i++) {
		int func_number;
		do {
			cout << "  " << i + 1 << ": ";
			cin >> func_number;
		} while (func_number != 1 && func_number != 2 && func_number != 3 && func_number != 4 && func_number != 5);
		this->insert(ptr[func_number - 1]);
	}
}

template <typename T>
void Tree<T>::map(T value) {
	map(root, value);
}

template <typename T>
void Tree<T>::PrintValueFunction() {
	PrintValueFunction(root);
}

template <typename T>
void Tree<T>::where(Tree<T> *new_tree) {
	where(root, new_tree);
}

template <typename T>
void Tree<T>::MergeTrees(Tree<T> *second_tree) { //
	MergeTrees(root, second_tree);
}

template <typename T>
void Tree<T>::SubtreeExtraction(T value, Tree<T> *res_tree) {
	int *flag = new int; *flag = 0;
	SubtreeExtraction(root, value, res_tree, flag);
	delete flag;
}

template <typename T>
bool Tree<T>::IfElementContain(T value) {
	bool* check_ptr = new bool; *check_ptr = false;
	IfElementContain(root, value, check_ptr);
	bool check = *check_ptr;
	delete check_ptr;
	return check;
}

template <typename T>
bool Tree<T>::IfTreeContain(Tree<T> *smallTree) {
	bool *check_ptr = new bool; *check_ptr = 0;
	bool *if_same = new bool; *if_same = 1;
	IfTreeContain(root, smallTree->root, check_ptr, if_same);
	delete if_same;
	bool to_return = *check_ptr;
	delete check_ptr;
	return to_return;
}

template <typename T>
void Tree<T>::PrintByLevels() {
	int max_level = 0;
	while (pow(3, max_level) - 3 <= root->kids) 
		max_level++;
	cout << "Печать по уровням -> " << endl;
	for (int i = 0; i < max_level; i++) {
		PrintMentionedLevel(root, i);
		cout << endl;
	}
}
#endif /* __TEMPLATE_IMPL_H__ */
