/****************************
*							*
*		BLG 335E 			*
*      HOMEWORK 2			*
*   EMRE REYHANLIOGLU 		*
*      150140126			*
*							*
****************************/


// EVENT CLASS 

#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <cstring> 


using namespace std;


class Event{
	private:
		char* name;
		int startTime;
		int endTime;
		
	public:
		Event(char* name, int startTime, int endTime);
		~Event();
		char* getEventName();
		int getStartTime();
		int getEndTime();	
};


Event::Event(char* name, int startTime, int endTime){
	// Set name
	this->name = new char[strlen(name)+1];
	strcpy(this->name, name);
	
	// Set start time
	this->startTime = startTime;
	
	// Set end time
	this->endTime = endTime;
}

Event::~Event(){
	delete(this->name);
}

char* Event::getEventName(){
	char* buffer =new char[strlen(this->name)+1];
	strcpy(buffer, this->name);
	return buffer;
}

int Event::getStartTime(){
	return this->startTime;
}

int Event::getEndTime(){
	return this->endTime;
}


#endif

