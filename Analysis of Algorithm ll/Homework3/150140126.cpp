/*****************************
* (C) 2020 Emre Reyhanlýoðlu *
*    All rights reserved.	 *
*							 *
*	     BLG 336E 			 *
*       HOMEWORK 3		 	 *
*    EMRE REYHANLIOGLU 		 *
*       150140126			 *
*							 *
*****************************/


#include <iostream>
#include <cstring>


#include "FileReader.h"
#include "TestScheduler.h"



using namespace std;


int main(int argc, char *argv[]){
	

	if(argc == 2){
		FileReader fileReader(argv[1]);
		
		fileReader.read();
		
		TestScheduler* testScheduler = fileReader.getTestScheduler();
	
		testScheduler->orderByMaximizingBugDetectionRate();
		testScheduler->orderByEarlyBugs();

			
	}
	else{
		printf("Check your input parameters!\n");
	}
	
	

	return 0;
		
}

