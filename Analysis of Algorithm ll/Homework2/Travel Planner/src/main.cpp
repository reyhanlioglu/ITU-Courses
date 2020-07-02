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


#include <iostream>
#include <cstring>

#include "presentation/TravelSimulation.h"



using namespace std;




int main(int argc, char *argv[]){

	
	if(argc == 2){
		TravelSimulation::simulate(argv[1]);
	}

	else{
		printf("Check your input parameters\n\n");
	}
	
	return 0;	
}



