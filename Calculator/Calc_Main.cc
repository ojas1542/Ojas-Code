#include <iostream>
#include "CALC.h"


using namespace std;

int main() {

double num1;
double num2;
int choice;

cout << "You can use two numbers here for the the following operations, please use operation's corresponding number" << endl;
cout << "1.Addition" << endl;
cout << "2.Subtraction" << endl;
cout << "3.Multiplication" << endl;
cout << "4.Division" << endl;
cin >> choice;

Operations user(num1, num2);
switch(choice)
{
  case 1:
    cout << "You are adding." << endl;
    cout << "Answer" << user.add();
    break;
  case 2:
    cout << "You are subtracting" << endl;
    break;
  case 3:
    cout << "You are Multiplying" << endl;
    break;
  case 4:
    cout << "You are dividing" << endl;
    break;
}

return 0;
}
