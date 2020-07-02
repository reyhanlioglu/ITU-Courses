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



#ifndef TESTSUITE_H
#define TESTSUITE_H


#include <iostream>
#include <cstring>

#include "TestCase.h"
#include "DistanceCalculator.h"

#define TEST_CASE_MAX_LIMIT 50



using namespace std;




class TestSuite{
	private:
		int indexOfTestCaseThatHasMaximumCoverage;
		int* orderedTestCaseIndexes;
		int* testIdList;
		
		
	
	public:
		TestSuite();
		~TestSuite();
		string id;
		TestCase** testCaseList;
		int numberOfTestCases;
		int numberOfBugs;
		int runningTime;
		
		void addTestCase(TestCase* testCase);
		void printTestSuite();
		void printOrderedTestIds();
		int findMaximumCoverageTestCase();
		void orderTestCasesByCoverage();
				
		
};

// Constructors
TestSuite::TestSuite(){
	this->id.assign("");
	this->numberOfTestCases = 0;
	this->numberOfBugs = 0;
	this->runningTime = 0;
	this->testCaseList =  new TestCase*[TEST_CASE_MAX_LIMIT];
	this->indexOfTestCaseThatHasMaximumCoverage = 0;
	this->orderedTestCaseIndexes = new int[TEST_CASE_MAX_LIMIT];
	this->testIdList = new int[TEST_CASE_MAX_LIMIT];
}



// Destructor
TestSuite::~TestSuite(){
	for(int i=0; i<this->numberOfTestCases; i++){
		delete(this->testCaseList[i]);
	}
	delete[] this->testCaseList;
	
	delete(this->orderedTestCaseIndexes);
	delete(this->testIdList);
	
}


void TestSuite::addTestCase(TestCase* testCase){
	this->testCaseList[this->numberOfTestCases++] = testCase;
}


void TestSuite::printTestSuite(){
	cout<<"Test Suite ID: "<<this->id<<endl;
	cout<<"Number of bugs: "<<this->numberOfBugs<<endl;
	cout<<"Running time: "<<this->runningTime<<endl;
	cout<<"TEST CASES"<<endl;
	for(int i=0; i<this->numberOfTestCases; i++){
		cout<<"Test case "<<i+1<< ": ";
		TestCase* test = this->testCaseList[i];
		for(int j=0; j<test->frequencyLength; j++){
			cout<<test->frequencyList[j];
			if(j != test->frequencyLength-1){
				cout<<"-";
			}
		}
		cout<<endl;
	}
	cout<<endl<<endl;
}


int TestSuite::findMaximumCoverageTestCase(){
	int maxCoverage = 0;
	for(int i=0; i<this->numberOfTestCases; i++){
		if(this->testCaseList[i]->testCoverage > maxCoverage){
			maxCoverage = this->testCaseList[i]->testCoverage;
			this->indexOfTestCaseThatHasMaximumCoverage = i;
		}
	}
	return this->indexOfTestCaseThatHasMaximumCoverage;
}


void TestSuite::orderTestCasesByCoverage(){
	int distancesFromHighestCoveragedTest[this->numberOfTestCases];
	
	// Initilializing ids
	for(int i=0; i<this->numberOfTestCases; i++){
		testIdList[i] = i+1;
	}
	
	// Calculating distance between test cases by using Levenshtein's distance computing algorithm
	for(int i=0; i<this->numberOfTestCases; i++){
		int distance = DistanceCalculator::calculateDistanceBetweenTests(this->testCaseList[this->indexOfTestCaseThatHasMaximumCoverage], this->testCaseList[i]);
		distancesFromHighestCoveragedTest[i] = distance;
	}
	
	
	// Simple bublesort algorithm to sort test ids based on distances
    for (int i=this->numberOfTestCases-1; i>0; i--){
	    for (int j=this->numberOfTestCases-1; j>0; j--){
	    	if (distancesFromHighestCoveragedTest[j-1] < distancesFromHighestCoveragedTest[j]){
	    		// Swap distance values
	    		int temp = distancesFromHighestCoveragedTest[j-1];
	    		distancesFromHighestCoveragedTest[j-1] = distancesFromHighestCoveragedTest[j];
	    		distancesFromHighestCoveragedTest[j] = temp;
	    		
	    		// Swap ids
	    		int temp2 = testIdList[j-1];
	    		testIdList[j-1] = testIdList[j];
	    		testIdList[j] = temp2;
	    		
			}
		}
	}
	
	
	// IDs are ordered by an decreasing order but most coverage test case is at the end(0 distance to itself)
	// It should be at the beginning, so that I have to rotate my list to right circularly by 1
	int lastId = testIdList[this->numberOfTestCases-1];
	int lastDistance = distancesFromHighestCoveragedTest[this->numberOfTestCases-1];
	for(int i=this->numberOfTestCases-2; i>=0; i--){
		testIdList[i+1] = testIdList[i];
		distancesFromHighestCoveragedTest[i+1] = distancesFromHighestCoveragedTest[i];
	}
	testIdList[0] = lastId;
	distancesFromHighestCoveragedTest[0] = lastDistance;
		
}


void TestSuite::printOrderedTestIds(){
		
	cout<<this->id<<": {";
	for(int i=0; i<this->numberOfTestCases; i++){
		cout<<testIdList[i];
		if(i != this->numberOfTestCases-1){
			cout<<",";
		}
		else{
			cout<<"}\n";
		}	
	}
}



#endif

