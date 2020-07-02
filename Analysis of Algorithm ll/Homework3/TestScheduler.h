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



#ifndef TESTSCHEDULER_H
#define TESTSCHEDULER_H


#include <iostream>
#include <cstring>

#include "TestSuite.h"



using namespace std;



class TestScheduler{
	private:
		int** V;
		int* selectedSuites;
		
		
		int getMax(int a, int b);
		bool isValueComingFromPreviousRow(int row, int col);
		int findIndexOfValueAtGivenRow(int value, int row, int rowSize);
		int calculateTotalRunningTime();
		
	
	public:
		TestScheduler(TestSuite** testSuiteList, int numberOfTestSuites, int maxRunningTime);
		~TestScheduler();
		TestSuite** testSuiteList;
		int numberOfTestSuites;
		int maxRunningTime;
		int totalRunningTime;
		
		void orderByMaximizingBugDetectionRate();
		void orderByEarlyBugs();
		
			
};

// Constructor
TestScheduler::TestScheduler(TestSuite** testSuiteList, int numberOfTestSuites, int maxRunningTime){
	this->testSuiteList = testSuiteList;
	this->numberOfTestSuites = numberOfTestSuites;
	this->maxRunningTime = maxRunningTime;
	this->selectedSuites = new int[numberOfTestSuites];
	this->totalRunningTime = 0;
	
	this->V = new int*[numberOfTestSuites+1];
	for(int i=0; i<numberOfTestSuites+1; i++){
		this->V[i] = new int[maxRunningTime+1];
	}
	
	for(int i=0; i<numberOfTestSuites+1; i++)
		for(int j=0; j<maxRunningTime+1; j++)
			V[i][j] = 0;
	

}

// Destructor
TestScheduler::~TestScheduler(){
	for(int i=0; i<this->numberOfTestSuites; i++){
		delete this->testSuiteList[i];
	}
	delete[] this->testSuiteList;
	
	for(int i=0; i<numberOfTestSuites+1; i++){
		delete this->V[i];
	}
	delete[] this->V;
	delete(this->selectedSuites);
}


void TestScheduler::orderByMaximizingBugDetectionRate(){
	
	int timeArray[numberOfTestSuites];
	int bugsArray[numberOfTestSuites];
	
	for(int i=0; i<numberOfTestSuites; i++){
		timeArray[i] = this->testSuiteList[i]->runningTime;
		bugsArray[i] = this->testSuiteList[i]->numberOfBugs;
	}
	
		
	
	for(int i=1; i<numberOfTestSuites+1; i++){
		for(int j=1; j<maxRunningTime+1; j++){
			int value = 0;
			
			if(j - timeArray[i-1] < 0){
				value = V[i-1][j];
			}
			else{
				value = getMax( V[i-1][j], V[i-1][j - timeArray[i-1]] + bugsArray[i-1] );
			}
			
			V[i][j] = value;
		}
	}
	
	
	for(int i=0; i<numberOfTestSuites; i++){
		selectedSuites[i] = 0;
	}
	
	int totalValue = V[numberOfTestSuites][maxRunningTime];
	int currentRow = numberOfTestSuites;
	int currentCol = maxRunningTime;
	
	
	
	while(totalValue > 0){
		bool isItFromPreviousLine = isValueComingFromPreviousRow(currentRow, currentCol);
		
		if(isItFromPreviousLine){
			currentRow--;
		}
		else{
			selectedSuites[currentRow-1] = 1;
			
			// Subtract the row's value from total value
			totalValue -= bugsArray[currentRow-1];
			
			// Find the updated value's index in the row
			currentCol= findIndexOfValueAtGivenRow(totalValue, currentRow, maxRunningTime+1);
		}
	}
	
	// PRINTING RESULTS
	cout<<"Optimum selected set of test suites is {";
	for(int i=0; i<numberOfTestSuites; i++){
		if(selectedSuites[i] == 1){
			cout<<this->testSuiteList[i]->id<<",";
		}
	}
	cout<<"}"<<endl;
	
	cout<<"The number of previously discovered bugs by running these test suites is "<<V[numberOfTestSuites][maxRunningTime]<<endl;

}


void TestScheduler::orderByEarlyBugs(){
	int totalRunningTime = calculateTotalRunningTime();
	
	cout<<"\n\nTotal amount of running time: "<<totalRunningTime<<endl;
	
	cout<<"\nSelected test suites' cases are ordered according to early bug detection algorithm:\n";
	for(int i=0; i<this->numberOfTestSuites; i++){
		if(this->selectedSuites[i] != 0){
			this->testSuiteList[i]->findMaximumCoverageTestCase();
			this->testSuiteList[i]->orderTestCasesByCoverage();
			this->testSuiteList[i]->printOrderedTestIds();	
		}
	}

}




// HELPER METHODS FOR PART 1
int TestScheduler::getMax(int a, int b){
	return a >= b ? a: b;
}


bool TestScheduler::isValueComingFromPreviousRow(int row, int col){
	if(row < 1 || col < 0)
		return false;
		
	if(this->V[row][col] == this->V[row-1][col]){
		return true;
	}
		
	
	return false;
}


int TestScheduler::findIndexOfValueAtGivenRow(int value, int row, int rowSize){
	for(int i=0; i<rowSize; i++){
		if(V[row][i] == value){
			return i;
		}
	}
}


int TestScheduler::calculateTotalRunningTime(){
	for(int i=0; i<this->numberOfTestSuites; i++){
		if(this->selectedSuites[i] != 0){
			this->totalRunningTime += this->testSuiteList[i]->runningTime;
		}
	}
	return this->totalRunningTime;
}


#endif

