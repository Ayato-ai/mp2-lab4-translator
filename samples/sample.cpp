#include <iostream>
#include "translator.h"
using namespace std;

int main() {
	setlocale(2, "rus");
	string temp;
	cout << "Введите арифметическое выражение - ";
	cin >> temp;
	translator tr(temp);
	cout << "Ответ = " << tr.translation();
}
