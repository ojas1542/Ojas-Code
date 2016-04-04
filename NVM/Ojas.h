#ifndef OJAS_H
#define OJAS_H
#include <iostream>

using namespace std;

class Naruto
{
	public:
		Naruto();
		~Naruto();
		int naruto_class_life = 5;
		void setNarutoMaxLife();
	
	protected:
		
};

class Madara
{
	public:
		Madara();
		~Madara();
		void setMadaraLife(int);
		void setFinalAttack();
		void setMadaraMaxLife();
		void ShadowCloneJutsu();
		void WindStyleRasen();
		void KunaiAttack();
		void Gamakichi_Attack();
		void Kurama_attack();
		void Team7Attack();
		int madara_class_life = 6;
	protected:
		
		
};

#endif
