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


// Print last level class which prints the last layer informations of the graph

#ifndef PRINTLASTLEVELOFGRAPH_H
#define PRINTLASTLEVELOFGRAPH_H


#include "CreateGraph.h"


using namespace std;

class PrintLastLevelOfGraph{
	private:
		PrintLastLevelOfGraph();
		static void lastLevelPrinter(GameStatus* node, int lastLevel);
	
	public:
		static void execute(GameStatus* root, int lastLevel);
	
};


void PrintLastLevelOfGraph::execute(GameStatus* root, int lastLevel){
	lastLevelPrinter(root, lastLevel);
}

// Helper method for recursion
void PrintLastLevelOfGraph::lastLevelPrinter(GameStatus* node, int lastLevel){
	// If it is one of the last level nodes, then print it
	if(node->stats->level == lastLevel){
		printf("P_HP:%d P_PP:%d B_HP:%d B_PP:%d PROB:%.4f\n", 
				node->pikachu->HP, node->pikachu->PP, node->blastoise->HP, 
				node->blastoise->PP, node->stats->probability);
	}
	else{
		// If current node has any child, then call this function with it recursively
		int numberOfChildren = node->numberOfChildren;
		if(numberOfChildren > 0){
			for(int i=0; i<numberOfChildren; i++){
				lastLevelPrinter(node->children[i], lastLevel);
			}
		}
	}
}


#endif
