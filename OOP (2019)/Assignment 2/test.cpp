/*      @Author         *\
|*   Emre Reyhanlioglu  *|
\*      150140126       */

using namespace std;

#include <stdio.h>
#include "Operator.h"
#include "ArithmeticOperator.h"
#include "OperatorGrid.h"





int main()
{
	if(true){
		OperatorGrid grid(5,8);
	}
	
	Operator op(3,4,5);
//	op.reset(1,2,3);
	
	op.set_size(24);
	int x = op.get_size();
	//cout<<x<<endl;
	
	
	
	//plusOp.print_operator();
	
	ArithmeticOperator plusOp2(12,13,17,'i');
	plusOp2.print_operator();
	
	cout<<endl<<"GRID TEST"<<endl;
	ArithmeticOperator* plusOp5 = new ArithmeticOperator(3,3,2,'-');
	ArithmeticOperator* plusOp = new ArithmeticOperator(3,8,2,'+');
	ArithmeticOperator* plusOp3 = new ArithmeticOperator(3,6,2,'x');
	ArithmeticOperator* plusOp4 = new ArithmeticOperator(5,9,2,'x');
	ArithmeticOperator* plusOp6 = new ArithmeticOperator(5,6,4,'/');
	OperatorGrid grid(16,11);
	grid.place_operator(plusOp5);
	grid.place_operator(plusOp3);
	grid.place_operator(plusOp);
	grid.place_operator(plusOp4);
	grid.place_operator(plusOp6);
	
	grid.printGrid();



	
}
