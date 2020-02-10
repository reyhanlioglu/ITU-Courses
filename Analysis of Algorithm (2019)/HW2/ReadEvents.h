/****************************
*							*
*		BLG 335E 			*
*      HOMEWORK 2			*
*   EMRE REYHANLIOGLU 		*
*      150140126			*
*							*
****************************/


// ReadEvents Class

#ifndef READEVENTS_H
#define READEVENTS_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "Event.h"
#define EVENT_MAX_SIZE 1000

using namespace std;



// This class reads all of the events from the given text file
class ReadEventFile{
	private:
		Event** eventList;
		int numberOfEvents;
	
	public:
		ReadEventFile(const char* filename);
		~ReadEventFile();
		Event** getEvents();
		int getNumberOfEvents();
};

// This method opens the file provided in the constructor, reads all of the events and add them to event list
ReadEventFile::ReadEventFile(char const* filename){
	this->numberOfEvents = 0;
	this->eventList = new Event*[EVENT_MAX_SIZE];
	
	string line, splitted; 
	ifstream file;
	file.open(filename);
	
	 if (!file) {
        cout << "File could not be opened!";
        return;
    }
    
    for(int i=0; getline(file, line); i++ ) {
    	int j=0, k=0;
	    
    	char *eventLine = new char[line.length()];
    	char *eventName = new char[line.length()];
    	char* eventStartTime = new char[7];
    	char* eventEndTime = new char[7];
    	
    	// Get line as a char array
    	strcpy(eventLine, line.c_str()); 
    	
    	// Read event name
		for(j=0; eventLine[j] != ' '; j++){
			eventName[j] = eventLine[j];
		}
		eventName[j++] = '\0';

		// Read start time
		for(k=0; eventLine[j] != ' '; j++, k++){
			eventStartTime[k] = eventLine[j];
		}
		eventStartTime[k] = '\0';
		j++;

		// Read end time
		for(k=0; eventLine[j] != '\0'; j++, k++){
			eventEndTime[k] = eventLine[j];
		}
		eventEndTime[k] = '\0';
		
		// Create an event object to save these results 
		Event* newEvent = new Event(eventName, std::atoi(eventStartTime), std::atoi(eventEndTime));
		
		// Add the event to the eventList
		eventList[numberOfEvents++] = newEvent;
		
		// Free the allocated memory
		delete(eventLine);
		delete(eventName);
		delete(eventStartTime);
		delete(eventEndTime);
	}
	
	file.close();
}

Event** ReadEventFile::getEvents(){
	return this->eventList;
}

int ReadEventFile::getNumberOfEvents(){
	return this->numberOfEvents;
}


ReadEventFile::~ReadEventFile(){
	// free all of the events
	for(int i=0; i<numberOfEvents; i++)
		delete(this->eventList[i]);
	
	delete (this->eventList);
}

#endif

