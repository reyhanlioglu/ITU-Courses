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


// Game Status class which holds the state of the game at that moment

#ifndef GAMESTATUS_H
#define GAMESTATUS_H

#include "characters/Pikachu.h"
#include "characters/Blastoise.h"
#include "Stats.h"

#include <iostream>
#include <cstring>

#define SKILL_NAME_LENGTH 15


using namespace std;


class GameStatus{
	public:
		Pikachu* pikachu;
		Blastoise* blastoise;
		Stats* stats;
		GameStatus* parent;
		GameStatus** children;
		int numberOfChildren;
		int maxNumberOfChildren;
		GameStatus();
		GameStatus(Pikachu* pikachu, Blastoise* blastoise, Stats* stats, 
					bool isSkillEffective, GameStatus* parent, char* usedSkillName);
		void printStatus();
		bool isSkillEffective;
		char* usedSkillName;
};

GameStatus::GameStatus(){}

GameStatus::GameStatus(Pikachu* pikachu, Blastoise* blastoise, Stats* stats, 
					bool isSkillEffective, GameStatus* parent, char* usedSkillName){
	this->pikachu = pikachu;
	this->blastoise = blastoise;
	this->stats = stats;
	this->isSkillEffective = isSkillEffective;
	this->parent = parent;
	this->numberOfChildren = 0;
	this->usedSkillName = new char[SKILL_NAME_LENGTH];
	strcpy(this->usedSkillName, usedSkillName);
}


void GameStatus::printStatus(){
	printf("Current Level: %d\nTurn: %c\nProbability: %f\n" ,
			stats->level,
			stats->turn,
			stats->probability
		);
	printf("P_HP:%d P_PP:%d B_HP:%d B_PP:%d\n", pikachu->HP, pikachu->PP, blastoise->HP, blastoise->PP);
	printf(pikachu->isDead ? "Pikachu is dead\n": "Pikachu is alive\n");
	printf(blastoise->isDead ? "Blastoise is dead\n": "Blastoise is alive\n\n");
}



#endif
