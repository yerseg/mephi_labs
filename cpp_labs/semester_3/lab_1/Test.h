#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include "Sequence.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include "Sorters.h"
#include "Help_Func.h"

using namespace std;

void Test_Sort() {
	cout << "ÇÀÏÓÑÊ ïðîñòîãî ÒÅÑÒÈÐÎÂÀÍÈß" << endl;

	bool flag1 = false, flag2 = false;
	Sorter<int> sort;
	ListSequence<int> test_arr;

	test_arr.Append(239);
	test_arr.Append(477);
	test_arr.Append(0);
	test_arr.Append(25);
	test_arr.Append(79);
	test_arr.Append(1098);

	ListSequence<int> test_arr2 = test_arr;

	cout << "ÑÎÐÒÈÐÎÂÊÀ ÂÑÒÀÂÊÀÌÈ" << endl;
	sort.InsectionSort(&test_arr);
	if (test_arr.Get(0) == 0 && test_arr.Get(1) == 25 && test_arr.Get(2) == 79 && test_arr.Get(3) == 239 && test_arr.Get(4) == 477 && test_arr.Get(5) == 1098)
		flag1 = true;

	cout << "ÁÛÑÒÐÀß ÑÎÐÒÈÐÎÂÊÀ" << endl;
	sort.QuickSort(&test_arr2);
	if (test_arr2.Get(0) == 0 && test_arr2.Get(1) == 25 && test_arr2.Get(2) == 79 && test_arr2.Get(3) == 239 && test_arr2.Get(4) == 477 && test_arr2.Get(5) == 1098)
		flag2 = true;

	if (flag1 && flag2)
		cout << "ÎÁÅ ÑÎÐÒÈÐÎÂÊÈ ÐÀÁÎÒÀÞÒ ÂÅÐÍÎ" << endl;
	else if (!flag1 && flag2)
		cout << "ÎØÈÁÊÀ Â ÑÎÐÒÈÐÎÂÊÅ ÂÑÒÀÂÊÀÌÈ" << endl;
	else if (flag1 && !flag2)
		cout << "ÎØÈÁÊÀ Â ÁÛÑÒÐÎÉ ÑÎÐÒÈÐÎÂÊÅ" << endl;
	else
		cout << "ÎÁÅ ÑÎÐÒÈÐÎÂÊÈ ÐÀÁÎÒÀÞÒ ÍÅÏÐÀÂÈËÜÍÎ" << endl;
}

#endif /* TEST_H */
