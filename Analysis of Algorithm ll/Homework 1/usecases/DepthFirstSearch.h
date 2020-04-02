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


// Depth First Search algorithm

#ifndef DEPTHFIRSTSEARCH_H
#define DEPTHFIRSTSEARCH_H


#include "CreateGraph.h"



using namespace std;

class DepthFirstSearch{
	private:
		int numberOfNodes;
		GameStatus* root;
		void traverseHelper(GameStatus* node);
			
	
	public:
		DepthFirstSearch(GameStatus* root);
		void traverse();
		int getNumberOfNodes();
	
};

DepthFirstSearch::DepthFirstSearch(GameStatus* root){
	this->root = root;
	this->numberOfNodes = 0;
}


void DepthFirstSearch::traverse(){
	this->traverseHelper(this->root);
}


// Traverse helper method
void DepthFirstSearch::traverseHelper(GameStatus* node){
	if(node == NULL)
		return;
	
	else{
		int numberOfChildren = node->numberOfChildren;
		// Traverse all of the children nodes recursively
		for(int i=0; i<numberOfChildren; i++){
			traverseHelper(node->children[i]);
		}
		// Increase the number of nodes
		this->numberOfNodes++;
		
		// TESTING: Print the node to make sure the order is correct
		// node->printStatus();
	}	
}

// Getter
int DepthFirstSearch::getNumberOfNodes(){
	return this->numberOfNodes;
}


#endif
