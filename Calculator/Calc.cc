#include "Calc.h"


using namespace std;

Operations::Operations() {
  newNum1 = 0.0;
  newNum2 = 0.0;
}

Operations::Operations(double num1, double num2) {
  newNum1 = num1;
  newNum2 = num2;
}

Operations::~Operations() {
}

double Operations::add() {
  return newNum1 + newNum2;
}

