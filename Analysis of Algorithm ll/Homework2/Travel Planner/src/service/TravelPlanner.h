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


// Travel Planner Class

#ifndef TRAVELPLANNER_H
#define TRAVELPLANNER_H

#include "ShortestPathFinder.h"
#include "../data/Node.h"

#include <vector>
#include <iostream>

#define DISTANCE_MAX 999999
#define WAITING_TIME 30


using namespace std;

enum TravelStatus{
	NOT_INITIALIZED,
	NO_SOLUTION,
	BOTH_USE_SHORTEST_PATHS,
	LUCY_USES_ALTERNATIVE_PATH,
	JOSEPH_USES_ALTERNATIVE_PATH,
	BOTH_USE_ALTERNATIVE_PATHS,	
};


class TravelPlanner{
	private:
		vector<Node*> LucysPathFromHomeToDest;
		vector<Node*> LucysAlternativePathFromHomeToDest;
		
		vector<Node*> LucysPathFromDestToHome;
		vector<Node*> LucysAlternativePathFromDestToHome;
		
		vector<Node*> JosephsPathFromHomeToDest;
		vector<Node*> JosephsAlternativePathFromHomeToDest;
		
		vector<Node*> JosephsPathFromDestToHome;
		vector<Node*> JosephsAlternativePathFromDestToHome;
		
		int LucysHome, LucysDestination;
		int JosephsHome, JosephsDestination;
		
		int LucysLeavingTime;
		int JosephsLeavingTime;
		
		
		TravelStatus travelStatusForward;
		TravelStatus travelStatusBackward;
		
		vector<Node*> lucysForwardPath;
		vector<Node*> josephsForwardPath;
		
		vector<Node*> lucysBackwardPath;
		vector<Node*> josephsBackwardPath;
		
		
		bool isThereAnyCollisionFromHomeToDestination(vector<Node*> LucysPathFromHomeToDest, vector<Node*> JosephsPathFromHomeToDest);
		bool isThereAnyCollisionFromDestinationToHome(vector<Node*> LucysPathFromDestToHome, vector<Node*> JosephsPathFromDestToHome);
		
		void planForwardPath();
		void planBackwardPath();
		
		bool canWeChangeLucysForwardPath();
		bool canWeChangeJosephsForwardPath();
		bool canWeChangeBothForwardPaths();
		
		
		
	
	public:
		TravelPlanner(int LucysHome, int LucysDestination, int JosephsHome, int JosephsDestination, int** adjacencyMatrix, int numberOfNodes);
		void plan();
		void showPlannedTravelDetails();
		
};


TravelPlanner::TravelPlanner(int LucysHome, int LucysDestination, int JosephsHome, int JosephsDestination, int** adjacencyMatrix, int numberOfNodes){
	this->LucysHome = LucysHome;
	this->LucysDestination = LucysDestination;
	this->JosephsHome = JosephsHome;
	this->JosephsDestination = JosephsDestination;
	
	this->LucysLeavingTime = 0;
	this->JosephsLeavingTime = 0;
	
	this->travelStatusForward = NOT_INITIALIZED;
	this->travelStatusBackward = NOT_INITIALIZED;
	
	
	// Setting Lucy's shortest paths with an alternative paths
	this->LucysPathFromHomeToDest = ShortestPathFinder(adjacencyMatrix, LucysHome, LucysDestination, numberOfNodes).find()->getShortestPath();
	this->LucysAlternativePathFromHomeToDest = ShortestPathFinder(adjacencyMatrix, LucysHome, LucysDestination, numberOfNodes).find()->getSecondShortestPath();
	
	this->LucysPathFromDestToHome = ShortestPathFinder(adjacencyMatrix, LucysDestination, LucysHome, numberOfNodes).find()->getShortestPath();
	this->LucysAlternativePathFromDestToHome = ShortestPathFinder(adjacencyMatrix, LucysDestination, LucysHome, numberOfNodes).find()->getSecondShortestPath();
	
	// Setting Josephs' shortest paths with an alternative paths
	this->JosephsPathFromHomeToDest = ShortestPathFinder(adjacencyMatrix, JosephsHome, JosephsDestination, numberOfNodes).find()->getShortestPath();
	this->JosephsAlternativePathFromHomeToDest = ShortestPathFinder(adjacencyMatrix, JosephsHome, JosephsDestination, numberOfNodes).find()->getSecondShortestPath();
	
	this->JosephsPathFromDestToHome = ShortestPathFinder(adjacencyMatrix, JosephsDestination, JosephsHome, numberOfNodes).find()->getShortestPath();
	this->JosephsAlternativePathFromDestToHome = ShortestPathFinder(adjacencyMatrix, JosephsDestination, JosephsHome, numberOfNodes).find()->getSecondShortestPath();
}


void TravelPlanner::plan(){
	this->planForwardPath();
	this->planBackwardPath();
}


void TravelPlanner::planForwardPath(){
	
	// If there is not any collision from home to destination
	if( !isThereAnyCollisionFromHomeToDestination(this->LucysPathFromHomeToDest, this->JosephsPathFromHomeToDest) ){

		// Use the shortest paths and set their leaving times based on these paths
		LucysLeavingTime = LucysPathFromHomeToDest.at(LucysPathFromHomeToDest.size() - 1)->distanceFromReferencePoint + WAITING_TIME;
		JosephsLeavingTime = JosephsPathFromHomeToDest.at(JosephsPathFromHomeToDest.size() - 1)->distanceFromReferencePoint + WAITING_TIME;
		
		lucysForwardPath = LucysPathFromHomeToDest;
		josephsForwardPath = JosephsPathFromHomeToDest;
		
		travelStatusForward = BOTH_USE_SHORTEST_PATHS;
	}
	
	// Else, there is a collision, check the second shortest paths
	else{
		
		// If there is not any alternative path for both of them
		if( LucysAlternativePathFromHomeToDest.size() == 0 &&  JosephsAlternativePathFromHomeToDest.size() == 0 ){
			travelStatusForward = NO_SOLUTION;
			return;
		}
		
		// If Lucy has an alternative path but Joseph does not
		else if( LucysAlternativePathFromHomeToDest.size() > 0 &&  JosephsAlternativePathFromHomeToDest.size() == 0 ){
			// Check for collision again for the alternative path 
			if( canWeChangeLucysForwardPath() ){
				// SUCCESSFULLY CHANGED
				travelStatusForward = LUCY_USES_ALTERNATIVE_PATH;
			}
			else{
				travelStatusForward = NO_SOLUTION;
				return;
			}
			
			
		}
		
		// If Joseph has an alternative path but Lucy does not
		else if( LucysAlternativePathFromHomeToDest.size() == 0 &&  JosephsAlternativePathFromHomeToDest.size() > 0 ){
			// Check for collision again for the alternative path 
			if( canWeChangeJosephsForwardPath() ){
				// SUCCESSFULLY CHANGED
				travelStatusForward = JOSEPH_USES_ALTERNATIVE_PATH;
				
			}
			else{
				travelStatusForward = NO_SOLUTION;
				return;
			}	
		}
		
		// If both of them has an alternative path, then select the shortest one without collision if possible
		else if( LucysAlternativePathFromHomeToDest.size() > 0 &&  JosephsAlternativePathFromHomeToDest.size() > 0 ){
			int lucysShortestPathLength = LucysPathFromHomeToDest.at(LucysPathFromHomeToDest.size()-1)->distanceFromReferencePoint;
			int lucysAlternativePathLength = LucysAlternativePathFromHomeToDest.at(LucysAlternativePathFromHomeToDest.size()-1)->distanceFromReferencePoint;
			int josephsShortestPathLength = JosephsPathFromHomeToDest.at(JosephsPathFromHomeToDest.size()-1)->distanceFromReferencePoint;
			int josephsAlternativePathLength = JosephsAlternativePathFromHomeToDest.at(JosephsAlternativePathFromHomeToDest.size()-1)->distanceFromReferencePoint;
			
			// If Lucy's alternative path has LESS DELAY for the overall time than Joseph's, then try to change Lucy's path
			if( lucysAlternativePathLength - lucysShortestPathLength  < josephsAlternativePathLength - josephsShortestPathLength){
				// Check for collision for the Lucy's alternative path
				if( canWeChangeLucysForwardPath() ){
					// SUCCESSFULLY CHANGED
					travelStatusForward = LUCY_USES_ALTERNATIVE_PATH;
					
				}
				// If we can't change the Lucy's path, then we have to try Joseph's alternative path
				else{
					if( canWeChangeJosephsForwardPath() ){
						// SUCCESSFULLY CHANGED
						travelStatusForward = JOSEPH_USES_ALTERNATIVE_PATH;
						
					}
					else{
						travelStatusForward = NO_SOLUTION;
					}
					
				}
			}
			// Else, Joseph's alternative path has LESS DELAY for the overall time than Lucy's, then try to change Joseph's path
			else{
				// Check for collision for the Joseph's alternative path
				if( canWeChangeJosephsForwardPath() ){
					// SUCCESSFULLY CHANGED
					travelStatusForward = JOSEPH_USES_ALTERNATIVE_PATH;	
				}
				// If we can't change the Joseph's path, then we have to try Lucy's alternative path
				else{
					if( canWeChangeLucysForwardPath() ){
						// SUCCESSFULLY CHANGED
						travelStatusForward = LUCY_USES_ALTERNATIVE_PATH;	
					}
					else{
						travelStatusForward = NO_SOLUTION;
					}	
				}	
			}
			
			// If there is still NO SOLUTION, then try to use alternative paths for both of Lucy and Joseph
			if( travelStatusForward == NO_SOLUTION){
				if( canWeChangeBothForwardPaths() ){
					// SUCCESSFULLY CHANGED
					travelStatusForward = BOTH_USE_ALTERNATIVE_PATHS;
				}
				// None of the alternative paths worked, so there is no possible solution
				else {
					travelStatusForward = NO_SOLUTION;
					return;
				}
			}		
		}
	
	}
	
}


void TravelPlanner::planBackwardPath(){
	
	
	switch(this->travelStatusForward){
		case NO_SOLUTION:
		case NOT_INITIALIZED:
			return;
		
		// Forward paths are already set, now we should set the backward paths
		case BOTH_USE_SHORTEST_PATHS:
		case LUCY_USES_ALTERNATIVE_PATH:
		case JOSEPH_USES_ALTERNATIVE_PATH:
		case BOTH_USE_ALTERNATIVE_PATHS:
			
			
			// If there is not any collision from destination to home
			if( !isThereAnyCollisionFromDestinationToHome(this->LucysPathFromDestToHome, this->JosephsPathFromDestToHome) ){
				lucysBackwardPath = LucysPathFromDestToHome;
				josephsBackwardPath = JosephsPathFromDestToHome;
				
				travelStatusBackward = BOTH_USE_SHORTEST_PATHS;
			}
			
			
			// Else, there is a collision, check the second shortest paths
			else{
		
				// If there is not any alternative path for both of them
				if( LucysAlternativePathFromDestToHome.size() == 0 &&  JosephsAlternativePathFromDestToHome.size() == 0 ){
					travelStatusBackward = NO_SOLUTION;
					return;
				}
				
				// If Lucy has an alternative path but Joseph does not
				else if( LucysAlternativePathFromDestToHome.size() > 0 &&  JosephsAlternativePathFromDestToHome.size() == 0 ){
					// Check for collision again for the alternative path 
					if( !isThereAnyCollisionFromDestinationToHome(LucysAlternativePathFromDestToHome, JosephsPathFromDestToHome) ){
						// SUCCESSFULLY CHANGED
						lucysBackwardPath = LucysAlternativePathFromDestToHome;
						josephsBackwardPath = JosephsPathFromDestToHome;
					
						travelStatusBackward = LUCY_USES_ALTERNATIVE_PATH;
					}
					else{
						travelStatusBackward = NO_SOLUTION;
						return;
					}
				}
				
				// If Joseph has an alternative path but Lucy does not
				else if( LucysAlternativePathFromDestToHome.size() == 0 &&  JosephsAlternativePathFromDestToHome.size() > 0 ){
					// Check for collision again for the alternative path 
					if( !isThereAnyCollisionFromDestinationToHome(LucysPathFromDestToHome, JosephsAlternativePathFromDestToHome) ){
						// SUCCESSFULLY CHANGED
						lucysBackwardPath = LucysPathFromDestToHome;
						josephsBackwardPath = JosephsAlternativePathFromDestToHome;
					
						travelStatusBackward = JOSEPH_USES_ALTERNATIVE_PATH;
					}
					else{
						travelStatusBackward = NO_SOLUTION;
						return;
					}
				}
				
				
				// If both of them has an alternative path, then select the shortest one without collision if possible
				else if( LucysAlternativePathFromDestToHome.size() > 0 &&  JosephsAlternativePathFromDestToHome.size() > 0 ){
					int lucysShortestPathLength = LucysPathFromDestToHome.at(LucysPathFromDestToHome.size()-1)->distanceFromReferencePoint;
					int lucysAlternativePathLength = LucysAlternativePathFromDestToHome.at(LucysAlternativePathFromDestToHome.size()-1)->distanceFromReferencePoint;
					int josephsShortestPathLength = JosephsPathFromDestToHome.at(JosephsPathFromDestToHome.size()-1)->distanceFromReferencePoint;
					int josephsAlternativePathLength = JosephsAlternativePathFromDestToHome.at(JosephsAlternativePathFromDestToHome.size()-1)->distanceFromReferencePoint;
					
					// If Lucy's alternative path has LESS DELAY for the overall time than Joseph's, then try to change Lucy's path
					if( lucysAlternativePathLength - lucysShortestPathLength  < josephsAlternativePathLength - josephsShortestPathLength){
						// Check for collision for the Lucy's alternative path
						if( !isThereAnyCollisionFromDestinationToHome(LucysAlternativePathFromDestToHome, JosephsPathFromDestToHome) ){
							// SUCCESSFULLY CHANGED
							lucysBackwardPath = LucysAlternativePathFromDestToHome;
							josephsBackwardPath = JosephsPathFromDestToHome;
					
							travelStatusBackward = LUCY_USES_ALTERNATIVE_PATH;	
						}
						// If we can't change the Lucy's path, then we have to try Joseph's alternative path
						else{
							if( !isThereAnyCollisionFromDestinationToHome(LucysPathFromDestToHome, JosephsAlternativePathFromDestToHome) ){
								// SUCCESSFULLY CHANGED
								lucysBackwardPath = LucysPathFromDestToHome;
								josephsBackwardPath = JosephsAlternativePathFromDestToHome;
								
								travelStatusBackward = JOSEPH_USES_ALTERNATIVE_PATH;	
							}
							else{
								travelStatusBackward = NO_SOLUTION;
							}
							
						}
					}
					// Else, Joseph's alternative path has LESS DELAY for the overall time than Lucy's, then try to change Joseph's path
					else{
						// Check for collision for the Joseph's alternative path
						if( !isThereAnyCollisionFromDestinationToHome(LucysPathFromDestToHome, JosephsAlternativePathFromDestToHome) ){
							// SUCCESSFULLY CHANGED
							lucysBackwardPath = LucysPathFromDestToHome;
							josephsBackwardPath = JosephsAlternativePathFromDestToHome;
							
							travelStatusBackward = JOSEPH_USES_ALTERNATIVE_PATH;	
						}
						// If we can't change the Joseph's path, then we have to try Lucy's alternative path
						else{
							if( !isThereAnyCollisionFromDestinationToHome(LucysAlternativePathFromDestToHome, JosephsPathFromDestToHome) ){
								// SUCCESSFULLY CHANGED
								lucysBackwardPath = LucysAlternativePathFromDestToHome;
								josephsBackwardPath = JosephsPathFromDestToHome;
							
								travelStatusBackward = LUCY_USES_ALTERNATIVE_PATH;	
							}
							else{
								travelStatusBackward = NO_SOLUTION;
							}	
						}	
					}
					
					// If there is still NO SOLUTION, then try to use alternative paths for both of Lucy and Joseph
					if( travelStatusBackward == NO_SOLUTION){
						if( !isThereAnyCollisionFromDestinationToHome(LucysAlternativePathFromDestToHome, JosephsAlternativePathFromDestToHome) ){
							// SUCCESSFULLY CHANGED
							lucysBackwardPath = LucysAlternativePathFromDestToHome;
							josephsBackwardPath = JosephsAlternativePathFromDestToHome;
								
							travelStatusBackward = BOTH_USE_ALTERNATIVE_PATHS;
						}
						// None of the alternative paths worked, so there is no possible solution
						else {
							travelStatusBackward = NO_SOLUTION;
							return;
						}
					}		
				}
			}
			
			
			break;
		
		
		
	}
	
}


// CHECKING WHETHER FORWARD PATHS CAN CHANGE OR NOT
bool TravelPlanner::canWeChangeLucysForwardPath(){
	if( !isThereAnyCollisionFromHomeToDestination(LucysAlternativePathFromHomeToDest, JosephsPathFromHomeToDest) ){
		LucysLeavingTime = LucysAlternativePathFromHomeToDest.at(LucysAlternativePathFromHomeToDest.size() - 1)->distanceFromReferencePoint + WAITING_TIME;
		JosephsLeavingTime = JosephsPathFromHomeToDest.at(JosephsPathFromHomeToDest.size() - 1)->distanceFromReferencePoint + WAITING_TIME;	
		
		lucysForwardPath = LucysAlternativePathFromHomeToDest;
		josephsForwardPath = JosephsPathFromHomeToDest;
		
		return true;
	}
	return false;
}

bool TravelPlanner::canWeChangeJosephsForwardPath(){
	if( !isThereAnyCollisionFromHomeToDestination(LucysPathFromHomeToDest, JosephsAlternativePathFromHomeToDest) ){
		LucysLeavingTime = LucysPathFromHomeToDest.at(LucysPathFromHomeToDest.size() - 1)->distanceFromReferencePoint + WAITING_TIME;
		JosephsLeavingTime = JosephsAlternativePathFromHomeToDest.at(JosephsAlternativePathFromHomeToDest.size() - 1)->distanceFromReferencePoint + WAITING_TIME;
		
		lucysForwardPath = LucysPathFromHomeToDest;
		josephsForwardPath = JosephsAlternativePathFromHomeToDest;
		
		return true;
	}	
	return false;
}

bool TravelPlanner::canWeChangeBothForwardPaths(){
	if( !isThereAnyCollisionFromHomeToDestination(LucysAlternativePathFromHomeToDest, JosephsAlternativePathFromHomeToDest) ){
		LucysLeavingTime = LucysAlternativePathFromHomeToDest.at(LucysAlternativePathFromHomeToDest.size() - 1)->distanceFromReferencePoint + WAITING_TIME;
		JosephsLeavingTime = JosephsAlternativePathFromHomeToDest.at(JosephsAlternativePathFromHomeToDest.size() - 1)->distanceFromReferencePoint + WAITING_TIME;
		
		lucysForwardPath = LucysAlternativePathFromHomeToDest;
		josephsForwardPath = JosephsAlternativePathFromHomeToDest;
		
		return true;
	}	
	return false;
}





bool TravelPlanner::isThereAnyCollisionFromHomeToDestination(vector<Node*> LucysPathFromHomeToDest, vector<Node*> JosephsPathFromHomeToDest){
	int lucyPathSize = LucysPathFromHomeToDest.size();
	int josephPathSize = JosephsPathFromHomeToDest.size();
	
	// CHECKING FOR THE NODE COLLISIONS
	for(int i=0; i<lucyPathSize; i++){
		for(int j=0; j<josephPathSize; j++){
			// If they have a common node in their paths
			if( LucysPathFromHomeToDest.at(i)->index == JosephsPathFromHomeToDest.at(j)->index ){
				// Check whether their arrival times are same or not
				if( LucysPathFromHomeToDest.at(i)->distanceFromReferencePoint == JosephsPathFromHomeToDest.at(j)->distanceFromReferencePoint ){
					// They are both at the same node at the same time, so that return true
					return true;
				}
			}
		}
	}
	
	
	// CHECKING FOR THE COLLISION AT THE DESTINATION NODES FOR BOTH OF THEM
	
	int LucysDestinationNodeIndex = LucysPathFromHomeToDest.at(lucyPathSize-1)->index;
	int LucysDestinationNodeArrivalTime = LucysPathFromHomeToDest.at(lucyPathSize-1)->distanceFromReferencePoint;
	
	// If Joseph's path has Lucy's destination node, then it should be checked for 30 minutes waiting time
	for(int i=0; i<josephPathSize; i++){
		if( JosephsPathFromHomeToDest.at(i)->index == LucysDestinationNodeIndex){
			int josephsArrivalTime = JosephsPathFromHomeToDest.at(i)->distanceFromReferencePoint;
			// If Joseph comes when Lucy was still there
			if( josephsArrivalTime >= LucysDestinationNodeArrivalTime && josephsArrivalTime <= LucysDestinationNodeArrivalTime + WAITING_TIME ){
				return true;
			}
		}
	}
	
	
	
	int JosephsDestinationNodeIndex = JosephsPathFromHomeToDest.at(josephPathSize-1)->index;
	int JosephsDestinationNodeArrivalTime = JosephsPathFromHomeToDest.at(josephPathSize-1)->distanceFromReferencePoint;
	
	// If Lucy's path has Joseph's destination node, then it should be checked for 30 minutes waiting time
	for(int i=0; i<lucyPathSize; i++){
		if( LucysPathFromHomeToDest.at(i)->index == JosephsDestinationNodeIndex){
			int lucysArrivalTime = LucysPathFromHomeToDest.at(i)->distanceFromReferencePoint;
			// If Lucy comes when Joseph was still there
			if( lucysArrivalTime >= JosephsDestinationNodeArrivalTime && lucysArrivalTime <= JosephsDestinationNodeArrivalTime + WAITING_TIME ){
				return true;
			}
		}
	}
	
	// If there is not any collision up to this point, then return [false].
	return false;	
}


bool TravelPlanner::isThereAnyCollisionFromDestinationToHome(vector<Node*> LucysPathFromDestToHome, vector<Node*> JosephsPathFromDestToHome){
	
	
	int lucyPathSize = LucysPathFromDestToHome.size();
	int josephPathSize = JosephsPathFromDestToHome.size();
	
	// CHECKING FOR THE NODE COLLISIONS
	for(int i=0; i<lucyPathSize; i++){
		for(int j=0; j<josephPathSize; j++){
			// If they have a common node in their paths
			if( LucysPathFromDestToHome.at(i)->index == JosephsPathFromDestToHome.at(j)->index ){
				// Check whether their arrival times are same or not
				if( LucysPathFromDestToHome.at(i)->distanceFromReferencePoint + LucysLeavingTime == 
					JosephsPathFromDestToHome.at(j)->distanceFromReferencePoint + JosephsLeavingTime ){
					// They are both at the same node at the same time, so that return true
					return true;
				}
			}
		}
	}
	
	// CHECKING FOR THE COLLISION IF LUCY GOES JOSEPH DESTINATION NODE WHEN JOSEPH STILL AT THERE
	int josephsDestinationIndex = JosephsPathFromDestToHome.at(0)->index;
	for(int i=0; i<lucyPathSize; i++){
		// If Lucy arrives Joseph's destination before he leaves, then there is a colllision
		if( LucysPathFromDestToHome.at(i)->index == josephsDestinationIndex && 
			LucysPathFromDestToHome.at(i)->distanceFromReferencePoint + LucysLeavingTime <= JosephsLeavingTime){
			return true;
		}
	}
	
	// CHECKING FOR THE COLLISION IF JOSEPH GOES JOSEPH DESTINATION NODE WHEN LUCY STILL AT THERE
	int lucysDestinationIndex = LucysPathFromDestToHome.at(0)->index;
	for(int i=0; i<josephPathSize; i++){
		// If Lucy arrives Joseph's destination before he leaves, then there is a colllision
		if( JosephsPathFromDestToHome.at(i)->index == lucysDestinationIndex && 
			JosephsPathFromDestToHome.at(i)->distanceFromReferencePoint + JosephsLeavingTime <= LucysLeavingTime){
			return true;
		}
	}
	
	// If there is not any collision up to this point, then return [false].
	return false;
	
}



void TravelPlanner::showPlannedTravelDetails(){
	//printf("Forward status:%d, backward status:%d\n\n", this->travelStatusForward, this->travelStatusBackward);
	
	if(travelStatusForward == NO_SOLUTION){
		printf("There is not any possible solution for forward paths.\n");
		return;
	}
	
	if(travelStatusBackward == NO_SOLUTION){
		printf("There is not any possible solution for backward paths.\n");
		return;
	}
	
	// Print Joseph's path
	int josephsForwardPathSize = this->josephsForwardPath.size();
	int josephsBackwardPathSize = this->josephsBackwardPath.size();
	int josephsDuration = josephsBackwardPath.at(josephsBackwardPathSize-1)->distanceFromReferencePoint + this->JosephsLeavingTime;
	
	printf("Joseph's Path, duration: %d\n", josephsDuration);
	
	for(int i=0; i<josephsForwardPathSize; i++){
		josephsForwardPath.at(i)->printNode();
	}
	
	printf("-- return --\n");
	
	for(int i=0; i<josephsBackwardPathSize; i++){
		int nodeIndex = josephsBackwardPath.at(i)->index;
		int nodeTime = josephsBackwardPath.at(i)->distanceFromReferencePoint + this->JosephsLeavingTime;
		
		printf("Node: %d  Time: %d\n", nodeIndex, nodeTime);
		
	}
	
	
	printf("\n");
	
	
	// Print Lucy's path
	int lucysForwardPathSize = this->lucysForwardPath.size();
	int lucysBackwardPathSize = this->lucysBackwardPath.size();
	
	int lucysDuration = lucysBackwardPath.at(lucysBackwardPathSize-1)->distanceFromReferencePoint + this->LucysLeavingTime;
	
	printf("Lucy's Path, duration: %d\n", lucysDuration);
	
	for(int i=0; i<lucysForwardPathSize; i++){
		lucysForwardPath.at(i)->printNode();
	}
	
	printf("-- return --\n");
	
	for(int i=0; i<lucysBackwardPathSize; i++){
		int nodeIndex = lucysBackwardPath.at(i)->index;
		int nodeTime = lucysBackwardPath.at(i)->distanceFromReferencePoint + this->LucysLeavingTime;
		
		printf("Node: %d  Time: %d\n", nodeIndex, nodeTime);
	}
	
	
	
}







#endif

