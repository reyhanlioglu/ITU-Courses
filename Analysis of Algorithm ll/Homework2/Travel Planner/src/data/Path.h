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


// Path Class

#ifndef PATH_H
#define PATH_H

#include <iostream>


using namespace std;


class Path{
	
	public:
		Path(int from, int to, int distance);
		int from;
		int to;
		int distance;
		void printPathInformations();
};



Path::Path(int from, int to, int distance){
	this->from = from;
	this->to = to;
	this->distance = distance;	
}

void Path::printPathInformations(){
	printf("Distance from %d to %d is %d\n", this->from, this->to, this->distance);
}

#endif

