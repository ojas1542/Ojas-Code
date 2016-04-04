#include "Ojas.h"



Naruto::~Naruto()
{
}



void Naruto::setNarutoMaxLife()
{
	naruto_class_life - 1;
}

void Madara::setMadaraMaxLife()
{
	madara_class_life - 1;
}

void Madara::setFinalAttack()
{
	madara_class_life - 2;
}

void Madara::ShadowCloneJutsu()
{
	setMadaraMaxLife();
	cout << "Madara has" << madara_class_life << "left" << endl;
}

void Madara::WindStyleRasen()
{
	setMadaraMaxLife();
	cout << "Wind Style Rasen-Shuriken!!!" << endl;
	cout << "Madara has" << madara_class_life << "left" << endl;
}

void Madara::KunaiAttack()
{
	setMadaraMaxLife();
	cout << "Madara!!" << endl;
	cout << "Madara has" << madara_class_life << "left" << endl;
}

void Madara::Gamakichi_Attack()
{
	setMadaraMaxLife();
	cout << "Lets go gamakichi!" << endl;
	cout << "Madara has" << madara_class_life << "left" << endl;
}

void Madara::Kurama_attack()
{
	setMadaraMaxLife();
	cout << "Lets go Kurama!" << endl;
	cout << "Madara has" << madara_class_life << "left" << endl;
}

void Madara::Team7Attack()
{
	cout << "Lets go Sasuke" << endl;
	setFinalAttack();
	cout << "Madara has" << madara_class_life << "left" << endl;
}



