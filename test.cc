#include <iostream> //allows for console input and output.
#include <string> //allows usage of "string" data-type.
#include "BMI.h" //includes a files that has the class(traits) for the object.

using namespace std; //belongs under one workspace which looking at -
                      // program simplicity.

int main()    //main function, user interface function of return type int.
{
	string name;   //variable that will store person's (object's) name.
	int height;    //variable that will store person's (object's) height.
	double weight; //variable that will store person's (object's) weight.
	cout << "Enter Name:  " << endl;  //console output. Prompt for name.
	cin >> name; //console input. User enters name.
	cout << "Enter Height:  " <<endl; //console output. Prompt for height.
	cin >> height;  //console input. User enters height.
	cout << "Enter Weight:  " <<endl; //console out. Prompt for weight.
	cin >> weight; //console input. User enters weight.

	BMI patient(name, height, weight);

	// Object(virtual person) of class BMI created.
	cout << "Your Name:  " << patient.getName() << endl; //Print back name.
	cout << "Your Height:  " << patient.getHeight() <<endl; //print back height.
	cout << "Your Weight:  " << patient.getWeight() <<endl; //print back weight.
    cout << "Your BMI:  " << patient.calculatedBMI(); //print back BMI.
    return 0; //Programs ends with return value 0.
}
