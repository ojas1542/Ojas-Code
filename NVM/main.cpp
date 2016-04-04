#include <iostream>
#include "Ojas.h"

using namespace std; 


Madara *mad_initial;
Naruto *nar_initial;
	
int choice;
bool Start_Play();
bool Start_Play()
{
	if(choice == 1)
		{
			cout << "Let's Begin!";
			
		}
		else
		{
			cout << "Bye! :)";
		}
}

void If_Play_Selected();

void If_Play_Selected()
{
	cout << "Here are Naruto's jutsus!" << endl;
			cout << "Firstly though, Madara and you have 5 lives!" << endl;
			cout << "Only a combination of your jutsus will help you defeat him since you lose a life every turn everytime you attack" << endl;
			cout << "Every attack costs you a life" << endl;
			cout << "1. Shadow Clone Jutsu \n";
			cout << "2.Wind Style Rasen Shuriken \n";
			cout << "3. Kurama Combo attack! \n";
			cout << "4.Kunai attack \n";
			cout << "5. Fighting with Gamakichi";
			cout << "6. team7 with Sasuke";

		}

int main() {
	
	
                                               	
	cout << "Welcome to Naruto Vs Madara" << endl;
	cout << "Press 1 to play, press 2 to quit" << endl;
	cin >> choice;
	Start_Play();
	cout << "Ok then!";
	If_Play_Selected();
	int attackchoice;
	cin >> attackchoice;
    while(mad_initial->madara_class_life != 0)
    {
    	switch(attackchoice)
    	{
    		case 1:
    			mad_initial->ShadowCloneJutsu();
    		case 2:
    			mad_initial->WindStyleRasen();
    		case 3:
    			mad_initial->Kurama_attack();
    		case 4: 
    		    mad_initial->KunaiAttack();
    		case 5:
    			mad_initial->Gamakichi_Attack();
    		case 6:
    			mad_initial->Team7Attack();
    		}
    		if(mad_initial->madara_class_life == 0)
    		  {
			  cout << "You win!!";
		}
    		else
    		{
    			cout << "Go Naruto!";
			}
			if(nar_initial->naruto_class_life == 0)
			{
				cout << "Sorry, you lost";
			}
			else
			{
				cout << "Come on!";
			}
    	}
	
	
	return 0;
}
	
																													                                                                                                                 
	
	
 

