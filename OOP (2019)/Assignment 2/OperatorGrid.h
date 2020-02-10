/*      @Author         *\
|*   Emre Reyhanlioglu  *|
\*      150140126       */

using namespace std;

#ifndef OPERATORGRID_H
#define OPERATORGRID_H

#define MAX_OPERATOR_SIZE 200

#include <iostream>
#include "ArithmeticOperator.h"


class OperatorGrid
{
	int grid_rows;
	int grid_cols;
	char **grid;
	
	int num_operators;
	ArithmeticOperator *operators[MAX_OPERATOR_SIZE];
	
	public:
		OperatorGrid(int rows, int cols);
		~OperatorGrid();
		
		bool place_operator(ArithmeticOperator *);
		bool move_operator(int x, int y, char direction, int move_by);
		void print_operators();	
		void findCenter(ArithmeticOperator &op, int &centerX, int &centerY, int &centerSize, int &opIndex);
		void printGrid();
};


OperatorGrid::OperatorGrid(int rows, int cols)
{
	grid_rows = rows;
	grid_cols = cols;
	num_operators = 0;
	
	// Construct Grid
	grid = new char*[grid_rows];
	if( grid_rows>0 && grid_cols>0 )
	{
		for(int i = 0; i < grid_rows; i++)
		{
			grid[i] = new char[grid_cols];	
	    	for(int j=0; j<grid_cols; j++)
	    		grid[i][j] = ' ';
		}
	    	
	}
	
	// Operators
	for(int i = 0; i < MAX_OPERATOR_SIZE; i++)
    	operators[i] = NULL;	
	
}

OperatorGrid::~OperatorGrid()
{
	// DELETE GRID
    for(int i = 0; i < grid_rows; i++)
    	delete[] grid[i];
    delete[] grid;    
    
    // DELETE OPERATORS
    for(int i=0; i<MAX_OPERATOR_SIZE; i++)
    	delete[] operators[i];
    //delete []operators;  //There is a warning but idk why 
    
    cout<<"DESTRUCTOR: GIVE BACK["<<grid_rows<<","<<grid_cols<<"] chars."<<endl;
    cout<<"DESTRUCTOR: GIVE BACK["<<num_operators<<"] Operators."<<endl;
    
    
}

void OperatorGrid::print_operators()
{
	for(int i=0; i<num_operators; i++)
	{
		operators[i]->print_operator();
	}
}	

void OperatorGrid::printGrid()
{
	for(int i=0; i<2*grid_cols+1; i++)
		cout<<"-";
	cout<<endl;
	for(int i=0; i<grid_rows; i++)
	{
		cout<<"|";
		for(int j=0; j<grid_cols; j++)
		{
			
			cout<<grid[i][j];
			if(j != grid_cols-1)
				cout<<" ";
		}
		cout<<"|"<<endl;
	}
	
	for(int i=0; i<2*grid_cols+1; i++)
		cout<<"-";
	cout<<endl;
		
			
}


bool OperatorGrid::place_operator(ArithmeticOperator *op)
{
	char sign = op->get_sign();
	int x = op->get_x();
	int y = op->get_y();
	int size = op->get_size();
	
	if(sign == '+')
	{
		bool noConflictError = true, noBorderError=true;
		
		// CHECKING GRID FOR BORDER ERROR
		if(x+size > grid_rows || x-size < 1 || y+size > grid_cols || y-size < 1)
		{
			cout<<"BORDER ERROR: Operator "<<sign<<" with size "<<size<<" can not be placed on ("<<x<<","<<y<<")."<<endl;
			noBorderError = false;
		}
			
		
		
		// CHECKING GRID FOR CONFLICT ERROR
		for(int i=-size; i<=size; i++)
		{
			if(x>0 && y>0 && x-size<=grid_rows && y-size<=grid_cols )
			{
				if(x+i<=grid_rows &&  x+i >0 && y-1<grid_cols && grid[x+i-1][y-1] != ' ')
					noConflictError = false;
				if(y+i<=grid_cols && y+i >0 && x-1<grid_rows && grid[x-1][y+i-1] != ' ')
					noConflictError = false;
			}
		}
		
		if(!noConflictError)
		{
			cout<<"CONFLICT ERROR: Operator "<<sign<<" with size "<<size<<" can not be placed on ("<<x<<","<<y<<")."<<endl;
		}
		
		
		// IF THERE IS NOT ANY PROBLEM, PLACE THE OPERATOR
		if(noConflictError && noBorderError)
		{
			for(int i=-size; i<=size; i++)
			{
				grid[x+i-1][y-1] = '+';
				grid[x-1][y+i-1] = '+';
			}
			cout<<"SUCCESS: Operator "<<sign<<" with size "<<size<<" is placed on ("<<x<<","<<y<<")."<<endl;
			operators[num_operators++] = op;
			return true;
		}
		else
			return false;	
		
	}
	
	else if(sign == '-')
	{
		bool noConflictError = true, noBorderError=true;
		
		// CHECKING GRID FOR BORDER ERROR
		if(x > grid_rows || x < 1 || y+size > grid_cols || y-size < 1)
		{
			cout<<"BORDER ERROR: Operator "<<sign<<" with size "<<size<<" can not be placed on ("<<x<<","<<y<<")."<<endl;
			noBorderError = false;
		}
			
		
		
		// CHECKING GRID FOR CONFLICT ERROR
		for(int i=-size; i<=size; i++)
		{
			if(x>0 && y>0 && x<=grid_rows && y-size<=grid_cols )
			{
				if(y+i<=grid_cols && y+i >0 && x-1<grid_rows && grid[x-1][y+i-1] != ' ')
					noConflictError = false;
			}
		}
		
		if(!noConflictError)
		{
			cout<<"CONFLICT ERROR: Operator "<<sign<<" with size "<<size<<" can not be placed on ("<<x<<","<<y<<")."<<endl;
		}
		
		
		// IF THERE IS NOT ANY PROBLEM, PLACE THE OPERATOR
		if(noConflictError && noBorderError)
		{
			for(int i=-size; i<=size; i++)
			{
				grid[x-1][y+i-1] = '-';
			}
			cout<<"SUCCESS: Operator "<<sign<<" with size "<<size<<" is placed on ("<<x<<","<<y<<")."<<endl;
			operators[num_operators++] = op;
			return true;
		}
		else
			return false;	
		
	}
	
	else if(sign == 'x')
	{
		bool noConflictError = true, noBorderError=true;
		
		// CHECKING GRID FOR BORDER ERROR
		if(x+size > grid_rows || x-size < 1 || y+size > grid_cols || y-size < 1)
		{
			cout<<"BORDER ERROR: Operator "<<sign<<" with size "<<size<<" can not be placed on ("<<x<<","<<y<<")."<<endl;
			noBorderError = false;
		}
			
		
		
		// CHECKING GRID FOR CONFLICT ERROR
		for(int i=-size; i<=size; i++)
		{
			if(x>0 && y>0 && x-size<=grid_rows && y-size<=grid_cols )
			{
				if(x+i-1<grid_rows && x+i >0 && y+i>0 && y+i-1<grid_cols && grid[x+i-1][y+i-1] != ' ')
					noConflictError = false;
				if(x-i-1<grid_rows && x-i >0 && y+i>0 && y+i-1<grid_cols && grid[x-i-1][y+i-1] != ' ')
					noConflictError = false;
			}
		}
		
		if(!noConflictError)
		{
			cout<<"CONFLICT ERROR: Operator "<<sign<<" with size "<<size<<" can not be placed on ("<<x<<","<<y<<")."<<endl;
		}
		
		
		// IF THERE IS NOT ANY PROBLEM, PLACE THE OPERATOR
		if(noConflictError && noBorderError)
		{
			for(int i=-size; i<=size; i++)
			{
				grid[x+i-1][y+i-1] = 'x';
				grid[x-i-1][y+i-1] = 'x';
			}
			cout<<"SUCCESS: Operator "<<sign<<" with size "<<size<<" is placed on ("<<x<<","<<y<<")."<<endl;
			operators[num_operators++] = op;
			return true;
		}
		else
			return false;	
		
	}
	
	
	else if(sign == '/')
	{
		bool noConflictError = true, noBorderError=true;
		
		// CHECKING GRID FOR BORDER ERROR
		if(x+size > grid_rows || x-size < 1 || y+size > grid_cols || y-size < 1)
		{
			cout<<"BORDER ERROR: Operator "<<sign<<" with size "<<size<<" can not be placed on ("<<x<<","<<y<<")."<<endl;
			noBorderError = false;
		}
			
		
		
		// CHECKING GRID FOR CONFLICT ERROR
		for(int i=-size; i<=size; i++)
		{
			if(x>0 && y>0 && x-size<=grid_rows && y-size<=grid_cols )
			{
				if(x-i-1<grid_rows && x-i >0 && y+i>0 && y+i-1<grid_cols && grid[x-i-1][y+i-1] != ' ')
					noConflictError = false;
			}
		}
		
		if(!noConflictError)
		{
			cout<<"CONFLICT ERROR: Operator "<<sign<<" with size "<<size<<" can not be placed on ("<<x<<","<<y<<")."<<endl;
		}
		
		
		// IF THERE IS NOT ANY PROBLEM, PLACE THE OPERATOR
		if(noConflictError && noBorderError)
		{
			for(int i=-size; i<=size; i++)
			{
				grid[x-i-1][y+i-1] = '/';
			}
			cout<<"SUCCESS: Operator "<<sign<<" with size "<<size<<" is placed on ("<<x<<","<<y<<")."<<endl;
			operators[num_operators++] = op;
			return true;
		}
		else
			return false;	
		
	}
	
	else 
		return false;	
}


bool OperatorGrid::move_operator(int x, int y, char direction, int move_by)
{
	if(direction == 'R' || direction == 'r')
	{
		char sign = grid[x-1][y-1];
		int centerX=0 , centerY=0, size=0, opIndex=-1;
		ArithmeticOperator currentOp(x,y,0,sign);
		bool noBorderError = true, noConflictError = true;
		
		// SETTING centerX and centerY VALUES (USED CALL BY REFERENCE)
		findCenter(currentOp, centerX, centerY, size, opIndex);
		
		if(sign == '+')
		{
			// CHECKING GRID FOR BORDER ERROR
			if(centerX+size > grid_rows || centerX-size < 1 || centerY+size+move_by > grid_cols || centerY-size+move_by < 1)
			{
				cout<<"BORDER ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX<<","<<centerY+move_by<<")."<<endl;
				noBorderError = false;
			}
				
			
			// DELETE ITSELF
			for(int i=-size; i<=size; i++)
			{
				grid[centerX+i-1][centerY-1] = ' ';
				grid[centerX-1][centerY+i-1] = ' ';
			}
				
			// CHECKING GRID FOR CONFLICT ERROR
			for(int i=-size; i<=size; i++)
			{
				if(centerX>0 && centerY>0 && centerX-size<=grid_rows && centerY-size<=grid_cols )
				{
					if(centerX+i<=grid_rows &&  centerX+i >0 && centerY+move_by>0 && centerY+move_by<=grid_cols && grid[centerX+i-1][centerY+move_by-1] != ' ')
						noConflictError = false;
						
					if(centerY+i+move_by<=grid_cols && centerY+i+move_by >0 && centerX<=grid_rows && grid[centerX-1][centerY+i+move_by-1] != ' ')
						noConflictError = false;
				}
			}
			
			if(!noConflictError)
			{
				cout<<"CONFLICT ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX<<","<<centerY+move_by<<")."<<endl;
			}
			
			
			//                      WRITING PART
			// IF THERE IS NOT ANY PROBLEM, PLACE THE OPERATOR AT NEW COORDINATES
			if(noConflictError && noBorderError)
			{
				
				for(int i=-size; i<=size; i++)
				{
					grid[centerX+i-1][centerY+move_by-1] = '+';
					grid[centerX-1][centerY+i+move_by-1] = '+';
				}
				cout<<"SUCCESS: "<<sign<<" moved from ("<<centerX<<","<<centerY<<") to ("<<centerX<<","<<centerY+move_by<<")."<<endl;
				if(opIndex != -1)
				{
					operators[opIndex] = new ArithmeticOperator(centerX, centerY+move_by, size, '+');
				}
				
				return true;
			}
			else
			{
				// REWRITE DELETED FIRST SIGN
				for(int i=-size; i<=size; i++)
				{
					grid[centerX+i-1][centerY-1] = '+';
					grid[centerX-1][centerY+i-1] = '+';
				}
				return false;
			}			
		}
		
		
		
		
		else if(sign == '-')
		{
			// CHECKING GRID FOR BORDER ERROR
			if(centerX > grid_rows || centerX < 1 || centerY+size+move_by > grid_cols || centerY-size+move_by < 1)
			{
				cout<<"BORDER ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX<<","<<centerY+move_by<<")."<<endl;
				noBorderError = false;
			}
				
			
			// DELETE ITSELF
			for(int i=-size; i<=size; i++)
			{
				grid[centerX-1][centerY+i-1] = ' ';
			}
				
			// CHECKING GRID FOR CONFLICT ERROR
			for(int i=-size; i<=size; i++)
			{
				if(centerX>0 && centerY>0 && centerX-size<=grid_rows && centerY-size<=grid_cols )
				{
					if(centerY+i+move_by<=grid_cols && centerY+i+move_by>0 && centerX<=grid_rows && grid[centerX-1][centerY+i+move_by-1] != ' ')
						noConflictError = false;
				}
			}
			
			if(!noConflictError)
			{
				cout<<"CONFLICT ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX<<","<<centerY+move_by<<")."<<endl;
			}
			
			
			//                      WRITING PART
			// IF THERE IS NOT ANY PROBLEM, PLACE THE OPERATOR AT NEW COORDINATES
			if(noConflictError && noBorderError)
			{
				
				
				for(int i=-size; i<=size; i++)
				{
					grid[centerX-1][centerY+i+move_by-1] = '-';
				}
				cout<<"SUCCESS: "<<sign<<" moved from ("<<centerX<<","<<centerY<<") to ("<<centerX<<","<<centerY+move_by<<")."<<endl;
				if(opIndex != -1)
				{
					operators[opIndex] = new ArithmeticOperator(centerX, centerY+move_by, size, '-');
				}
				
				return true;
			}
			else
			{
				// REWRITE DELETED FIRST SIGN
				for(int i=-size; i<=size; i++)
				{
					grid[centerX-1][centerY+i-1] = '-';
				}
				return false;
			}			
		}
		
		
		
		
		else if(sign == 'x')
		{
			// CHECKING GRID FOR BORDER ERROR
			if(centerX+size > grid_rows || centerX-size < 1 || centerY+size+move_by > grid_cols || centerY-size+move_by < 1)
			{
				cout<<"BORDER ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX<<","<<centerY+move_by<<")."<<endl;
				noBorderError = false;
			}
				
			
			// DELETE ITSELF
			for(int i=-size; i<=size; i++)
			{
				grid[centerX+i-1][centerY+i-1] = ' ';
				grid[centerX-i-1][centerY+i-1] = ' ';
			}
				
			// CHECKING GRID FOR CONFLICT ERROR
			for(int i=-size; i<=size; i++)
			{
				if(centerX>0 && centerY>0 && centerX-size<=grid_rows && centerY-size<=grid_cols )
				{
					if(centerX+i<=grid_rows &&  centerX+i >0 && centerY+i+move_by>0 && centerY+i+move_by<=grid_cols && grid[centerX+i-1][centerY+i+move_by-1] != ' ')
						noConflictError = false;
						
					if(centerY+i+move_by<=grid_cols && centerY+i+move_by >0 && centerX-i>0 && centerX-i<=grid_rows && grid[centerX-i-1][centerY+i+move_by-1] != ' ')
						noConflictError = false;
				}
			}
			
			if(!noConflictError)
			{
				cout<<"CONFLICT ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX<<","<<centerY+move_by<<")."<<endl;
			}
			
			
			//                      WRITING PART
			// IF THERE IS NOT ANY PROBLEM, PLACE THE OPERATOR AT NEW COORDINATES
			if(noConflictError && noBorderError)
			{
				
				
				for(int i=-size; i<=size; i++)
				{
					grid[centerX+i-1][centerY+i+move_by-1] = 'x';
					grid[centerX-i-1][centerY+i+move_by-1] = 'x';
				}
				cout<<"SUCCESS: "<<sign<<" moved from ("<<centerX<<","<<centerY<<") to ("<<centerX<<","<<centerY+move_by<<")."<<endl;
				if(opIndex != -1)
				{
					operators[opIndex] = new ArithmeticOperator(centerX, centerY+move_by, size, 'x');
				}
				
				return true;
			}
			else
			{
				// REWRITE DELETED FIRST SIGN
				for(int i=-size; i<=size; i++)
				{
					grid[centerX+i-1][centerY+i-1] = 'x';
					grid[centerX-i-1][centerY+i-1] = 'x';
				}
				return false;
			}			
		}
		
		
		else if(sign == '/')
		{
			// CHECKING GRID FOR BORDER ERROR
			if(centerX+size > grid_rows || centerX-size < 1 || centerY+size+move_by > grid_cols || centerY-size+move_by < 1)
			{
				cout<<"BORDER ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX<<","<<centerY+move_by<<")."<<endl;
				noBorderError = false;
			}
				
			
			// DELETE ITSELF
			for(int i=-size; i<=size; i++)
			{
				grid[centerX-i-1][centerY+i-1] = ' ';
			}
				
			// CHECKING GRID FOR CONFLICT ERROR
			for(int i=-size; i<=size; i++)
			{
				if(centerX>0 && centerY>0 && centerX-size<=grid_rows && centerY-size<=grid_cols )
				{	
					if(centerY+i+move_by<=grid_cols && centerY+i+move_by >0 && centerX-i>0 && centerX-i<=grid_rows && grid[centerX-i-1][centerY+i+move_by-1] != ' ')
						noConflictError = false;
				}
			}
			
			if(!noConflictError)
			{
				cout<<"CONFLICT ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX<<","<<centerY+move_by<<")."<<endl;
			}
			
			
			//                      WRITING PART
			// IF THERE IS NOT ANY PROBLEM, PLACE THE OPERATOR AT NEW COORDINATES
			if(noConflictError && noBorderError)
			{
				
				
				for(int i=-size; i<=size; i++)
				{
					grid[centerX-i-1][centerY+i+move_by-1] = '/';
				}
				cout<<"SUCCESS: "<<sign<<" moved from ("<<centerX<<","<<centerY<<") to ("<<centerX<<","<<centerY+move_by<<")."<<endl;
				if(opIndex != -1)
				{
					operators[opIndex] = new ArithmeticOperator(centerX, centerY+move_by, size, '/');
				}
				
				return true;
			}
			else
			{
				// REWRITE DELETED FIRST SIGN
				for(int i=-size; i<=size; i++)
				{
					grid[centerX-i-1][centerY+i-1] = '/';
				}
				return false;
			}			
		}
		else 
			return false;
			
	}
	

	else if(direction == 'L' || direction == 'l')
	{
		char sign = grid[x-1][y-1];
		int centerX=0 , centerY=0, size=0, opIndex=-1;
		ArithmeticOperator currentOp(x,y,0,sign);
		bool noBorderError = true, noConflictError = true;
		
		// SETTING centerX and centerY VALUES (USED CALL BY REFERENCE)
		findCenter(currentOp, centerX, centerY, size, opIndex);
		
		if(sign == '+')
		{
			// CHECKING GRID FOR BORDER ERROR
			if(centerX+size > grid_rows || centerX-size < 1 || centerY+size-move_by > grid_cols || centerY-size-move_by < 1)
			{
				cout<<"BORDER ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX<<","<<centerY-move_by<<")."<<endl;
				noBorderError = false;
			}
				
			
			// DELETE ITSELF
			for(int i=-size; i<=size; i++)
			{
				grid[centerX+i-1][centerY-1] = ' ';
				grid[centerX-1][centerY+i-1] = ' ';
			}
				
			// CHECKING GRID FOR CONFLICT ERROR
			for(int i=-size; i<=size; i++)
			{
				if(centerX>0 && centerY>0 && centerX-size<=grid_rows && centerY-size<=grid_cols )
				{
					if(centerX+i<=grid_rows &&  centerX+i >0 && centerY-move_by>0 && centerY-move_by<=grid_cols && grid[centerX+i-1][centerY-move_by-1] != ' ')
						noConflictError = false;
						
					if(centerY+i-move_by<=grid_cols && centerY+i-move_by >0 && centerX<=grid_rows && grid[centerX-1][centerY+i-move_by-1] != ' ')
						noConflictError = false;
				}
			}
			
			if(!noConflictError)
			{
				cout<<"CONFLICT ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX<<","<<centerY-move_by<<")."<<endl;
			}
			
			
			//                      WRITING PART
			// IF THERE IS NOT ANY PROBLEM, PLACE THE OPERATOR AT NEW COORDINATES
			if(noConflictError && noBorderError)
			{
				
				
				for(int i=-size; i<=size; i++)
				{
					grid[centerX+i-1][centerY-move_by-1] = '+';
					grid[centerX-1][centerY+i-move_by-1] = '+';
				}
				cout<<"SUCCESS: "<<sign<<" moved from ("<<centerX<<","<<centerY<<") to ("<<centerX<<","<<centerY-move_by<<")."<<endl;
				if(opIndex != -1)
				{
					operators[opIndex] = new ArithmeticOperator(centerX, centerY-move_by, size, '+');
				}
				
				return true;
			}
			else
			{
				// REWRITE DELETED FIRST SIGN
				for(int i=-size; i<=size; i++)
				{
					grid[centerX+i-1][centerY-1] = '+';
					grid[centerX-1][centerY+i-1] = '+';
				}
				return false;
			}			
		}
		
		
		
		
		else if(sign == '-')
		{
			// CHECKING GRID FOR BORDER ERROR
			if(centerX > grid_rows || centerX < 1 || centerY+size-move_by > grid_cols || centerY-size-move_by < 1)
			{
				cout<<"BORDER ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX<<","<<centerY-move_by<<")."<<endl;
				noBorderError = false;
			}
				
			
			// DELETE ITSELF
			for(int i=-size; i<=size; i++)
			{
				grid[centerX-1][centerY+i-1] = ' ';
			}
				
			// CHECKING GRID FOR CONFLICT ERROR
			for(int i=-size; i<=size; i++)
			{
				if(centerX>0 && centerY>0 && centerX-size<=grid_rows && centerY-size<=grid_cols )
				{
					if(centerY+i-move_by<=grid_cols && centerY+i-move_by >0 && centerX<=grid_rows && grid[centerX-1][centerY+i-move_by-1] != ' ')
						noConflictError = false;
				}
			}
			
			if(!noConflictError)
			{
				cout<<"CONFLICT ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX<<","<<centerY-move_by<<")."<<endl;
			}
			
			
			//                      WRITING PART
			// IF THERE IS NOT ANY PROBLEM, PLACE THE OPERATOR AT NEW COORDINATES
			if(noConflictError && noBorderError)
			{
				
				
				for(int i=-size; i<=size; i++)
				{
					grid[centerX-1][centerY+i-move_by-1] = '-';
				}
				cout<<"SUCCESS: "<<sign<<" moved from ("<<centerX<<","<<centerY<<") to ("<<centerX<<","<<centerY-move_by<<")."<<endl;
				if(opIndex != -1)
				{
					operators[opIndex] = new ArithmeticOperator(centerX, centerY-move_by, size, '-');
				}
				
				return true;
			}
			else
			{
				// REWRITE DELETED FIRST SIGN
				for(int i=-size; i<=size; i++)
				{
					grid[centerX-1][centerY+i-1] = '-';
				}
				return false;
			}			
		}
		
		
		
		
		else if(sign == 'x')
		{
			// CHECKING GRID FOR BORDER ERROR
			if(centerX+size > grid_rows || centerX-size < 1 || centerY+size-move_by > grid_cols || centerY-size-move_by < 1)
			{
				cout<<"BORDER ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX<<","<<centerY-move_by<<")."<<endl;
				noBorderError = false;
			}
				
			
			// DELETE ITSELF
			for(int i=-size; i<=size; i++)
			{
				grid[centerX+i-1][centerY+i-1] = ' ';
				grid[centerX-i-1][centerY+i-1] = ' ';
			}
				
			// CHECKING GRID FOR CONFLICT ERROR
			for(int i=-size; i<=size; i++)
			{
				if(centerX>0 && centerY>0 && centerX-size<=grid_rows && centerY-size<=grid_cols )
				{
					if(centerX+i<=grid_rows &&  centerX+i >0 && centerY+i-move_by>0 && centerY+i-move_by<=grid_cols && grid[centerX+i-1][centerY+i-move_by-1] != ' ')
						noConflictError = false;
						
					if(centerY+i-move_by<=grid_cols && centerY+i-move_by >0 && centerX-i>0 && centerX-i<=grid_rows && grid[centerX-i-1][centerY+i-move_by-1] != ' ')
						noConflictError = false;
				}
			}
			
			if(!noConflictError)
			{
				cout<<"CONFLICT ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX<<","<<centerY-move_by<<")."<<endl;
			}
			
			
			//                      WRITING PART
			// IF THERE IS NOT ANY PROBLEM, PLACE THE OPERATOR AT NEW COORDINATES
			if(noConflictError && noBorderError)
			{
				
				
				for(int i=-size; i<=size; i++)
				{
					grid[centerX+i-1][centerY+i-move_by-1] = 'x';
					grid[centerX-i-1][centerY+i-move_by-1] = 'x';
				}
				cout<<"SUCCESS: "<<sign<<" moved from ("<<centerX<<","<<centerY<<") to ("<<centerX<<","<<centerY-move_by<<")."<<endl;
				if(opIndex != -1)
				{
					operators[opIndex] = new ArithmeticOperator(centerX, centerY-move_by, size, 'x');
				}
				
				return true;
			}
			else
			{
				// REWRITE DELETED FIRST SIGN
				for(int i=-size; i<=size; i++)
				{
					grid[centerX+i-1][centerY+i-1] = 'x';
					grid[centerX-i-1][centerY+i-1] = 'x';
				}
				return false;
			}			
		}
		
		
		else if(sign == '/')
		{
			// CHECKING GRID FOR BORDER ERROR
			if(centerX+size > grid_rows || centerX-size < 1 || centerY+size-move_by > grid_cols || centerY-size-move_by < 1)
			{
				cout<<"BORDER ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX<<","<<centerY-move_by<<")."<<endl;
				noBorderError = false;
			}
				
			
			// DELETE ITSELF
			for(int i=-size; i<=size; i++)
			{
				grid[centerX-i-1][centerY+i-1] = ' ';
			}
				
			// CHECKING GRID FOR CONFLICT ERROR
			for(int i=-size; i<=size; i++)
			{
				if(centerX>0 && centerY>0 && centerX-size<=grid_rows && centerY-size<=grid_cols )
				{	
					if(centerY+i-move_by<=grid_cols && centerY+i-move_by>0 && centerX-i>0 && centerX-i<=grid_rows && grid[centerX-i-1][centerY+i-move_by-1] != ' ')
						noConflictError = false;
				}
			}
			
			if(!noConflictError)
			{
				cout<<"CONFLICT ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX<<","<<centerY-move_by<<")."<<endl;
			}
			
			
			//                      WRITING PART
			// IF THERE IS NOT ANY PROBLEM, PLACE THE OPERATOR AT NEW COORDINATES
			if(noConflictError && noBorderError)
			{
				
				
				for(int i=-size; i<=size; i++)
				{
					grid[centerX-i-1][centerY+i-move_by-1] = '/';
				}
				cout<<"SUCCESS: "<<sign<<" moved from ("<<centerX<<","<<centerY<<") to ("<<centerX<<","<<centerY-move_by<<")."<<endl;
				if(opIndex != -1)
				{
					operators[opIndex] = new ArithmeticOperator(centerX, centerY-move_by, size, '/');
				}
				
				return true;
			}
			else
			{
				// REWRITE DELETED FIRST SIGN
				for(int i=-size; i<=size; i++)
				{
					grid[centerX-i-1][centerY+i-1] = '/';
				}
				return false;
			}			
		}
		else 
			return false;		
	}
	
	
	else if(direction == 'U' || direction == 'u')
	{
		char sign = grid[x-1][y-1];
		int centerX=0 , centerY=0, size=0, opIndex=-1;
		ArithmeticOperator currentOp(x,y,0,sign);
		bool noBorderError = true, noConflictError = true;
		
		// SETTING centerX and centerY VALUES (USED CALL BY REFERENCE)
		findCenter(currentOp, centerX, centerY, size, opIndex);
		
		if(sign == '+')
		{
			// CHECKING GRID FOR BORDER ERROR
			if(centerX+size-move_by > grid_rows || centerX-size-move_by < 1 || centerY+size > grid_cols || centerY-size < 1)
			{
				cout<<"BORDER ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX-move_by<<","<<centerY<<")."<<endl;
				noBorderError = false;
			}
				
			
			// DELETE ITSELF
			for(int i=-size; i<=size; i++)
			{
				grid[centerX+i-1][centerY-1] = ' ';
				grid[centerX-1][centerY+i-1] = ' ';
			}
				
			// CHECKING GRID FOR CONFLICT ERROR
			for(int i=-size; i<=size; i++)
			{
				if(centerX>0 && centerY>0 && centerX-size<=grid_rows && centerY-size<=grid_cols )
				{
					if(centerX-move_by+i<=grid_rows &&  centerX-move_by+i >0 && centerY<=grid_cols && grid[centerX-move_by+i-1][centerY-1] != ' ')
						noConflictError = false;
						
					if(centerY+i<=grid_cols && centerY+i >0 && centerX-move_by+i >0 && centerX-move_by<=grid_rows && grid[centerX-move_by-1][centerY+i-1] != ' ')
						noConflictError = false;
				}
			}
			
			if(!noConflictError)
			{
				cout<<"CONFLICT ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX-move_by<<","<<centerY<<")."<<endl;
			}
			
			
			//                      WRITING PART
			// IF THERE IS NOT ANY PROBLEM, PLACE THE OPERATOR AT NEW COORDINATES
			if(noConflictError && noBorderError)
			{
				
				
				for(int i=-size; i<=size; i++)
				{
					grid[centerX-move_by+i-1][centerY-1] = '+';
					grid[centerX-move_by-1][centerY+i-1] = '+';
				}
				cout<<"SUCCESS: "<<sign<<" moved from ("<<centerX<<","<<centerY<<") to ("<<centerX-move_by<<","<<centerY<<")."<<endl;
				if(opIndex != -1)
				{
					operators[opIndex] = new ArithmeticOperator(centerX-move_by, centerY, size, '+');
				}
				
				return true;
			}
			else
			{
				// REWRITE DELETED FIRST SIGN
				for(int i=-size; i<=size; i++)
				{
					grid[centerX+i-1][centerY-1] = '+';
					grid[centerX-1][centerY+i-1] = '+';
				}
				return false;
			}			
		}
		
		
		
		
		else if(sign == '-')
		{
			// CHECKING GRID FOR BORDER ERROR
			if(centerX-move_by > grid_rows || centerX-move_by < 1 || centerY+size > grid_cols || centerY-size < 1)
			{
				cout<<"BORDER ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX-move_by<<","<<centerY<<")."<<endl;
				noBorderError = false;
			}
				
			
			// DELETE ITSELF
			for(int i=-size; i<=size; i++)
			{
				grid[centerX-1][centerY+i-1] = ' ';
			}
				
			// CHECKING GRID FOR CONFLICT ERROR
			for(int i=-size; i<=size; i++)
			{
				if(centerX>0 && centerY>0 && centerX-size<=grid_rows && centerY-size<=grid_cols )
				{
					if(centerY+i<=grid_cols && centerY+i >0 && centerX-move_by>0 && centerX-move_by<=grid_rows  && grid[centerX-move_by-1][centerY+i-1] != ' ')
						noConflictError = false;
				}
			}
			
			if(!noConflictError)
			{
				cout<<"CONFLICT ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX-move_by<<","<<centerY<<")."<<endl;
			}
			
			
			//                      WRITING PART
			// IF THERE IS NOT ANY PROBLEM, PLACE THE OPERATOR AT NEW COORDINATES
			if(noConflictError && noBorderError)
			{
				
				
				for(int i=-size; i<=size; i++)
				{
					grid[centerX-move_by-1][centerY+i-1] = '-';
				}
				cout<<"SUCCESS: "<<sign<<" moved from ("<<centerX<<","<<centerY<<") to ("<<centerX-move_by<<","<<centerY<<")."<<endl;
				if(opIndex != -1)
				{
					operators[opIndex] = new ArithmeticOperator(centerX-move_by, centerY, size, '-');
				}
				
				return true;
			}
			else
			{
				// REWRITE DELETED FIRST SIGN
				for(int i=-size; i<=size; i++)
				{
					grid[centerX-1][centerY+i-1] = '-';
				}
				return false;
			}			
		}
		
		
		
		
		else if(sign == 'x')
		{
			// CHECKING GRID FOR BORDER ERROR
			if(centerX+size-move_by > grid_rows || centerX-move_by-size < 1 || centerY+size > grid_cols || centerY-size < 1)
			{
				cout<<"BORDER ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX-move_by<<","<<centerY<<")."<<endl;
				noBorderError = false;
			}
				
			
			// DELETE ITSELF
			for(int i=-size; i<=size; i++)
			{
				grid[centerX+i-1][centerY+i-1] = ' ';
				grid[centerX-i-1][centerY+i-1] = ' ';
			}
				
			// CHECKING GRID FOR CONFLICT ERROR
			for(int i=-size; i<=size; i++)
			{
				if(centerX>0 && centerY>0 && centerX-size<=grid_rows && centerY-size<=grid_cols )
				{
					if(centerX-move_by+i<=grid_rows &&  centerX-move_by+i >0 && centerY+i>0 && centerY+i<=grid_cols && grid[centerX-move_by+i-1][centerY+i-1] != ' ')
						noConflictError = false;
						
					if(centerY+i<=grid_cols && centerY+i >0 && centerX-move_by-i>0 && centerX-move_by-i<=grid_rows && grid[centerX-move_by-i-1][centerY+i-1] != ' ')
						noConflictError = false;
				}
			}
			
			if(!noConflictError)
			{
				cout<<"CONFLICT ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX-move_by<<","<<centerY<<")."<<endl;
			}
			
			
			//                      WRITING PART
			// IF THERE IS NOT ANY PROBLEM, PLACE THE OPERATOR AT NEW COORDINATES
			if(noConflictError && noBorderError)
			{
				
				
				for(int i=-size; i<=size; i++)
				{
					grid[centerX+i-move_by-1][centerY+i-1] = 'x';
					grid[centerX-i-move_by-1][centerY+i-1] = 'x';
				}
				cout<<"SUCCESS: "<<sign<<" moved from ("<<centerX<<","<<centerY<<") to ("<<centerX-move_by<<","<<centerY<<")."<<endl;
				if(opIndex != -1)
				{
					operators[opIndex] = new ArithmeticOperator(centerX-move_by, centerY, size, 'x');
				}
				
				return true;
			}
			else
			{
				// REWRITE DELETED FIRST SIGN
				for(int i=-size; i<=size; i++)
				{
					grid[centerX+i-1][centerY+i-1] = 'x';
					grid[centerX-i-1][centerY+i-1] = 'x';
				}
				return false;
			}			
		}
		
		
		else if(sign == '/')
		{
			// CHECKING GRID FOR BORDER ERROR
			if(centerX-move_by+size > grid_rows || centerX-move_by-size < 1 || centerY+size > grid_cols || centerY-size < 1)
			{
				cout<<"BORDER ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX-move_by<<","<<centerY<<")."<<endl;
				noBorderError = false;
			}
				
			
			// DELETE ITSELF
			for(int i=-size; i<=size; i++)
			{
				grid[centerX-i-1][centerY+i-1] = ' ';
			}
				
			// CHECKING GRID FOR CONFLICT ERROR
			for(int i=-size; i<=size; i++)
			{
				if(centerX>0 && centerY>0 && centerX-size<=grid_rows && centerY-size<=grid_cols )
				{	
					if(centerY+i<=grid_cols && centerY+i >0 && centerX-move_by-i>0 && centerX-move_by-i<=grid_rows && grid[centerX-move_by-i-1][centerY+i-1] != ' ')
						noConflictError = false;
				}
			}
			
			if(!noConflictError)
			{
				cout<<"CONFLICT ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX-move_by<<","<<centerY<<")."<<endl;
			}
			
			
			//                      WRITING PART
			// IF THERE IS NOT ANY PROBLEM, PLACE THE OPERATOR AT NEW COORDINATES
			if(noConflictError && noBorderError)
			{
				
				
				for(int i=-size; i<=size; i++)
				{
					grid[centerX-move_by-i-1][centerY+i-1] = '/';
				}
				cout<<"SUCCESS: "<<sign<<" moved from ("<<centerX<<","<<centerY<<") to ("<<centerX-move_by<<","<<centerY<<")."<<endl;
				if(opIndex != -1)
				{
					operators[opIndex] = new ArithmeticOperator(centerX-move_by, centerY, size, '/');
				}
				
				return true;
			}
			else
			{
				// REWRITE DELETED FIRST SIGN
				for(int i=-size; i<=size; i++)
				{
					grid[centerX-i-1][centerY+i-1] = '/';
				}
				return false;
			}			
		}
		else 
			return false;	
	}
	
	
	else if(direction == 'D' || direction == 'd')
	{
		char sign = grid[x-1][y-1];
		int centerX=0 , centerY=0, size=0, opIndex=-1;
		ArithmeticOperator currentOp(x,y,0,sign);
		bool noBorderError = true, noConflictError = true;
		
		// SETTING centerX and centerY VALUES (USED CALL BY REFERENCE)
		findCenter(currentOp, centerX, centerY, size, opIndex);
		
		if(sign == '+')
		{
			// CHECKING GRID FOR BORDER ERROR
			if(centerX+size+move_by > grid_rows || centerX-size+move_by < 1 || centerY+size > grid_cols || centerY-size < 1)
			{
				cout<<"BORDER ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX+move_by<<","<<centerY<<")."<<endl;
				noBorderError = false;
			}
				
			
			// DELETE ITSELF
			for(int i=-size; i<=size; i++)
			{
				grid[centerX+i-1][centerY-1] = ' ';
				grid[centerX-1][centerY+i-1] = ' ';
			}
				
			// CHECKING GRID FOR CONFLICT ERROR
			for(int i=-size; i<=size; i++)
			{
				if(centerX>0 && centerY>0 && centerX-size<=grid_rows && centerY-size<=grid_cols )
				{
					if(centerX+move_by+i<=grid_rows &&  centerX+move_by+i >0 && centerY<=grid_cols && grid[centerX+move_by+i-1][centerY-1] != ' ')
						noConflictError = false;
						
					if(centerY+i<=grid_cols && centerY+i >0 && centerX+move_by+i >0 && centerX+move_by<=grid_rows && grid[centerX+move_by-1][centerY+i-1] != ' ')
						noConflictError = false;
				}
			}
			
			if(!noConflictError)
			{
				cout<<"CONFLICT ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX+move_by<<","<<centerY<<")."<<endl;
			}
			
			
			//                      WRITING PART
			// IF THERE IS NOT ANY PROBLEM, PLACE THE OPERATOR AT NEW COORDINATES
			if(noConflictError && noBorderError)
			{
				
				
				for(int i=-size; i<=size; i++)
				{
					grid[centerX+move_by+i-1][centerY-1] = '+';
					grid[centerX+move_by-1][centerY+i-1] = '+';
				}
				cout<<"SUCCESS: "<<sign<<" moved from ("<<centerX<<","<<centerY<<") to ("<<centerX+move_by<<","<<centerY<<")."<<endl;
				if(opIndex != -1)
				{
					operators[opIndex] = new ArithmeticOperator(centerX+move_by, centerY, size, '+');
				}
				
				return true;
			}
			else
			{
				// REWRITE DELETED FIRST SIGN
				for(int i=-size; i<=size; i++)
				{
					grid[centerX+i-1][centerY-1] = '+';
					grid[centerX-1][centerY+i-1] = '+';
				}
				return false;
			}			
		}
		
		
		
		
		else if(sign == '-')
		{
			// CHECKING GRID FOR BORDER ERROR
			if(centerX+move_by > grid_rows || centerX+move_by < 1 || centerY+size > grid_cols || centerY-size < 1)
			{
				cout<<"BORDER ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX+move_by<<","<<centerY<<")."<<endl;
				noBorderError = false;
			}
				
			
			// DELETE ITSELF
			for(int i=-size; i<=size; i++)
			{
				grid[centerX-1][centerY+i-1] = ' ';
			}
				
			// CHECKING GRID FOR CONFLICT ERROR
			for(int i=-size; i<=size; i++)
			{
				if(centerX>0 && centerY>0 && centerX-size<=grid_rows && centerY-size<=grid_cols )
				{
					if(centerY+i<=grid_cols && centerY+i >0 && centerX+move_by<=grid_rows && centerX+move_by>0 && grid[centerX+move_by-1][centerY+i-1] != ' ')
						noConflictError = false;
				}
			}
			
			if(!noConflictError)
			{
				cout<<"CONFLICT ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX+move_by<<","<<centerY<<")."<<endl;
			}
			
			
			//                      WRITING PART
			// IF THERE IS NOT ANY PROBLEM, PLACE THE OPERATOR AT NEW COORDINATES
			if(noConflictError && noBorderError)
			{
				
				
				for(int i=-size; i<=size; i++)
				{
					grid[centerX+move_by-1][centerY+i-1] = '-';
				}
				cout<<"SUCCESS: "<<sign<<" moved from ("<<centerX<<","<<centerY<<") to ("<<centerX+move_by<<","<<centerY<<")."<<endl;
				if(opIndex != -1)
				{
					operators[opIndex] = new ArithmeticOperator(centerX+move_by, centerY, size, '-');
				}
				
				return true;
			}
			else
			{
				// REWRITE DELETED FIRST SIGN
				for(int i=-size; i<=size; i++)
				{
					grid[centerX-1][centerY+i-1] = '-';
				}
				return false;
			}			
		}
		
		
		
		
		else if(sign == 'x')
		{
			// CHECKING GRID FOR BORDER ERROR
			if(centerX+size+move_by > grid_rows || centerX+move_by-size < 1 || centerY+size > grid_cols || centerY-size < 1)
			{
				cout<<"BORDER ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX+move_by<<","<<centerY<<")."<<endl;
				noBorderError = false;
			}
				
			
			// DELETE ITSELF
			for(int i=-size; i<=size; i++)
			{
				grid[centerX+i-1][centerY+i-1] = ' ';
				grid[centerX-i-1][centerY+i-1] = ' ';
			}
				
			// CHECKING GRID FOR CONFLICT ERROR
			for(int i=-size; i<=size; i++)
			{
				if(centerX>0 && centerY>0 && centerX-size<=grid_rows && centerY-size<=grid_cols )
				{
					if(centerX+move_by+i<=grid_rows &&  centerX+move_by+i >0 && centerY+i>0 && centerY+i<=grid_cols && grid[centerX+move_by+i-1][centerY+i-1] != ' ')
						noConflictError = false;
						
					if(centerY+i<=grid_cols && centerY+i >0 && centerX+move_by-i>0 && centerX+move_by-i<=grid_rows && grid[centerX+move_by-i-1][centerY+i-1] != ' ')
						noConflictError = false;
				}
			}
			
			if(!noConflictError)
			{
				cout<<"CONFLICT ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX+move_by<<","<<centerY<<")."<<endl;
			}
			
			
			//                      WRITING PART
			// IF THERE IS NOT ANY PROBLEM, PLACE THE OPERATOR AT NEW COORDINATES
			if(noConflictError && noBorderError)
			{
				
				
				for(int i=-size; i<=size; i++)
				{
					grid[centerX+i+move_by-1][centerY+i-1] = 'x';
					grid[centerX-i+move_by-1][centerY+i-1] = 'x';
				}
				cout<<"SUCCESS: "<<sign<<" moved from ("<<centerX<<","<<centerY<<") to ("<<centerX+move_by<<","<<centerY<<")."<<endl;
				if(opIndex != -1)
				{
					operators[opIndex] = new ArithmeticOperator(centerX+move_by, centerY, size, 'x');
				}
				
				return true;
			}
			else
			{
				// REWRITE DELETED FIRST SIGN
				for(int i=-size; i<=size; i++)
				{
					grid[centerX+i-1][centerY+i-1] = 'x';
					grid[centerX-i-1][centerY+i-1] = 'x';
				}
				return false;
			}			
		}
		
		
		else if(sign == '/')
		{
			// CHECKING GRID FOR BORDER ERROR
			if(centerX+move_by+size > grid_rows || centerX+move_by-size < 1 || centerY+size > grid_cols || centerY-size < 1)
			{
				cout<<"BORDER ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX+move_by<<","<<centerY<<")."<<endl;
				noBorderError = false;
			}
				
			
			// DELETE ITSELF
			for(int i=-size; i<=size; i++)
			{
				grid[centerX-i-1][centerY+i-1] = ' ';
			}
				
			// CHECKING GRID FOR CONFLICT ERROR
			for(int i=-size; i<=size; i++)
			{
				if(centerX>0 && centerY>0 && centerX-size<=grid_rows && centerY-size<=grid_cols )
				{	
					if(centerY+i<=grid_cols && centerY+i >0 && centerX+move_by-i>0 && centerX+move_by-i<=grid_rows && grid[centerX+move_by-i-1][centerY+i-1] != ' ')
						noConflictError = false;
				}
			}
			
			if(!noConflictError)
			{
				cout<<"CONFLICT ERROR: "<<sign<<" can not be moved from ("<<centerX<<","<<centerY<<") to ("<<centerX+move_by<<","<<centerY<<")."<<endl;
			}
			
			
			//                      WRITING PART
			// IF THERE IS NOT ANY PROBLEM, PLACE THE OPERATOR AT NEW COORDINATES
			if(noConflictError && noBorderError)
			{
				
				
				for(int i=-size; i<=size; i++)
				{
					grid[centerX+move_by-i-1][centerY+i-1] = '/';
				}
				cout<<"SUCCESS: "<<sign<<" moved from ("<<centerX<<","<<centerY<<") to ("<<centerX+move_by<<","<<centerY<<")."<<endl;
				if(opIndex != -1)
				{
					operators[opIndex] = new ArithmeticOperator(centerX+move_by, centerY, size, '/');
				}
				
				return true;
			}
			else
			{
				// REWRITE DELETED FIRST SIGN
				for(int i=-size; i<=size; i++)
				{
					grid[centerX-i-1][centerY+i-1] = '/';
				}
				return false;
			}			
		}
		else 
			return false;	
	}
	else 
		return false;
}


void OperatorGrid::findCenter(ArithmeticOperator &op, int &centerX, int &centerY, int &centerSize, int &opIndex)
{
	char sign = op.get_sign();
	int x = op.get_x();
	int y = op.get_y();
	
	for(int i=0; i<num_operators; i++)
	{
		ArithmeticOperator* iter = operators[i];
		int iterX = iter->get_x();
		int iterY = iter->get_y();
		int iterSize = iter->get_size();
		char iterSign = iter->get_sign();
		
		if(sign == '+' && iterSign == '+')
		{
			for(int j=-iterSize; j<=iterSize; j++)
			{
				if(  (x == iterX+j && y == iterY) || (x == iterX && y == iterY+j) )
				{
					centerX = iterX;
					centerY = iterY;
					centerSize = iterSize;
					opIndex = i;
					return;
				}	
			}
		}
		
		else if(sign == '-' && iterSign == '-')
		{
			for(int j=-iterSize; j<=iterSize; j++)
			{
				if(x == iterX && y == iterY+j)
				{
					centerX = iterX;
					centerY = iterY;
					centerSize = iterSize;
					opIndex = i;
					return;
				}	
			}
		}
		
		else if(sign == 'x' && iterSign == 'x')
		{
			for(int j=-iterSize; j<=iterSize; j++)
			{
				if( (x == iterX+j && y == iterY+j) || (x == iterX-j && y == iterY+j) )
				{
					centerX = iterX;
					centerY = iterY;
					centerSize = iterSize;
					opIndex = i;
					return;
				}	
			}
		}
		
		else if(sign == '/' && iterSign == '/')
		{
			for(int j=-iterSize; j<=iterSize; j++)
			{
				if( x == iterX-j && y == iterY+j )
				{
					centerX = iterX;
					centerY = iterY;
					centerSize = iterSize;
					opIndex = i;
					return;
				}	
			}
		}	
	}
}


#endif
