/* @Author
* Student Name: Emre Reyhanlioglu
* Student ID : 150140126
* Date:  6/11/2018 */


#include <iostream>
#include <stdio.h>

using namespace std;

typedef struct occur_node {
	char character;
	occur_node *next;
	int occurence;
}occurNode;

typedef struct vocab_node {
	char character;
	vocab_node *next;
	occur_node *list;
}vocabNode;


typedef struct vocab_list
{
	vocab_node *head;
	void create();
	void print();
	void add_char(char );
	void add_occurence(char , char );
	int get_occurence(char );
	int get_union_occurence (char , char );
}vocabList;

typedef struct language_model {
	vocab_list *vocabularylist;
	void readData (const char *);
	double calculateProbability (char, char);
}languageModel;


//FUNCTIONS OF VOCAB_LIST
void vocab_list::create()
{
	head = NULL;
}

void vocab_list::print()
{
	vocabNode *iter = head;
	occurNode *ptrList;

	while(iter !=NULL)
	{
		ptrList = iter->list;
		if(ptrList !=NULL)
		{
			if(iter->character == ' ')
				cout<<"<SP>"<<":"<<endl;
			else 
			{
				if (iter->character != '\n' && iter->character != '\r' && iter->character != '\0' )
						cout<<iter->character<<":"<<endl;
			}
		}
		
		while(ptrList !=NULL)
		{
			if(ptrList->character == ' ')
				cout<<"\t<"<<"<SP>"<<","<<ptrList->occurence<<">"<<endl;
			else 
			{
				if (ptrList->character != '\n' && ptrList->character != '\r' && ptrList->character != '\0')
					cout<<"\t<"<<ptrList->character<<","<<ptrList->occurence<<">"<<endl;
			}
			
				
			ptrList = ptrList->next;
		}
		iter = iter->next;
	}
}

void vocab_list::add_char(char c)
{
	vocabNode *iter = head;	
	if( (c>=97) && (c<=122)  )
	{
		if(head == NULL)  //ADDING FIRST NODE
		{
			head = new vocabNode;
			head->character = c;
			head->next = NULL;
			head->list = NULL;
			return;	
		}
	
	
		else   //ADDING OTHER NODES
		{
			if( (c< (head->character))  )    //AT THE BEGINNING
			{
				vocabNode *newNode = new vocabNode;
				newNode->character = c;
				newNode->next = head;
				newNode->list = NULL;
				head = newNode;
			}
			else if ( (c> (head->character)) )  //IN BETWEEN OR END
			{
				
				while(   iter->next !=NULL && ((iter->next->character) <=c)   )
				{
					iter = iter->next;
				}
			
				if(iter->character < c)
				{
					vocabNode *temp = new vocabNode;
					temp->character = c;
					temp->next = iter->next;
					temp->list = NULL;
					iter->next = temp;
				}
			}
			
		}   
	}
	else
	{
		if(c=='\n' || c=='\0')  return;
		while(   iter->next !=NULL && ((iter->next->character) !=c)   )
		{
			iter = iter->next;
			if(iter->next ==NULL)break;
		}
		if( iter->next == NULL)
		{
			iter->next = new vocabNode;
			iter->next->character = c;
			iter->next->list = NULL;
			iter->next->next = NULL;
		}
		
		
	}
}

void vocab_list::add_occurence(char a , char b)
{
	if(  (a>=65)  &&  (a<=90 ) )	
			a+=32;
	if(  (b>=65)  &&  (b<=90 ) )	
			b+=32;
	if(a == '\n' || b == '\n' || a == '\r' || b == '\r'|| a == '\0' || b == '\0')	return;
	
	vocabNode *iter = head;

	for ( iter=head ;iter != NULL; iter=iter->next)
	{
		occurNode *listPtr = iter->list;
		
		if ( iter->character == a)
		{	
			if ( iter->list == NULL) //ADDING FIRST NODE
			{
				occurNode *temp = new occurNode;
				temp->character = b;
				temp->next = NULL;
				temp->occurence = 1;
				iter->list = temp;
				break;
			}
			
			while ( listPtr->next != NULL && (listPtr->character != b)  )
			{
				listPtr = listPtr->next;
			}
			
			if(listPtr->character == b) //IF NODE EXIST, INCREASE OCCURENCE
			{
				listPtr->occurence++;
				break;
			}
			else if (listPtr->next == NULL) //IF NOT, ADD NEW NODE AT THE END
			{
				occurNode *temp = new occurNode;
				temp->character = b;
				temp->occurence = 1;
				temp->next= NULL;
				listPtr->next = temp;
				break;
			}	
		}	
	}		
}

int vocab_list::get_occurence(char c)
{
	vocabNode *iter = head;
	occurNode *ptrList;
	int occurence=0;
	
	iter = head;
	while(iter !=NULL)
	{
		ptrList = iter->list;
		if(iter->character == c)
		{
			while(ptrList !=NULL)
			{
				occurence += ptrList->occurence;
				ptrList = ptrList->next;
			}
			return occurence;
		}
		iter = iter->next;
	}
	return 0;		
}


int vocab_list::get_union_occurence (char a, char b)
{
	vocabNode *iter = head;
	occurNode *ptrList;
	
	iter = head;
	while(iter !=NULL)
	{
		ptrList = iter->list;
		if(iter->character == a)
		{
			while(ptrList !=NULL)
			{
				if(ptrList->character == b)
				return ptrList->occurence;
				ptrList=ptrList->next;
			}
		}
		iter = iter->next;
	}
	return 0;	
}



//FUNCTIONS OF LANGUAGE MODEL
void language_model::readData (const char *filename)
{
	FILE *fp = fopen(filename,"r");
	int endOfFile =0, i=0,j=0;
		
	//INITILIZING POEM ARRAY WITH POINTERS
	char** poem = new char*[25000];
	for(int i = 0; i < 25000; ++i)
   	 poem[i] = new char[400];
		
	for(i=0; i<25000; i++)
		for(j=0;j<400;j++)
			poem[i][j]='\0';	
		
		
	//READING THE TEXT FILE
	for(i=0; i<25000 && endOfFile == 0 ; i++)
	{
		for(j=0; j<400; j++)
		{
			if(fscanf(fp , "%c", &poem[i][j]) == EOF) 
			{
				endOfFile=1;
				break;
			}
			if(poem[i][j] == '\n')
			{
				poem[i][j] = '\0';
				break;
			}
		}
	}
	fclose(fp);

	//ACCESSING THE VOCABULARY LIST 
	vocabList * vocabList= languageModel::vocabularylist;

	//ADDING ONLY LETTERS AT THE BEGINNING
	for(i=0; i<25000; i++)
	{
		for(j=0; j<400; j++)
		{
			if( poem[i][j] == '\0' )	break;
			else
			{
				if( ( (poem[i][j]>=65)  &&  (poem[i][j]<=90 ) )  ||  ( (poem[i][j]>=97)  &&  (poem[i][j]<=122 ) ) )
				{
					if(  (poem[i][j]>=65)  &&  (poem[i][j]<=90 ) )	
						vocabList->add_char(poem[i][j]+32);
					else 
						vocabList->add_char(poem[i][j]);
				}
			}		
		}
	}
	
	//ADDING SPECIAL CHARACTERS AT THE END
	for(i=0; i<25000; i++)
	{
		for(j=0; j<400; j++)
		{
			if( poem[i][j] == '\n' )break;
			else
			{
				if(  !((poem[i][j]>=65)  &&  (poem[i][j]<=90 )))
				{
						if(poem[i][j] != '\n' && poem[i][j] != '\r')
						vocabList->add_char(poem[i][j]);
				}
			}	
		}
	}
	
	//ADDING OCCURANCE
	for(i=0; i<25000; i++)
	{
		for(j=0; j<400; j++)
		{
			if( poem[i][j] == '\n' || poem[i][j] == '\r'  )	break;
			else
			{
				{
					if( poem[i][j] != '\n'&& poem[i][j+1] != '\n'&& poem[i][j] != '\r'&& poem[i][j+1] != '\r')
					{
						vocabList->add_occurence(poem[i][j], poem[i][j+1]);
					}	
				}
			}	
		}
	}

	//FREE MEMORY
	for(int i = 0; i < 25000; ++i)
   	 	delete poem[i];
	delete poem;	
}


double language_model::calculateProbability (char a, char b)
{
	vocabList * vocabList= languageModel::vocabularylist;

	return (double)vocabList->get_union_occurence(a,b) / (double)vocabList->get_occurence(a);
}



int main(int argc, char **argv)
{
	languageModel *langModel = new languageModel;
	langModel->vocabularylist = new vocabList;
	vocabList *vocabList = langModel->vocabularylist;

	if(argc == 2)
	{
		vocabList->create();
		langModel->readData(argv[1]);
		vocabList->print();
	}
		
	else if(argc ==4)
	{
		//Space characters can also be calculated
		if(argv[3][0] == 'S' && argv[3][1] == 'P') argv[3][0] = ' ';
		if(argv[2][0] == 'S' && argv[2][1] == 'P') argv[2][0] = ' ';
		//Uppercase inputs can also be converted to lowercase and program continues
		if(argv[3][0] >=65 && argv[3][0]<=90) argv[3][0]+=32;
		if(argv[2][0] >=65 && argv[2][0]<=90) argv[2][0]+=32;
		
		vocabList->create();
		langModel->readData(argv[1]);
		double result = langModel->calculateProbability(argv[2][0], argv[3][0]);
		if(argv[3][0] == ' ')
			cout<<"Probability of co-occurrence ("<<argv[2][0]<<","<<"<SP>"<<") "<<"is "<<result<<endl;
		else if(argv[2][0] == ' ')
			cout<<"Probability of co-occurrence ("<<"<SP>"<<","<<argv[3][0]<<") "<<"is "<<result<<endl;
		else
			cout<<"Probability of co-occurrence ("<<argv[2][0]<<","<<argv[3][0]<<") "<<"is "<<result<<endl;
	}
	
	//FREE MEMORY
	delete langModel->vocabularylist;
	delete langModel;

	return 0;	
}
