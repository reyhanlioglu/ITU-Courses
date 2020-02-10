/****************************
*							*
*		BLG 335E 			*
*      HOMEWORK 2			*
*   EMRE REYHANLIOGLU 		*
*      150140126			*
*							*
****************************/


// EventNode Class

#ifndef EVENTNODE_H
#define EVENTNODE_H

#include <iostream>
#include <cstring> 

#include "Event.h"

enum EventType{
	START,
	END
};

class EventNode{
	private:
		char* eventName;
		EventType eventType;
		int eventTime;
		
	
	public:
		EventNode(char* eventName, int eventTime, EventType eventType, int index);
		~EventNode();
		EventType getEventType(); 
		char* getEventName();
		int getEventTime();
		int index;
};

EventNode::EventNode(char* eventName, int eventTime, EventType eventType, int index){
	this->index = index;
	this->eventName = new char[strlen(eventName)+1];
	strcpy(this->eventName, eventName);
	
	this->eventType = eventType;
	this->eventTime = eventTime;
}

EventNode::~EventNode(){
	delete(this->eventName);
}

char* EventNode::getEventName(){
	char* temp = new char[strlen(eventName)+1];
	strcpy(temp, this->eventName);
	return temp;
}

int EventNode::getEventTime(){
	return this->eventTime;
}

EventType EventNode::getEventType(){
	return this->eventType;
}


#endif

