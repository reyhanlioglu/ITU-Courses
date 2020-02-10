/*      @Author         *\
|*   Emre Reyhanlioglu  *|
\*      150140126       */

using namespace std;

#ifndef ARITHMETICOPERATOR_H
#define ARITHMETICOPERATOR_H

#include <iostream>
#include "Operator.h"


class ArithmeticOperator: public Operator
{
	char sign;
	
	public:
		ArithmeticOperator(int x, int y, int size, char sign);
		
		char get_sign();
		
		void print_operator();
};


// CONSTRUCTOR
ArithmeticOperator::ArithmeticOperator(int x, int y, int size, char sign)
: Operator(x,y,size)
{
	if(sign == '+' || sign == '-' || sign == 'x' || sign == '/')
		this->sign = sign;
	else
		cout<<"SIGN parameter is invalid!"<<endl;
}


// GETTER METHOD
char ArithmeticOperator::get_sign()
{
	return sign;
}


// PRINT METHOD
void ArithmeticOperator::print_operator()
{
	cout<<"ARITHMETIC_OPERATOR["<<sign<<"], CENTER_LOCATION["<<this->get_x()<<","<<this->get_y()<<"], SIZE["<<this->get_size()<<"]"<< endl;
}




#endif
