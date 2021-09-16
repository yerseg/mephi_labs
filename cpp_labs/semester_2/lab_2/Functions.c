#include <malloc.h>
#include <stdio.h>
#include <locale.h>
#include "Header.h"
#define TRUE 1
#define FALSE 0

//Хранимые функции
int func1(int n) {
	return n * n;
}

int func2(int n) {
	if (n == 0 || n == 1)
		return 1;
	return n * func2(n - 1);
}

int func3(int n) {
	return n + 1;
}

int func4(int n) {
	return 2 * n;
}

int func5(int n) {
	if (n >= 0)
		return TRUE;
	if (n < 0)
		return FALSE;
	else
		return FALSE;
}

//Функции для очереди

List* list_alloc() {
	return (List*)malloc(sizeof(List));
}

Queue* queue_alloc() {
	return (Queue*)malloc(sizeof(Queue));
}

String* string_alloc() {
	return (String*)malloc(sizeof(String));
}

Queue* init_queue(Queue* queue) {
	queue->head = queue->tail = NULL;
	queue->size = 0;
	return queue;
}

void push(Queue* queue, void* elem) {
	List* list = list_alloc();
	list->next = queue->tail;
	queue->tail = list;
	if (list->next == NULL)
		queue->head = list;
	queue->size++;
	list->element_ptr = elem;
}

void* pop(Queue* queue) {
	void* elem = queue->head->element_ptr;
	List* list_curr = queue->tail;
	List* list_head = queue->head;
	while (list_curr->next != list_head && list_curr->next != NULL) {
		list_curr = list_curr->next;
	}
	list_curr->next = NULL;
	free(list_head);
	queue->head = list_curr;
	queue->size--;
	return elem;
}

void* string_set() {
	String* str = (String*)malloc(sizeof(String));
	str->string_size = 1;
	char c;
	str->string_ptr = (char*)malloc(sizeof(char));
	printf("Введите строку:\n");
	while ((c = getchar()) != '\n') {
		str->string_ptr = (char*)realloc(str->string_ptr, (str->string_size + 1) * sizeof(char));
		str->string_ptr[str->string_size - 1] = c;
		str->string_ptr[str->string_size] = '\0';
		str->string_size++;
	}
	return (void*)str;
}

void* function_set() {
	int n;
	printf("Укажите номер функции, которую хотите отправить в очередь(1-5)->");
	do {
		scanf_s("%i", &n);
		rewind(stdin);
		if (n > 5 || n < 1)
			printf("ОШИБКА: повторите ввод->");
	} while (n > 5 || n < 1);
	if (n == 1)
		return func1;
	if (n == 2)
		return func2;
	if (n == 3)
		return func3;
	if (n == 4)
		return func4;
	if (n == 5)
		return func5;
	else
		return NULL;
}

int out_function(void* ptr, int x) {
	int res;
	res = ((int(*)(int))ptr)(x);
	return res;
}

void out_string(void* ptr) {
	String* str = (String*)ptr;
	for (int i = 0; i < str->string_size; i++)
		putchar(str->string_ptr[i]);
	putchar('\n');
}

void string_list_set(Queue* string_queue) {
	int p, i = 0;
	printf("Укажите какое количество СТРОК добавим в очередь изначально->");
	do {
		scanf_s("%d", &p);
		rewind(stdin);
		if (p <= 0)
			printf("ОШИБКА: повторите ввод->");
	} while (p <= 0);

	rewind(stdin);
	while (i < p) {
		void* str = string_set();
		push(string_queue, str);
		i++;
	}

	do {
		printf("Будем ли ещё добавлять строки в очередь? (1 - да, 0 - нет) ->");
		do {
			scanf_s("%d", &p);
			rewind(stdin);
			if (p != 0 && p != 1)
				printf("ОШИБКА: повторите ввод->");
		} while (p != 0 && p != 1);

		if (p == 1) {
			void* str = string_set();
			push(string_queue, str);
		}
	} while (p != 0);
}

void out_list_string(Queue* string_queue) {
	int p, c, maxP, j = 0;
	printf("Введите количество СТРОК, которые будут выведены немедленно(max = %d)", string_queue->size);
	do {
		scanf_s("%d", &p);
		rewind(stdin);
		if (p > string_queue->size || p<0)
			printf("ОШИБКА: повторите ввод->");
	} while (p > string_queue->size || p<0);
	maxP = string_queue->size;
	for (int i = 0; i < p; i++) {
		void* str = pop(string_queue);
		out_string(str);
		String* q = (String*)str;
		free(q->string_ptr);
		free(q);
	}

	if (p != maxP) {
		do {
			printf("Будем ли ещё брать элементы из очереди: 1 - yes, 0 - no ->");
			do {
				scanf_s("%i", &c);
				rewind(stdin);
			} while (c != 1 && c != 0);
			if (c == 1 && string_queue->size != 0) {
				void* str = pop(string_queue);
				out_string(str);
				String* q = (String*)str;
				free(q->string_ptr);
				free(q);
			}
			else
				printf("ОШИБКА\n");
		} while (c != 0 && string_queue->size != 0);
	}
	for (int i = 0; i < string_queue->size; i++) {
		void* str = pop(string_queue);
		String* s = (String*)str;
		free(s->string_ptr);
		free(s);
	}
}

void func_list_set(Queue* func_queue) {
	int p, i = 0;
	printf("Укажите какое количество ФУНКЦИЙ добавим в очередь изначально->");
	do {
		scanf_s("%d", &p);
		rewind(stdin);
		if (p <= 0)
			printf("ОШИБКА: повторите ввод->");
	} while (p <= 0);

	while (i < p) {
		void* func = function_set();
		push(func_queue, func);
		i++;
	}

	do {
		printf("Будем ли ещё добавлять функции в очередь? (1 - да, 0 - нет) ->");
		do {
			scanf_s("%d", &p);
			rewind(stdin);
			if (p != 0 && p != 1)
				printf("ОШИБКА: повторите ввод->");
		} while (p != 0 && p != 1);
		if (p == 1) {
			void* func = function_set();
			push(func_queue, func);
		}
	} while (p != 0);
}

void out_list_func(Queue* func_queue) {
	int p, x, c, maxP, j = 0;
	printf("Введите количество ФУНКЦИЙ, которые будут выведены немедленно(max = %d)", func_queue->size);
	do {
		scanf_s("%d", &p);
		rewind(stdin);
		if (p > func_queue->size || p<0)
			printf("ОШИБКА: повторите ввод->");
	} while (p > func_queue->size || p<0);
	maxP = func_queue->size;
	for (int i = 0; i < p; i++) {
		void* func = pop(func_queue);
		printf("Введите значение для функции->");
		scanf_s("%d", &x);
		rewind(stdin);
		int res = out_function(func, x);
		printf("Function(%d) == %d\n", x, res);
	}

	if (p != maxP) {
		do {
			printf("Будем ли ещё брать элементы из очереди: 1 - yes, 0 - no ->");
			do {
				scanf_s("%i", &c);
				rewind(stdin);
			} while (c != 1 && c != 0);
			if (c == 1 && func_queue->size != 0) {
				void* func = pop(func_queue);
				printf("Введите значение для функции->");
				scanf_s("%d", &x);
				rewind(stdin);
				int res = out_function(func, x);
				printf("Function(X) == %d\n", res);
				free(func);
			}
			else
				printf("ОШИБКА\n");
		} while (c != 0 && func_queue->size != 0);
	}
	for (int i = 0; i < func_queue->size; i++) {
		void* func = pop(func_queue);
		free(func);
	}
}

void out_concate_func(Queue* queue, int func_count, int string_count) {
	int p, x, c, i, j, maxP = 0;
	printf("\nВведите количество СТРОК, которые будут выведены немедленно(max = %d)", string_count);
	do {
		scanf_s("%d", &p);
		rewind(stdin);
		if (p > string_count || p<0)
			printf("ОШИБКА: повторите ввод->");
	} while (p > string_count || p<0);
	maxP = string_count;
	for (int i = 0; i < p; i++) {
		void* str = pop(queue);
		string_count--;
		out_string(str);
	}

	if (p != maxP) {
		do {
			printf("Будем ли ещё брать элементы из очереди: 1 - yes, 0 - no ->");
			do {
				scanf_s("%i", &c);
				rewind(stdin);
			} while (c != 1 && c != 0);
			if (c == 1 && string_count != 0) {
				void* str = pop(queue);
				string_count--;
				out_string(str);
			}
			else
				printf("ОШИБКА\n");
		} while (c != 0 && string_count != 0);
	}
	for (int i = 0; i < string_count; i++) {
		void* str = pop(queue);
		String* s = (String*)str;
		free(s->string_ptr);
		free(s);
	}

	printf("\nВведите количество ФУНКЦИЙ, которые будут выведены немедленно(max = %d)", func_count);
	do {
		scanf_s("%d", &p);
		rewind(stdin);
		if (p > func_count || p<0)
			printf("ОШИБКА: повторите ввод->");
	} while (p > func_count || p<0);
	maxP = func_count;
	for (i = 0; i < p; i++) {
		void* func = pop(queue);
		func_count--;
		printf("Введите значение для функции->");
		scanf_s("%d", &x);
		rewind(stdin);
		int res = out_function(func, x);
		printf("\nFunction(%d) == %d\n", x, res);
	}

	if (p != maxP) {
		do {
			printf("Будем ли ещё брать элементы из очереди: 1 - yes, 0 - no ->");
			do {
				scanf_s("%i", &c);
				rewind(stdin);
			} while (c != 1 && c != 0);
			if (c == 1 && func_count != 0) {
				void* func = pop(queue);
				func_count--;
				printf("Введите значение для функции->");
				scanf_s("%d", &x);
				rewind(stdin);
				int res = out_function(func, x);
				printf("\nFunction(X) == %d\n", res);
			}
			else
				printf("ОШИБКА\n");
		} while (c != 0 && func_count != 0);
	}
}

void out_concate_string(Queue* queue, int string_count, int func_count) {
	int p, x, c, i, maxP, j = 0;

	printf("\nВведите количество ФУНКЦИЙ, которые будут выведены немедленно(max = %d)", func_count);
	do {
		scanf_s("%d", &p);
		rewind(stdin);
		if (p > func_count || p<0)
			printf("ОШИБКА: повторите ввод->");
	} while (p > func_count || p<0);
	maxP = func_count;
	for (i = 0; i < p; i++) {
		void* func = pop(queue);
		func_count--;
		printf("Введите значение для функции->");
		scanf_s("%d", &x);
		rewind(stdin);
		int res = out_function(func, x);
		printf("\nFunction(%d) == %d\n", x, res);
	}

	if (p != maxP) {
		do {
			printf("Будем ли ещё брать элементы из очереди: 1 - yes, 0 - no ->");
			do {
				scanf_s("%i", &c);
				rewind(stdin);
			} while (c != 1 && c != 0);
			if (c == 1 && func_count != 0) {
				void* func = pop(queue);
				func_count--;
				printf("Введите значение для функции->");
				scanf_s("%d", &x);
				rewind(stdin);
				int res = out_function(func, x);
				printf("\nFunction(X) == %d\n", res);
			}
			else
				printf("ОШИБКА\n");
		} while (c != 0 && func_count != 0);
	}
	for (int i = 0; i < func_count; i++) {
		void* str = pop(queue);
		free(str);
	}

	printf("\nВведите количество СТРОК, которые будут выведены немедленно(max = %d)", string_count);
	do {
		scanf_s("%d", &p);
		rewind(stdin);
		if (p > string_count || p<0)
			printf("ОШИБКА: повторите ввод->");
	} while (p > string_count || p<0);
	maxP = string_count;
	for (int i = 0; i < p; i++) {
		void* str = pop(queue);
		string_count--;
		out_string(str);
	}

	if (p != maxP) {
		do {
			printf("Будем ли ещё брать элементы из очереди: 1 - yes, 0 - no ->");
			do {
				scanf_s("%i", &c);
				rewind(stdin);
			} while (c != 1 && c != 0);
			if (c == 1 && string_count != 0) {
				void* str = pop(queue);
				string_count--;
				out_string(str);
			}
			else
				printf("ОШИБКА\n");
		} while (c != 0 && string_count != 0);
	}
	for (int i = 0; i < string_count; i++) {
		void* str = pop(queue);
		String* s = (String*)str;
		free(s->string_ptr);
		free(s);
	}
}

void GoInterface(int type, int function) {
	int con1 = FALSE, con2 = FALSE, flag1 = 0, flag = 0;
	if (type == 1) {
		Queue *func_queue = queue_alloc();
		func_queue = init_queue(func_queue);
		printf("\nФУНКЦИИ\n\n");
		func_list_set(func_queue);

		if (function == 1) {
			Queue* new_queue;
			Queue *string_queue2 = queue_alloc();
			string_queue2 = init_queue(string_queue2);
			printf("\nСТРОКИ\n\n");
			string_list_set(string_queue2);
			new_queue = concat(func_queue, string_queue2);
			printf("\nКОНКАТЕНАЦИЯ проведена\nКОНКАТЕНИРОВАННАЯ ОЧЕРЕДЬ:\n");
			out_concate_func(new_queue, func_queue->size, string_queue2->size);
			free(func_queue);
			free(string_queue2);
			free(new_queue);
		}
		if (function == 2) {
			Queue* new_func_queue;
			int p, *arr;
			printf("Введите какое количество элементов будем извлекать (max = %d)-->", func_queue->size);
			do {
				scanf_s("%d", &p);
				rewind(stdin);
				if (p > func_queue->size || p<0)
					printf("ОШИБКА: повторите ввод->");
			} while (p > func_queue->size || p<0);
			arr = index_for_extract(func_queue, p);
			new_func_queue = extract_subsequence(func_queue, arr, p);
			printf("\nИЗВЛЕЧЕНИЕ проведено:\n");
			out_list_func(new_func_queue);
			free(new_func_queue);
			free(func_queue);
		}
		if (function == 3) {
			Queue* sub_func_queue;
			int* index;
			sub_func_queue = queue_alloc();
			sub_func_queue = init_queue(sub_func_queue);
			printf("Введите ПОДПОСЛЕДОВАТЕЛЬНОСТЬ ФУНКЦИЙ\n");
			func_list_set(sub_func_queue);
			index = search_subsequence(func_queue, sub_func_queue, compare_func);
			int size = func_queue->size;
			printf("\nИСХОДНАЯ ОЧЕРЕДЬ:\n");
			out_list_func(func_queue);
			printf("\nИСКОМАЯ ПОДПОСЛЕДОВАТЕЛЬНОСТЬ:\n");
			out_list_func(sub_func_queue);
			for (int h = 0; h < size; h++) {
				if (index[h] == -1)
					flag1++;
			}
			if (flag1 == size - 1)
				printf("\nERROR 404: not found\n");
			else {
				printf("НАЙДЕНО по следующим индексам:\n");
				for (int k = 0; k < size; k++)
					printf("%d\n", index[k]);
			}
			free(index);
			free(sub_func_queue);
			free(func_queue);
		}
		else
			;
	}

	if (type == 2) {
		Queue *string_queue = queue_alloc();
		string_queue = init_queue(string_queue);
		printf("\nСТРОКИ\n\n");
		string_list_set(string_queue);

		if (function == 1) {
			Queue* new_queue;
			Queue *func_queue2 = queue_alloc();
			func_queue2 = init_queue(func_queue2);
			printf("\nФУНКЦИИ\n\n");
			func_list_set(func_queue2);
			new_queue = concat(string_queue, func_queue2);
			printf("\nКОНКАТЕНАЦИЯ проведена\nКОНКАТЕНИРОВАННАЯ ОЧЕРЕДЬ:\n");
			out_concate_func(new_queue, string_queue->size, func_queue2->size);
			free(string_queue);
			free(func_queue2);
			free(new_queue);
		}
		if (function == 2) {
			Queue* new_string_queue;
			int p, *arr;
			printf("Введите какое количество элементов будем извлекать (max = %d)-->", string_queue->size);
			do {
				scanf_s("%d", &p);
				rewind(stdin);
				if (p > string_queue->size || p<0)
					printf("ОШИБКА: повторите ввод->");
			} while (p > string_queue->size || p<0);
			arr = index_for_extract(string_queue, p);
			new_string_queue = extract_subsequence(string_queue, arr, p);
			printf("\nИЗВЛЕЧЕНИЕ проведено:\n");
			out_list_string(new_string_queue);
			free(string_queue);
			free(new_string_queue);
		}
		if (function == 3) {
			Queue* sub_string_queue;
			int* index;
			sub_string_queue = queue_alloc();
			sub_string_queue = init_queue(sub_string_queue);
			printf("\nВведите ПОДПОСЛЕДОВАТЕЛЬНОСТЬ СТРОК\n");
			string_list_set(sub_string_queue);
			index = search_subsequence(string_queue, sub_string_queue, compare_string);
			int size = string_queue->size;
			printf("\nИСХОДНАЯ ОЧЕРЕДЬ:\n");
			out_list_string(string_queue);
			printf("\nИСКОМАЯ ПОДПОСЛЕДОВАТЕЛЬНОСТЬ:\n");
			out_list_string(sub_string_queue);
			for (int h = 0; h < size; h++) {
				if (index[h] == -1)
					flag1++;
			}
			if (flag1 == size)
				printf("\nERROR 404: not found\n");
			else {
				printf("НАЙДЕНО по следующим индексам:\n");
				for (int k = 0; k < size; k++)
					printf("%d\n", index[k]);
			}
			free(index);
			free(sub_string_queue);
			free(string_queue);
		}
		else
			;
	}
	else
		;
}

//Функции concat, extract, search

Queue* concat(Queue* queue1, Queue* queue2) {
	Queue* new_queue = queue_alloc();
	new_queue->head = queue1->head;
	new_queue->tail = queue1->tail;
	new_queue->size = queue1->size;
	new_queue->head->next = queue2->tail;
	new_queue->head = queue2->head;
	new_queue->size = new_queue->size + queue2->size;
	return new_queue;
}

Queue* extract_subsequence(Queue* queue, int* arr, int count) {
	int p, flag;
	Queue* new_queue = queue_alloc();
	new_queue = init_queue(new_queue);
	for (int j = 0; j < count; j++) {
		List* list_curr = queue->tail;
		for (int k = 0; k < queue->size - arr[j] - 1; k++) {
			list_curr = list_curr->next;
		}
		push(new_queue, list_curr->element_ptr);
	}
	free(arr);
	return new_queue;
}

int* search_subsequence(Queue* queue, Queue* subqueue, int function(void*, void*)) {
	int flag2 = 0, p = 1, m = 0, j = 0, flag = 0, flag1;
	int* index = (int*)malloc(queue->size * sizeof(int));
	for (int z = 0; z < queue->size; z++)
		index[z] = -1;
	for (int i = 0; i < queue->size; i++) {

		List* sublist_curr = subqueue->tail;
		List* list_curr = queue->tail;

		for (int k = subqueue->size - j - 1; k > 0; k--) {
			sublist_curr = sublist_curr->next;
		}
		for (int l = queue->size - i - 1; l > 0; l--) {
			list_curr = list_curr->next;
		}

		if (function(sublist_curr->element_ptr, list_curr->element_ptr) == TRUE) {
			index[j + m] = i;
			j++;
			if (j == subqueue->size) {
				m = p * j;
				j = 0;
			}
			p++;
		}
	}
	for (int h = 0; h < queue->size; h++) {
		if (index[h] != -1)
			flag++;
	}
	flag1 = flag % subqueue->size;
	if (flag1 != 0 && flag<subqueue->size)
		for (int z = 0; z < queue->size; z++)
			index[z] = -1;
	return index;
}

int compare_string(void* str1, void* str2) {
	String* string1 = (String*)str1;
	String* string2 = (String*)str2;
	if (string1->string_size != string2->string_size)
		return FALSE;
	for (int i = 0; i < string1->string_size; i++) {
		if (string1->string_ptr[i] != string2->string_ptr[i])
			return FALSE;
	}
	return TRUE;
}

int compare_func(void* f1, void* f2) {
	if (f1 == f2)
		return TRUE;
	else
		return FALSE;
}

int* index_set(Queue* queue, int p) {
	int s, i = 0;
	int* arr = (int*)malloc(p * sizeof(int));
	printf("Введите индекс %d-го элемента, учитывая 0-ой элемент (голова очереди)-->", i);
	do {
		scanf_s("%d", &s);
		rewind(stdin);
		if (s >= queue->size || s < 0)
			printf("ОШИБКА: повторите ввод->");
	} while (s >= queue->size || s < 0);
	arr[i] = s;

	for (i = 1; i < p; i++) {
		printf("Введите индекс %d-го элемента, учитывая 0-ой элемент (голова очереди)-->", i);
		do {
			scanf_s("%d", &s);
			rewind(stdin);
			if (s >= queue->size || s < 0 || arr[i - 1] >= s)
				printf("ОШИБКА: повторите ввод->");
		} while (s >= queue->size || s < 0 || arr[i - 1] >= s);
		arr[i] = s;
		if (s == queue->size - 1 && i != p - 1) {
			for (int j = i; j < p; j++) {
				arr[j] = -1;
			}
			i = 2 * p;
		}
	}
	return arr;
}

int* index_for_extract(Queue* queue, int count) {
	int flag, *arr;
	do {
		arr = index_set(queue, count);
		for (int l = 0; l < count; l++) {
			if (arr[l] == -1)
				flag = TRUE;
			else
				flag = FALSE;
		}
		if (flag == TRUE) {
			printf("ОШИБКА: повторите ввод\n");
		}
	} while (flag == TRUE);
	return arr;
}
