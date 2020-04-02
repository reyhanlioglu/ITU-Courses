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


// Blastoise Class

#ifndef BLASTOISE_H
#define BLASTOISE_H

#include "Character.h"
#include "../../usecases/read_skillset_from_file/ReadSkillSet.h"

const int BLASTOISE_INITIAL_HP = 200;
const int BLASTOISE_INITIAL_PP = 100;


using namespace std;


class Blastoise: public Character {
	public:
		Blastoise();
		Blastoise(int HP, int PP);
		~Blastoise();
		Skill** getAvailableSkills(int currentLevel);
		Blastoise* clone();
};

Blastoise::Blastoise(): Character(BLASTOISE_INITIAL_HP, BLASTOISE_INITIAL_PP){
	// Reading and setting the skill set of pikachu
	ReadSkillSet* skillReader = new ReadSkillSet();
	this->skillSet = skillReader->getBlastoiseSkills();
	this->numberOfSkills = skillReader->getBlastoiseSkillCount(); 
	getAvailableSkills(0);
}

Blastoise::Blastoise(int HP, int PP): Character(HP, PP){
}

Blastoise::~Blastoise(){
	
}

Skill** Blastoise::getAvailableSkills(int currentLevel){
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


Blastoise* Blastoise::clone(){
	Blastoise* clonedCharacter = new Blastoise(this->HP, this->PP);
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
