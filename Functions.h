#ifndef FUNCTIONS_H
#define FUNCTIONS_H

class Functions
{
	public:
		void addition();
		void subtraction();
		void multiply();
		void divide();
		
	private:
		double num1;
		double num2;
		
		friend void setNum(Functions setN, double num1s, double num2s);
	   
	    
};

void Functions::setNum() {
	setN.num1 = num1s;
	setN.num2 = num2s;
}


#endif




void Functions::addition() {
	num1 + num2;
}

void Functions::divide() {
	num1 / num2;
}

void Functions::multiply() {
	num1 * num2;
}

void Functions::subtraction() {
	num1 - num2;
}
