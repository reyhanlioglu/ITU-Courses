/*****************************
* (C) 2020 Emre Reyhanlýoðlu *
*    All rights reserved.	 *
*							 *
*	     BLG 336E 			 *
*       HOMEWORK 1		 	 *
*    EMRE REYHANLIOGLU 		 *
*       150140126			 *
*							 *
*****************************/


// Pikachu Class

#ifndef PIKACHU_H
#define PIKACHU_H

#include "Character.h"
#include "../../usecases/read_skillset_from_file/ReadSkillSet.h"

const int PIKACHU_INITIAL_HP = 200;
const int PIKACHU_INITIAL_PP = 100;


using namespace std;


class Pikachu: public virtual Character {
	public:
		Pikachu();
		Pikachu(int HP, int PP);
		~Pikachu();
		Skill** getAvailableSkills(int currentLevel);
		Pikachu* clone();
};

Pikachu::Pikachu(): Character(PIKACHU_INITIAL_HP, PIKACHU_INITIAL_PP){
	// Reading and setting the skill set of pikachu
	ReadSkillSet* skillReader = new ReadSkillSet();
	this->skillSet = skillReader->getPikachuSkills();
	this->numberOfSkills = skillReader->getPikachuSkillCount(); 
	getAvailableSkills(0);
}

Pikachu::Pikachu(int HP, int PP): Character(HP, PP){
}

Pikachu::~Pikachu(){
	
}

Skill** Pikachu::getAvailableSkills(int currentLevel){
	Skill** availableSkills = new Skill*[this->numberOfSkills];
	int numberOfAvailableSkills = 0;
	
	for(int i=0; i<this->numberOfSkills; i++){
		if(this->skillSet[i]->isAvailable(currentLevel)){
			availableSkills[numberOfAvailableSkills++] = this->skillSet[i];
		}
	}
	
	this->availableSkillCount = numberOfAvailableSkills;
	return availableSkills;
}


Pikachu* Pikachu::clone(){
	Pikachu* clonedCharacter = new Pikachu(this->HP, this->PP);
	clonedCharacter->isDead = this->isDead;
	clonedCharacter->numberOfSkills = this->numberOfSkills;
	clonedCharacter->availableSkillCount = this->availableSkillCount;
	
	Skill** clonedSkillSet = new Skill*[this->numberOfSkills];
	for(int i=0; i<this->numberOfSkills; i++){
		clonedSkillSet[i] = this->skillSet[i];
	}
	
	clonedCharacter->skillSet = clonedSkillSet;
	return clonedCharacter;
}


#endif
