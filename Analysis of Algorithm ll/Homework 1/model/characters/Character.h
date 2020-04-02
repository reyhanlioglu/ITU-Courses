/*****************************
* (C) 2020 Emre Reyhanlıoğlu *
*    All rights reserved.	 *
*							 *
*	     BLG 336E 			 *
*       HOMEWORK 1		 	 *
*    EMRE REYHANLIOGLU 		 *
*       150140126			 *
*							 *
*****************************/


// Character Interface

#ifndef CHARACTER_H
#define CHARACTER_H

#include "../../model/Skill.h"


using namespace std;



class Character{
	public:
		Skill** skillSet;
		int numberOfSkills;
		int availableSkillCount;
		int HP;
		int PP;
		bool isDead;
		
		Character(int HP, int PP);
		~Character();
		virtual Skill** getAvailableSkills(int currentLevel) = 0;
};

Character::Character(int HP, int PP){
	this->HP = HP;
	this->PP = PP;
	this->isDead = false;
}

Character::~Character(){}






#endif
