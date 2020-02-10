/**********************\
|     ASSIGNMENT 2     |
|   Emre REYHANLIOGLU  |
|      150140126       |
\**********************/
#include <stdio.h>

int calculate_Point_Value(int segment , char ring);
int calculate_Remaining_Points(int current_Points , int segment , char ring , int starting_Condition);

int main(void)
{
	int game_Status_Continue=1 , current_Points=0 , segment=0 , target=0 , starting_Condition=1 , calculated_Remaining_Points=0;
	char ring;

	printf("Target: ");
	scanf("%d", &target);
	current_Points=target;

	while(game_Status_Continue)
	{
		printf("\nThrow: ");
		scanf("%d %c", &segment, &ring);

		calculated_Remaining_Points = calculate_Remaining_Points(current_Points , segment , ring , starting_Condition);

		if(calculated_Remaining_Points < current_Points) //Checking whether the game is started
			starting_Condition = 0;

		current_Points = calculated_Remaining_Points;

		printf("Points: %d\n", current_Points);

		if(current_Points == 0)  // The game is finished
			game_Status_Continue = 0;
	}
	return 0;
}

int calculate_Point_Value(int segment , char ring)
{
	if(ring == 'S')
		return segment;
	else if(ring == 'D')
		return 2*segment;
	else if(ring == 'T')
		return 3*segment;
	else if(ring == 'O')
		return 25;
	else if(ring == 'I')
		return 50;
	else
		return 0;
}

int calculate_Remaining_Points(int current_Points , int segment , char ring , int starting_Condition)
{
	int point_Value=0 ;
	if( !starting_Condition || (starting_Condition && ring =='D') )
	{
		point_Value = calculate_Point_Value(segment , ring);

		starting_Condition = 0;

		if( (current_Points - point_Value) < 2 && (current_Points - point_Value)!= 0)
			return current_Points;  //Doesn't change the current points
		else if( (current_Points - point_Value) == 0 && ring != 'D')
			return current_Points;  //Doesn't change the current points
		else
		{
			current_Points -= point_Value;
			return current_Points;
		}
	}
	else
		return current_Points; //Doesn't change the current points
}
