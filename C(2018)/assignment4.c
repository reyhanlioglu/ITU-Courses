/**********************\
|     ASSIGNMENT 4     |
|   Emre REYHANLIOGLU  |
|      150140126       |
\**********************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //used for strlen function


typedef struct instruction_s{
int step;
int index;
}ins;

char *get_word(char *s, int n);
void get_sentence(char **lines, ins *instructions, int n_instructions , char *sentence);


int main(int argc, char **argv)
{
	int i=0,j=0 , endOfFile=0 , n_instructions=0;
	FILE *bookPtr , *insPtr;
	
	char **book = (char**)malloc(sizeof(char*)*10000);
	for(i=0; i<10000; i++)
		book[i] = (char*)malloc(sizeof(char)*200);

	ins *instructions = (ins*)malloc(sizeof(ins)*10000);

	bookPtr = fopen(argv[1], "r");
	insPtr  = fopen(argv[2] , "r");

	for(i=0; i<10000 && endOfFile == 0 ; i++)
	{
		for(j=0; j<200; j++)
		{
			if(fscanf(bookPtr , "%c", &book[i][j]) == EOF) endOfFile=1;
			if(book[i][j] == '\n')
			{
				book[i][j] = '\0';
				break;
			}
		}
	}

	for(i=0; i<10000 ; i++)
	{
		if(fscanf(insPtr , "%d %d", &instructions[i].step , &instructions[i].index) == EOF) break;
		n_instructions++;
	}


	char *sentence = (char*)malloc(sizeof(char)*200);
	get_sentence (book , instructions , n_instructions , sentence);
	
	printf("%s\n", sentence);

	
	//Memory Deallocation
	free(instructions);
	free(sentence);	
	for(i=0; i<10000; i++)
		free(book[i]);
	free(book);
	
		
	fclose(bookPtr);
	fclose(insPtr);

	return 0;
}

char *get_word(char *s, int n)
{
	char *iter = s;
	char *word = (char*)malloc(sizeof(char)*50);
	int i=0 , j=0 ;
	
	//Bastaki gecersiz karakterler kadar iterater'i ilerletme
	while(  !( (*iter>='A') && (*iter<='Z') ) && !( (*iter>='a') && (*iter<='z') )  )
			iter++;


	//Aranan kelimeden once gelen kelimeler kadar iterater'i ilerletme
	for(i=0; i<n-1 ; i++)
	{
		//Kelimeden bosluga kadar olan kisim
		while( (*iter != ' ') && (*iter != '\0')  )
		{
			iter++;
		}
		//Bosluktan siradaki kelimeye kadar olan kisim
		while(   (*iter == ' ') && (*iter != '\0') )
			iter++;
		
	}
	//Aranan kelimeyi word arrayine yazma
	for(j=0; *iter != ' '; j++ )
	{
			if(  ( (*iter>='a') && (*iter<='z') ) )
			{	*(word+j) = *iter;	iter++;   }
			else if ( ( (*iter>='A') && (*iter<='Z') ) )
			{	*(word+j) = *iter - ('A'-'a');	iter++;  }
			else if ( *(iter) == '\0')
				break;
			else
			{	j--;  iter++; }
	}
	*(word+j) = '\0';
	return word;
	free(word);
}

void get_sentence (char **lines , ins *instructions, int n_instructions, char *sentence)
{
	int i=0 , j=0 , offset = 0 , iter=0 , lenght=0;
	
	for(i=0; i<n_instructions; i++)
	{
		offset += (instructions+i)->step;

		lenght = strlen(get_word(lines[offset-1] , (instructions+i)->index));
		
		for(j=0; j<lenght; j++, iter++)
			*(sentence+iter) = *(get_word(lines[offset-1] , (instructions+i)->index) + j);
		
		*(sentence+iter) = ' '; iter++;
	}
	*(sentence+iter) = '\0';
}
