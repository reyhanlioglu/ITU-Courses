/* @Author
* Student Name: Emre Reyhanlioglu
* Student ID : 150140126
* Date:  30/11/2018 */


#include <iostream>
#include <stdio.h>

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
}stack;



//METHODS OF STACK
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
	if (head == NULL)
	{
		cout<<"Stack is empty. You can't pop anymore!"<<endl;
		return 0;
	}
	
	else if(head == tail && head !=NULL)  //POPPING THE LAST NODE
	{
		temp = head->value;
		head = NULL;
		tail = NULL;
		return temp;	
	}	

	else   //POPPING OTHER NODES
	{
		node *iter = head;
		while (iter->next != tail)
			iter = iter->next;
		
		temp = tail->value;
		tail = iter;
		delete tail->next;
		tail->next = NULL;
		//delete iter; yazinca neden program cokuyor? 
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
}


int main()
{
	int tableDeckCount=0, playerDeckCount=0, tableDeckValue=0, playerDeckValue=0, i=0, j=0;
	bool gameContinues = true;
	
	FILE *fp = fopen("1.game","r");
	
	//READING THE FIRST LINE OF FILE
	fscanf(fp , "%d %d\n", &tableDeckCount , &playerDeckCount); //******SHOULD BE EDITED FOR MAIN PARAMETERS **********
	
	//DEFINING A TABLE STACK
	stack *table = new stack;
	table->create();
	
	//DEFINING A BIN STACK
	stack *bin = new stack;
	bin->create();
	
	//READING TABLE DECK AND PUSHING THEM INTO STACK
	for(i=0; i<tableDeckCount; i++)
	{
		fscanf(fp , "%d ", &tableDeckValue);
		table->push(tableDeckValue);
	}
	
	//DEFINING PLAYERS' DECK STACKS
	stack *player1 = new stack;
	stack *player2 = new stack;
	player1->create();
	player2->create();
	
	//PUSHING FIRST PLAYER'S DECK INTO STACK
	for(i=0; i<playerDeckCount; i++)
	{
		fscanf(fp , "%d ", &playerDeckValue);
		player1->push(playerDeckValue);
	}
	
	//PUSHING FIRST PLAYER'S DECK INTO STACK
	for(i=0; i<playerDeckCount; i++)
	{
		fscanf(fp , "%d ", &playerDeckValue);
		player2->push(playerDeckValue);
	}


	/*  //  TESTING THE INITIAL STACKS
		cout<<endl<<"Initial Table Deck: ";
		table->print();
		cout<<endl<<"Initial Player1 Deck: ";
		player1->print();
		cout<<endl<<"Initial Player2 Deck: ";
		player2->print();
		cout<<endl<<"Initial Bin Deck: ";
		bin->print();
		cout<<endl<<endl;
	*/					
	
	//NUMBER OF ROUND OF GAME IS tableDeckCount	
	for(i=0; i<tableDeckCount && gameContinues; i++)
	{
		int currentTableValue=table->pop();
		
		//GAME OVER
		if (currentTableValue == 0)
		{
			gameContinues = false;
		}
		
		//IF TABLE HAS A POSSITIVE VALUE
		else if(currentTableValue>0)
		{
			if(i%2 == 0) //IF FIRST PLAYER IS PLAYING
			{
				//SECOND PLAYER GIVES currentTableValue CARDS to FIRST PLAYER or to BIN
				for(j=0; j<currentTableValue; j++)
				{
					if(player2->tail == NULL)
					{
						//FIRST PLAYER WINS
						gameContinues = false;
						break;
					}
					else if(player2->tail->value > player1->tail->value)
					{
						player1->push(player2->pop());
					}
						
					else
					{
						bin->push(player2->pop());
					}
								
				}
			}
			else  //IF SECOND PLAYER IS PLAYING
			{
				//FIRST PLAYER GIVES currentTableValue CARDS to SECOND PLAYER or to BIN
				for(j=0; j<currentTableValue; j++)
				{
					if(player1->tail == NULL)
					{
						//SECOND PLAYER WINS
						gameContinues = false;
						break;
					}
					else if(player1->tail->value > player2->tail->value)
					{
						player2->push(player1->pop());
					}
					else
					{
						bin->push(player1->pop());
					}
				}
			}
		}
		
		//IF TABLE HAS A NEGATIVE VALUE
		else
		{
			currentTableValue *= -1;
			if(i%2 == 0) //IF FIRST PLAYER IS PLAYING
			{
				//FIRST PLAYER GIVES currentTableValue CARDS to SECOND PLAYER or to BIN
				for(j=0; j<currentTableValue; j++)
				{
					if(player1->tail == NULL)
					{
						//SECOND PLAYER WINS
						gameContinues = false;
						break;
					}
					else if( (player1->tail->value) > (player2->tail->value))
					{
						player2->push(player1->pop());
					}
						
					else
					{
						bin->push(player1->pop());
					}
				
							
				}
				
			}
			else  //IF SECOND PLAYER IS PLAYING
			{
				//SECOND PLAYER GIVES currentTableValue CARDS to FIRST PLAYER or to BIN
				for(j=0; j<currentTableValue; j++)
				{
					if(player2->tail == NULL)
					{
						//FIRST PLAYER WINS
						gameContinues = false;
						break;
					}
					else if(player2->tail->value > player1->tail->value)
					{
						player1->push(player2->pop());
					}
					else
					{
						bin->push(player2->pop());
					}				
				}
			}
		}
		
	/*	//	TESTING BY PRINTING THE STACKS
		cout<<"\n   "<<i+1<<". Round\n"<<endl<<"Table Deck: ";
		table->print();
		cout<<endl<<"Bin Deck: ";
		bin->print();
		cout<<endl<<"Player1 Deck: ";
		player1->print();
		cout<<endl<<"Player2 Deck: ";
		player2->print();
		cout<<endl<<endl;
	*/
	}
	
	//PRINTING THE RESULT WHICH IS NUMBER OF ELEMENTS IN BIN STACK
	cout<<bin->getCount();

	
	
	//DELETING THE POINTERS
	delete bin;
	delete table;
	delete player1;
	delete player2;
	
	return 0;
}
