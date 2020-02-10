/* @Author
Student Name: Emre Reyhanlioglu
Student ID : 150140126
Date: 20.12.2018 */ 

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

typedef struct nodeT {
	int data;
	nodeT* left;
	nodeT* right;
	bool controlled;
}nodeT;

typedef struct nodeQueue {
	int value;
	nodeQueue *next;
}node;

typedef struct queue
{
	node *head;
	node *tail;
	void create();
	void print();
	int removeFromBeginning();
	int removeFromEnd();
	void addToEnd (int );
	int getCount();
	void clearQueue();
}queue;




void constructTree(nodeT* ptr, int values[], int length, int n ){ 

	if( n < length )
	{
		ptr->data = values[n];

		if(2*n+1<length)
		{
      		ptr->left = new nodeT;
      		ptr->left->left= ptr->left->right = NULL;
      		ptr->left->controlled = false;
        	constructTree(ptr->left, values, length, 2*n+1);
		}
		
      	if(2*n+2 < length)
      	{
      		ptr->right = new nodeT;
      		ptr->right->left= ptr->right->right = NULL;
      		ptr->right->controlled = false;
        	constructTree(ptr->right, values, length, 2*n+2);	
		}    	     
    }
}

void findThePath (nodeT* head, nodeT* top, nodeT* ptr, int expectedSum, int* sum, queue* path, int* pathFound)
{	
	(*sum) += ptr->data;
	path->addToEnd(ptr->data);
	
	//IF SUM IS BIGGER THAN EXPECTED SUM, THEN BLOCK NODE'S ACCESS AND RECHECK FROM BEGINNING
	if((ptr->controlled == false) && *sum > expectedSum)
	{ 
		ptr->controlled = true;
		path->clearQueue();
		*sum = head->data;
		findThePath(head, top, top, expectedSum, sum, path, pathFound);
		return;
	}
	//IF PATH IS FOUND THEN RETURN
	if((ptr->controlled == false) && *sum == expectedSum)
	{
		*pathFound = 1;
		return;
	}
	//IF SUM IS LESS THAN EXPECTED SUM THEN GO ON
	if(ptr->controlled == false && *sum < expectedSum)
	{
		//IF THERE IS A LEFT CHILD THEN CONTINUE WITH IT
		if(ptr->left && ptr->left->controlled == false)
		{
			findThePath(head, top, ptr->left, expectedSum, sum, path, pathFound);
			return;
		}
		//IF THERE IS A RIGHT CHILD TOO THEN CONTINUE WITH IT	
		if(ptr->right && ptr->right->controlled == false)
		{	
			findThePath(head, top, ptr->right, expectedSum, sum, path, pathFound);
			 return;
		}
		
		//IF THE NODE IS AT BOTTOM THEN BLOCK NODE'S ACCESS AND RECHECK FROM BEGINNING
		if(ptr->left == NULL || ptr->right == NULL)
		{
			ptr->controlled = true;
			path->clearQueue();
			*sum = head->data;
			findThePath(head, top, top, expectedSum, sum, path, pathFound);
			return;
		}	
		//IF THE NODE'S CHILDREN HAVE CHECKED(BLOCKED) THEN BLOCK NODE'S ACCESS TOO AND RECHECK FROM BEGINNING
		if(ptr != top && ptr->left && ptr->left->controlled == true && ptr->right && ptr->right->controlled == true)
		{	
			ptr->controlled = true;
			path->clearQueue();
			*sum = head->data;
			findThePath(head, top, top, expectedSum, sum, path, pathFound);
			return;
		}
		//IF THE NODE IS TOP NODE THEN THERE IS NOT ANY PATH 
		if(ptr == top)
		{
			ptr->controlled = true;
			return;
		}		
	}
	return;
}


int main(int, char* argv[])
{
	nodeT* head = new nodeT;
	head->left=head->right=NULL;
	
	int i=0, input=0, expectedSum=0, numberOfElements=0;
	int *sum = new int;
	int *treeElements;
	int *pathFound = new int;
	*pathFound = 0;
	
	///CREATING A QUEUE FOR STORING TEXT FILE VALUES AND STORING PATH (Clearing text file values then using to store path)
	queue* myQueue = new queue;
	myQueue->create();
	
	FILE *fp = fopen(argv[1],"r"); 
	
	//READING THE FILE AND ADDING VALUES INTO QUEUE
	while(fscanf(fp,"%d", &input)!=EOF)
		myQueue->addToEnd(input);
		
	fclose(fp);
	
	//POPPING EXPECTED SUM FROM QUEUE
	expectedSum = myQueue->removeFromEnd() ;
	
	//COPYING VALUES FROM QUEUE TO DYNAMIC ARRAY
	numberOfElements = myQueue->getCount();
	treeElements = new int[numberOfElements];
	for(i=0; i<numberOfElements; i++)
		treeElements[i] = myQueue->removeFromBeginning();
	
	//CONSTRUCTING THE TREE
	constructTree(head, treeElements, numberOfElements, 0);
	
	//CHECKING THE FIRST SUBTREE 
	myQueue->clearQueue(); //Clearing the previous tree elements to use it to remember path
	*sum = head->data;	   //Setting sum to initial head value
	if(head->left)
		findThePath ( head, head->left, head->left, expectedSum, sum, myQueue , pathFound);
	if(*pathFound == 1 && head->data < expectedSum)
	{
		cout<<"Path Found: "<<head->data<<" ";
		myQueue->print();
	}
	else if (head->data == expectedSum)
		cout<<"Path Found: "<<head->data<<endl;	
	else
		cout<<"No Path Found"<<endl;
	
	
	//CHECKING THE SECOND SUBTREE 
	myQueue->clearQueue(); //Clearing previous path
	*sum = head->data;	   //Setting sum to initial head value
	*pathFound = 0;		   //Setting pathFound to false 
	if(head->right)
		findThePath ( head, head->right, head->right, expectedSum, sum, myQueue , pathFound);
	if(*pathFound == 1 && head->data < expectedSum)
	{
		cout<<"Path Found: "<<head->data<<" ";
		myQueue->print();
	}
	else if (head->data == expectedSum)
		cout<<"Path Found: "<<head->data<<endl;
	else
		cout<<"No Path Found"<<endl;

	
	//GIVING MEMORY BACK 
	myQueue->clearQueue();	
	delete head;
	delete sum;
	delete pathFound;
	delete[] treeElements;

	return 0;
}







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

int queue::removeFromEnd()
{
	int temp=0;
	node* iter=head;
	while(iter->next != tail)
		iter = iter->next;
	temp = tail->value;
	delete tail;
	tail = iter;
	tail->next=NULL;
	return temp;
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

