#include <iostream>
#ifndef CALC_H
#define CALC_H
using namespace std;

class Operations {
  public:
  Operations();
  Operations(double, double);
  ~Operations();
  double add();  
  private:
    double newNum1;
    double newNum2;
  };
#endif 
