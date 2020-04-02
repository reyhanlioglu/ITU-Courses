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


// ReadSkillSet Class

#ifndef READSKILLSET_H
#define READSKILLSET_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "../../model/Skill.h"


#define SKILL_MAX_SIZE 20

using namespace std;

const char* PIKACHU_TEXT_FILE = "usecases/read_skillset_from_file/pikachu.txt";
const char* BLASTOISE_TEXT_FILE = "usecases/read_skillset_from_file/blastoise.txt";


// This class reads all of the events from the given text file
class ReadSkillSet{
	private:
		int pikachuSkillCount;
		int blastoiseSkillCount;
		Skill** pikachuSkillList;
		Skill** blastoiseSkillList;
		Skill** readFromFile(const char* filename, Skill** skills);
		void dispose();
	
	public:
		ReadSkillSet();
		~ReadSkillSet();
		Skill** getPikachuSkills();
		Skill** getBlastoiseSkills();
		int getPikachuSkillCount();
		int getBlastoiseSkillCount();
		
};

// This method opens the files provided in the constructor, reads all of the skills and add them into skill lists
ReadSkillSet::ReadSkillSet(){
	this->blastoiseSkillCount = 0;
	this->pikachuSkillCount = 0;
	this->pikachuSkillList = new Skill*[SKILL_MAX_SIZE];
	this->blastoiseSkillList = new Skill*[SKILL_MAX_SIZE];
	
	readFromFile(PIKACHU_TEXT_FILE, this->pikachuSkillList);
	readFromFile(BLASTOISE_TEXT_FILE, this->blastoiseSkillList);
}


ReadSkillSet::~ReadSkillSet(){
	dispose();
}


Skill** ReadSkillSet::getPikachuSkills(){
	return this->pikachuSkillList;
}


Skill** ReadSkillSet::getBlastoiseSkills(){
	return this->blastoiseSkillList;
}

int ReadSkillSet::getPikachuSkillCount(){
	return this->pikachuSkillCount;
}

int ReadSkillSet::getBlastoiseSkillCount(){
	return this->blastoiseSkillCount;
} 


Skill** ReadSkillSet::readFromFile(const char* filename, Skill** skills){
	string line, splitted; 
	ifstream file;
	file.open(filename);

	 if (!file) {
        cout << "File could not be opened!";
        return NULL;
    }
    
    // Read the first line (unnecessary line)
    getline(file, line);
    
    for(int i=0; getline(file, line); i++ ) {
    	int j=0, k=0, len=line.length();
	    
	    char *skillLine = new char[len];
    	char *skillName = new char[len];
    	char *neededPower = new char[len];
    	char *accuracy = new char[len];
    	char *damage = new char[len];
    	char *firstUsage = new char[len];
    	
    	
    	// Increase the number of skills
    	if(strcmp(filename, PIKACHU_TEXT_FILE) == 0){
    		this->pikachuSkillCount++;
		} else if(strcmp(filename, BLASTOISE_TEXT_FILE) == 0){
    		this->blastoiseSkillCount++;
		}
    	
    	
    	// Get line as a char array
    	strcpy(skillLine, line.c_str()); 
    	
    	// Read skill name
		for(j=0; skillLine[j] != ','; j++){
			skillName[j] = skillLine[j];
		}
		skillName[j++] = '\0';
		//cout<<"Skill name is "<<skillName<<endl;

		// Read needed power
		for(k=0; skillLine[j] != ','; j++, k++){
			neededPower[k] = skillLine[j];
		}
		neededPower[k] = '\0';
		j++;
		//cout<<"Needed power is "<<neededPower<<endl;

		// Read accuracy
		for(k=0; skillLine[j] != ','; j++, k++){
			accuracy[k] = skillLine[j];
		}
		accuracy[k] = '\0';
		j++;
		//cout<<"Accuracy power is "<<accuracy<<endl;
		
		// Read damage
		for(k=0; skillLine[j] != ','; j++, k++){
			damage[k] = skillLine[j];
		}
		damage[k] = '\0';
		j++;
		//cout<<"Damage power is "<<damage<<endl;
		
		// Read first usage
		for(k=0; skillLine[j] != '\n' && skillLine[j] != '\0'; j++, k++){
			firstUsage[k] = skillLine[j];
		}
		firstUsage[k] = '\0';
		//cout<<"firstUsage is "<<firstUsage<<endl;
		

		// Create a skill object to save these results 
		Skill* newSkill = new Skill(skillName, atoi(neededPower), atof(accuracy), atof(damage), atoi(firstUsage));

		// Add the skill into the pikachu skill list
		skills[i] = newSkill;
		
		// Free the allocated memory
		delete(skillLine);
		delete(skillName);
		delete(neededPower);
		delete(accuracy);
		delete(damage);
		delete(firstUsage);
	}
	
	file.close();
}


void ReadSkillSet::dispose(){
	delete (this->pikachuSkillList);
	delete (this->blastoiseSkillList);
}



#endif

