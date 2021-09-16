#ifndef __HEADER_H__
#define __HEADER_H__

typedef struct list_t {
	void* element_ptr;
	struct list_t *next;
} List;

typedef struct queue_t {
	int size;
	struct list_t *head;
	struct list_t *tail;
} Queue;

typedef struct string_t {
	int string_size;
	char* string_ptr;
} String;

int func1(int);

int func2(int);

int func3(int);

int func4(int);

int func5(int);

List* list_alloc();

Queue* queue_alloc();

String* string_alloc();

Queue* init_queue(Queue*);

void push(Queue*, void*);

void* pop(Queue*);

void* string_set();

void* function_set();

int out_function(void*, int);

void out_string(void*);

void string_list_set(Queue*);

void out_list_string(Queue*);

void func_list_set(Queue*);

void out_list_func(Queue*);

int* index_set(Queue*, int);

int* index_for_extract(Queue*, int);

Queue* concat(Queue*, Queue*);

Queue* extract_subsequence(Queue*, int*, int);

int compare_string(void*, void*);

int compare_func(void*, void*);

int* search_subsequence(Queue*, Queue*, int function(void*, void*));

void out_concate_func(Queue*, int, int);

void out_concate_string(Queue*, int, int);

void GoInterface(int, int);

void Testing();

int concat_test();

int extract_test();

int search_test();

#endif /* _HEADER__H__ */