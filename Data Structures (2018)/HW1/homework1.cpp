#include <iostream>
#include <stdlib.h>

void printGrid(char **grid , int grid_x , int grid_y);
void findCenter(char **grid, int grid_x, int grid_y, int inputX, int inputY, int *center_x, int *center_y, int *length, int *plusSave, int *multiplySave, int *dividerSave, int *minusSave);


using namespace std;

int main(int argc, char **argv)
{
	
	int i=0 , j=0 , k=0 , grid_x=0 , grid_y=0 , operation_x=0 , operation_y=0 , operation_length=0 , inst_x=0 , inst_y=0 , inst_length=0;
	char operation_type  ;
	
	//Instruction string
	char *instruction_type = new char[4];
	
	
	FILE *fp1 = fopen(argv[1],"r");
	FILE *fp2 = fopen(argv[2], "r");
	
	
	//Reading the first line of grid.txt
	fscanf(fp1 , "%d %d\n", &grid_x , &grid_y);
	
	//Initilizing the grid by using pointers
	char** grid = new char*[grid_x];
	if( (grid_x>0 ) && grid_y>0 )
	{
		for(int i = 0; i < grid_x; i++)
	    	grid[i] = new char[grid_y];	
		cout<<"A grid is created: "<<grid_x<<" "<<grid_y<<endl;
	}

    	
    //Filling the grid with '.' to display it better
    for (i=0; i<grid_x; i++)
    	for (j=0; j<grid_y; j++)
    		grid[i][j] = '.';
    		
    
    //Save the placed operations
    int *plusSave = new int[20];
    	for(i=0; i<20; i++)	plusSave[i]=0;
    int *minusSave = new int[20];
    	for(i=0; i<20; i++)	minusSave[i]=0;
    int *multiplySave = new int[20];
    	for(i=0; i<20; i++)	multiplySave[i]=0;
    int *dividerSave = new int[20];
    	for(i=0; i<20; i++)	dividerSave[i]=0;
    	
    	
    //Reading the operations one by one until end of file
    while(fscanf(fp1,"%c %d %d %d\n",&operation_type, &operation_x, &operation_y, &operation_length) != EOF)
	{
			
		//Border Error Conditions	
		if (operation_type=='+' || operation_type=='x' || operation_type=='/' )
		{
			if ( (operation_x + operation_length > grid_x)  ||  (operation_x - operation_length <= 0) || (operation_y + operation_length > grid_y)  ||  (operation_y - operation_length <= 0) ) 
			{
				cout << "BORDER ERROR: Operator "<<operation_type<<" with size "<<operation_length<<" can not be placed on ("<<operation_x<<","<<operation_y<<")."<<endl;
			}
				
		}
		else if( operation_type=='-' )
		{
			if ( (operation_x  > grid_x)  ||  (operation_x <= 0) || (operation_y + operation_length > grid_y)  ||  (operation_y - operation_length <= 0) ) 
			{
				cout << "BORDER ERROR: Operator "<<operation_type<<" with size "<<operation_length<<" can not be placed on ("<<operation_x<<","<<operation_y<<")."<<endl;
			}
		}
		
		//Checking the Conflict Error and Placing operation elements if there is not any error
		if ( (operation_type=='+') || (operation_type=='x') || (operation_type=='/') || (operation_type=='-') )
		{
			bool isEmpty = true;
			if ( operation_type=='+' )
			{
				//Checking the grid's necessery parts whether empty or not
				for(i=-1*operation_length ; i<=operation_length ; i++) 
				{		
					if(  (operation_x-1 >=0) && (operation_y + i-1>=0) && (operation_y + i <= grid_y) && (operation_x <=grid_x) && (grid[operation_x-1][operation_y + i-1] != '.'))
					{
						isEmpty = false;
						break;
					}
					if(  (operation_x+i-1 >=0) && (operation_y -1>=0) && (operation_y <= grid_y) && (operation_x+i <=grid_x) && (grid[operation_x+i-1][operation_y-1] != '.'))
					{
						isEmpty = false;
						break;
					}
				}
				//Do the operation if grid's necessery parts are empty, else print the error message
				if( isEmpty && (operation_x - operation_length -1>=0) && (operation_x + operation_length <= grid_x) && (operation_y - operation_length -1>=0) && (operation_y + operation_length <= grid_y))
				{
					for(i=-1*operation_length ; i<=operation_length ; i++) 
					{
						grid[operation_x-1][operation_y + i-1] = '+' ;
						grid[operation_x +i-1][operation_y-1] = '+' ;
					}
					cout << "SUCCESS: Operator "<<operation_type<<" with size "<<operation_length<<" is placed on ("<<operation_x<<","<<operation_y<<")."<<endl;
					
					
					//Encyripting the operation informations to save it and use it in instruction part
					for(i=0; i<20; i++)
					{
						if(plusSave[i] == 0)
						{
							plusSave[i] = 100*operation_x + 10*operation_y + operation_length;
							break;
						}
					}
					
				}
				else if (!isEmpty)
					cout << "CONFLICT ERROR: Operator "<<operation_type<<" with size "<<operation_length<<" can not be placed on ("<<operation_x<<","<<operation_y<<")."<<endl;
				
			}
			
			else if ( operation_type=='-' )
			{
				//Checking the grid's necessery parts whether empty or not
				for(i=-1*operation_length ; i<=operation_length ; i++) 
				{	
					if(  (operation_x-1 >=0) && (operation_y + i-1>=0) && (operation_y + i <= grid_y) && (operation_x <=grid_x) && (grid[operation_x-1][operation_y + i-1] != '.'))
					{
						isEmpty = false;
						break;
					}
							
				}
				//Do the operation if grid's necessery parts are empty
				if( isEmpty && (operation_x -1>=0) && (operation_x <= grid_x) && (operation_y - operation_length -1>=0) && (operation_y + operation_length <= grid_y))
				{
					for(i=-1*operation_length ; i<=operation_length ; i++) 
					{
						grid[operation_x-1][operation_y + i-1] = '-' ;
					}
					cout << "SUCCESS: Operator "<<operation_type<<" with size "<<operation_length<<" is placed on ("<<operation_x<<","<<operation_y<<")."<<endl;
					
					//Encyripting the operation informations to save it and use it in instruction part
					for(i=0; i<20; i++)
					{
						if(minusSave[i] == 0)
						{
							minusSave[i] = 100*operation_x + 10*operation_y + operation_length;
							break;
						}
					}
					
				}
				else if (!isEmpty)
					cout << "CONFLICT ERROR: Operator "<<operation_type<<" with size "<<operation_length<<" can not be placed on ("<<operation_x<<","<<operation_y<<")."<<endl;
			}
			
			
			else if ( operation_type=='x' )
			{
				//Checking the grid's necessery parts whether empty or not
				for(i=-1*operation_length ; i<=operation_length ; i++) 
				{	
					if( (operation_x+i-1 >=0) && (operation_y + i-1>=0) && (operation_y + i <= grid_y) && (operation_x+i <=grid_x) && (grid[operation_x+i-1][operation_y + i-1] != '.'))
					{
						isEmpty = false;
						break;
					}
					if( (operation_x-i-1 >=0) && (operation_y + i-1>=0) && (operation_y + i <= grid_y) && (operation_x-i <=grid_x) && (grid[operation_x-i-1][operation_y + i-1] != '.'))
					{
						isEmpty = false;
						break;
					}		
				}
				//Do the operation if grid's necessery parts are empty, else print the error message
				if( isEmpty && (operation_x - operation_length -1>=0) && (operation_x + operation_length <= grid_x) && (operation_y - operation_length -1>=0) && (operation_y + operation_length <= grid_y))
				{
					for(i=-1*operation_length ; i<=operation_length ; i++) 
					{
						grid[operation_x + i-1][operation_y + i-1] = 'x' ;
						grid[operation_x - i-1][operation_y + i-1] = 'x' ;
					}
					cout << "SUCCESS: Operator "<<operation_type<<" with size "<<operation_length<<" is placed on ("<<operation_x<<","<<operation_y<<")."<<endl;
					
					//Encyripting the operation informations to save it and use it in instruction part
					for(i=0; i<20; i++)
					{
						if(multiplySave[i] == 0)
						{
							multiplySave[i] = 100*operation_x + 10*operation_y + operation_length;
							break;
						}
					}
					
				}
				else if (!isEmpty)
					cout << "CONFLICT ERROR: Operator "<<operation_type<<" with size "<<operation_length<<" can not be placed on ("<<operation_x<<","<<operation_y<<")."<<endl;
				
			}
			
			else if ( operation_type=='/' )
			{
				
				//Checking the grid's necessery parts whether empty or not
				for(i=-1*operation_length ; i<=operation_length ; i++) 
				{
					
						
					if( (operation_x-i-1 >=0) && (operation_y + i-1>=0) && (operation_y + i <= grid_y) && (operation_x-i <=grid_x) && (grid[operation_x-i-1][operation_y + i-1] != '.'))
					{
						isEmpty = false;
						break;
					}	
				}
				//Do the operation if grid's necessery parts are empty, else print the error message
				if( isEmpty && (operation_x - operation_length -1>=0) && (operation_x + operation_length <= grid_x) && (operation_y - operation_length -1>=0) && (operation_y + operation_length <= grid_y) )
				{
					for(i=-1*operation_length ; i<=operation_length ; i++) 
					{
						grid[operation_x - i-1][operation_y + i-1] = '/' ;
					}
					cout << "SUCCESS: Operator "<<operation_type<<" with size "<<operation_length<<" is placed on ("<<operation_x<<","<<operation_y<<")."<<endl;
					
					//Encyripting the operation informations to save it and use it in instruction part
					for(i=0; i<20; i++)
					{
						if(dividerSave[i] == 0)
						{
							dividerSave[i] = 100*operation_x + 10*operation_y + operation_length;
							break;
						}
					}
					
				}
				else if (!isEmpty) 
					cout << "CONFLICT ERROR: Operator "<<operation_type<<" with size "<<operation_length<<" can not be placed on ("<<operation_x<<","<<operation_y<<")."<<endl;
				
			}
			
			
			
		}
	}	
    
    fclose(fp1);
    
    
    while(fscanf(fp2,"%s %d %d %d\n", instruction_type, &inst_x, &inst_y, &inst_length) != EOF)
    {
    	int *center_x = new int , *center_y = new int , *length = new int;
    	char op_type = grid[inst_x-1][ inst_y-1];
    	bool noProblem = true;
    	
    	findCenter(grid , grid_x , grid_y , inst_x , inst_y , center_x , center_y , length, plusSave, multiplySave, dividerSave, minusSave);


    	//MOVE RIGHT OPERATION (MVR)
    	if (*instruction_type == 'M' && *(instruction_type+1) == 'V' && *(instruction_type+2) == 'R')
    	{
    		//Checking the border error
    		if( (*center_y + *length + inst_length > grid_y)&&(*length>0))
    		{
    			cout<<"BORDER ERROR: "<< op_type <<" can not be moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)<<","<<(*center_y)+inst_length<<"). "<<endl;
			}		
			
		//Checking the conflict error and move right operation
					
			if(op_type == '+')
			{
				bool full = false , overflow = false;  
				
				//Delete it
				for(j=-1*(*length); j<= *length; j++)
				{
					grid[*center_x-1][*center_y-1+j] ='.';
					grid[*center_x-1+j][*center_y-1] ='.';
				}
				
				//Check whether empty or not
				for(j=-1*(*length); j<= *length; j++)
				{
					if ( (*center_y-j+inst_length> grid_y))
					{
						overflow = true; 
					}
					if( ((*center_y+j+inst_length<= grid_y) && (grid[*center_x-1][*center_y-1+j+inst_length] !='.')) )
					{
						full = true; break;
					}
						
					if( (*center_y+inst_length<= grid_y) && (grid[*center_x-1+j][*center_y-1+inst_length] !='.') )
					{
						full = true; break;
					}
							
				}
				
				//Write at new coordinates
				if(!full && !overflow) 
				{	
					
					for(j=-1*(*length);  (j<= *length) ; j++)
					{
						grid[*center_x-1][*center_y-1+j+inst_length] ='+';
						grid[*center_x-1+j][*center_y-1+inst_length] ='+';
					}
					//Update new center coordinate informations
					for(i=0; i<20;i++)
					{
						if(plusSave[i] == (*center_x)*100+(*center_y)*10+(*length))
						{
							plusSave[i] = (*center_x)*100+(*center_y+inst_length)*10+(*length) ;
						}		
					}
					cout<<"SUCCESS: "<< op_type <<" moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)<<","<<(*center_y)+inst_length<<"). "<<endl;
				}
				else
				{
					//Rewrite it at first place(dont change anything) if there is an error
					for(j=-1*(*length); (full||overflow) && (j<= *length) ; j++)
					{
						grid[*center_x-1][*center_y-1+j] ='+';
						grid[*center_x-1+j][*center_y-1] ='+';
					}
					if (full)
						cout<<"CONFLICT ERROR: "<< op_type <<" can not be moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)<<","<<(*center_y)+inst_length<<"). "<<endl;
				}		
			}
			
			
			else if(op_type == 'x')
			{
				bool full = false , overflow = false;
				
				//Delete it
				for(j=-1*(*length); j<= *length; j++)
				{
					grid[*center_x-1+j][*center_y-1+j] ='.';
					grid[*center_x-1+j][*center_y-1-j] ='.';
				}
				
				//Check whether empty or not
				for(j=-1*(*length); j<= *length; j++)
				{
					if ( (*center_y-j+inst_length> grid_y))
					{
						overflow = true; 
					}
					if( (*center_y+j+inst_length<= grid_y) && (grid[*center_x-1+j][*center_y-1+j+inst_length] !='.') )
					{
						full = true; break;
					}
						
					if( (*center_y-j+inst_length<= grid_y) && (grid[*center_x-1+j][*center_y-1-j+inst_length] !='.') )
					{
						full = true; break;
					}			
				}
				
				//Write at new coordinates
				if(!full && !overflow)
				{	
					
					for(j=-1*(*length);  (j<= *length) ; j++)
					{
						grid[*center_x-1+j][*center_y-1+j+inst_length] ='x';
						grid[*center_x-1+j][*center_y-1-j+inst_length] ='x';
					}
					//Update new center coordinate informations
					for(i=0; i<20;i++)
					{
						if(multiplySave[i] == (*center_x)*100+(*center_y)*10+(*length))
						{
							multiplySave[i] = (*center_x)*100+(*center_y+inst_length)*10+(*length) ;
						}		
					}
					cout<<"SUCCESS: "<< op_type <<" moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)<<","<<(*center_y)+inst_length<<"). "<<endl;
				}
				else
				{
					//Rewrite it at first place(dont change anything) if there is an error
					for(j=-1*(*length); (full||overflow) && (j<= *length) ; j++)
					{
						grid[*center_x-1+j][*center_y-1+j] ='x';
						grid[*center_x-1+j][*center_y-1-j] ='x';
					}
					if(full)
						cout<<"CONFLICT ERROR: "<< op_type <<" can not be moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)<<","<<(*center_y)+inst_length<<"). "<<endl;
				}		
			}
			
			
			
			else if(op_type == '/')
			{
				bool full = false , overflow = false;
				
				//Delete it
				for(j=-1*(*length); j<= *length; j++)
				{
					grid[*center_x-1+j][*center_y-1-j] ='.';
				}
				
				//Check whether empty or not
				for(j=-1*(*length); j<= *length; j++)
				{	
					if ( (*center_y-j+inst_length> grid_y))
					{
						overflow = true; 
					}
					
					if( (*center_y-j+inst_length<= grid_y) && (grid[*center_x-1+j][*center_y-1-j+inst_length] !='.') )
					{
						full = true; break;
					}		
				}
				//Write at new coordinates
				if(!full && !overflow)
				{	
					
					for(j=-1*(*length);  (j<= *length) ; j++)
					{
						grid[*center_x-1+j][*center_y-1-j+inst_length] ='/';
					}
					//Update new center coordinate informations
					for(i=0; i<20;i++)
					{
						if(dividerSave[i] == (*center_x)*100+(*center_y)*10+(*length))
						{
							dividerSave[i] = (*center_x)*100+(*center_y+inst_length)*10+(*length) ;
						}		
					}
					cout<<"SUCCESS: "<< op_type <<" moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)<<","<<(*center_y)+inst_length<<"). "<<endl;
				}
				else
				{
					//Rewrite it at first place(dont change anything) if there is an error
					for(j=-1*(*length); (full||overflow) && (j<= *length) ; j++)
					{
						grid[*center_x-1+j][*center_y-1-j] ='/';
					}
					if(full)
						cout<<"CONFLICT ERROR: "<< op_type <<" can not be moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)<<","<<(*center_y)+inst_length<<"). "<<endl;
				}		
			}
			
			
			else if(op_type == '-')
			{
				bool full = false , overflow = false;  
				
				//Delete it
				for(j=-1*(*length); j<= *length; j++)
				{
					grid[*center_x-1][*center_y-1+j] ='.';
				}
				
				//Check whether empty or not
				for(j=-1*(*length); j<= *length; j++)
				{
					if ( (*center_y-j+inst_length> grid_y))
					{
						overflow = true; 
					}
					if( ((*center_y+j+inst_length<= grid_y) && (grid[*center_x-1][*center_y-1+j+inst_length] !='.')) )
					{
						full = true; break;
					}
							
				}
				
				//Write at new coordinates
				if(!full && !overflow) 
				{	
					
					for(j=-1*(*length);  (j<= *length) ; j++)
					{
						grid[*center_x-1][*center_y-1+j+inst_length] ='-';
					}
					//Update new center coordinate informations
					for(i=0; i<20;i++)
					{
						if(minusSave[i] == (*center_x)*100+(*center_y)*10+(*length))
						{
							minusSave[i] = (*center_x)*100+(*center_y+inst_length)*10+(*length) ;
						}		
					}
					cout<<"SUCCESS: "<< op_type <<" moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)<<","<<(*center_y)+inst_length<<"). "<<endl;
				}
				else
				{
					//Rewrite it at first place(dont change anything) if there is an error
					for(j=-1*(*length); (full||overflow) && (j<= *length) ; j++)
					{
						grid[*center_x-1][*center_y-1+j] ='-';
					}
					if (full)
						cout<<"CONFLICT ERROR: "<< op_type <<" can not be moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)<<","<<(*center_y)+inst_length<<"). "<<endl;
				}		
			}	
		}
		
		
		
		//MOVE LEFT OPERATION (MVL)
    	if (*instruction_type == 'M' && *(instruction_type+1) == 'V' && *(instruction_type+2) == 'L')
    	{
    		//Checking the border error
    		if( (*center_y - *length - inst_length <=0) && (*length>0))
    		{
    			cout<<"BORDER ERROR: "<< op_type <<" can not be moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)<<","<<(*center_y)-inst_length<<"). "<<endl;
			}		
			
		//Checking the conflict error and move left operation
					
			if(op_type == '+')
			{
				bool full = false , overflow = false;  
				
				//Delete it
				for(j=-1*(*length); j<= *length; j++)
				{
					grid[*center_x-1][*center_y-1+j] ='.';
					grid[*center_x-1+j][*center_y-1] ='.';
				}
				
				//Check whether empty or not
				for(j=-1*(*length); j<= *length; j++)
				{
					if ( (*center_y+j-inst_length<=0 ))
					{
						overflow = true; 
					}
					if( ((*center_y+j-inst_length>0) && (grid[*center_x-1][*center_y-1+j-inst_length] !='.')) )
					{
						full = true; break;
					}
						
					if( (*center_y-inst_length>0) && (grid[*center_x-1+j][*center_y-1-inst_length] !='.') )
					{
						full = true; break;
					}
							
				}
				
				//Write at new coordinates
				if(!full && !overflow) 
				{	
					
					for(j=-1*(*length);  (j<= *length) ; j++)
					{
						grid[*center_x-1][*center_y-1+j-inst_length] ='+';
						grid[*center_x-1+j][*center_y-1-inst_length] ='+';
					}
					//Update new center coordinate informations
					for(i=0; i<20;i++)
					{
						if(plusSave[i] == (*center_x)*100+(*center_y)*10+(*length))
						{
							plusSave[i] = (*center_x)*100+(*center_y-inst_length)*10+(*length) ;
						}		
					}
					cout<<"SUCCESS: "<< op_type <<" moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)<<","<<(*center_y)-inst_length<<"). "<<endl;
				}
				else
				{
					//Rewrite it at first place(dont change anything) if there is an error
					for(j=-1*(*length); (full||overflow) && (j<= *length) ; j++)
					{
						grid[*center_x-1][*center_y-1+j] ='+';
						grid[*center_x-1+j][*center_y-1] ='+';
					}
					if (full)
						cout<<"CONFLICT ERROR: "<< op_type <<" can not be moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)<<","<<(*center_y)-inst_length<<"). "<<endl;
				}		
			}
			
			
			else if(op_type == 'x')
			{
				bool full = false , overflow = false;
				
				//Delete it
				for(j=-1*(*length); j<= *length; j++)
				{
					grid[*center_x-1+j][*center_y-1+j] ='.';
					grid[*center_x-1+j][*center_y-1-j] ='.';
				}
				
				//Check whether empty or not
				for(j=-1*(*length); j<= *length; j++)
				{
					if ( (*center_y+j-inst_length<=0))
					{
						overflow = true; 
					}
					if( (*center_y+j-inst_length>0) && (grid[*center_x-1+j][*center_y-1+j-inst_length] !='.') )
					{
						full = true; break;
					}
						
					if( (*center_y-j-inst_length>0) && (grid[*center_x-1+j][*center_y-1-j-inst_length] !='.') )
					{
						full = true; break;
					}			
				}
				
				//Write at new coordinates
				if(!full && !overflow)
				{	
					
					for(j=-1*(*length);  (j<= *length) ; j++)
					{
						grid[*center_x-1+j][*center_y-1+j-inst_length] ='x';
						grid[*center_x-1+j][*center_y-1-j-inst_length] ='x';
					}
					//Update new center coordinate informations
					for(i=0; i<20;i++)
					{
						if(multiplySave[i] == (*center_x)*100+(*center_y)*10+(*length))
						{
							multiplySave[i] = (*center_x)*100+(*center_y-inst_length)*10+(*length) ;
						}		
					}
					cout<<"SUCCESS: "<< op_type <<" moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)<<","<<(*center_y)-inst_length<<"). "<<endl;
				}
				else
				{
					//Rewrite it at first place(dont change anything) if there is an error
					for(j=-1*(*length); (full||overflow) && (j<= *length) ; j++)
					{
						grid[*center_x-1+j][*center_y-1+j] ='x';
						grid[*center_x-1+j][*center_y-1-j] ='x';
					}
					if(full)
						cout<<"CONFLICT ERROR: "<< op_type <<" can not be moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)<<","<<(*center_y)-inst_length<<"). "<<endl;
				}		
			}
			
			
			
			else if(op_type == '/')
			{
				bool full = false , overflow = false;
				
				//Delete it
				for(j=-1*(*length); j<= *length; j++)
				{
					grid[*center_x-1+j][*center_y-1-j] ='.';
				}
				
				//Check whether empty or not
				for(j=-1*(*length); j<= *length; j++)
				{	
					if ( (*center_y+j-inst_length<=0))
					{
						overflow = true; 
					}
					
					if( (*center_y-j-inst_length>0) && (grid[*center_x-1+j][*center_y-1-j-inst_length] !='.') )
					{
						full = true; break;
					}		
				}
				//Write at new coordinates
				if(!full && !overflow)
				{	
					
					for(j=-1*(*length);  (j<= *length) ; j++)
					{
						grid[*center_x-1+j][*center_y-1-j-inst_length] ='/';
					}
					//Update new center coordinate informations
					for(i=0; i<20;i++)
					{
						if(dividerSave[i] == (*center_x)*100+(*center_y)*10+(*length))
						{
							dividerSave[i] = (*center_x)*100+(*center_y-inst_length)*10+(*length) ;
						}		
					}
					cout<<"SUCCESS: "<< op_type <<" moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)<<","<<(*center_y)-inst_length<<"). "<<endl;
				}
				else
				{
					//Rewrite it at first place(dont change anything) if there is an error
					for(j=-1*(*length); (full||overflow) && (j<= *length) ; j++)
					{
						grid[*center_x-1+j][*center_y-1-j] ='/';
					}
					if(full)
						cout<<"CONFLICT ERROR: "<< op_type <<" can not be moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)<<","<<(*center_y)-inst_length<<"). "<<endl;
				}		
			}
			
			
			else if(op_type == '-')
			{
				bool full = false , overflow = false;  
				
				//Delete it
				for(j=-1*(*length); j<= *length; j++)
				{
					grid[*center_x-1][*center_y-1+j] ='.';
				}
				
				//Check whether empty or not
				for(j=-1*(*length); j<= *length; j++)
				{
					if ( (*center_y+j-inst_length<=0))
					{
						overflow = true; 
					}
					if( ((*center_y+j-inst_length>0) && (grid[*center_x-1][*center_y-1+j-inst_length] !='.')) )
					{
						full = true; break;
					}
							
				}
				
				//Write at new coordinates
				if(!full && !overflow) 
				{	
					
					for(j=-1*(*length);  (j<= *length) ; j++)
					{
						grid[*center_x-1][*center_y-1+j-inst_length] ='-';
					}
					//Update new center coordinate informations
					for(i=0; i<20;i++)
					{
						if(minusSave[i] == (*center_x)*100+(*center_y)*10+(*length))
						{
							minusSave[i] = (*center_x)*100+(*center_y-inst_length)*10+(*length) ;
						}
						cout<<"SUCCESS: "<< op_type <<" moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)<<","<<(*center_y)-inst_length<<"). "<<endl;		
					}
				}
				else
				{
					//Rewrite it at first place(dont change anything) if there is an error
					for(j=-1*(*length); (full||overflow) && (j<= *length) ; j++)
					{
						grid[*center_x-1][*center_y-1+j] ='-';
					}
					if (full)
						cout<<"CONFLICT ERROR: "<< op_type <<" can not be moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)<<","<<(*center_y)-inst_length<<"). "<<endl;
				}		
			}	
		}
    	
    	
    	//MOVE DOWN OPERATION (MVD)
    	if (*instruction_type == 'M' && *(instruction_type+1) == 'V' && *(instruction_type+2) == 'D')
    	{
    		bool full = false , overflow = false; 
    		
    		//Checking the border error
    		if((op_type != '-') && (*center_x + *length + inst_length > grid_x)&&(*length>0))
    		{
    			cout<<"BORDER ERROR: "<< op_type <<" can not be moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)+inst_length<<","<<(*center_y)<<"). "<<endl;
				overflow = true;
			}
			if((op_type == '-') && (*center_x + inst_length > grid_x)&&(*length>0))
    		{
    			cout<<"BORDER ERROR: "<< op_type <<" can not be moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)+inst_length<<","<<(*center_y)<<"). "<<endl;
				overflow = true;
			}		
			
		//Checking the conflict error and move down operation
					
			if(op_type == '+')
			{
				 
				
				//Delete it
				for(j=-1*(*length); j<= *length; j++)
				{
					grid[*center_x-1][*center_y-1+j] ='.';
					grid[*center_x-1+j][*center_y-1] ='.';
				}
				
				
				//Check whether empty or not
				for(j=-1*(*length); j<= *length; j++)
				{
					if( ((*center_x+inst_length<= grid_x) && (grid[*center_x-1+inst_length][*center_y-1+j] !='.')) )
					{
						full = true; break;
					}
						
					if( (*center_x+j+inst_length<= grid_x) && (grid[*center_x-1+j+inst_length][*center_y-1] !='.') )
					{
						full = true; break;
					}
							
				}
				
				//Write at new coordinates
				if(!full && !overflow) 
				{	
					
					for(j=-1*(*length);  (j<= *length) ; j++)
					{
						grid[*center_x-1+inst_length][*center_y-1+j] ='+';
						grid[*center_x-1+j+inst_length][*center_y-1] ='+';
					}
					//Update new center coordinate informations
					for(i=0; i<20;i++)
					{
						if(plusSave[i] == (*center_x)*100+(*center_y)*10+(*length))
						{
							plusSave[i] = (*center_x+inst_length)*100+(*center_y)*10+(*length) ;
						}		
					}
					cout<<"SUCCESS: "<< op_type <<" moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)+inst_length<<","<<(*center_y)<<"). "<<endl;
				}
				else
				{
					//Rewrite it at first place(dont change anything) if there is an error
					for(j=-1*(*length); (full||overflow) && (j<= *length) ; j++)
					{
						grid[*center_x-1][*center_y-1+j] ='+';
						grid[*center_x-1+j][*center_y-1] ='+';
					}
					if (full)
						cout<<"CONFLICT ERROR: "<< op_type <<" can not be moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)+inst_length<<","<<(*center_y)<<"). "<<endl;
				}		
			}
			
			
			else if(op_type == 'x')
			{
				
				//Delete it
				for(j=-1*(*length); j<= *length; j++)
				{
					grid[*center_x-1+j][*center_y-1+j] ='.';
					grid[*center_x-1+j][*center_y-1-j] ='.';
				}
				
				//Check whether empty or not
				for(j=-1*(*length); j<= *length; j++)
				{
					if( (*center_x+j+inst_length<= grid_x) && (grid[*center_x-1+j+inst_length][*center_y-1+j] !='.') )
					{
						full = true; break;
					}
						
					if( (*center_x-j+inst_length<= grid_x) && (grid[*center_x-1-j+inst_length][*center_y-1+j] !='.') )
					{	
						full = true; break;
					}	
				
				}
		
				//Write at new coordinates
				if(!full && !overflow)
				{	
					
					for(j=-1*(*length);  (j<= *length) ; j++)
					{
						grid[*center_x-1+j+inst_length][*center_y-1+j] ='x';
						grid[*center_x-1+j+inst_length][*center_y-1-j] ='x';
					}
					//Update new center coordinate informations
					for(i=0; i<20;i++)
					{
						if(multiplySave[i] == (*center_x)*100+(*center_y)*10+(*length))
						{
							multiplySave[i] = (*center_x+inst_length)*100+(*center_y)*10+(*length) ;
						}		
					}
					cout<<"SUCCESS: "<< op_type <<" moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)+inst_length<<","<<(*center_y)<<"). "<<endl;
				}
				
				else
				{
					//Rewrite it at first place(dont change anything) if there is an error
					for(j=-1*(*length); (full||overflow) && (j<= *length) ; j++)
					{
						grid[*center_x-1+j][*center_y-1+j] ='x';
						grid[*center_x-1+j][*center_y-1-j] ='x';
					}
					if(full)
						cout<<"CONFLICT ERROR: "<< op_type <<" can not be moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)+inst_length<<","<<(*center_y)<<"). "<<endl;
				}		
			}
			
			
			
			else if(op_type == '/')
			{
				
				//Delete it
				for(j=-1*(*length); j<= *length; j++)
				{
					grid[*center_x-1+j][*center_y-1-j] ='.';
				}
				
				//Check whether empty or not
				for(j=-1*(*length); j<= *length; j++)
				{	
					if( (*center_x+j+inst_length<= grid_x) && (grid[*center_x-1+j+inst_length][*center_y-1-j] !='.') )
					{
						full = true; break;
					}		
				}
				//Write at new coordinates
				if(!full && !overflow)
				{	
					
					for(j=-1*(*length);  (j<= *length) ; j++)
					{
						grid[*center_x-1+j+inst_length][*center_y-1-j] ='/';
					}
					//Update new center coordinate informations
					for(i=0; i<20;i++)
					{
						if(dividerSave[i] == (*center_x)*100+(*center_y)*10+(*length))
						{
							dividerSave[i] = (*center_x+inst_length)*100+(*center_y)*10+(*length) ;
						}		
					}
					cout<<"SUCCESS: "<< op_type <<" moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)+inst_length<<","<<(*center_y)<<"). "<<endl;
				}
				else
				{
					//Rewrite it at first place(dont change anything) if there is an error
					for(j=-1*(*length); (full||overflow) && (j<= *length) ; j++)
					{
						grid[*center_x-1+j][*center_y-1-j] ='/';
					}
					if(full)
						cout<<"CONFLICT ERROR: "<< op_type <<" can not be moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)+inst_length<<","<<(*center_y)<<"). "<<endl;
				}		
			}
			
			
			else if(op_type == '-')
			{
				
				//Delete it
				for(j=-1*(*length); j<= *length; j++)
				{
					grid[*center_x-1][*center_y-1+j] ='.';
				}
				
				//Check whether empty or not
				for(j=-1*(*length); j<= *length; j++)
				{
					if( ((*center_x+inst_length<= grid_x) && (grid[*center_x-1+inst_length][*center_y-1+j] !='.')) )
					{
						full = true; break;
					}
							
				}
				
				//Write at new coordinates
				if(!full && !overflow) 
				{	
					
					for(j=-1*(*length);  (j<= *length) ; j++)
					{
						grid[*center_x-1+inst_length][*center_y-1+j] ='-';
					}
					//Update new center coordinate informations
					for(i=0; i<20;i++)
					{
						if(minusSave[i] == (*center_x)*100+(*center_y)*10+(*length))
						{
							minusSave[i] = (*center_x+inst_length)*100+(*center_y)*10+(*length) ;
						}		
					}
					cout<<"SUCCESS: "<< op_type <<" moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)+inst_length<<","<<(*center_y)<<"). "<<endl;
				}
				else
				{
					//Rewrite it at first place(dont change anything) if there is an error
					for(j=-1*(*length); (full||overflow) && (j<= *length) ; j++)
					{
						grid[*center_x-1][*center_y-1+j] ='-';
					}
					if (full)
						cout<<"CONFLICT ERROR: "<< op_type <<" can not be moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)+inst_length<<","<<(*center_y)<<"). "<<endl;
				}		
			}	
		}
    
		
    	//MOVE DOWN OPERATION (MVU)
    	if (*instruction_type == 'M' && *(instruction_type+1) == 'V' && *(instruction_type+2) == 'U')
    	{
    		bool full = false , overflow = false; 
    		
    		//Checking the border error
    		if((op_type != '-') && (*center_x - *length - inst_length <=0)&&(*length>0))
    		{
    			cout<<"BORDER ERROR: "<< op_type <<" can not be moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)-inst_length<<","<<(*center_y)<<"). "<<endl;
				overflow = true;
			}
			if((op_type == '-') && (*center_x - inst_length <=0)&&(*length>0))
    		{
    			cout<<"BORDER ERROR: "<< op_type <<" can not be moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)-inst_length<<","<<(*center_y)<<"). "<<endl;
				overflow = true;
			}		
			
		//Checking the conflict error and move down operation
					
			if(op_type == '+')
			{
				 
				
				//Delete it
				for(j=-1*(*length); j<= *length; j++)
				{
					grid[*center_x-1][*center_y-1+j] ='.';
					grid[*center_x-1+j][*center_y-1] ='.';
				}
				
				
				//Check whether empty or not
				for(j=-1*(*length); j<= *length; j++)
				{
					if( ((*center_x+j-inst_length>0) && (grid[*center_x-1-inst_length][*center_y-1+j] !='.')) )
					{
						full = true; break;
					}
						
					if( (*center_x+j-inst_length>0) && (grid[*center_x-1+j-inst_length][*center_y-1] !='.') )
					{
						full = true; break;
					}
							
				}
				
				//Write at new coordinates
				if(!full && !overflow) 
				{	
					
					for(j=-1*(*length);  (j<= *length) ; j++)
					{
						grid[*center_x-1-inst_length][*center_y-1+j] ='+';
						grid[*center_x-1+j-inst_length][*center_y-1] ='+';
					}
					//Update new center coordinate informations
					for(i=0; i<20;i++)
					{
						if(plusSave[i] == (*center_x)*100+(*center_y)*10+(*length))
						{
							plusSave[i] = (*center_x-inst_length)*100+(*center_y)*10+(*length) ;
						}		
					}
					cout<<"SUCCESS: "<< op_type <<" moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)-inst_length<<","<<(*center_y)<<"). "<<endl;
				}
				else
				{
					//Rewrite it at first place(dont change anything) if there is an error
					for(j=-1*(*length); (full||overflow) && (j<= *length) ; j++)
					{
						grid[*center_x-1][*center_y-1+j] ='+';
						grid[*center_x-1+j][*center_y-1] ='+';
					}
					if (full)
						cout<<"CONFLICT ERROR: "<< op_type <<" can not be moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)-inst_length<<","<<(*center_y)<<"). "<<endl;
				}		
			}
			
			
			else if(op_type == 'x')
			{
				
				//Delete it
				for(j=-1*(*length); j<= *length; j++)
				{
					grid[*center_x-1+j][*center_y-1+j] ='.';
					grid[*center_x-1+j][*center_y-1-j] ='.';
				}
				
				//Check whether empty or not
				for(j=-1*(*length); j<= *length; j++)
				{
					if( (*center_x+j-inst_length>0) && (grid[*center_x-1+j-inst_length][*center_y-1+j] !='.') )
					{
						full = true; break;
					}
						
					if( (*center_x-j-inst_length>0) && (grid[*center_x-1-j-inst_length][*center_y-1+j] !='.') )
					{	
						full = true; break;
					}	
				
				}
		
				//Write at new coordinates
				if(!full && !overflow)
				{	
					
					for(j=-1*(*length);  (j<= *length) ; j++)
					{
						grid[*center_x-1+j-inst_length][*center_y-1+j] ='x';
						grid[*center_x-1+j-inst_length][*center_y-1-j] ='x';
					}
					//Update new center coordinate informations
					for(i=0; i<20;i++)
					{
						if(multiplySave[i] == (*center_x)*100+(*center_y)*10+(*length))
						{
							multiplySave[i] = (*center_x-inst_length)*100+(*center_y)*10+(*length) ;
						}		
					}
					cout<<"SUCCESS: "<< op_type <<" moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)-inst_length<<","<<(*center_y)<<"). "<<endl;
				}
				
				else
				{
					//Rewrite it at first place(dont change anything) if there is an error
					for(j=-1*(*length); (full||overflow) && (j<= *length) ; j++)
					{
						grid[*center_x-1+j][*center_y-1+j] ='x';
						grid[*center_x-1+j][*center_y-1-j] ='x';
					}
					if(full)
						cout<<"CONFLICT ERROR: "<< op_type <<" can not be moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)-inst_length<<","<<(*center_y)<<"). "<<endl;
				}		
			}
			
			
			
			else if(op_type == '/')
			{
				
				//Delete it
				for(j=-1*(*length); j<= *length; j++)
				{
					grid[*center_x-1+j][*center_y-1-j] ='.';
				}
				
				//Check whether empty or not
				for(j=-1*(*length); j<= *length; j++)
				{	
					if( (*center_x+j-inst_length>0) && (grid[*center_x-1+j-inst_length][*center_y-1-j] !='.') )
					{
						full = true; break;
					}		
				}
				//Write at new coordinates
				if(!full && !overflow)
				{	
					
					for(j=-1*(*length);  (j<= *length) ; j++)
					{
						grid[*center_x-1+j-inst_length][*center_y-1-j] ='/';
					}
					//Update new center coordinate informations
					for(i=0; i<20;i++)
					{
						if(dividerSave[i] == (*center_x)*100+(*center_y)*10+(*length))
						{
							dividerSave[i] = (*center_x-inst_length)*100+(*center_y)*10+(*length) ;
						}		
					}
					cout<<"SUCCESS: "<< op_type <<" moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)-inst_length<<","<<(*center_y)<<"). "<<endl;
				}
				else
				{
					//Rewrite it at first place(dont change anything) if there is an error
					for(j=-1*(*length); (full||overflow) && (j<= *length) ; j++)
					{
						grid[*center_x-1+j][*center_y-1-j] ='/';
					}
					if(full)
						cout<<"CONFLICT ERROR: "<< op_type <<" can not be moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)-inst_length<<","<<(*center_y)<<"). "<<endl;
				}		
			}
			
			
			else if(op_type == '-')
			{
				
				//Delete it
				for(j=-1*(*length); j<= *length; j++)
				{
					grid[*center_x-1][*center_y-1+j] ='.';
				}
				
				//Check whether empty or not
				for(j=-1*(*length); j<= *length; j++)
				{
					if( ((*center_x-inst_length>0) && (grid[*center_x-1-inst_length][*center_y-1+j] !='.')) )
					{
						full = true; break;
					}
							
				}
				
				//Write at new coordinates
				if(!full && !overflow) 
				{	
					
					for(j=-1*(*length);  (j<= *length) ; j++)
					{
						grid[*center_x-1-inst_length][*center_y-1+j] ='-';
					}
					//Update new center coordinate informations
					for(i=0; i<20;i++)
					{
						if(minusSave[i] == (*center_x)*100+(*center_y)*10+(*length))
						{
							minusSave[i] = (*center_x-inst_length)*100+(*center_y)*10+(*length) ;
						}		
					}
					cout<<"SUCCESS: "<< op_type <<" moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)-inst_length<<","<<(*center_y)<<"). "<<endl;
				}
				else
				{
					//Rewrite it at first place(dont change anything) if there is an error
					for(j=-1*(*length); (full||overflow) && (j<= *length) ; j++)
					{
						grid[*center_x-1][*center_y-1+j] ='-';
					}
					if (full)
						cout<<"CONFLICT ERROR: "<< op_type <<" can not be moved from ("<<*center_x<<","<<*center_y<<") to ("<<(*center_x)-inst_length<<","<<(*center_y)<<"). "<<endl;
				}		
			}	
		} 	
    	
	}
    	
    
    //printGrid(grid, grid_x , grid_y);
    
    fclose(fp2);
    
    //Free the memory, use delete
    for(int i = 0; i < grid_x; i++)
    	delete(grid[i]);
    delete(grid);
    		
}


void printGrid(char **grid , int grid_x , int grid_y)
{
	int i,j;
	for (i=0; i<grid_x; i++)
    {
    	for (j=0; j<grid_y; j++)
    		cout << grid[i][j]<<" ";
    	cout << endl;
	}
}
void findCenter(char **grid, int grid_x, int grid_y, int inputX, int inputY, int *center_x, int *center_y, int *length, int *plusSave, int *multiplySave, int *dividerSave, int *minusSave)
{
	
	char operation = grid[inputX-1][inputY-1];
	int i=0 , j=0 , k=0 , tempX=0, tempY=0, tempLength=0 ;
	bool found = false;
	
	if(operation == '+')
	{
		for(i=0; i<20; i++)
		{
			if(plusSave[i]!=0)
			{ 
				tempX = plusSave[i]/100;
				tempY = (plusSave[i]/10)%10;
				tempLength = plusSave[i]%10;
				
				for(j=(-1*tempLength); j<=tempLength; j++)
				{
					
					if( ((tempX==inputX) && (tempY+j == inputY)) || ((tempX+j==inputX) && (tempY == inputY)) )
					{
						found=true;
						*center_x = tempX;
						*center_y = tempY;
						*length = tempLength;
						break;	
					}			
				}	
			}	
			if(found)
				break;
		}
	}
	
	else if(operation == 'x')
	{
		for(i=0; i<20; i++)
		{
			if(multiplySave[i]!=0)
			{ 
				tempX = multiplySave[i]/100;
				tempY = (multiplySave[i]/10)%10;
				tempLength = multiplySave[i]%10;
				
				for(j=(-1*tempLength); j<=tempLength; j++)
				{
					for(k=(-1*tempLength); k<=tempLength; k++)
					{
					
						if( ((tempX+j==inputX) && (tempY+k == inputY)) || ((tempX-j==inputX) && (tempY+k == inputY)) )
						{
							found=true;
							*center_x = tempX;
							*center_y = tempY;
							*length = tempLength;
							break;	
						}			
					}
					if(found)
						break;
				}	
			}	
			if(found)
				break;
		}
	}
	
	else if(operation == '/')
	{
		for(i=0; i<20; i++)
		{
			if(dividerSave[i]!=0)
			{ 
				tempX = dividerSave[i]/100;
				tempY = (dividerSave[i]/10)%10;
				tempLength = dividerSave[i]%10;
				
				for(j=(-1*tempLength); j<=tempLength; j++)
				{
					for(k=(-1*tempLength); k<=tempLength; k++)
					{
					
						if( ((tempX-j==inputX) && (tempY+k == inputY)) )
						{
							found=true;
							*center_x = tempX;
							*center_y = tempY;
							*length = tempLength;
							break;	
						}			
					}
					if(found)
						break;
				}	
			}	
			if(found)
				break;
		}
	}
	
	
	else if(operation == '-')
	{
		for(i=0; i<20; i++)
		{
			
			if(minusSave[i]!=0)
			{ 
				tempX = minusSave[i]/100;
				tempY = (minusSave[i]/10)%10;
				tempLength = minusSave[i]%10;
				
				
				for(j=(-1*tempLength); j<=tempLength; j++)
				{
					if( ((tempX==inputX) && (tempY+j == inputY)) )
					{
						found=true;
						*center_x = tempX;
						*center_y = tempY;
						*length = tempLength;
						break;	
					}			
					
				}
			}	
			if(found)
				break;
		}
	}
		
}

