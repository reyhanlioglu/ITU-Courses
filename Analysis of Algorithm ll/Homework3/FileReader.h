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


// File Reader Class


#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <fstream>
#include <cstring>

#include "TestSuite.h"
#include "TestCase.h"
#include "TestScheduler.h"

#define TEST_SET_MAX_SIZE 30
#define MAX_ALLOWED_STRING_INDEX 26
#define MAX_FREQUENCY_LENGTH 50
#define MAX_TEST_SUITE_SIZE 50



using namespace std;


const int FILENAME_LENGTH = 20;




// This class reads all of the data
class FileReader{
	private:
		char* filename;
		int numberOfNodes;
		TestScheduler* testScheduler;
		
		
	
	public:
		FileReader(const char* filename);
		~FileReader();
		
		void read();
		TestScheduler* getTestScheduler();
		
			
};


// Constructor
FileReader::FileReader(const char* filename){
	this->filename = new char[FILENAME_LENGTH];
	strcpy(this->filename, filename);
	
	this->testScheduler = NULL;
		
}


// This method opens the files provided in the constructor
void FileReader::read(){
	
	string line; 
	ifstream file;
	
	file.open(this->filename);

	 if (!file) {
        cout << "File could not be opened!";
        return;
    }
    
    // Read the first line
    getline(file, line);
    
    line = line.substr(MAX_ALLOWED_STRING_INDEX, line.length()-1);
    int maxRunningTime = stoi(line);
    
    
    // Read the empty and header lines
    getline(file, line);
	getline(file, line);
    
    TestSuite** testSuiteList = new TestSuite*[MAX_TEST_SUITE_SIZE];
	int numberOfTestSuites = 0;
    
    // Read test suites one by one
    for(int i=0; getline(file, line); i++){
    	TestSuite* testSuite = new TestSuite();
    	string testSuiteId;
    	int numberOfBugs, runningTime, numberOfTestCases = 0;
    	
    	// Find the first space character's position to read test suite id
    	int pos = line.find(" ");
    	
    	testSuiteId = line.substr(0, pos);
    	testSuite->id.assign(testSuiteId);
    	line.erase(0, pos + 1);
    	
    	// Find the first space character's position to read number of detected bugs
    	pos = line.find(" ");
    	
    	numberOfBugs = stoi(line.substr(0, pos));
    	testSuite->numberOfBugs = numberOfBugs;
    	line.erase(0, pos + 1);
    	
    	
    	// Find the first space character's position to read running time of the test suite
    	pos = line.find(" ");
    	
    	runningTime = stoi(line.substr(0, pos));
    	testSuite->runningTime = runningTime;
    	line.erase(0, pos + 1);
    	
    	// Read and parse test cases 
    	while ((pos = line.find(" ")) != std::string::npos) {
    		int* frequencyArray = new int[MAX_FREQUENCY_LENGTH];
    		int frequencyLength = 0;
    		
		    string testCase = line.substr(0, pos);
		    line.erase(0, pos + 1);
		    
		    string frequency;
		    while ((pos = testCase.find("-")) != std::string::npos) {
			    frequency = testCase.substr(0, pos);
			    frequencyArray[frequencyLength++] = stoi(frequency);
			    testCase.erase(0, pos + 1); 
			}
			frequencyArray[frequencyLength++] = stoi(testCase);
			
			// Add test case into test suite
			testSuite->addTestCase(new TestCase(frequencyArray, frequencyLength));
			
		}
		
		
		// Read and parse the last test case
		//cout<<line<<endl;
		
		int* frequencyArray = new int[MAX_FREQUENCY_LENGTH];
    	int frequencyLength = 0;
		
		string freq;
	    while ((pos = line.find("-")) != std::string::npos) {
		    freq = line.substr(0, pos);
		    frequencyArray[frequencyLength++] = stoi(freq);
		    line.erase(0, pos + 1); 
		}
		frequencyArray[frequencyLength++] = stoi(line);
		
		// Add last test case into test suite
		testSuite->addTestCase(new TestCase(frequencyArray, frequencyLength));
	
    	
    	testSuiteList[numberOfTestSuites++] = testSuite;
    	
	}
	
	
	this->testScheduler = new TestScheduler(testSuiteList, numberOfTestSuites, maxRunningTime);
  
	file.close();
}


TestScheduler* FileReader::getTestScheduler(){
	return this->testScheduler;
}



FileReader::~FileReader(){
	delete(this->filename);
	delete(this->testScheduler);
	
}


#endif

