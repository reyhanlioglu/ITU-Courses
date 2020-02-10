/*      @Author         *\
|*   Emre Reyhanlioglu  *|
\*      150140126       */

using namespace std;

#include <iostream>
#include <fstream>
#include <sstream>
#include "vector.h"
#include "polynomial.h"




Vector* readVectors(int &numberOfVectors);
Polynomial* readPolynoms(int &numberOfPolynoms);
void userInterface(Vector *vectors, Polynomial *polynoms, int&numberOfVectors, int&numberOfPolynoms);
void printMenu();
void printVectorsAndPolynoms(Vector *v, Polynomial *p);
void doPolynomialOperations(Polynomial *p, int &numberOfPolynoms);
void doVectorOperations(Vector *v, int &numberOfVectors);


int main()
{
	int numberOfVectors=0, numberOfPolynoms=0;
	
    Vector* vectors = readVectors(numberOfVectors);
    Polynomial* polynoms = readPolynoms(numberOfPolynoms);
    userInterface(vectors, polynoms, numberOfVectors, numberOfPolynoms);
    
    delete []polynoms;
    delete []vectors;
    return 0;
}




Vector* readVectors(int &numberOfVectors)
{
	int i=0, input=0;
    std::string values; 
    
    Vector* vectors;	
    ifstream file;
    file.open("Vector.txt");
    if(!file.is_open())
    {
    	cout<<"Error: Vector.txt file could not be opened!"<<endl;
    	return NULL;
	}
 	
 	//Reading the first line
	std::getline(file, values);
	std::istringstream convert( values );
	convert >> numberOfVectors;
	vectors = new Vector[numberOfVectors+1];
	
	//Reading vectors and adding them into array of vectors
    for (i=0; std::getline(file, values); i++)
    {
    	//Detecting vector's dimension (Counting number of elements in the row)
        std::istringstream is( values );
   	 	int counter = 0;
   		while( is >> input ) 
			counter++;
    	
    	//Initilizing the elements of vector
    	std::istringstream iss( values );
   	 	int *array = new int[counter];
   	 	int  j=0;
   		for(j=0; iss >> input ; j++) 
			array[j] = input;
		
		//Adding new vectors to the array
    	vectors[i] =  Vector(counter, array);
    //	vectors[i].print();	 //TESTING
    }
    file.close();
	return vectors;			
}


Polynomial* readPolynoms(int &numberOfPolynoms)
{
	int i=0, input=0;
    std::string values; 
    
    Polynomial* polynoms;	
    ifstream file;
    file.open("Polynomial.txt");
    if(!file.is_open())
    {
    	cout<<"Error: Polynomial.txt file could not be opened!"<<endl;
    	return NULL;
	}
 
 	//Reading the first line
	std::getline(file, values);
	std::istringstream convert( values );
	convert >> numberOfPolynoms;
	polynoms = new Polynomial[numberOfPolynoms+1];
	
	//Reading vectors and adding them into array of vectors
    for (i=0; std::getline(file, values); i++)
    {
    	//Detecting polynom's degree (Counting number of elements in the row)
        std::istringstream is( values );
   	 	int counter = 0;
   		while( is >> input ) 
			counter++;
		
		counter -= 1;    //First element of the line is removed
    	
    	//Initilizing the elements of polynom
    	std::istringstream iss( values );
   	 	int *array = new int[counter];
   	 	
   	 	iss >> input;
   	 	int  j=0;
   		for(j=0; iss >> input ; j++) 
   			array[j] = input;
			
		//Adding new polynoms to the array
    	polynoms[i] =  Polynomial(counter, array);
    	//cout<<polynoms[i]<<endl;  //TESTING	 	
    }
    file.close();
	return polynoms;			
}

void userInterface(Vector *vectors, Polynomial *polynoms, int&numberOfVectors, int&numberOfPolynoms)
{
	char option, overflow[200];
	bool terminate = false;
	
	cout<<"Polynomial and Vector List Program!"<<endl;
	if(vectors != NULL && polynoms != NULL)
    {
    	cout<<"Polynomials and Vectors are read from text files!"<<endl;
    	printMenu();
    	
    	
    	while(!terminate)
    	{
    		cout<<endl<<"Enter an option: ";
    		cin>>option;
			cin.getline(overflow,200,'\n');  //OVERFLOW PROTECTED
	    	switch(option)
	    	{
	    		case '0':
	    			terminate = true;
	    			break;
	    		case '1':
	    			printVectorsAndPolynoms(vectors, polynoms);
	    			break;
	    		case '2':
	    			doPolynomialOperations(polynoms, numberOfPolynoms);
	    			break;
	    		case '3':
	    			doVectorOperations(vectors, numberOfVectors);
	    			break;
	    		case '4':
	    			printMenu();
	    			break;
	    		default:
	    			cout<<"Invalid option!"<<endl;
	    			break;
			}
		}
	}
    
}

void printMenu()
{
	cout<<endl<<"Possible Actions:"<<endl;
	cout<<"1. Print Polynomial and Vector lists"<<endl;
	cout<<"2. Do a polynomial operation"<<endl;
	cout<<"3. Do a vector operation"<<endl;
	cout<<"4. Help: Print possible actions"<<endl;
	cout<<"0. Exit the program"<<endl<<endl;
}

void printVectorsAndPolynoms(Vector *v, Polynomial *p)
{
	int i;
	cout<<"Vectors:"<<endl;
	for(i=0; v != NULL && v[i].getSize()>0 ; i++)
		cout<<i+1<<". "<<v[i]<<endl;
	cout<<endl;
	
	cout<<"Polynoms:"<<endl;
	for(i=0; p != NULL && p[i].getSize()>0 ; i++)
		cout<<i+1<<". "<<p[i]<<endl;
	cout<<endl;
}

void doPolynomialOperations(Polynomial *p, int &numberOfPolynoms)
{
	cout<<"Which polynomial operation would you like to do? (+:addition, *multiplication):"<<endl;
	int op1=0, op2=0;
	char op, overflow[200];
	cin>>op1>>op>>op2;
	cin.getline(overflow,200,'\n');  //OVERFLOW PROTECTED
	
	if(op1>0 && op2>0 && op1 <= numberOfPolynoms && op2 <= numberOfPolynoms)
	{
		if(op == '*')
			cout<<"("<<p[op1-1]<<") * ("<<p[op2-1]<<") = "<<p[op1-1]*p[op2-1]<<endl;
			
		else if(op == '+')
			cout<<"("<<p[op1-1]<<") + ("<<p[op2-1]<<") = "<<p[op1-1]+p[op2-1]<<endl;	
		else
			cout<<"ERROR: Invalid operation request!"<<endl;
	}
	else
		cout<<"ERROR: Polynom could not found at that index!"<<endl;
}

void doVectorOperations(Vector *v, int &numberOfVectors)
{
	cout<<"Which vector operation would you like to do? (+:addition, *:scalar multiplication, .:dot product):"<<endl;
	int op1=0, op2=0;
	char op, overflow[200];
	cin>>op1>>op>>op2;
	cin.getline(overflow,200,'\n');  //OVERFLOW PROTECTED
	
	if(op != '*' && op1>0 && op2>0 && op1 <= numberOfVectors && op2 <= numberOfVectors) 
	{
		if(op == '.' && v[op1-1].getSize() == v[op2-1].getSize())
			cout<<v[op1-1]<<" . "<<v[op2-1]<<" = "<<v[op1-1]*v[op2-1]<<endl;
			
		else if(op == '+' && v[op1-1].getSize() == v[op2-1].getSize())
			cout<<v[op1-1]<<" + "<<v[op2-1]<<" = "<<v[op1-1]+v[op2-1]<<endl;
		
		else if(  v[op1-1].getSize() != v[op2-1].getSize() )
			cout<<"ERROR: Vectors have different sizes!"<<endl;
			
		else
			cout<<"ERROR: Vector could not found at that index!"<<endl;
	}
	
	else if(op == '*' && op1>0 && op2>0 && op1 <= numberOfVectors)
	{
		cout<<v[op1-1]<<" * "<<op2<<" = ";
		cout<<v[op1-1] * op2<<endl;
	}
	
	else
		cout<<"ERROR: Vector could not found at that index!"<<endl;
}

