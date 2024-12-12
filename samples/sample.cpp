#include <iostream>
#include <conio.h>
#include "translator.h"
using namespace std;

int main() {
	setlocale(2, "rus");
	char g;
	try {
		string temp;

		cout << "Введите арифметическое выражение - ";
		cin >> temp;
		translator tr(temp);
		cout << "Ответ = " << tr.translation();
	}
	catch (const invalid_argument& error) {
		cerr << "Ошибка: " << error.what() << endl;
	}
	g = _getch();
	cout << g;
}
