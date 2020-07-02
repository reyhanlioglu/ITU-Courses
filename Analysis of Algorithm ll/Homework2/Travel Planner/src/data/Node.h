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


// Node Class

#ifndef NODE_H
#define NODE_H

#include <vector>
#include <iostream>


using namespace std;


class Node{
	
	public:
		Node(int index, int distanceFromReferancePoint);
		int index;
		int distanceFromReferencePoint;
		
		bool hasContain(int nodeIndex);
		vector<Node*> pathFromReferencePoint;
		Node* clone();
		void printNode();
};



Node::Node(int index, int distanceFromReferencePoint){
	this->index = index;
	this->distanceFromReferencePoint = distanceFromReferencePoint;
	
}

Node* Node::clone(){
	Node* cloneNode = new Node(this->index, this->distanceFromReferencePoint);
	cloneNode->pathFromReferencePoint = this->pathFromReferencePoint;
	return cloneNode;
}

bool Node::hasContain(int nodeIndex){
	int length = this->pathFromReferencePoint.size();
	bool isFound = false;
	
	for(int i=0; i<length; i++){
		if(this->pathFromReferencePoint.at(i)->index == nodeIndex){
			isFound = true;
		}
	}
	
	return isFound;
}

void Node::printNode(){
	printf("Node: %d  Time: %d\n", this->index, this->distanceFromReferencePoint);
}



#endif

