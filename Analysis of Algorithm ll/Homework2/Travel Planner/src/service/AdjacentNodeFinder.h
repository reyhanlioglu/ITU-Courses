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


// Adjacent Node Finder Class

#ifndef ADJACENTNODEFINDER_H
#define ADJACENTNODEFINDER_H



using namespace std;


class AdjacentNodeFinder{
	private:
		int** matrix;
		int numberOfNodes;
		int numberOfAdjacentNodes;
		

	
	public:
		AdjacentNodeFinder(int** matrix, int numberOfNodes);
		int* getAdjacentNodes(int from);
		int getNumberOfAdjacentNodes();
				
};



AdjacentNodeFinder::AdjacentNodeFinder(int** matrix, int numberOfNodes){
	this->matrix = matrix;
	this->numberOfNodes = numberOfNodes;
	this->numberOfAdjacentNodes = 0;
	

}

int* AdjacentNodeFinder::getAdjacentNodes(int from){
	int* adjacentList = new int[numberOfNodes];
	numberOfAdjacentNodes = 0;
	
	for(int i=0; i<numberOfNodes; i++){
		if(matrix[from][i] != 0){
			adjacentList[numberOfAdjacentNodes++] = i;
		}
	}
	
	return adjacentList;
}

int AdjacentNodeFinder::getNumberOfAdjacentNodes(){
	return this->numberOfAdjacentNodes;
}




#endif

