#ifndef __TEMPLATE__H__
#define __TEMPLATE__H__
#include <string>

using namespace std;

typedef struct students_t {
	char* firstName;
	char* middleName;
	char* lastName;
	int rate;
	int yearofBirth;
} Student;

typedef struct lecturers_t {
	char* firstName;
	char* middleName;
	char* lastName;
	unsigned short grade;
	int yearofBirth;
} Lecturer;

template <typename T>
struct TreeNode {
	T data;
	int kids;
	TreeNode *leftkid;
	TreeNode *rightkid;
	TreeNode *centrkid;
};

template <typename T>
class Tree {
	TreeNode<T> *root;

	void destroyTree(TreeNode<T> *node);

	void RCLrootPrint(TreeNode<T> *node);

	void RCLrootPrintKids(TreeNode<T> *node);

	int GetValueFunction(TreeNode<void*> *node);

	void PrintValueFunction(TreeNode<void*> *node);

	// 1. map
	void map(TreeNode<T> *node, T value);
	
	// check для строк
	bool check(TreeNode<string> *node);

	// check для функций
	bool check(TreeNode<void*> *node);

	// 2. where
	void where(TreeNode<T> *node, Tree<T> *new_tree);

	// 3. слияние
	void MergeTrees(TreeNode<T> *node_of_1st_tree, Tree<T> *second_tree);

	// 4. извлечение поддерева по заданному элементу
	void SubtreeExtraction(TreeNode<T> *node, T value, Tree<T> *res_tree, int *flag);

	// 5. поиск элемента на вхождение
	void IfElementContain(TreeNode<T> *node, T value, bool* check_ptr);

	// 6. поиск дерева на вхождение
	void IfTreeContain(TreeNode<T> *big_node, TreeNode<T> *small_node, bool *check_ptr, bool *if_same);

	void PrintMentionedLevel(TreeNode<T> *node, int level);

public:

	void CompareTrees(TreeNode<T> *first, TreeNode<T> *second, bool* if_same);

	Tree();

	~Tree();

	TreeNode<T> *GetRoot();

	int GetKids();

	void insert(T data);

	void RCLrootPrint();

	void SetTree();

	void SetFunctionTree(void **ptr);

	void map(T value);

	void PrintValueFunction();

	void where(Tree<T> *new_tree);

	void MergeTrees(Tree<T> *second_tree);

	void SubtreeExtraction(T value, Tree<T> *res_tree);

	bool IfElementContain(T value);

	bool IfTreeContain(Tree<T> *smallTree);

	void PrintByLevels();

};
#include "Template_Impl.h"

#endif /* __TEMPLATE__H__ */
