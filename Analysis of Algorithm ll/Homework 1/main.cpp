/*****************************
* (C) 2020 Emre Reyhanlýoðlu *
*    All rights reserved.	 *
*							 *
*	     BLG 336E 			 *
*       HOMEWORK 1		 	 *
*    EMRE REYHANLIOGLU 		 *
*       150140126			 *
*							 *
*****************************/


#include <iostream>
#include <cstring>

#include "simulation/SimulateGraphImplementation.h"
#include "simulation/SimulateBFS.h"
#include "simulation/SimulateDFS.h"
#include "simulation/FindEasiestPath.h"

#define PART3_MAX_LEVEL 9


using namespace std;


int main(int argc, char *argv[]){

	// Part 1 or Part 3
	if(argc == 3){
		if( strcmp(argv[1], "part1") == 0 ){
			int maxLevel = atoi(argv[2]);
			SimulateGraphImplementation::execute(maxLevel);
		}
		else if( strcmp(argv[1], "part3") == 0 ){
			char expectedWinner;
			
			// Setting the expected winner and checking for any spelling error
			if( strcmp(argv[2], "pikachu") == 0 ) expectedWinner = 'P';
			else if( strcmp(argv[2], "blastoise") == 0 ) expectedWinner = 'B';
			else {
				printf("Invalid character type. Please enter a valid character type (pikachu or blastoise)\n");
				return 0;
			}
			
			FindEasiestPath::execute(PART3_MAX_LEVEL, expectedWinner);
		}
		else{
			printf("Invalid input\n");
		}
			
	}
	// Part 2
	else if(argc == 4){
		if( strcmp(argv[1], "part2") == 0 ){
			int maxLevel = atoi(argv[2]);
			if( strcmp(argv[3], "bfs") == 0 ){
				SimulateBFS::execute(maxLevel);
			}
			else if( strcmp(argv[3], "dfs")  == 0 ){
				SimulateDFS::execute(maxLevel);
			}
		}
		else{
			printf("Invalid input\n");
		}
	}
	else{
		printf("Check your input paramteres\n");
	}

	return 0;
		
}

