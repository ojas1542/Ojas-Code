#include <iostream> //Input output console.
#include <string> //allowing data-type string.

using namespace std; // belong to standard namepaces.

#ifndef BMI_H_ //Header file BMI.h not defined.
#define BMI_H_ //Define the header file.

class BMI { //creates class named BMI
public: //members (traits) that are accessible.
	BMI(); //functions, default constructor.
	BMI(string, int, double); //overload constructor.
   ~BMI(); //destructor
    string getName();
    int getHeight();
    double getWeight();
    double calculatedBMI();
private:
   string newName;
   int newHeight;
   double newWeight;
};

#endif /* BMI_H_ */
