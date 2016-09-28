#include <iostream>
#include "Functions.h"


using namespace std;
int operation;
int main(int argc, char** argv) {
	double num1i;
	double num2i;
	cout << "Welcome to the caculator. Use the number next to option" << endl;
	cout << "1.Add, 2.Sub, 3.Mult, 4.Div";
	cout << "num1";
	cin >> num1i;
	cout << "num2";
	cin >> num2i;
	
	Functions user;
	switch(operation) {
		case '1':
			setNum(user, num1i, num2i);
			cout << user.addition();
			break;
		case '2':
			setNum(user, num1i, num2i);
			cout << user.subtraction();
			break;
		case '3':
			setNum(user, num1i, num2i);
			cout << user.multiply();
			break;
		case '4':
			setNum(user, num1i, num2i);
			cout << user.subtraction();
			break;
			
			
	}
	return 0;
}
