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


// Use Skill Class which simulates the effects of the given attack skill

#ifndef USESKILL_H
#define USESKILL_H

#include "../model/Skill.h"
#include "../model/characters/Character.h"

#include <cstring>
#include <iostream>


using namespace std;


class UseSkill{
	private:
		static bool isItAttackSkill(Skill* skill);	
			
	public:
		static void execute(Skill* usedSkill, Character* attacker, Character* defender, bool isEffective);		
};


bool UseSkill::isItAttackSkill(Skill* skill){
	return strcmp(skill->name, "Skip") != 0;
}


void UseSkill::execute(Skill* usedSkill, Character* attacker, Character* defender, bool isEffective){
	// When "Skip" skill is used
	if(!isItAttackSkill(usedSkill)){
		//cout<<"Skip is used\n"<<endl;
		attacker->PP += 100;
		return;
	}
	// When attack skills are used
	else{
		// When attacker has enough energy power
		if(attacker->PP >= usedSkill->neededPower*(-1)){
			// Energy consumption
			attacker->PP += usedSkill->neededPower;
			
			// Damage to the target if the attack is effective
			if(isEffective){
				defender->HP -= usedSkill->damage;
				
				// Check whether defender is dead or not
				if(defender->HP <= 0){
					defender->isDead = true;
					defender->HP = 0;
				}
			}
			return;	
		}
		// When attacker does not have enough energy power
		else {
			return;
		}		
	}
}


#endif
