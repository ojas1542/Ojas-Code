/*
 * ADD.h
 *
 *  Created on: Apr 5, 2016
 *      Author: ojas
 */

#ifndef ADD_H_
#define ADD_H_

class ADD {
public:
	ADD();
	~ADD();
	ADD(int, double);
	int add();
private:
	int newnum1;
	double newnum2;
};


ADD::ADD()
{
	newnum1 = 0;
	newnum2 = 0;
}

ADD::~ADD()
{

}

ADD::ADD(int num1, double num2)
{
	newnum1 = num1;
	newnum2 = num2;
}

int ADD::add()
{
	return newnum1 + newnum2;
}

#endif /* ADD_H_ */
