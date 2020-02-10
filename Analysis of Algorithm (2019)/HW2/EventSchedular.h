/****************************
*							*
*		BLG 335E 			*
*      HOMEWORK 2			*
*   EMRE REYHANLIOGLU 		*
*      150140126			*
*							*
****************************/


// EventScheduler Class

#ifndef EVENTSCHEDULAR_H
#define EVENTSCHEDULAR_H

#include <iostream>
#include <cstring> 

#include "EventNode.h"

using namespace std;



class EventSchedular{
	private:
		EventNode** events;
		int numberOfEvents;
		int currentTime;
		
		EventNode* getLeftNode(EventNode* node);
		EventNode* getRightNode(EventNode* node);
		bool hasAnyChild(EventNode* node);
		void swapNodes(int pos1, int pos2);
		void minHeapify(int position);
		EventNode* popFirstEvent();
		
			
	public:
		EventSchedular(Event** events, int numberOfTotalEvents);
		void runTests();
		void printEvents();
		void buildMinHeap();
		void simulate();
				
};



EventSchedular::EventSchedular(Event** events, int numberOfEvents){
	this->currentTime = 0;
	this->numberOfEvents = 2 * numberOfEvents;
	this->events = new EventNode*[numberOfEvents * 2];

	// PUT ALL OF THE EVENTS TO THE LIST(START AND END ARE DIFFERENT EVENTS IN THIS CLASS, SO EVERYTHING IS MULTIPLIED BY 2)
	for(int i=0, j=0; i<2*numberOfEvents; i+=2, j++){
		this->events[i] = new EventNode(events[j]->getEventName(), events[j]->getStartTime(), START, i);
		this->events[i+1] = new EventNode(events[j]->getEventName(), events[j]->getEndTime(), END, i+1);
	}

	
} 

// This method heapifies the tree recursively
// If any child of the node is less then the parent, then it swaps parent with the child that has minimum event time
void EventSchedular::minHeapify(int position){
	
	int leftTime=0 , rightTime = 0, nodeTime = events[position]->getEventTime();
	
	// If there is at least 1 child
	if(hasAnyChild(events[position])){
		EventNode* leftChild = getLeftNode(events[position]);
		if(leftChild != NULL)
			leftTime = leftChild->getEventTime();
		
		EventNode* rightChild = getRightNode(events[position]);
		if(rightChild != NULL)
			rightTime = rightChild->getEventTime();
		
		
		// If there is only left child
		if(rightChild == NULL) {
			// SWAP PARENT WITH LEFT CHILD IF NEEDED
		   	if(nodeTime > events[2*position+1]->getEventTime() ){
		   		//printf("Swap Left: %d with %d\n", events[position]->getEventTime(), events[2*position+1]->getEventTime());
		   		swapNodes(position, 2*position+1);
		   		minHeapify(2*position+1);
			}		
		}
		else {
			// If left child's time is less than right child's time then swap if needed
			if(leftTime < rightTime && leftTime < nodeTime){
				//printf("Swap Left: %d with %d\n", events[position]->getEventTime(), events[2*position+1]->getEventTime());
				swapNodes(position, 2*position+1);
		   		minHeapify(2*position+1);
			} // Otherwise, swap parent with right child if needed
			else if(nodeTime > rightTime){
				//printf("Swap Right: %d with %d\n", events[position]->getEventTime(), events[2*position+2]->getEventTime());
				swapNodes(position, 2*position+2);
		   		minHeapify(2*position+2);
			}
		}
	}
}


// This method builds the min heap from deep level of the tree to the head level
void EventSchedular::buildMinHeap(){
	for(int i=numberOfEvents/2; i>=0; i--){
		//printf("EVENT %s %d will be process (i = %d)\n",events[i]->getEventName(), events[i]->getEventTime(), i);
		minHeapify(i);
	}
	
}


EventNode* EventSchedular::popFirstEvent(){
	if(this->numberOfEvents > 0){
		EventNode* firstEvent = events[0];
		events[0] = events[this->numberOfEvents-1];
		events[0]->index = 0;
		
		this->numberOfEvents--;
		minHeapify(0);
		
		return firstEvent;
	}
	else
		return NULL;
}



void EventSchedular::swapNodes(int pos1, int pos2){
	//printf("Swap %d with %d\n", events[pos1]->getEventTime(), events[pos2]->getEventTime());
	
	EventNode* temp = events[pos1];
	
	events[pos1] = events[pos2];
	events[pos1]->index = pos1;
	
	events[pos2] = temp;
	events[pos2]->index = pos2;
	
	
	//cout<<endl<<endl;
	//printEvents();
	//cout<<endl<<endl;	
}



EventNode* EventSchedular::getLeftNode(EventNode* node){
	if(this->numberOfEvents-1 < 2 * node->index +1){
		//printf("There is not any left child of Node: %s\n",node->getEventName());
		return NULL;
	}
	else 
		return this->events[2 * node->index +1];	
}


EventNode* EventSchedular::getRightNode(EventNode* node){
	if(this->numberOfEvents-1 < 2 * node->index +2){
		//printf("There is not any right child of Node: %s\n",node->getEventName());
		return NULL;
	}
	else 
		return this->events[2 * node->index +2];	
}


bool EventSchedular::hasAnyChild(EventNode* node){
	int index = node->index;
	if(this->numberOfEvents-1 < index*2 +1)
		return false;
	else
		return true;
}


void EventSchedular::printEvents(){
	for(int i=0; i<numberOfEvents; i++){
		printf("EVENT %d name:%s,  time %d,  type: %d\n", this->events[i]->index, this->events[i]->getEventName(), this->events[i]->getEventTime(), this->events[i]->getEventType());
	}
}



void EventSchedular::simulate(){
	int numberOfElements = this->numberOfEvents;
	
	if(numberOfElements == 0){
		printf("There is not any event to simulate. Please make sure your input file is full\n");
		return;
	}
	
	for(int i=0 ; this->numberOfEvents > 0; ){
		
		if(currentTime == events[0]->getEventTime()){
			EventNode* event = popFirstEvent();
			
			// PRINT STATUS
			printf("TIME %d: %s ",event->getEventTime(), event->getEventName());
			if(event->getEventType() == START)
				printf("STARTED\n");
			else if(event->getEventType() == END)
				printf("ENDED\n");
				
			// If there is not any event at this time, then increase current time of simulation by one
			if(events[0]->getEventTime() != this->currentTime)
				this->currentTime++;
			
			delete(event);
		}
		else{
			printf("TIME %d: NO EVENT\n",this->currentTime);
			this->currentTime++;
		}
		
	}
	printf("TIME %d: NO MORE EVENTS, SCHEDULER EXITS\n", this->currentTime);
}
















// This method is written only for testing purposes
void EventSchedular::runTests(){
	//TESTING
	
	// TEST 3 -> PUT ALL EVENTS ON THE LIST
	cout<<endl<<"Test 3"<<endl;
	for(int i=0; i<numberOfEvents; i++){
		printf("EVENT %d name:%s,  time %d,  type: %d\n", this->events[i]->index+1, this->events[i]->getEventName(), this->events[i]->getEventTime(), this->events[i]->getEventType());
	}
	
	// TEST 4 -> GET LEFT AND RIGHT CHILD 
	cout<<endl<<"Test 4"<<endl;
	EventNode* leftChild = getLeftNode(events[2]);
	if(leftChild != NULL)
		printf("Left child of head is %s and time: %d\n", leftChild->getEventName(), leftChild->getEventTime());
	
	EventNode* rightChild = getRightNode(events[2]);
	if(rightChild != NULL)
		printf("Left child of head is %s and time: %d\n", rightChild->getEventName(), rightChild->getEventTime());
	
}


#endif

