
#include "BMI.h"
#include <string>
BMI::BMI()
{
  newHeight = 0;
  newWeight = 0.0;
}

BMI::BMI(string name, int height, double weight)
{
  newName = name;
  newHeight = height;
  newWeight = weight;
}

BMI::~BMI() {
}

string BMI::getName()
{
	return newName;
}

int BMI::getHeight()
{
	return newHeight;
}

double BMI::getWeight()
{
	return newWeight;
}

double BMI::calculatedBMI()
{
	return ((newWeight * 703) / (newHeight * newHeight));
}


