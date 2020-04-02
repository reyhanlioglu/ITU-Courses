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


// Breadth First Search algorithm

#ifndef BREADTHFIRSTSEARCH_H
#define BREADTHFIRSTSEARCH_H


#include "CreateGraph.h"

#include <queue> 
#include <stack>


using namespace std;

class BreadthFirstSearch{
	private:
		queue<GameStatus*> nodeQueue;
		int numberOfNodes;
		bool isItFirst;
		char* expectedWinner;
		bool canSomebodyWin;
		GameStatus* root;
		GameStatus* nodeWhichHasEasiestPath;

		void addChildrenNodes(GameStatus* node);
		void checkWhetherGameIsFinishedOrNot(GameStatus* node);
			
	
	public:
		BreadthFirstSearch(GameStatus* root);
		void traverse();
		int getNumberOfNodes();
		void printEasiestPath();
		void setExpectedWinner(char winner);
};

BreadthFirstSearch::BreadthFirstSearch(GameStatus* root){
	this->root = root;
	this->numberOfNodes = 0;
	this->nodeWhichHasEasiestPath = NULL;
	this->isItFirst = true;
	this->expectedWinner = new char[1];
	this->canSomebodyWin = false;
}


// Helper method which adds given node's children into queue 
// and increments the total number of nodes
// Also there is a control methods which checks whether game is finished or not 
// This control mechanism is needed for PART 4
// NOTE: This additional control MAY SLOW part 3 DOWN a little bit
void BreadthFirstSearch::addChildrenNodes(GameStatus* node){
	if(node == NULL)
		return;
	
	// Control for PART 4
	// If node has not any children, probably game is finished 
	// but it may be null because of the graph's level limit
	if(node->children == NULL){
		checkWhetherGameIsFinishedOrNot(node);
		return;
	}
	
	int numberOfChildren = node->numberOfChildren;
	// Add children into queue
	for(int i=0; i<numberOfChildren; i++){
		this->nodeQueue.push(node->children[i]);
		this->numberOfNodes++;	
	}
}


// Traverse method
void BreadthFirstSearch::traverse(){
	// Add children into queue (also this method counts the number of nodes)
	if(root == NULL)
		return;
	
	// Add the root node
	this->nodeQueue.push(root);
	this->numberOfNodes++;
	
	// Add other nodes
	for(int i=0; nodeQueue.size() > 0; i++){
		// Add front node's children
		addChildrenNodes(nodeQueue.front());
		// Pop the front node
		nodeQueue.pop();
	}
}

// Getter
int BreadthFirstSearch::getNumberOfNodes(){
	return this->numberOfNodes;
}

// PART 4 Helper Method
void BreadthFirstSearch::checkWhetherGameIsFinishedOrNot(GameStatus* node){
	if(node->pikachu->isDead || node->blastoise->isDead){
		this->canSomebodyWin = true;
		
		// Expected winner did not initilized, Part 3 is not working, so skip this method
		if( expectedWinner == NULL || (expectedWinner[0] != 'B' && expectedWinner[0] != 'P'))
			return;
			
		// Check whether expected winner is alive or not
		if( (this->expectedWinner[0] == 'B' && node->blastoise->isDead)  // If blastoise should be won, then blastoise must be alive
		  || (this->expectedWinner[0] == 'P' && node->pikachu->isDead) ) // If pikachu should be won, then pikachu must be alive
		  return;
		
		// This block should run only once to get first easiest path
		if(isItFirst){
			this->nodeWhichHasEasiestPath = node;
			isItFirst = false;
		}	
	}
}


void BreadthFirstSearch::setExpectedWinner(char winner){
	this->expectedWinner[0] = winner;
}


void BreadthFirstSearch::printEasiestPath(){
	if(this->nodeWhichHasEasiestPath == NULL){
		// Somebody is won but its not expected
		if(canSomebodyWin){
			if(expectedWinner[0] == 'B'){
				printf("I'm sorry. There is not any possible action sequence for Blastoise to win this game :(\n");
			}
			else if(expectedWinner[0] == 'P'){
				printf("I'm sorry. There is not any possible action sequence for Pikachu to win this game :(\n");
			}
		}
		// Game is going on
		else{
			printf("There is not any easiest path in this graph\nNobody is dead. Game is going on!\n");
		}
		return;
	}
	
	// TEST: PRINTING THE NODE WHICH HAS EASIEST PATH 
	//nodeWhichHasEasiestPath->printStatus();
	
	// Getting the probability and level count
	float probability = nodeWhichHasEasiestPath->stats->probability;
	int levelCount = 0;
	
	// Stack is needed to reverse the order from current node to the head node while printing
	stack <GameStatus*> easiestPath;
	
	GameStatus* iterator = nodeWhichHasEasiestPath;
	while(iterator->parent != NULL){
		easiestPath.push(iterator);
		iterator = iterator->parent;
		levelCount++;
	}
	
	
	// Now we can print the easiest path in order
	int pathSize = easiestPath.size();
	for(int i=0; i<pathSize; i++){
		GameStatus* currentNode = easiestPath.top();
		
		if(currentNode->stats->turn == 'B')
			printf("\tPikachu ");
		else if(currentNode->stats->turn == 'P')
			printf("\tBlastoise ");
		printf("used %s.", currentNode->usedSkillName);
		if(currentNode->isSkillEffective)
			printf("It's effective.\n");
		else
			printf("It's noneffective.\n");
		
		easiestPath.pop();
	}
	
	printf("\tLevel count : %d\n", levelCount);
	printf("\tProbability : %f\n", probability);	
}

#endif
