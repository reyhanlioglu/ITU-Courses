/*
 * runtime.cpp
 *
 *      Author: Emre Reyhanlioglu
 *      Number: 150140126
 */

#include "runtime.h"
#include <iostream>
#include <fstream>
#include <sstream>


#define outOfScope 1999999
#define STATEMENT_LIMIT 999

using namespace std;

AddressValue executeStatement( const Statement & statement, 
			       const AddressValue currentAddress, 
			       ScalarValue variables [5], 
			       Stack<ScalarValue> & callStack, 
			       const AddressValue addressOfCalleeIfCall, 
			       bool & isDone )
{
	//These for unused parameters to go warnings away
    (void) variables;
    (void) callStack;
    (void) isDone;
    (void) addressOfCalleeIfCall;
    
    //Your entry point is here
    
    int temp=outOfScope;
    
    if(statement.arg2=="a")
    	temp = variables[0];
	else if(statement.arg2=="b")
    	temp = variables[1];
	else if(statement.arg2=="c")
    	temp = variables[2];
	else if(statement.arg2=="d")
    	temp = variables[3];
    else if(statement.arg2=="e")
    	temp = variables[4];

	
    
    if( statement.type == "inc")
    {
    	if(temp == outOfScope)
    		std::istringstream ( statement.arg2 ) >> temp;
    	
    	if(statement.arg1 == "a")
    		variables[0] += temp;
    	else if(statement.arg1 == "b")
    		variables[1] += temp;
    	else if(statement.arg1 == "c")
    		variables[2] += temp;
    	else if(statement.arg1 == "d")
    		variables[3] += temp;
    	else if(statement.arg1 == "e")
    		variables[4] += temp;
    	else{
    		//ERROR
		}
	}
	
	else if( statement.type == "dec")
    {
    	if(temp == outOfScope)
    		std::istringstream ( statement.arg2 ) >> temp;
    	
    	if(statement.arg1 == "a")
    		variables[0] -= temp;
    	else if(statement.arg1 == "b")
    		variables[1] -= temp;
    	else if(statement.arg1 == "c")
    		variables[2] -= temp;
    	else if(statement.arg1 == "d")
    		variables[3] -= temp;
    	else if(statement.arg1 == "e")
    		variables[4] -= temp;
    	else{
    		//ERROR
		}	
	}
	
	else if( statement.type == "mul")
    {
    	if(temp == outOfScope)
    		std::istringstream ( statement.arg2 ) >> temp;
    	
    	if(statement.arg1 == "a")
    		variables[0] *= temp;
    	else if(statement.arg1 == "b")
    		variables[1] *= temp;
    	else if(statement.arg1 == "c")
    		variables[2] *= temp;
    	else if(statement.arg1 == "d")
    		variables[3] *= temp;
    	else if(statement.arg1 == "e")
    		variables[4] *= temp;
    	else{
    		//ERROR
		}	
	}
	
	else if( statement.type == "div")
    {
    	if(temp == outOfScope)
    		std::istringstream ( statement.arg2 ) >> temp;
    	
    	if(statement.arg1 == "a")
    		variables[0] /= temp;
    	else if(statement.arg1 == "b")
    		variables[1] /= temp;
    	else if(statement.arg1 == "c")
    		variables[2] /= temp;
    	else if(statement.arg1 == "d")
    		variables[3] /= temp;
    	else if(statement.arg1 == "e")
    		variables[4] /= temp;
    	else{
    		//ERROR
		}	
	}
	
	else if( statement.type == "return")
	{
		//If callStack is empty
		if(callStack.getCount() == 0)
		{
			isDone = true;
			
			if(statement.arg1 =="a")
				cout<<variables[0]<<endl;
			else if(statement.arg1 =="b")
				cout<<variables[1]<<endl;
			else if(statement.arg1 =="c")
				cout<<variables[2]<<endl;
			else if(statement.arg1 =="d")
				cout<<variables[3]<<endl;
			else if(statement.arg1 =="e")
				cout<<variables[4]<<endl;
			
			return -1;
		}
		else
		{
			AddressValue poppedAddress = callStack.pop();
			if(statement.arg1 != "e")
				variables[4]=callStack.pop();
			else 
				callStack.pop();
				
			if(statement.arg1 != "d")
				variables[3]=callStack.pop();
			else 
				callStack.pop();
				
			if(statement.arg1 != "c")
				variables[2]=callStack.pop();
			else 
				callStack.pop();
				
			if(statement.arg1 != "b")
				variables[1]=callStack.pop();
			else 
				callStack.pop();
				
			if(statement.arg1 != "a")
				variables[0]=callStack.pop();
			else 
				callStack.pop();
				
			return poppedAddress+1;
		}
	}
	
	else if( statement.type == "call")
	{
		callStack.push(variables[0]);
		callStack.push(variables[1]);
		callStack.push(variables[2]);
		callStack.push(variables[3]);
		callStack.push(variables[4]);
		callStack.push(currentAddress);
		
		if(statement.arg2 == "a")
		{
			variables[1]=0;	variables[2]=0; variables[3]=0; variables[4]=0;
		}
		else if(statement.arg2 == "b")
		{
			variables[0]=0;	variables[2]=0; variables[3]=0; variables[4]=0;
		}
		else if(statement.arg2 == "c")
		{
			variables[0]=0;	variables[1]=0; variables[3]=0; variables[4]=0;
		}
		else if(statement.arg2 == "d")
		{
			variables[0]=0;	variables[1]=0; variables[2]=0; variables[4]=0;
		}
		else if(statement.arg2 == "e")
		{
			variables[0]=0;	variables[1]=0; variables[2]=0; variables[3]=0;
		}
		
		
		return addressOfCalleeIfCall+1;
		
	}
    
    //Return what address you want to go next
    return currentAddress + 1;
}

template <typename T> void Stack<T>::create()
{
	head = NULL;
	tail = NULL;
}

template <typename T> void Stack<T>::print()
{
	node *iter = head;
	while (iter != NULL)
	{
		printf("%d ",iter->value);
		iter = iter->next;
	}
}

template <typename T> int Stack<T>::pop()
{
	int temp;

	//IF STACK IS EMPTY
	if (head == NULL)
	{
		return 0;
	}
	
	//POPPING THE LAST NODE
	else if(head == tail && head !=NULL)  
	{
		temp = head->value;
		head = NULL;
		tail = NULL;
		return temp;	
	}	

	//POPPING OTHER NODES
	else   
	{
		node *iter = head;
		while (iter->next != tail)
			iter = iter->next;
		
		temp = tail->value;
		tail = iter;
		delete tail->next;
		tail->next = NULL;
		//delete iter; yazinca neden program sacmaliyor? 
		return temp;
	}
}

template <typename T> void Stack<T>::push(int n)
{
	if(head == NULL)  //ADDING FIRST NODE
	{
		head = new node;
		head->value = n;
		head->next = NULL;
		tail = head;
		return;	
	}


	else   //ADDING OTHER NODES
	{
		tail->next = new node;
		tail= tail->next;
		tail->value = n;
		tail->next = NULL; 
	}   	
}

template <typename T> int Stack<T>::getCount()
{
	node *iter;
	int count=0;
	for(iter=head; iter!=NULL; iter=iter->next)
		count++;
	delete iter;
	return count;
}



int main(int, char *argv[]) 
{

	Statement *statement = new Statement[STATEMENT_LIMIT];
	string line;
	int lineIndex=0, numberOfLine=0;
	
	std::ifstream infile(argv[1]);
	
	//PARAMETERS
	AddressValue currentAddress;
	AddressValue addressOfCalleeIfCall;
	Stack<ScalarValue>  callStack;
	bool isDone = false;
	ScalarValue variables [5] = {0,0,0,0,0};
	
	callStack.create();
	
	
	//READING ALL OF THE STATEMENTS 
	for( std::string line; getline( infile, line ); lineIndex++)
	{
	    istringstream iss(line);
	    string word;
	    while(iss >> word) 
		{
	    	statement[lineIndex].arg1="";
	    	statement[lineIndex].arg2="";
	    	statement[lineIndex].type = word;
	    	
	    	if(iss >>word)
	    		statement[lineIndex].arg1=word;
	    	if(iss >> word)
	    		statement[lineIndex].arg2=word;
	    }    
	}
	numberOfLine = lineIndex;
	
	
	//Search for main function
	for(lineIndex=0; lineIndex<numberOfLine; lineIndex++)
	{
		if(statement[lineIndex].arg1 == "main")
		{
			currentAddress = lineIndex;
			break;
		}
	}
	currentAddress++;
	
	while( !isDone )
	{
		if(statement[currentAddress].type == "call")
		{
			for(lineIndex=0; lineIndex<numberOfLine; lineIndex++)
			{
				if( (statement[currentAddress].arg1 == statement[lineIndex].arg1) &&(statement[lineIndex].type =="function") )
				{
					addressOfCalleeIfCall = lineIndex;
					break;
				}
			}
		}
		else
			addressOfCalleeIfCall =0;
			
		
		currentAddress = executeStatement(statement[currentAddress], currentAddress, variables, callStack,
						 addressOfCalleeIfCall, isDone);
	}
	delete [] statement;
	return 0;	
}


