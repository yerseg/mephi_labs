#include <stdio.h>
#include <malloc.h>
#include <locale.h>
#include "Header.h"
#define TRUE 1
#define FALSE 0

void Testing() {
	int flag[5];
	int stud_count = 3, lect_count = 3; //количество студентов и преподавателей
	setlocale(LC_ALL, "Rus");

	Array* Lect_Arr = array_alloc(); //выделяем память под структуру Array
	Array* Stud_Arr = array_alloc();

	(Array*)array_set(Lect_Arr, lect_count);
	(Array*)array_set(Stud_Arr, stud_count);

	Lecturer* lect;
	for (int i = 0; i < Lect_Arr->elements_count; i++) {
		lect = (Lecturer*)lect_alloc();
		int k = 0, l = 0, s = 0;

		//Заполнение полей

		lect->firstName = (char*)malloc(5 * sizeof(char));
		lect->middleName = (char*)malloc(5 * sizeof(char));
		lect->lastName = (char*)malloc(5 * sizeof(char));

		lect->firstName[0] = 'a'+i;
		lect->firstName[1] = 'b'+2*i;
		lect->firstName[2] = 'c'+3*i;
		lect->firstName[3] = 'd'+4*i;
		lect->firstName[4] = '\0';

		lect->middleName[0] = 'e'+i;
		lect->middleName[1] = 'f'+2*i;
		lect->middleName[2] = 'g'+3*i;
		lect->middleName[3] = 'h'+4*i;
		lect->middleName[4] = '\0';

		lect->lastName[0] = 'i'+i;
		lect->lastName[1] = 'j'+2*i;
		lect->lastName[2] = 'k'+3*i;
		lect->lastName[3] = 'l'+4*i;
		lect->lastName[4] = '\0';

		lect->id.series = 1234 + i;
		lect->id.number = 123456 + i;

		lect->yearofBirth = 1980 + i;

		lect->grade = 0+i;

		Lect_Arr->memory_ptr[i] = (void*)lect; //отправили в ячейку динмассива
	}

	Student* stud;
	for (int i = 0; i < Stud_Arr->elements_count; i++) {
		stud = (Student*)stud_alloc();
		int k = 0, l = 0, s = 0;

		//Заполнение полей

		stud->firstName = (char*)malloc(5 * sizeof(char));
		stud->middleName = (char*)malloc(5 * sizeof(char));
		stud->lastName = (char*)malloc(5 * sizeof(char));

		stud->firstName[0] = 'a' + i;
		stud->firstName[1] = 'b' + 2 * i;
		stud->firstName[2] = 'c' + 3 * i;
		stud->firstName[3] = 'd' + 4 * i;
		stud->firstName[4] = '\0';

		stud->middleName[0] = 'e' + i;
		stud->middleName[1] = 'f' + 2 * i;
		stud->middleName[2] = 'g' + 3 * i;
		stud->middleName[3] = 'h' + 4 * i;
		stud->middleName[4] = '\0';

		stud->lastName[0] = 'i' + i;
		stud->lastName[1] = 'j' + 2 * i;
		stud->lastName[2] = 'k' + 3 * i;
		stud->lastName[3] = 'l' + 4 * i;
		stud->lastName[4] = '\0';

		stud->id.series = 1234 + i;
		stud->id.number = 123456 + i;

		stud->yearofBirth = 1996 + i;

		stud->rate = 3+i;

		Stud_Arr->memory_ptr[i] = (void*)stud; //отправили в ячейку динмассива
	}

	flag[0] = test_concate(Lect_Arr, Stud_Arr);

	flag[1] = test_where_lect(Lect_Arr);

	Array* Lect_Arr1 = array_alloc();
	(Array*)array_set(Lect_Arr1, lect_count);
	Lecturer* lect1;
	for (int i = 0; i < Lect_Arr1->elements_count; i++) {
		lect1 = (Lecturer*)lect_alloc();
		int k = 0, l = 0, s = 0;

		//Заполнение полей

		lect1->firstName = (char*)malloc(5 * sizeof(char));
		lect1->middleName = (char*)malloc(5 * sizeof(char));
		lect1->lastName = (char*)malloc(5 * sizeof(char));

		lect1->firstName[0] = 'a' + i;
		lect1->firstName[1] = 'b' + 2 * i;
		lect1->firstName[2] = 'c' + 3 * i;
		lect1->firstName[3] = 'd' + 4 * i;
		lect1->firstName[4] = '\0';

		lect1->middleName[0] = 'e' + i;
		lect1->middleName[1] = 'f' + 2 * i;
		lect1->middleName[2] = 'g' + 3 * i;
		lect1->middleName[3] = 'h' + 4 * i;
		lect1->middleName[4] = '\0';

		lect1->lastName[0] = 'i' + i;
		lect1->lastName[1] = 'j' + 2 * i;
		lect1->lastName[2] = 'k' + 3 * i;
		lect1->lastName[3] = 'l' + 4 * i;
		lect1->lastName[4] = '\0';

		lect1->id.series = 1234 + i;
		lect1->id.number = 123456 + i;

		lect1->yearofBirth = 1980 + i;

		lect1->grade = 0;

		Lect_Arr1->memory_ptr[i] = (void*)lect1; //отправили в ячейку динмассива
	}

	flag[2] = test_map_lect(Lect_Arr1);

	flag[3] = test_where_stud(Stud_Arr);

	Array* Stud_Arr1 = array_alloc();
	(Array*)array_set(Stud_Arr1, stud_count);
	Student* stud1;
	for (int i = 0; i < Stud_Arr1->elements_count; i++) {
		stud1 = (Student*)stud_alloc();
		int k = 0, l = 0, s = 0;

		//Заполнение полей

		stud1->firstName = (char*)malloc(5 * sizeof(char));
		stud1->middleName = (char*)malloc(5 * sizeof(char));
		stud1->lastName = (char*)malloc(5 * sizeof(char));

		stud1->firstName[0] = 'a' + i;
		stud1->firstName[1] = 'b' + 2 * i;
		stud1->firstName[2] = 'c' + 3 * i;
		stud1->firstName[3] = 'd' + 4 * i;
		stud1->firstName[4] = '\0';

		stud1->middleName[0] = 'e' + i;
		stud1->middleName[1] = 'f' + 2 * i;
		stud1->middleName[2] = 'g' + 3 * i;
		stud1->middleName[3] = 'h' + 4 * i;
		stud1->middleName[4] = '\0';

		stud1->lastName[0] = 'i' + i;
		stud1->lastName[1] = 'j' + 2 * i;
		stud1->lastName[2] = 'k' + 3 * i;
		stud1->lastName[3] = 'l' + 4 * i;
		stud1->lastName[4] = '\0';

		stud1->id.series = 1234 + i;
		stud1->id.number = 123456 + i;

		stud1->yearofBirth = 1997 + i;

		stud1->rate = 3 + i;

		Stud_Arr1->memory_ptr[i] = (void*)stud1; //отправили в ячейку динмассива
	}

	flag[4] = test_map_stud(Stud_Arr1);
	
	if (flag[0] == FALSE || flag[1] == FALSE || flag[2] == FALSE || flag[3] == FALSE || flag[4] == FALSE) {
		if (flag[0] == FALSE)
			printf("Конкатенация: ОШИБКА\n");
		if (flag[1] == FALSE)
			printf("Where с преподавателями: ОШИБКА\n");
		if (flag[2] == FALSE)
			printf("Map с преподавателями: ОШИБКА\n");
		if (flag[3] == FALSE)
			printf("Where с студентами: ОШИБКА\n");
		if (flag[4] == FALSE)
			printf("Map с студентами: ОШИБКА\n");
	}
	else
		printf("Все функции работают КОРРЕКТНО\n");
}

int test_concate(Array* lect, Array* stud) {
	Array* new_arr = concat(lect, stud);
	if (new_arr->memory_ptr[0] == lect->memory_ptr[0] && new_arr->memory_ptr[1] == lect->memory_ptr[1] && new_arr->memory_ptr[2] == lect->memory_ptr[2] && new_arr->memory_ptr[3] == stud->memory_ptr[0] && new_arr->memory_ptr[4] == stud->memory_ptr[1] && new_arr->memory_ptr[5] == stud->memory_ptr[2])
		return TRUE;
	else
		return FALSE;
	free_concate(new_arr, lect->elements_count, stud->elements_count);
}

int test_where_lect(Array* lect) {
	int flag = 0;
	where(lect, grade_sort);
	for (int i = 0; i < lect->elements_count; i++) {
		Lecturer* lecturer = lect->memory_ptr[i];
		if (lecturer->grade == 2)
			;
		else
			flag = flag + 1;
	}
	if (flag == 0)
		return TRUE;
	else
		return FALSE;
	free_Lecturer(lect);
}

int test_map_lect(Array* lect) {
	int flag = 0;
	map(lect, grade_change);
	for (int i = 0; i < lect->elements_count; i++) {
		Lecturer* lecturer = lect->memory_ptr[i];
		if (lecturer->grade == 2)
			;
		else
			flag = flag + 1;
	}
	if (flag == 0)
		return TRUE;
	else
		return FALSE;
	free_Lecturer(lect);
}

int test_where_stud(Array* stud) {
	int flag = 0;
	where(stud, age_sort_stud);
	for (int i = 0; i < stud->elements_count; i++) {
		Student* student = stud->memory_ptr[i];
		if (2018 - student->yearofBirth > 21)
			flag = flag + 1;
	}
	if (flag == 0)
		return TRUE;
	else
		return FALSE;
	free_Student(stud);
}

int test_map_stud(Array* stud) {
	int flag = 0;
	map(stud, No_Birthday_Stud);
	for (int i = 0; i < stud->elements_count; i++) {
		Student* student = stud->memory_ptr[i];
		if (student->yearofBirth == 0)
			;
		else
			flag = flag + 1;
	}
	if (flag == 0)
		return TRUE;
	else
		return FALSE;
	free_Lecturer(stud);
}