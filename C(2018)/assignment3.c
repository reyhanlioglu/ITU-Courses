/**********************\
|     ASSIGNMENT 3     |
|   Emre REYHANLIOÐLU  |
|      150140126       |
\**********************/


#include <stdio.h>
#define PARKING_SIZE_MAX 50

int abs (int input); //Returns absolute value of input
void error_000();
void error_001();
void error_002();
void error_003();
void error_004(int x, int y);

int main(void)
{
	int parking_area[PARKING_SIZE_MAX][PARKING_SIZE_MAX] = {{0}} , best_slot[6] ;
	int size , cars , x , y , i , j , k , l , Manhattan_max=0 , closest_distance;
	
	do 
	{
		printf("Size: ");	scanf("%d", &size);
		if(size > PARKING_SIZE_MAX || size<1)  error_000();
		
	}while(size > PARKING_SIZE_MAX || size<1);
	
	do
	{
		printf("Cars: ");	scanf("%d", &cars);
		if(cars > (size*size) || cars<0)  error_001();
	}while(cars > (size*size) || cars<0);
	
	closest_distance= 2*size; //Possible max value for this variable
	
	if ( (size <= PARKING_SIZE_MAX) && (cars <= (size*size))) // No need but for security
	{
		if(cars<(size*size))  //If park is full , skip this part
		{
			for ( i=0; i<cars; i++)
			{
				printf("Locations: ");	scanf("%d%d", &x, &y);
				
				if(x>size || y>size)
				{
					error_002();
				}
				else if(x<1 || y<1)
				{
					error_003();
				}
					
				else if(parking_area[x-1][y-1] == 1)
					error_004(x , y);
				else
					parking_area[x-1][y-1] = 1;
			}
		}
		
		else if(cars == (size*size)) //If park is full , fill all slots with cars
		{
			for (i=0; i<size; i++)
				for(j=0; j<size; j++)
					parking_area[i][j] = 1;
		}
				
		
		for ( i=0; i<size; i++ )        		     // i represents x value for empty slot
		{
			for( j=0; j<size; j++ )    		         // j represents y value for empty slot
			{
				if(parking_area[i][j] == 0)   
				{
					for(k=0; k<size; k++)           //k represents x value for the nearest car  
					{
						for(l=0; l<size; l++)       //l represents y value for the nearest car 
						{
							if(parking_area[k][l] == 1)  
							{
								if( (abs(k-i) + abs(l-j)) < closest_distance) //Checking whether this car is nearer or not
								{
									best_slot[3] = k+1;
									best_slot[4] = l+1;
									best_slot[5] = abs(k-i) + abs(l-j);
									closest_distance = best_slot[5];
								}
							}
						}
					}
					if(closest_distance > Manhattan_max) //Choosing the largest distance to the nearest car in every step
					{
						Manhattan_max = closest_distance;
						best_slot[0] = Manhattan_max;
						best_slot[1] = i+1;
						best_slot[2] = j+1;
					}
					else if(closest_distance == Manhattan_max) //Choosing the minimum x and y coordinates if there are more than one nearest cars
					{
						if( i+1 < best_slot[1])
							best_slot[1] = i+1;
						else if ( ((i+1) == best_slot[1]) && (j+1) < best_slot[2])
							best_slot[2] = j+1;
					}
					closest_distance= 2*size;  //Setting this variable to max again to do same operations for other coordinates
				}
			}
		}
	}
		
	printf("Best Slot Found In: %d %d\n", best_slot[1], best_slot[2]);
	
	return 0;
}



int abs (int input)
{
	if(input < 0)
		input *= -1;
	return input;
}

void error_000()
{
	printf("Size must be between %d and 1)\n", PARKING_SIZE_MAX);
}


void error_001()
{
	printf("Invalid number of cars.\n");
}


void error_002()
{
	printf("This entry is ignored. (Your input location does not exist for this parking area size)\n");
}

void error_003()
{
	printf("This entry is ignored. (Your input coordinates are invalid)\n");
}

void error_004(int x , int y) 
{
	printf("This entry is ignored. (Location (%d , %d) is full)\n",x,y);
}
