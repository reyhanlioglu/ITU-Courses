/*****************************
* (C) 2020 Emre Reyhanlýoðlu *
*    All rights reserved.	 *
*							 *
*	     BLG 336E 			 *
*       HOMEWORK 2		 	 *
*    EMRE REYHANLIOGLU 		 *
*       150140126			 *
*							 *
*****************************/


// Travel Simulation Class

#ifndef TRAVELSIMULATION_H
#define TRAVELSIMULATION_H

#include "../data/FileReader.h"
#include "../service/CreateGraph.h"
#include "../service/TravelPlanner.h"




using namespace std;


class TravelSimulation{
	private:
		TravelSimulation();
	
	public:
		static void simulate(char* filename);
};

void TravelSimulation::simulate(char* filename){
	
	FileReader fileReader(filename);
	fileReader.read();
	Path** list = fileReader.getPathList();
	
	
	int numberOfNodes = fileReader.getNumberOfNodes();
	int numberOfPaths = fileReader.getNumberOfPaths();
	
	int LucysHome = fileReader.getLucysHome();
	int LucysDestination = fileReader.getLucysDestination();
	int JosephsHome = fileReader.getJosephsHome();
	int JosephsDestination = fileReader.getJosephsDestination();
	

	
	CreateGraph graph(list, numberOfNodes, numberOfPaths);
	int** adjacencyMatrix = graph.getAdjacencyMatrix();
	
	
	TravelPlanner* travelPlanner = new TravelPlanner(
													LucysHome, LucysDestination, 
													JosephsHome, JosephsDestination,
													adjacencyMatrix, numberOfNodes
													);
													
	travelPlanner->plan();
	travelPlanner->showPlannedTravelDetails();
	
}




#endif

