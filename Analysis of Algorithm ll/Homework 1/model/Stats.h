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


// Stats class which holds the status of the game at that moment

#ifndef STATS_H
#define STATS_H



class Stats{
	public:
		char turn;
		float probability;
		int level;
		bool isLeaf;
		Stats(char turn, float probability, int level, bool isLeaf);
};


Stats::Stats(char turn, float probability, int level, bool isLeaf){
	this->turn = turn;
	this->probability = probability;
	this->level = level;
	this->isLeaf = isLeaf;
}


#endif
