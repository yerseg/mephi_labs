#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "ArraySequence.h"
#include "ListSequence.h"
#include "Sequence.h"
#include "Help_Func.h"
#include "Sorters.h"

template <typename T>
class UserInterface {
private:
	unsigned int mode, seq, flag1, flag2, flag3;
public:
	UserInterface() {};
	void Interface();
	void GoInterface();
};

template <typename T>
void UserInterface<T>::Interface() {
	int mode_, seq_, flag1_, flag2_, flag3_, flag;
	do {
		do {
			cout << "Âûáåðèòå ðåæèì ðàáîòû: ÀÂÒÎÌÀÒÈ×ÅÑÊÈÉ (0) èëè ÐÓ×ÍÎÉ (1) --> " << endl;
			while (!(cin >> mode_)) {
				cin.clear();
				cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
				while (cin.get() != '\n') continue;
			}
			if (mode_ != 0 && mode_ != 1)
				cout << "ERROR: ïîâòîðèòå ââîä-->";
		} while (mode_ != 0 && mode_ != 1);

		do {
			cout << "Âûáåðèòå òèï ïîñëåäîâàòåëüíîñòè: ÌÀÑÑÈÂ (0) èëè ÑÏÈÑÎÊ (1) --> " << endl;
			while (!(cin >> seq_)) {
				cin.clear();
				cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
				while (cin.get() != '\n') continue;
			}
			if (seq_ != 0 && seq_ != 1)
				cout << "ERROR: ïîâòîðèòå ââîä-->";
		} while (seq_ != 0 && seq_ != 1);

		do {
			cout << "Áóäåì ïðîâåðÿòü êîððåêòíîñòü ñîðòèðîâîê? (0 - N, 1 - Y)" << endl;
			while (!(cin >> flag1_)) {
				cin.clear();
				cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
				while (cin.get() != '\n') continue;
			}
			if (flag1_ != 0 && flag1_ != 1)
				cout << "ERROR: ïîâòîðèòå ââîä->";
		} while (flag1_ != 0 && flag1_ != 1);

		do {
			cout << "Áóäåì ëè ñðàâíèâàòü ñîðòèðîâêè? (1 - Y, 0 - N)" << endl;
			while (!(cin >> flag2_)) {
				cin.clear();
				cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
				while (cin.get() != '\n') continue;
			}
			if (flag2_ != 0 && flag2_ != 1)
				cout << "ÎØÈÁÊÀ: ïîâòîðèòå ââîä->";
		} while (flag2_ != 0 && flag2_ != 1);

		do {
			cout << "Áóëåì ëè ïðèìåíÿòü ñîðòèðîâêè ê óæå îñòîðòèðîâàííîìó ìàññèâó è îòñîðòèðîâàííîìó â îáðàòíóþ ñòîðîíó ìàññèâó? (1 - Y, 0 - N)" << endl;
			while (!(cin >> flag3_)) {
				cin.clear();
				cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
				while (cin.get() != '\n') continue;
			}
			if (flag3_ != 0 && flag3_ != 1)
				cout << "ÎØÈÁÊÀ: ïîâòîðèòå ââîä->";
		} while (flag3_ != 0 && flag3_ != 1);

		this->mode = mode_;
		this->seq = seq_;
		this->flag1 = flag1_;
		this->flag2 = flag2_;
		this->flag3 = flag3_;

		GoInterface();

		do {
			cout << "Çàâåðøèòü ðàáîòó ïðîãðàììû? (1 - ÄÀ, 0 - ÍÅÒ) --> ";
			while (!(cin >> flag)) {
				cin.clear();
				cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
				while (cin.get() != '\n') continue;
			}
			if (flag != 0 && flag != 1)
				cout << "ERROR: ïîâòîðèòå ââîä->";
		} while (flag != 0 && flag != 1);
	} while (flag != 1 && flag == 0);
}

template <typename T>
void UserInterface<T>::GoInterface() {
	Sorter<T> sort;
	int N, flag;
	if (this->mode == 0) {
		cout << "ÀÂÒÎÌÀÒÈ×ÅÑÊÈÉ ÐÅÆÈÌ" << endl << endl;
		if (this->seq == 0) {
			cout << "ÏÎÑËÅÄÎÂÀÒÅËÜÍÎÑÒÜ --> ÌÀÑÑÈÂ" << endl << endl;
			ArraySequence<T> arr_2;
			if (this->flag1 == 1) {
				cout << "ÏÐÎÂÅÐÊÀ ÑÎÐÒÈÐÎÂÎÊ" << endl;
				ArraySequence<T> arr_1;
				do {
					cout << "Ââåäèòå êîëè÷åñòâî ýëåìåíòîâ â ìàññèâå: " << endl;
					while (!(cin >> N)) {
						cin.clear();
						cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (N < 1)
						cout << "ÎØÈÁÊÀ: ïîâòîðèòå ââîä->";
				} while (N < 1);
				Rand_Seq_Gen(&arr_1, N);

				ArraySequence<T> arr_1_ = arr_1;

				sort.InsectionSort(&arr_1);
				cout << "Ñîðòèðîâêà âñòàâêàìè: ";
				if (Test_After_Sort(&arr_1))
					cout << "TRUE" << endl;
				else
					cout << "FALSE" << endl;
				sort.QuickSort(&arr_1_);
				cout << "Áûñòðàÿ ñîðòèðîâêà: ";
				if (Test_After_Sort(&arr_1_))
					cout << "TRUE" << endl;
				else
					cout << "FALSE" << endl;
			}

			if (this->flag2 == 1) {
				cout << "ÑÐÀÂÍÅÍÈÅ ÑÎÐÒÈÐÎÂÎÊ ÏÎ ÂÐÅÌÅÍÈ" << endl;
				do {
					cout << "Ââåäèòå êîëè÷åñòâî ýëåìåíòîâ â ìàññèâå: " << endl;
					while (!(cin >> N)) {
						cin.clear();
						cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (N < 1)
						cout << "ÎØÈÁÊÀ: ïîâòîðèòå ââîä->";
				} while (N < 1);
				Rand_Seq_Gen(&arr_2, N);
				do {
					cout << "Âûâåñòè ëè ìàññèâ íà ýêðàí? (0 - N, 1 - Y)" << endl;
					while (!(cin >> flag)) {
						cin.clear();
						cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (flag != 0 && flag != 1)
						cout << "ÎØÈÁÊÀ: ïîâòîðèòå ââîä->";
				} while (flag != 0 && flag != 1);
				if (flag == 1)
					arr_2.printAll();

				ArraySequence<T> arr_2_ = arr_2;

				Sorts_Compare(&arr_2, &arr_2_, sort);
				do {
					cout << "Âûâåñòè ëè ìàññèâ íà ýêðàí? (0 - N, 1 - Y)" << endl;
					while (!(cin >> flag)) {
						cin.clear();
						cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (flag != 0 && flag != 1)
						cout << "ÎØÈÁÊÀ: ïîâòîðèòå ââîä->";
				} while (flag != 0 && flag != 1);
				if (flag == 1)
					arr_2.printAll();

				if (this->flag3 == 1) {
					cout << "ÑÐÀÂÍÅÍÈÅ ÑÎÐÒÈÐÎÂÎÊ Â ñëó÷àå îòñîðòèðîâàííîé è íåîòñîðòèðîâàííîé ïîñëåäîâàòåëüíîñòè" << endl;
					cout << "Ñëó÷àé ÎÒÑÎÐÒÈÐÎÂÀÍÍÎÉ ïîñëåäîâàòåëüíîñòè: " << endl;
					Sorts_Compare(&arr_2, &arr_2_, sort);
					Invert_Seq(&arr_2);
					ArraySequence<T> arr_3 = arr_2;
					cout << "Ñëó÷àé ÎÒÑÎÐÒÈÐÎÂÀÍÍÎÉ ïî óáûâàíèþ ïîñëåäîâàòåëüíîñòè: " << endl;
					Sorts_Compare(&arr_2, &arr_3, sort);
				}
			}
		}
		if (this->seq == 1) {
			ListSequence<T> list_2;
			cout << "ÏÎÑËÅÄÎÂÀÒÅËÜÍÎÑÒÜ --> ÑÏÈÑÎÊ" << endl << endl;
			if (this->flag1 == 1) {
				cout << "ÏÐÎÂÅÐÊÀ ÑÎÐÒÈÐÎÂÎÊ" << endl;
				ListSequence<T> list_1;
				do {
					cout << "Ââåäèòå êîëè÷åñòâî ýëåìåíòîâ â ìàññèâå: " << endl;
					while (!(cin >> N)) {
						cin.clear();
						cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (N < 1)
						cout << "ÎØÈÁÊÀ: ïîâòîðèòå ââîä->";
				} while (N < 1);
				Rand_Seq_Gen(&list_1, N);

				ListSequence<T> list_1_ = list_1;

				sort.InsectionSort(&list_1);
				cout << "Ñîðòèðîâêà âñòàâêàìè: ";
				if (Test_After_Sort(&list_1))
					cout << "TRUE" << endl;
				else
					cout << "FALSE" << endl;
				sort.QuickSort(&list_1_);
				cout << "Áûñòðàÿ ñîðòèðîâêà: ";
				if (Test_After_Sort(&list_1_))
					cout << "TRUE" << endl;
				else
					cout << "FALSE" << endl;
			}

			if (this->flag2 == 1) {
				cout << "ÑÐÀÂÍÅÍÈÅ ÑÎÐÒÈÐÎÂÎÊ ÏÎ ÂÐÅÌÅÍÈ" << endl;
				do {
					cout << "Ââåäèòå êîëè÷åñòâî ýëåìåíòîâ â ìàññèâå: " << endl;
					while (!(cin >> N)) {
						cin.clear();
						cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (N < 1)
						cout << "ÎØÈÁÊÀ: ïîâòîðèòå ââîä->";
				} while (N < 1);
				Rand_Seq_Gen(&list_2, N);
				ListSequence<T> list_2_ = list_2;
				do {
					cout << "Âûâåñòè ëè ìàññèâ íà ýêðàí? (0 - N, 1 - Y)" << endl;
					while (!(cin >> flag)) {
						cin.clear();
						cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (flag != 0 && flag != 1)
						cout << "ÎØÈÁÊÀ: ïîâòîðèòå ââîä->";
				} while (flag != 0 && flag != 1);
				if (flag == 1)
					list_2.printAll();
				Sorts_Compare(&list_2, &list_2_, sort);
				do {
					cout << "Âûâåñòè ëè ìàññèâ íà ýêðàí? (0 - N, 1 - Y)" << endl;
					while (!(cin >> flag)) {
						cin.clear();
						cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (flag != 0 && flag != 1)
						cout << "ÎØÈÁÊÀ: ïîâòîðèòå ââîä->";
				} while (flag != 0 && flag != 1);
				if (flag == 1)
					list_2.printAll();

				if (this->flag3 == 1) {
					cout << "ÑÐÀÂÍÅÍÈÅ ÑÎÐÒÈÐÎÂÎÊ Â ñëó÷àå îòñîðòèðîâàííîé è íåîòñîðòèðîâàííîé ïîñëåäîâàòåëüíîñòè" << endl;
					cout << "Ñëó÷àé ÎÒÑÎÐÒÈÐÎÂÀÍÍÎÉ ïîñëåäîâàòåëüíîñòè: " << endl;
					Sorts_Compare(&list_2, &list_2_, sort);
					Invert_Seq(&list_2);
					ListSequence<T> list_3 = list_2;
					cout << "Ñëó÷àé ÎÒÑÎÐÒÈÐÎÂÀÍÍÎÉ ïî óáûâàíèþ ïîñëåäîâàòåëüíîñòè: " << endl;
					Sorts_Compare(&list_2, &list_3, sort);
				}
			}
		}
	}
	if (this->mode == 1) {
		cout << "ÐÓ×ÍÎÉ ÐÅÆÈÌ" << endl << endl;
		if (this->seq == 0) {
			cout << "ÏÎÑËÅÄÎÂÀÒÅËÜÍÎÑÒÜ --> ÌÀÑÑÈÂ" << endl << endl;
			ArraySequence<T> arr2;

			if (this->flag1 == 1) {
				cout << "ÏÐÎÂÅÐÊÀ ÑÎÐÒÈÐÎÂÎÊ" << endl;
				ArraySequence<T> arr1;
				int N;
				do {
					cout << "Ââåäèòå êîëè÷åñòâî ýëåìåíòîâ â ìàññèâå: " << endl;
					while (!(cin >> N)) {
						cin.clear();
						cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (N < 1)
						cout << "ÎØÈÁÊÀ: ïîâòîðèòå ââîä->";
				} while (N < 1);
				for (int i = 0; i < N; i++) {
					T k;
					cout << "Ââåäèòå " << i << "-ûé ýëåìåíò: ";
					while (!(cin >> k)) {
						cin.clear();
						cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
						while (cin.get() != '\n') continue;
					}
					arr1.Append(k);
				}
				sort.InsectionSort(&arr1);
				cout << "Ñîðòèðîâêà âñòàâêàìè: ";
				if (Test_After_Sort(&arr1))
					cout << "TRUE" << endl;
				else
					cout << "FALSE" << endl;
				ArraySequence<T> arr1_ = arr1;
				sort.QuickSort(&arr1_);
				cout << "Áûñòðàÿ ñîðòèðîâêà: ";
				if (Test_After_Sort(&arr1_))
					cout << "TRUE" << endl;
				else
					cout << "FALSE" << endl;
			}

			if (this->flag2 == 1) {
				cout << "ÑÐÀÂÍÅÍÈÅ ÑÎÐÒÈÐÎÂÎÊ ÏÎ ÂÐÅÌÅÍÈ" << endl;
				do {
					cout << "Ââåäèòå êîëè÷åñòâî ýëåìåíòîâ â ìàññèâå: " << endl;
					while (!(cin >> N)) {
						cin.clear();
						cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (N < 1)
						cout << "ÎØÈÁÊÀ: ïîâòîðèòå ââîä->";
				} while (N < 1);
				for (int i = 0; i < N; i++) {
					T k;
					cout << "Ââåäèòå " << i << "-ûé ýëåìåíò: ";
					while (!(cin >> k)) {
						cin.clear();
						cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
						while (cin.get() != '\n') continue;
					}
					arr2.Append(k);
				}
				do {
					cout << "Âûâåñòè ëè ìàññèâ íà ýêðàí? (0 - N, 1 - Y)" << endl;
					while (!(cin >> flag)) {
						cin.clear();
						cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (flag != 0 && flag != 1)
						cout << "ÎØÈÁÊÀ: ïîâòîðèòå ââîä->";
				} while (flag != 0 && flag != 1);
				if (flag == 1)
					arr2.printAll();
				ArraySequence<T> arr2_ = arr2;
				Sorts_Compare(&arr2, &arr2_, sort);
				do {
					cout << "Âûâåñòè ëè ìàññèâ íà ýêðàí? (0 - N, 1 - Y)" << endl;
					while (!(cin >> flag)) {
						cin.clear();
						cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (flag != 0 && flag != 1)
						cout << "ÎØÈÁÊÀ: ïîâòîðèòå ââîä->";
				} while (flag != 0 && flag != 1);
				if (flag == 1)
					arr2.printAll();

				if (this->flag3 == 1) {
					cout << "ÑÐÀÂÍÅÍÈÅ ÑÎÐÒÈÐÎÂÎÊ Â ñëó÷àå îòñîðòèðîâàííîé è íåîòñîðòèðîâàííîé ïîñëåäîâàòåëüíîñòè" << endl;
					cout << "Ñëó÷àé ÎÒÑÎÐÒÈÐÎÂÀÍÍÎÉ ïîñëåäîâàòåëüíîñòè: " << endl;
					Sorts_Compare(&arr2, &arr2_, sort);
					Invert_Seq(&arr2);
					ArraySequence<T> arr3 = arr2;
					cout << "Ñëó÷àé ÎÒÑÎÐÒÈÐÎÂÀÍÍÎÉ ïî óáûâàíèþ ïîñëåäîâàòåëüíîñòè: " << endl;
					Sorts_Compare(&arr2, &arr3, sort);
				}
			}
		}
		if (this->seq == 1) {
			ListSequence<T> list2;
			cout << "ÏÎÑËÅÄÎÂÀÒÅËÜÍÎÑÒÜ --> ÑÏÈÑÎÊ" << endl << endl;
			if (this->flag1 == 1) {
				cout << "ÏÐÎÂÅÐÊÀ ÑÎÐÒÈÐÎÂÎÊ" << endl;
				ListSequence<T> list1;
				do {
					cout << "Ââåäèòå êîëè÷åñòâî ýëåìåíòîâ â ìàññèâå: " << endl;
					while (!(cin >> N)) {
						cin.clear();
						cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (N < 1)
						cout << "ÎØÈÁÊÀ: ïîâòîðèòå ââîä->";
				} while (N < 1);
				for (int i = 0; i < N; i++) {
					T k;
					cout << "Ââåäèòå " << i << "-ûé ýëåìåíò: ";
					while (!(cin >> k)) {
						cin.clear();
						cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
						while (cin.get() != '\n') continue;
					}
					list1.Append(k);
				}
				sort.InsectionSort(&list1);
				cout << "Ñîðòèðîâêà âñòàâêàìè: ";
				if (Test_After_Sort(&list1))
					cout << "TRUE" << endl;
				else
					cout << "FALSE" << endl;
				ListSequence<T> list1_ = list1;
				sort.QuickSort(&list1_);
				cout << "Áûñòðàÿ ñîðòèðîâêà: ";
				if (Test_After_Sort(&list1_))
					cout << "TRUE" << endl;
				else
					cout << "FALSE" << endl;
			}

			if (this->flag2 == 1) {
				cout << "ÑÐÀÂÍÅÍÈÅ ÑÎÐÒÈÐÎÂÎÊ ÏÎ ÂÐÅÌÅÍÈ" << endl;
				do {
					cout << "Ââåäèòå êîëè÷åñòâî ýëåìåíòîâ â ìàññèâå: " << endl;
					while (!(cin >> N)) {
						cin.clear();
						cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (N < 1)
						cout << "ÎØÈÁÊÀ: ïîâòîðèòå ââîä->";
				} while (N < 1);
				for (int i = 0; i < N; i++) {
					T k;
					cout << "Ââåäèòå " << i << "-ûé ýëåìåíò: ";
					while (!(cin >> k)) {
						cin.clear();
						cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
						while (cin.get() != '\n') continue;
					}
					list2.Append(k);
				}
				do {
					cout << "Âûâåñòè ëè ìàññèâ íà ýêðàí? (0 - N, 1 - Y)" << endl;
					while (!(cin >> flag)) {
						cin.clear();
						cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (flag != 0 && flag != 1)
						cout << "ÎØÈÁÊÀ: ïîâòîðèòå ââîä->";
				} while (flag != 0 && flag != 1);
				if (flag == 1)
					list2.printAll();
				ListSequence<T> list2_ = list2;
				Sorts_Compare(&list2, &list2_, sort);
				do {
					cout << "Âûâåñòè ëè ìàññèâ íà ýêðàí? (0 - N, 1 - Y)" << endl;
					while (!(cin >> flag)) {
						cin.clear();
						cout << "ERROR: ââåäèòå ÷èñëî--> " << endl;
						while (cin.get() != '\n') continue;
					}
					if (flag != 0 && flag != 1)
						cout << "ÎØÈÁÊÀ: ïîâòîðèòå ââîä->";
				} while (flag != 0 && flag != 1);
				if (flag == 1)
					list2.printAll();

				if (this->flag3 == 1) {
					cout << "ÑÐÀÂÍÅÍÈÅ ÑÎÐÒÈÐÎÂÎÊ Â ñëó÷àå îòñîðòèðîâàííîé è íåîòñîðòèðîâàííîé ïîñëåäîâàòåëüíîñòè" << endl;
					cout << "Ñëó÷àé ÎÒÑÎÐÒÈÐÎÂÀÍÍÎÉ ïîñëåäîâàòåëüíîñòè: " << endl;
					Sorts_Compare(&list2, &list2_, sort);
					Invert_Seq(&list2);
					ListSequence<T> list3 = list2;
					cout << "Ñëó÷àé ÎÒÑÎÐÒÈÐÎÂÀÍÍÎÉ ïî óáûâàíèþ ïîñëåäîâàòåëüíîñòè: " << endl;
					Sorts_Compare(&list2, &list3, sort);
				}
			}
		}
	}
}

#endif /* USER_INTERFACE_H */