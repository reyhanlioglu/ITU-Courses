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


// Simulation class to find the easiest path by using BFS algorithm (Part 3)

#ifndef FINDEASIESTPATH_H
#define FINDEASIESTPATH_H

#include "SimulateBFS.h"

using namespace std;

class FindEasiestPath{
	private:
		FindEasiestPath();
	
	public:
		static void execute(int maxLevel, char expectedWinner);
};


void FindEasiestPath::execute(int maxLevel, char expectedWinner){
	
	// Starting Simulation
	printf("\nStarting BFS Simulation to find the easiest path if there is any\n");
	printf("I used BFS, because I need to find the closest node to the root\n\n");
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
	
	// Printing the easiest path by using BFS algorithm
	// I used BFS, because I need the closest node to the root
	BreadthFirstSearch bfs = BreadthFirstSearch(initialGameStatus);
	// Set the expected winner before travering the graph
	bfs.setExpectedWinner(expectedWinner);
	// Traversing the graph
	bfs.traverse();
	// After traversing the graph, easiest path is ready to print
	printf("Getting the results:\n\n");
	bfs.printEasiestPath();
}

#endif













