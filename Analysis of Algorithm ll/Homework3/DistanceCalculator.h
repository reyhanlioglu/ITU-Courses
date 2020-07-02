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



#ifndef CALCULATEDISTANCE_H
#define CALCULATEDISTANCE_H


#include <iostream>
#include <cstring>

#include "TestCase.h"



using namespace std;

class DistanceCalculator{
	public:
		static int calculateDistanceBetweenTests(TestCase* testCase1, TestCase* testCase2);
};


// HELPER METHOD FOR PART 2
int DistanceCalculator::calculateDistanceBetweenTests(TestCase* testCase1, TestCase* testCase2){
	
	int size1 = testCase1->frequencyLength;
	int size2 = testCase2->frequencyLength;
	
	// Result array 
    int resultArray[size1+1][size2+1]; 
  
    // Initializing the result array
    for (int i = 0; i <size1 + 1; i++) { 
        for (int j = 0; j <size2 + 1; j++) { 
            // When first test case statement ids is empty, minimum number of operations is j
            if (i == 0){
            	resultArray[i][j] = j;
			}
            
            // When second test case statement ids is empty, minimum number of operations is i
            else if (j == 0){
            	resultArray[i][j] = i;
			}
            
            // When last statement ids are same, we can ignore it and continue with the remaining statement ids
            else if (testCase1->orderedIdList[i-1] == testCase2->orderedIdList[j-1]) 
                resultArray[i][j] = resultArray[i-1][j-1]; 
  
            // If the last statement ids are different, we should select the minimum cost of 3 operations and increment it by 1
            else{
                 resultArray[i][j] = 1 + min(min(resultArray[i][j - 1], // Insert operation
                                   		resultArray[i - 1][j]), 		// Remove operation
                                   		resultArray[i - 1][j - 1]); 	// Replace operation
			}    
        } 
    } 
  
    return resultArray[size1][size2]; 
}


#endif
