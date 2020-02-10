/****************************
*							*
*		BLG 335E 			*
*      HOMEWORK 2			*
*   EMRE REYHANLIOGLU 		*
*      150140126			*
*							*
****************************/

#include <iostream>

#include "Event.h"
#include "ReadEvents.h"
#include "EventNode.h"
#include "EventSchedular.h"

using namespace std;


int main(int argc, char** argv){
	
	// Read the event txt file 
	ReadEventFile eventFile("events-t2.txt"); 

	// Get event list 
	Event** eventList = eventFile.getEvents();
	
	// Get number of events in the event list
	int numberOfEvents = eventFile.getNumberOfEvents();
	
	// Construct an Event Scheduler which deals with everything for us 
	EventSchedular* eventSchedular = new EventSchedular(eventList, numberOfEvents);
	
	// Build the min heap
	eventSchedular->buildMinHeap();
	
/*	// Testing method which shows all of the events in the list
	cout<<endl<<endl<<endl;
	/schedular->printEvents();
	cout<<endl<<endl<<endl; 	*/
	
	// Starting the simulation
	eventSchedular->simulate();

	return 0;
}

