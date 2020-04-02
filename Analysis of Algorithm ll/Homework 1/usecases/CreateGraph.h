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


// Create graph class which creates the graph of the game

#ifndef CREATEGRAPH_H
#define CREATEGRAPH_H

#include "../model/GameStatus.h"
#include "../model/Stats.h"
#include "UseSkill.h"


#include <iostream>



using namespace std;

class CreateGraph{
	private:
		Pikachu* pikachu;
		Blastoise* blastoise;
		int maxLevel;
		
		
	public:
		CreateGraph(Pikachu* pikachu, Blastoise* blastoise, int maxLevel);
		void execute(GameStatus* status);
};


CreateGraph::CreateGraph(Pikachu* pikachu, Blastoise* blastoise, int maxLevel){
	this->pikachu = pikachu;
	this->blastoise = blastoise;
	this->maxLevel = maxLevel;
}


void CreateGraph::execute(GameStatus* status){
	int currentLevel = status->stats->level;
	// Max level should not be exceeded
	if(currentLevel < maxLevel){
		
		// Both of the players should be alive for the next level generation
		if(!status->pikachu->isDead && !status->blastoise->isDead){
			// TEST PRINTER
			//status->printStatus();
			
			// When it is Pikachu's turn
			if(status->stats->turn == 'P'){
				Skill** availableSkills = status->pikachu->getAvailableSkills(currentLevel);
				int availableSkillCount = status->pikachu->availableSkillCount;
				
				// Set max number of children in the status node
				status->maxNumberOfChildren = availableSkillCount*2;  // Skills have 2 possible results: Success or miss
				status->children = new GameStatus*[status->maxNumberOfChildren];
				
				// Add new child nodes
				for(int i=0; i<availableSkillCount; i++){
					// Get the current skill
					Skill* currentSkill = availableSkills[i];
				
					// Clone existing players for successful attack
					Pikachu* clonedPikachuSuccess = status->pikachu->clone();
					Blastoise* clonedBlastoiseSuccess = status->blastoise->clone();
					// Clone existing players for failed attack
					Pikachu* clonedPikachuFail = status->pikachu->clone();
					Blastoise* clonedBlastoiseFail = status->blastoise->clone();
					
					
					// Initilize the new state using the current state variables
					
					
					// Add new branch after a SUCCESSFUL attack
					float successfulProbability = status->stats->probability * currentSkill->accuracy / availableSkillCount;
					if(successfulProbability > 0){
						// Use current skill which is effective
						bool isSkillEffective = true;
						UseSkill::execute(currentSkill, clonedPikachuSuccess, clonedBlastoiseSuccess, isSkillEffective);
						
						Stats* newStats = new Stats(
							'B', 
							successfulProbability, 
							currentLevel + 1,
							clonedBlastoiseSuccess->isDead
						);
						GameStatus* newGameStatus = new GameStatus(
							clonedPikachuSuccess,
							clonedBlastoiseSuccess,
							newStats,
							isSkillEffective,
							status,
							currentSkill->name
						);
						status->children[status->numberOfChildren++] = newGameStatus;
						
						// Call this function recursively for children if the game is not finished
						if(!clonedBlastoiseSuccess->isDead)
							execute(newGameStatus);
					}
					
					
					// Add new branch after a MISSED attack
					float missProbability = status->stats->probability * (1 - currentSkill->accuracy) / availableSkillCount;
					if(missProbability > 0){
						// Use current skill which is not effective
						bool isSkillEffective = false;
						UseSkill::execute(currentSkill, clonedPikachuFail, clonedBlastoiseFail, isSkillEffective);
						
						Stats* newStats = new Stats(
							'B', 
							missProbability, 
							currentLevel + 1, 
							false // If the attack is missed, then it can not be a leaf. Game is going on
						);
						GameStatus* newGameStatus = new GameStatus(
							clonedPikachuFail,
							clonedBlastoiseFail,
							newStats,
							isSkillEffective,
							status,
							currentSkill->name
						);
						status->children[status->numberOfChildren++] = newGameStatus;
						
						// Call this function recursively for children 
						execute(newGameStatus);
					}
						
				}
			}
			// When it is Blastoise's turn
			else if(status->stats->turn == 'B'){
				Skill** availableSkills = status->blastoise->getAvailableSkills(currentLevel);
				int availableSkillCount = status->blastoise->availableSkillCount;
				
				// Set max number of children in the status node
				status->maxNumberOfChildren = availableSkillCount*2;  // Skills have 2 possible results: Success or miss
				status->children = new GameStatus*[status->maxNumberOfChildren];
				
				// Add new child nodes
				for(int i=0; i<availableSkillCount; i++){
					// Get the current skill
					Skill* currentSkill = availableSkills[i];
				
					// Clone existing players for successful attack
					Pikachu* clonedPikachuSuccess = status->pikachu->clone();
					Blastoise* clonedBlastoiseSuccess = status->blastoise->clone();
					// Clone existing players for failed attack
					Pikachu* clonedPikachuFail = status->pikachu->clone();
					Blastoise* clonedBlastoiseFail = status->blastoise->clone();
					
					
					// Initilize the new state using the current state variables
					
					// Add new branch after a SUCCESSFUL attack
					float successfulProbability = status->stats->probability * currentSkill->accuracy / availableSkillCount;
					if(successfulProbability > 0){
						// Use current skill which is effective
						bool isSkillEffective = true;
						UseSkill::execute(currentSkill, clonedBlastoiseSuccess, clonedPikachuSuccess, isSkillEffective);
						
						Stats* newStats = new Stats(
							'P', 
							successfulProbability, 
							status->stats->level + 1,
							clonedPikachuSuccess->isDead
						);
						GameStatus* newGameStatus = new GameStatus(
							clonedPikachuSuccess,
							clonedBlastoiseSuccess,
							newStats,
							isSkillEffective,
							status,
							currentSkill->name
						);
						status->children[status->numberOfChildren++] = newGameStatus;
						
						// Call this function recursively for children if the game is not finished
						if(!clonedPikachuSuccess->isDead)
							execute(newGameStatus);
						
					}
					
					// Add new branch after a MISSED attack
					float missProbability = status->stats->probability * (1 - currentSkill->accuracy) / availableSkillCount;
					if(missProbability > 0){
						// Use current skill which is not effective
						bool isSkillEffective = false;
						UseSkill::execute(currentSkill, clonedBlastoiseFail, clonedPikachuFail, isSkillEffective);
						
						Stats* newStats = new Stats(
							'P', 
							missProbability, 
							status->stats->level + 1, 
							false // If the attack is missed, then it can not be a leaf. Game is going on
						);
						GameStatus* newGameStatus = new GameStatus(
							clonedPikachuFail,
							clonedBlastoiseFail,
							newStats,
							isSkillEffective,
							status,
							currentSkill->name
						);
						status->children[status->numberOfChildren++] = newGameStatus;
						
						
						// Call this function recursively for children 
						execute(newGameStatus);
					}
						
				}
				
			}
		}
		// If one of them is died, there won't be any more child nodes
		else{
			return;
		}
		
	}
	
}




#endif
