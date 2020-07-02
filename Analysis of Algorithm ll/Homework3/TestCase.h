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



#ifndef TESTCASE_H
#define TESTCASE_H


#include <iostream>
#include <cstring>



using namespace std;




class TestCase{
	
	public:
		TestCase(int* frequencyList, int frequencyLength);
		~TestCase();
		int frequencyLength;
		int* frequencyList;
		int* orderedIdList;
		int testCoverage;
		
		void printOrderedIdList();
				
};



// Constructor
TestCase::TestCase(int* frequencyList, int frequencyLength){
	this->frequencyLength = frequencyLength;
	this->frequencyList = new int[frequencyLength];
	this->orderedIdList = new int[frequencyLength];
	this->testCoverage = 0;
	
	
	for(int i=0; i<frequencyLength; i++){
		this->frequencyList[i] = frequencyList[i];
		this->orderedIdList[i] = i+1;
		
		if(frequencyList[i] > 0){
			this->testCoverage++;
		}
	}
	
	// Simple bublesort algorithm to sort frequencies and ids
    for (int i=0; i<frequencyLength-1; i++){
	    for (int j=0; j<frequencyLength-i-1; j++){
	    	if (frequencyList[j] > frequencyList[j+1]){
	    		// Swap values
	    		int temp = frequencyList[j+1];
	    		frequencyList[j+1] = frequencyList[j];
	    		frequencyList[j] = temp;
	    		
	    		// Swap ids
	    		int temp2 = orderedIdList[j+1];
	    		orderedIdList[j+1] = orderedIdList[j];
	    		orderedIdList[j] = temp2;
	    		
			}
		}     
	}  
}



// Destructor
TestCase::~TestCase(){
	delete(this->frequencyList);
	delete(this->orderedIdList);
}



void TestCase::printOrderedIdList(){
	for(int i=0; i<this->frequencyLength; i++){
		cout<<this->orderedIdList[i]<<" ";
	}
	cout<<endl;
}



#endif

