//============================================================================
// Name        (: testing.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "ADD.h"
using namespace std;

int main() {
	int num1;
	double num2;

	cout << "Enter num1" << endl;
	cin >> num1;
	cout << "Enter num1" << endl;
	cin >> num2;

	ADD User_1(num1, num2);
	cout << "Answer is \n" << User_1.add();

	return 0;
}
