/*      @Author         *\
|*   Emre Reyhanlioglu  *|
\*      150140126       */


#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>


int absValue(int in){return in>0 ? in : -in;}


class Polynomial
{
	int size;
    int *values;
    

public:
    Polynomial(int const=0, int const * const =NULL);  // CONSTRUCTOR
    ~Polynomial(); // DESTRUCTOR
    Polynomial(const Polynomial &p);  // COPY CONSTRUCTOR
    const Polynomial& operator=(const Polynomial &p); // = OPERATOR OVERLOAD
    const Polynomial operator*(const Polynomial &p)const;
    const Polynomial operator+(const Polynomial &p)const;  // + OPERATOR OVERLOAD
    friend std::ostream& operator<< (std::ostream &out, const Polynomial &v); // << OPERATOR OVERLOAD (Printing polynom)
    const int getSize(){return size;} 
};

// CONSTRUCTOR
Polynomial::Polynomial(const int s, int const * const val)
{
	size = s;
	values = new int[size];
	
	for (int i = 0; i < size; i++) 
        values[i] = val[i];
}

//COPY CONSTRUCTOR
Polynomial::Polynomial(const Polynomial &p)
{
	size = p.size;
	values = new int[size];
	for(int i=0; i<size; i++)
		values[i] = p.values[i];
}

// DESTRUCTOR
Polynomial::~Polynomial()
{
	delete []values;
}

// OPERATOR OVERLOADS
const Polynomial& Polynomial::operator=(const Polynomial &p)
{
	
	size = p.size;
	delete []values;
	values = new int[size];
	
	for(int i=0; i<size; i++)
	{
		values[i] = p.values[i];
	}
		
	return *this;
}

const Polynomial Polynomial::operator*(const Polynomial &p)const 
{
	if( !((size == 1 && values[0] == 0) || (p.size == 1 && p.values[0] == 0) ) )
	{
		int i, j, newSize, *array = new int[size+p.size-1];
		newSize = size+p.size-1;
		
		for(i=0; i<newSize; i++)	
			array[i] = 0;
		
		for(i=0; i<size; i++)
			for(j=0; j<p.size; j++)
				array[i+j] += values[i] * p.values[j];
		
		return Polynomial(newSize, array);
	}
	else
	{
		int *array = new int[1];
		array[0] = 0;
		return Polynomial(1,array);
	}
	
}

const Polynomial Polynomial::operator+(const Polynomial &p)const 
{
	int i, newSize, *array;
	newSize = size>p.size ? size : p.size;
	array = new int[newSize];
	
	for(i=0; i<newSize; i++)	
		array[i] = 0;
	
	for(i=0; i<size; i++)
		array[newSize-i-1] += values[size-i-1];
	
	for(i=0; i<p.size; i++)
		array[newSize-i-1] += p.values[p.size-i-1];
	
	return Polynomial(newSize, array);
}

// OVERLOADING << OPERATOR
std::ostream& operator<< (std::ostream &out, const Polynomial &p) 
{
	int i;
	for(i=0; i<p.size; i++)
	{
		//If the coefficient is zero, dont print
		if(p.values[i] != 0 && p.size > 1)
		{
			// COEFFICIENT SITUATIONS
			//If the coefficient is 1
			if(p.values[i] == 1)
			{
				//If its degree is not zero
				if(i < p.size-1)
					out<<"x";
				//If its degree is zero
				else 
					out<<"1";
			}
				
			//If the coefficient is -1	
			else if(p.values[i] == -1)
			{
				//If its degree is not zero
				if(i < p.size-1)
					out<<"-x";
				//If its degree is zero
				else 
					out<<"1";
			}
			//If the coefficient is neither 1 nor -1
			else 
			{
				//If its degree is not zero
				if(i < p.size-1)
					out<<absValue(p.values[i])<<"x";
				//If its degree is zero
				else
					out<<absValue(p.values[i]);
			}
				
			
			
			
			// POWER SITUATIONS
			//If the power is higher than 1, print power
			if(i < p.size-2)
				out<<"^"<<p.size-1-i;
			
			
			// SIGN SITUATIONS
			//Putting the necessary sign between terms
			if(i!=p.size-1)
			{
				if( p.values[i+1]>0) out<<" + ";
				else out<<" - ";
			}
		}
		else if(p.size == 1)
			out<<p.values[0];		
	}	
	return out;
}


#endif
