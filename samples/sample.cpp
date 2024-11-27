#include <iostream>
#include "translator.h"
using namespace std;

int isValid(string s) {
	Mstack<char> stack;
	for (int i = 0; i < s.length(); i++) {
		if ((s[i] == '(') || (s[i] == '[') || (s[i] == '{'))
			stack.push(s[i]);

		if (s[i] == ')') {
			if (stack.top() != '(')
				return 0;
			stack.pop();
		}
		if (s[i] == ']') {
			if (stack.top() != '[')
				return 0;
			stack.pop();
		}
		if (s[i] == '}') {
			if (stack.top() != '{')
				return 0;
			stack.pop();
		}
	}
	if (stack.size()) return 0;
	return 1;
}
int main() {
	string temp;
	cout << "Please, input string - ";
	cin >> temp;
	cout << "string is - " << temp << " - is ";
		if (isValid(temp))
			cout << "correct" << endl;
		else
			cout << "ancorrect" << endl;
}
