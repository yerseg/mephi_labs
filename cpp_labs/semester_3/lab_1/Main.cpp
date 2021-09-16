#include <iostream>
#include <ctime>
#include <chrono>
#include <locale>
#include <stdio.h>
#include "Sequence.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include "Sorters.h"
#include "Help_Func.h"
#include "UserInterface.h"
#include "Test.h"

using namespace std;
                                                        
int main() {
	setlocale(LC_ALL, "Rus");
	Test_Sort();
	UserInterface<int> interface;
	interface.Interface();
	system("pause");
}
