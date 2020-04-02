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


// Simulation class to simulate DFS algorithms (Part 2)

#ifndef SIMULATEDFS_H
#define SIMULATEDFS_H

#include "../usecases/DepthFirstSearch.h"

#include <ctime>


using namespace std;


class SimulateDFS{
	private:
		SimulateDFS();
	
	public:
		static void execute(int maxLevel);
	
};


void SimulateDFS::execute(int maxLevel){
	// Starting Simulation
	printf("\nStarting DFS Simulation\n");
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
	clock_t graphBeginTime = clock(); // Begin time to create graph
	CreateGraph(pikachu, blastoise, maxLevel).execute(initialGameStatus);
	clock_t graphEndTime = clock();   // End time to create graph
	
	// Traversing and calculating elapsed time
	DepthFirstSearch dfs = DepthFirstSearch(initialGameStatus);
	// Begin time
	clock_t traverseBeginTime = clock();
	// Traverse operation
	dfs.traverse();
	// End time
	clock_t traverseEndTime = clock();
	
	// Calculating Results
	int totalNumberOfNodes = dfs.getNumberOfNodes();
	double elapsedCreatingTimeInSeconds = double(graphEndTime - graphBeginTime) / CLOCKS_PER_SEC;
	double elapsedTraversingTimeInSeconds = double(traverseEndTime - traverseBeginTime) / CLOCKS_PER_SEC;
	
	// Printing Results
	printf("Getting the results\n\n");
	printf("Total number of nodes: %d\n", totalNumberOfNodes);
	printf("Elapsed time to create the graph is %f seconds\n", elapsedCreatingTimeInSeconds);
	printf("Elapsed time to traverse the graph with DFS is %f seconds\n", elapsedTraversingTimeInSeconds);
	
}


#endif

	
	
