#include <malloc.h>
#include <stdio.h>
#include <locale.h>
#include "Header.h"
#define TRUE 1
#define FALSE 0

void Testing() {
	int flag1, flag2, flag3;
	flag1 = concat_test();
	flag2 = extract_test();
	flag3 = search_test();
	if (flag1 == flag2 == flag3 == TRUE)
		printf("\nÒÅÑÒÈÐÎÂÀÍÈÅ çàâåðøåíî: âñå ôóíêöèè ðàáîòàþò ÊÎÐÐÅÊÒÍÎ\n\n");
	else {
		if (flag1 != TRUE)
			printf("\nÒÅÑÒÈÐÎÂÀÍÈÅ çàâåðøåíî: ÎØÈÁÊÀ â êîíêàòåíàöèè\n");
		if (flag2 != TRUE)
			printf("\nÒÅÑÒÈÐÎÂÀÍÈÅ çàâåðøåíî: ÎØÈÁÊÀ â èçâëå÷åíèè\n");
		if (flag3 != TRUE)
			printf("\nÒÅÑÒÈÐÎÂÀÍÈÅ çàâåðøåíî: ÎØÈÁÊÀ â ïîèñêå\n");
		else
			;
	}
}

int concat_test() {
	Queue *func_queue = queue_alloc();
	func_queue = init_queue(func_queue);
	Queue* new_queue;
	Queue *string_queue = queue_alloc();
	string_queue = init_queue(string_queue);

	for (int i = 1; i < 11; i++) {
		String* str = (String*)malloc(sizeof(String));
		str->string_size = 1;
		str->string_ptr = (char*)malloc(sizeof(char));
		for(int j = 0; j<11; j++) {
			str->string_ptr = (char*)realloc(str->string_ptr, (str->string_size + 1) * sizeof(char));
			str->string_ptr[str->string_size - 1] = 'a' + (j%i);
			str->string_ptr[str->string_size] = '\0';
			str->string_size++;
		}
		push(string_queue, str);
	}

	for (int i = 0; i < 5; i++) {
		if (i == 1)
			push(func_queue, func5);
		if (i == 2)
			push(func_queue, func3);
		if (i == 3)
			push(func_queue, func4);
		if (i == 4)
			push(func_queue, func1);
		if (i == 5)
			push(func_queue, func2);
		else
			;
	}
	new_queue = concat(func_queue, string_queue);
	List* current1 = new_queue->tail;
	List* current2 = string_queue->tail;
	List* current3 = func_queue->tail;
	int flag = TRUE;
	for (int k = 0; k < new_queue->size; k++) {
		if (k < new_queue->size - string_queue->size) {
			if (current1 != current3) 
				flag = FALSE;
			current1 = current1->next;
			current3 = current3->next;
		}
		if (k < new_queue->size && k >= new_queue->size - string_queue->size) {
			if (current1 != current2) 
				flag = FALSE;
			current1 = current1->next;
			current2 = current2->next;
		}
	}
	return flag;
	for (int p = 0; p < new_queue->size; p++) {
		void* d = pop(new_queue);
	}
	free(func_queue);
	free(string_queue);
	free(new_queue);
}

int extract_test() {
	Queue *func_queue = queue_alloc();
	func_queue = init_queue(func_queue);
	Queue* new_func_queue;
	for (int i = 0; i < 5; i++) {
		if (i == 0)
			push(func_queue, func5);
		if (i == 1)
			push(func_queue, func3);
		if (i == 2)
			push(func_queue, func4);
		if (i == 3)
			push(func_queue, func1);
		if (i == 4)
			push(func_queue, func2);
		else
			;
	}

	int* arr = malloc(3 * sizeof(int));
	int flag1 = TRUE;
	arr[0] = 1; arr[1] = 3; arr[2] = 4;
	new_func_queue = extract_subsequence(func_queue, arr, 3);
	void* f = pop(new_func_queue);
	if (f != func3)
		flag1 = FALSE;
	f = pop(new_func_queue);
	if (f != func1)
		flag1 = FALSE;
	f = pop(new_func_queue);
	if (f != func2)
		flag1 = FALSE;
	free(new_func_queue);
	free(func_queue);

	Queue *string_queue = queue_alloc();
	string_queue = init_queue(string_queue);
	Queue* new_string_queue;
	String** str_arr = (String**)malloc(6 * sizeof(String*));
	for (int i = 1; i < 7; i++) {
		String* str = (String*)malloc(sizeof(String));
		str->string_size = 1;
		str->string_ptr = (char*)malloc(sizeof(char));
		for (int j = 0; j<11; j++) {
			str->string_ptr = (char*)realloc(str->string_ptr, (str->string_size + 1) * sizeof(char));
			str->string_ptr[str->string_size - 1] = 'a' + (j%i);
			str->string_ptr[str->string_size] = '\0';
			str->string_size++;
		}
		push(string_queue, str);
		str_arr[i-1] = str;
	}

	int* arr2 = malloc(3 * sizeof(int));
	int flag2 = TRUE;
	arr2[0] = 1; arr2[1] = 3; arr2[2] = 4;
	new_string_queue = extract_subsequence(string_queue, arr2, 3);
	void* s = pop(new_string_queue);
	if (s != str_arr[1])
		flag2 = FALSE;
	s = pop(new_string_queue);
	if (s != str_arr[3])
		flag2 = FALSE;
	s = pop(new_string_queue);
	if (s != str_arr[4])
		flag2 = FALSE;
	for (int i = 0; i < 6; i++) {
		free(str_arr[i]->string_ptr);
		free(str_arr[i]);
	}
	free(str_arr);
	free(new_string_queue);
	free(string_queue);
	if (flag1 == flag2 == TRUE)
		return TRUE;
	else
		return FALSE;
}

int search_test() {
	Queue *func_queue = queue_alloc();
	func_queue = init_queue(func_queue);
	Queue* sub_func_queue;
	int* index;
	sub_func_queue = queue_alloc();
	sub_func_queue = init_queue(sub_func_queue);

	for (int i = 0; i < 5; i++) {
		if (i == 0)
			push(func_queue, func5);
		if (i == 1)
			push(func_queue, func3);
		if (i == 2)
			push(func_queue, func4);
		if (i == 3)
			push(func_queue, func1);
		if (i == 4)
			push(func_queue, func2);
		else
			;
	}

	for (int i = 0; i < 3; i++) {
		if (i == 0)
			push(sub_func_queue, func3);
		if (i == 1)
			push(sub_func_queue, func4);
		if (i == 2)
			push(sub_func_queue, func2);
		else
			;
	}
	int index_compare[5] = {1, 2, 4, -1, -1};
	int flag1 = TRUE;
	index = search_subsequence(func_queue, sub_func_queue, compare_func);
	for (int i = 0; i < func_queue->size; i++) {
		if (index[i] != index_compare[i])
			flag1 = FALSE;
		else
			;
	}
	free(index);
	free(sub_func_queue);
	free(func_queue);

	Queue *func_queue1 = queue_alloc();
	func_queue1 = init_queue(func_queue1);
	Queue* sub_func_queue1;
	int* index1;
	sub_func_queue1 = queue_alloc();
	sub_func_queue1 = init_queue(sub_func_queue1);

	for (int i = 0; i < 5; i++) {
		if (i == 0)
			push(func_queue1, func5);
		if (i == 1)
			push(func_queue1, func3);
		if (i == 2)
			push(func_queue1, func4);
		if (i == 3)
			push(func_queue1, func1);
		if (i == 4)
			push(func_queue1, func2);
		else
			;
	}

	for (int i = 0; i < 3; i++) {
		if (i == 0)
			push(sub_func_queue1, func3);
		if (i == 1)
			push(sub_func_queue1, func5);
		if (i == 2)
			push(sub_func_queue1, func2);
		else
			;
	}
	int index_compare1[5] = { -1, -1, -1, -1, -1 };
	int flag2 = TRUE;
	index1 = search_subsequence(func_queue1, sub_func_queue1, compare_func);
	for (int i = 0; i < func_queue1->size; i++) {
		if (index1[i] != index_compare1[i])
			flag2 = FALSE;
		else
			;
	}
	free(index1);
	free(sub_func_queue1);
	free(func_queue1);
	
	Queue *string_queue = queue_alloc();
	string_queue = init_queue(string_queue);
	Queue* sub_string_queue;
	int* index3;
	sub_string_queue = queue_alloc();
	sub_string_queue = init_queue(sub_string_queue);

	for (int i = 1; i < 7; i++) {
		String* str = (String*)malloc(sizeof(String));
		str->string_size = 1;
		str->string_ptr = (char*)malloc(sizeof(char));
		for (int j = 0; j<11; j++) {
			str->string_ptr = (char*)realloc(str->string_ptr, (str->string_size + 1) * sizeof(char));
			str->string_ptr[str->string_size - 1] = 'a' + (j%i);
			str->string_ptr[str->string_size] = '\0';
			str->string_size++;
		}
		push(string_queue, str);
	}

	for (int i = 1; i < 7; i++) {
		String* str = (String*)malloc(sizeof(String));
		str->string_size = 1;
		str->string_ptr = (char*)malloc(sizeof(char));
		for (int j = 0; j<11; j++) {
			str->string_ptr = (char*)realloc(str->string_ptr, (str->string_size + 1) * sizeof(char));
			str->string_ptr[str->string_size - 1] = 'a' + (j%i);
			str->string_ptr[str->string_size] = '\0';
			str->string_size++;
		}
		push(sub_string_queue, str);
	}
	int index_compare2[7] = { 0, 1, 2, 3, 4, 5, 6 };
	int flag3 = TRUE;
	index3 = search_subsequence(string_queue, sub_string_queue, compare_string);
	for (int i = 0; i < string_queue->size; i++) {
		if (index3[i] != index_compare2[i])
			flag3 = FALSE;
		else
			;
	}
	for (int i = 0; i < string_queue->size; i++) {
		void* s = pop(string_queue);
		String* str = (String*)s;
		free(str->string_ptr);
		free(str);
	}
	for (int i = 0; i < sub_string_queue->size; i++) {
		void* s = pop(sub_string_queue);
		String* str = (String*)s;
		free(str->string_ptr);
		free(str);
	}
	free(index3);
	free(sub_string_queue);
	free(string_queue);

	Queue *string_queue1 = queue_alloc();
	string_queue1 = init_queue(string_queue1);
	Queue* sub_string_queue1;
	int* index4;
	sub_string_queue1 = queue_alloc();
	sub_string_queue1 = init_queue(sub_string_queue1);

	for (int i = 1; i < 7; i++) {
		String* str = (String*)malloc(sizeof(String));
		str->string_size = 1;
		str->string_ptr = (char*)malloc(sizeof(char));
		for (int j = 0; j<11; j++) {
			str->string_ptr = (char*)realloc(str->string_ptr, (str->string_size + 1) * sizeof(char));
			str->string_ptr[str->string_size - 1] = 'a' + (j%i);
			str->string_ptr[str->string_size] = '\0';
			str->string_size++;
		}
		push(string_queue1, str);
	}

	for (int i = 1; i < 4; i++) {
		String* str = (String*)malloc(sizeof(String));
		str->string_size = 1;
		str->string_ptr = (char*)malloc(sizeof(char));
		for (int j = 0; j<11; j++) {
			str->string_ptr = (char*)realloc(str->string_ptr, (str->string_size + 1) * sizeof(char));
			str->string_ptr[str->string_size - 1] = 'a' + (i%3);
			str->string_ptr[str->string_size] = '\0';
			str->string_size++;
		}
		push(sub_string_queue1, str);
	}
	int index_compare3[7] = { -1, -1, -1, -1, -1, -1, -1 };
	int flag4 = TRUE;
	index4 = search_subsequence(string_queue1, sub_string_queue1, compare_string);
	for (int i = 0; i < string_queue1->size; i++) {
		if (index4[i] != index_compare3[i])
			flag4 = FALSE;
		else
			;
	}
	for (int i = 0; i < string_queue1->size; i++) {
		void* s = pop(string_queue1);
		String* str = (String*)s;
		free(str->string_ptr);
		free(str);
	}
	for (int i = 0; i < sub_string_queue1->size; i++) {
		void* s = pop(sub_string_queue1);
		String* str = (String*)s;
		free(str->string_ptr);
		free(str);
	}
	free(index4);
	free(sub_string_queue1);
	free(string_queue1);

	if (flag1 == flag2 == flag3 == flag4 == TRUE)
		return TRUE;
	else
		return FALSE;
}