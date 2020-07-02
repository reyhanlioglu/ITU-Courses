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


// Shortest and Second Shortest Path Finder by using Dijkstra Algorithm

#ifndef SHORTESTPATHFINDER_H
#define SHORTESTPATHFINDER_H

#include "AdjacentNodeFinder.h"
#include "../data/Node.h"

#include <vector>
#include <iostream>

#define DISTANCE_MAX 999999


using namespace std;


class ShortestPathFinder{
	private:
		int from;
		int to;
		int** matrix;
		int numberOfNodes;
		AdjacentNodeFinder* adjacentFinder;
		
		vector<Node*> shortestPath;
		vector<Node*> secondShortestPath; // If there is any
		
		int shortestDistance;
		int secondShortestDistance;	// If there is any
		
		void helperMethod(Node* node);
	
	public:
		ShortestPathFinder(int** adjacencyMatrix, int from, int to, int numberOfNodes);
		ShortestPathFinder* find();
		int getShortestPathLength(){return this->shortestDistance;};
		int getSecondShortestPathLength(){return this->secondShortestDistance;};
		
		vector<Node*> getShortestPath(){return this->shortestPath;}
		vector<Node*> getSecondShortestPath(){return this->secondShortestPath;}
		
		
};



ShortestPathFinder::ShortestPathFinder(int** adjacencyMatrix, int from, int to, int numberOfNodes){
	this->from = from;
	this->to = to;
	this->matrix = adjacencyMatrix;
	this->numberOfNodes = numberOfNodes;
 	this->adjacentFinder = new AdjacentNodeFinder(adjacencyMatrix, numberOfNodes);
 	
 	this->shortestDistance = DISTANCE_MAX;
 	this->secondShortestDistance = DISTANCE_MAX;
}


ShortestPathFinder* ShortestPathFinder::find(){
	// First starting node (Reference Node)
	Node* startingNode = new Node(from, 0);
	
	helperMethod(startingNode);
	
	return this;
}

void ShortestPathFinder::helperMethod(Node* node){
	
	// If destination is arrived
	if(node->index == this->to){
		node->pathFromReferencePoint.push_back(node);

		// If its shortest distance, then update variables
		if(node->distanceFromReferencePoint < shortestDistance){
			secondShortestDistance = shortestDistance;
			shortestDistance = node->distanceFromReferencePoint;
	
			secondShortestPath = shortestPath;
			shortestPath = node->pathFromReferencePoint;
		}
		// Else if its the second shortest distance, then update variables
		else if(node->distanceFromReferencePoint < secondShortestDistance){
			secondShortestDistance = node->distanceFromReferencePoint;
			secondShortestPath = node->pathFromReferencePoint;	
		}
	}

	// Else, keep going with adjacent nodes
	else {
		int* adjacentNodeIndexes = adjacentFinder->getAdjacentNodes(node->index);
		int numberOfAdjacentNodes = adjacentFinder->getNumberOfAdjacentNodes();
		
		for(int i=0; i<numberOfAdjacentNodes; i++){
			
			// If new node does not exist in the path history, then create new node from current node
			
			if( !node->hasContain(adjacentNodeIndexes[i]) ){
				// Clone the current node
				Node* clonedNode = node->clone();
				
				// Set the node index
				clonedNode->index = adjacentNodeIndexes[i];
				
				// Add current node into path history of the node
				clonedNode->pathFromReferencePoint.push_back(node);
				
				// Update the distance
				int from = node->index;
				int to = adjacentNodeIndexes[i];
				clonedNode->distanceFromReferencePoint += matrix[from][to]; // += distance between from and to
				
				// Keep going with new path RECURSIVELY
				helperMethod(clonedNode);
				
			}		
		}
	}
}



#endif

