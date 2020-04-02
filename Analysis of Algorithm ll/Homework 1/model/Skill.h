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


// Skill Class

#ifndef SKILL_H
#define SKILL_H

#include <cstring>
#include <stdio.h>

using namespace std;



class Skill{
	
	public:
		Skill(const char* name, int neededPower, float accuracy, float damage, int firstUsage);
		~Skill();
		char* name;
		int neededPower, firstUsage;
		float accuracy, damage; 
		bool isAvailable(int currentLevel);
};



Skill::Skill(const char* name, int neededPower, float accuracy, float damage, int firstUsage){
	this->name = new char[100];
	this->neededPower = neededPower;
	this->accuracy = accuracy/100;
	this->damage = damage;
	this->firstUsage = firstUsage;
	strcpy(this->name, name);
	
}

bool Skill::isAvailable(int currentLevel){
	return currentLevel >= firstUsage;
}


Skill::~Skill(){
	if(this->name != NULL)
		delete (this->name);
}

#endif

