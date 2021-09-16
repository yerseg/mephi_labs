#include <malloc.h>
#include <stdio.h>
#include <locale.h>
#include "Header.h"
#define TRUE 1
#define FALSE 0

int main() {
	setlocale(LC_ALL, "Rus");
	int track2, stop, track1, stop1 = 0, con1 = FALSE, con2 = FALSE, flag1 = 0, flag = 0;

	printf("Будем ли тестировать функции 0 - NO/1 - YES -->");
	do {
	scanf_s("%d", &stop);
	rewind(stdin);
	if (stop != 0 && stop != 1)
	printf("ОШИБКА: повторите ввод->");
	} while (stop != 0 && stop != 1);
	if (stop == TRUE)
	Testing();

	do {
		printf("Выберите с каким типом данных работаем: 1 - ФУНКЦИИ, 2 - СТРОКИ->\n");
		do {
			scanf_s("%d", &track1);
			rewind(stdin);
			if (track1 != 1 && track1 != 2)
				printf("ОШИБКА: повторите ввод->");
		} while (track1 != 1 && track1 != 2);
		printf("\nВыберите функцию concat(1), extract(2), search(3)-->\n");
		do {
			scanf_s("%d", &track2);
			rewind(stdin);
			if (track2 != 1 && track2 != 2 && track2 != 3)
				printf("ОШИБКА: повторите ввод->");
		} while (track2 != 1 && track2 != 2 && track2 != 3);

		GoInterface(track1, track2);
		
		printf("\nРАБОТА ЗАВЕРШЕНА\n\nПРОДОЛЖИТЬ работу программы? (1 - да, 0 - нет)-->");
		do {
			scanf_s("%d", &stop);
			rewind(stdin);
			if (stop != TRUE && stop != FALSE)
				printf("ОШИБКА: повторите ввод->");
		} while (stop != TRUE && stop != FALSE);
	} while (stop == TRUE);

	system("PAUSE");
	return 0;
}
