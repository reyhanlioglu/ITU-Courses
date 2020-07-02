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


// File Reader Class

#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <fstream>
#include <cstring>

#include "../data/Path.h"

#define PATH_LIST_MAX_SIZE 200


using namespace std;


const int FILENAME_LENGTH = 20;

// This class reads all of the paths and other necessary informations from the given text file
class FileReader{
	private:
		char* filename;
		Path** pathList;
		int JH, JD, LH, LD;
		int numberOfNodes;
		int numberOfPaths;
		
	
	public:
		FileReader(const char* filename);
		~FileReader();
		void read();
		
		// GETTERS
		Path** getPathList(){return this->pathList;}
		int getNumberOfPaths(){return this->numberOfPaths;}
		int getNumberOfNodes(){return this->numberOfNodes;}
		
		int getLucysHome(){return this->LH;}
		int getLucysDestination(){return this->LD;}
		int getJosephsHome(){return this->JH;}
		int getJosephsDestination(){return this->JD;}		
};

// Constructor
FileReader::FileReader(const char* filename){
	this->filename = new char[FILENAME_LENGTH];
	strcpy(this->filename, filename);
}


// This method opens the files provided in the constructor, 
// reads all of the paths and add them into the path list
void FileReader::read(){
	int from, to, distance; 
	ifstream file;
	
	file.open(this->filename);

	 if (!file) {
        cout << "File could not be opened!";
        return;
    }
    
    // Read the number of nodes in the city
    file >> this->numberOfNodes;
    
    // Read JH, JD, LH and LD
    file >> this->JH >> this->JD >> this->LH >> this->LD;
    
    // Memory allocation for the path array
    this->pathList = new Path*[PATH_LIST_MAX_SIZE];
    
    for(int i=0; !file.eof(); i++) {
		file >> from >> to >> distance;
		this->pathList[i] = new Path(from, to, distance);
		this->numberOfPaths++;
	}
	
	file.close();
}



FileReader::~FileReader(){
	delete(this->filename);
	
	for(int i=0; i<this->numberOfPaths; i++){
		delete(this->pathList[i]);
	}
	
	delete(this->pathList);
}


#endif

