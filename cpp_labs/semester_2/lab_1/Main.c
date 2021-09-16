#include <stdio.h>
#include <malloc.h>
#include <locale.h>
#include "Header.h"
#define TRUE 1
#define FALSE 0

int main() {
	int q, p, stop, track, con = FALSE;
	int stud_count = 0, lect_count = 0; //количество студентов и преподавателей
	setlocale(LC_ALL, "Rus");

	printf("Будем ли тестировать функции 0 - NO/1 - YES -->");
	do {
		scanf_s("%d", &stop);
		if (stop != 0 && stop != 1)
			printf("Ошибка 002: повторите ввод->");
	} while (stop != 0 && stop != 1);
	if (stop == TRUE)
		Testing();

	Array* Lect_Arr = array_alloc(); //выделяем память под структуру Array
	Array* Stud_Arr = array_alloc();


	while (stud_count == 0 && lect_count == 0) {
		printf("Введите количество студентов->\n");
		scanf_s("%d", &stud_count);
		printf("Введите количество преподавателей->\n");
		scanf_s("%d", &lect_count);
		if (stud_count == 0 && lect_count == 0) {
			printf("Ошибка 001: количество преподавателей и/или количество студентов должно быть больше 0\n");
		}
	}

	(Array*)array_set(Lect_Arr, lect_count);
	(Array*)array_set(Stud_Arr, stud_count);

	get_lect(Lect_Arr);
	get_stud(Stud_Arr);
	Array* new_arr = array_alloc();

	printf("Будем ли применять функции 0 - НЕТ/1 - ДА -->");
	do {
		scanf_s("%d", &stop);
		if (stop != 0 && stop != 1)
			printf("Ошибка 002: повторите ввод->");
	} while (stop != 0 && stop != 1); 
	
	
	while (stop != FALSE && con != TRUE) {
		printf("Выберите с кем хотите работать: преподаватели(1), студенты(2)->\n");
		do {
			scanf_s("%d", &track);
			if (track != 1 && track != 2)
				printf("Ошибка 003: повторите ввод->");
		} while (track != 1 && track != 2);

			if (track == 1) {
				printf("Выберите функцию map(1), where(2), concat(3)->");
				do {
					scanf_s("%d", &q);
					if (q != 1 && q != 2 && q != 3)
						printf("Ошибка 003: повторите ввод->");
				} while (q != 1 && q != 2 && q != 3);

				if (q == 1) {
					printf("Выберите желаемую функцию: повысить преподавателя(1)->\n");
					do {
						scanf_s("%d", &p);
						if (p != 1)
							printf("Ошибка 003: повторите ввод->");
					} while (p != 1);

					if (p == 1)
						map(Lect_Arr, grade_change);
				}
				if (q == 2) {
					printf("Выберите желаемую функцию: фильтр профессоров(1)->\n");
					do {
						scanf_s("%d", &p);
						if (p != 1)
							printf("Ошибка 003: повторите ввод->");
					} while (p != 1);

					if (p == 1)
					where(Lect_Arr, grade_sort);
				}
				if (q == 3) {
					new_arr = concat(Lect_Arr, Stud_Arr);
					con = TRUE;
				}
			}
			if (track == 2) {
				printf("Выберите функцию map(1), where(2), concat(3)->");
				do {
					scanf_s("%d", &q);
					if (q != 1 && q != 2 && q != 3)
						printf("Ошибка 003: повторите ввод->");
				} while (q != 1 && q != 2 && q != 3);

				if (q == 1) {
					printf("Выберите желаемую функцию: обнулить год рождения(1)->\n");
					scanf_s("%d", &p);
					if (p == 1)
						map(Stud_Arr, No_Birthday_Stud);
				}
				if (q == 2) {
					printf("Выберите желаемую функцию: фильтр по возрасту до 21(1)->\n");
					do {
						scanf_s("%d", &p);
						if (p != 1)
							printf("Ошибка 003: повторите ввод->");
					} while (p != 1);

					if (p == 1)
					where(Stud_Arr, age_sort_stud);
				}
				if (q == 3) {
					new_arr = concat(Lect_Arr, Stud_Arr);
					con = TRUE;
				}
			}
			if (con == FALSE) {
				printf("Будем ли применять функции 0/1->");
				do {
					scanf_s("%d", &stop);
					if (stop != 0 && stop != 1)
						printf("Ошибка 002: повторите ввод->");
				} while (stop != 0 && stop != 1);
			}
			else
				;
	}
	
	if (con == FALSE) {
		out(Lect_Arr, Stud_Arr);
	}
	if (con == TRUE) {
		printf("\n\nДО КОНКАТЕНАЦИИ\n\n");
		out(Lect_Arr, Stud_Arr);
		printf("\n\nПОСЛЕ КОНКАТЕНАЦИИ\n\n");
		lect_count = Lect_Arr->elements_count;
		stud_count = Stud_Arr->elements_count;
		out_concate(new_arr, lect_count, stud_count);
	}

	if (con == FALSE) {
		free_Lecturer(Lect_Arr);
		free_Student(Stud_Arr);
		free(new_arr);
	}
	if (con == TRUE) {
		free_concate(new_arr, lect_count, stud_count);
		free(Lect_Arr);
		free(Stud_Arr);
	} 
	
	system("PAUSE");
	return 0;
}