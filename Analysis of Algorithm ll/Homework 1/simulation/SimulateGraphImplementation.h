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


// Simulation class to simulate graph implementation (Part 1)

#ifndef SIMULATEGRAPHIMPLEMENTATION_H
#define SIMULATEGRAPHIMPLEMENTATION_H

#include "../usecases/PrintLastLevelOfGraph.h"



using namespace std;


class SimulateGraphImplementation{
	private:
		SimulateGraphImplementation();
	
	public:
		static void execute(int maxLevel);
	
};


void SimulateGraphImplementation::execute(int maxLevel){
	// Starting Simulation
	printf("\nStarting Graph Implementation Simulation\n");
	printf("Please wait for results...\n\n");
	
	// Initializing Players
	Pikachu* pikachu = new Pikachu();
	Blastoise* blastoise = new Blastoise();
	
	// Defining Initial Game Status
	GameStatus* initialGameStatus = new GameStatus(
		pikachu->clone(),
		blastoise->clone(),
		new Stats(
			'P',
			1,
			0,
			0
		),
		true,
		NULL,
		new char[1]
	);
	
	// Creating Graph
	CreateGraph(pikachu, blastoise, maxLevel).execute(initialGameStatus);
	
	// Printing the results
	printf("Printing the last level nodes of the graph:\n\n");
	PrintLastLevelOfGraph::execute(initialGameStatus, maxLevel);

}


#endif

	
	
