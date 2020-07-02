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


// Create Graph Class

#ifndef CREATEGRAPH_H
#define CREATEGRAPH_H

#include "../data/Path.h"

#include <iostream>


using namespace std;


class CreateGraph{
	private:
		Path** nodes;
		int numberOfNodes;
		int numberOfPaths;
		int** matrix;
		
		void createGraph();
	
	public:
		CreateGraph(Path** nodes, int numberOfNodes, int numberOfPaths);
		int** getAdjacencyMatrix();
		void printGraph();
				
};



CreateGraph::CreateGraph(Path** nodes, int numberOfNodes, int numberOfPaths){
	this->nodes = nodes;
	this->numberOfNodes = numberOfNodes;
	this->numberOfPaths = numberOfPaths;
	
	// Allocating memory for a 2 dimensional array 
	this->matrix = new int*[numberOfNodes];
	for(int i=0; i<numberOfNodes; i++){
		this->matrix[i] = new int[numberOfNodes];
		for(int j=0; j<numberOfNodes; j++){
			matrix[i][j] = 0;
		}
	}
	
	createGraph();
}

void CreateGraph::createGraph(){
	for(int i=0; i<this->numberOfPaths; i++){
		Path* currentNode = this->nodes[i];
		
		int from = currentNode->from;
		int to = currentNode->to; 
		int distance = currentNode->distance;
	
		this->matrix[from][to] = distance;	
	}
	
}

int** CreateGraph::getAdjacencyMatrix(){
	return this->matrix;
}

void CreateGraph::printGraph(){
	for(int i=0; i<numberOfNodes; i++){
		for(int j=0; j<numberOfNodes; j++){
			printf("%d ", this->matrix[i][j]);
		}
		printf("\n");
	}
}



#endif

