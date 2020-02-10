/* @Author
* Student Name: Emre Reyhanlioglu
* Student ID : 150140126
* Date:  11/12/2018 */


#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef struct node {
	int value;
	node *next;
}node;


typedef struct stack
{
	node *head;
	node *tail;
	void create();
	void print();
	int pop( );
	void push (int );
	int getCount();
	void clearStack();
}stackAnt;

typedef struct queue
{
	node *head;
	node *tail;
	void create();
	void print();
	int removeFromBeginning( );
	void addToEnd (int );
	int getCount();
	void clearQueue();
}queueAnt;


typedef struct Ants {
	queueAnt ants ;
	queueAnt holeDepths ;
	stackAnt hole ;
	void ReadFile ( char *);
	void ShowContents ( bool );
	void CrossRoad ();
}Ants;




// METHODS OF STACK

void stack::create()
{
	head = NULL;
	tail = NULL;
}

void stack::push(int n)
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

int stack::pop()
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
		return temp;
	}  	
}

int stack::getCount()
{
	node *iter;
	int count=0;
	for(iter=head; iter!=NULL; iter=iter->next)
		count++;
	delete iter;
	return count;
}

void stack::print()
{
	node *iter = head;
	while (iter != NULL)
	{
		cout<<iter->value<<" ";
		iter = iter->next;
	}
	cout<<endl;		
}

void stack::clearStack()
{
	node *iter = head;
	node *next;
	while (iter != NULL)  
   { 
       next = iter->next; 
       free(iter); 
       iter = next; 
   } 
   head = NULL;
}
// END OF METHODS OF STACK



// METHODS OF QUEUE

void queue::create()
{
	head = NULL;
	tail = NULL;
}

void queue::addToEnd(int n)
{
	if(head == NULL)  //ADDING FIRST NODE
	{
		head = new node;
		head->value = n;
		head->next = NULL;
		tail = head;
		tail->next=NULL;
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

int queue::removeFromBeginning()
{
	int temp;
	
	//IF QUEUE IS EMPTY
	if (head == NULL)
	{
		return 0;
	}
	
	//GETTING THE FIRST ELEMENT OF QUEUE
	else
	{
		node* iter= head;
		temp = head->value;
		head = head->next;
		delete iter;
		return temp;
	}
}

int queue::getCount()
{
	node *iter;
	int count=0;
	for(iter=head; iter!=NULL; iter=iter->next)
		count++;
	delete iter;
	return count;
}

void queue::print()
{
	node *iter = head;
	while (iter != NULL)
	{
		cout<<iter->value<<" ";
		iter = iter->next;
	}
	cout<<endl;		
}

void queue::clearQueue()
{
	node *iter = head;
	node *next;
	while (iter != NULL)  
   { 
       next = iter->next; 
       free(iter); 
       iter = next; 
   } 
   head = NULL;
}



// METHODS OF ANTS
void Ants::ReadFile(char * filename)
{
	int n=0, i=0, temp=0;
	FILE *fp = fopen(filename,"r");
	
	ants.create();
	holeDepths.create();
	
	//READING N FROM THE FILE
	fscanf(fp, "%d\n", &n); 
	
	//ADDING ANTS INTO ANTS QUEUE
	for(i=0; i<n; i++)
	{
		ants.addToEnd(i+1);
	}
	
	//READING DEPTHS OF THE HOLES
	while (fscanf(fp, "%d", &temp) !=EOF)
	{
		//ERROR CONDITION
		if(temp>=n)
		{
			cout<<"The depth of the holes cannot be larger than the total number of ants N"<<endl;
			return;
		}
		//IF THERE IS NO ERROR THEN ADD INTO holeDepths QUEUE
		holeDepths.addToEnd(temp);		
	}

	fclose(fp);
}


void Ants::ShowContents (bool show)
{
	if(show)
		ants.print();
	else
		holeDepths.print();
}

void Ants::CrossRoad ()
{
	int i=0, j=0, numberOfHole=0, depth=0;
	hole.create();
	numberOfHole = holeDepths.getCount();

	for(i=0; i<numberOfHole; i++)
	{
		depth = holeDepths.removeFromBeginning();
		
		for(j=0; j<depth; j++)
		{
			hole.push(ants.removeFromBeginning());
		}
		for(j=0; j<depth; j++)
		{
			ants.addToEnd(hole.pop());
		}
	}		
}

// END OF METHODS OF ANTS


int main(int, char* argv[])
{
	Ants a;
	a.ReadFile(argv[1]);
	
	cout << "The initial Ant sequence is: ";
	a.ShowContents(1); 
	cout << "The depth of holes are: ";
	a.ShowContents (0); 
	a.CrossRoad();
	cout << "The final Ant sequence is: ";
	a.ShowContents(1);
	
	
	//FREE MEMOMERY 
	a.ants.clearQueue();
	
	return 0;
}

