/*      @Author         *\
|*   Emre Reyhanlioglu  *|
\*      150140126       */


#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>



class Vector
{
	int size;
    int *values;
    

public:
    Vector(int const=0, int const * const =NULL);   //CONSTRUCTOR
    ~Vector();  									//DESTRUCTOR
    Vector(const Vector &p);  				 		//COPY CONSTRUCTOR
    const Vector operator+(const Vector &v)const;   // + OPERATOR OVERLOAD
    const Vector& operator=(const Vector &v); 		// = OPERATOR OVERLOAD
    const Vector operator*(const int scalar)const;  // * OPERATOR OVERLOAD (Scaling)
    const int operator*(const Vector &v)const;		// * OPERATOR OVERLOAD (Dot product)
    friend std::ostream& operator<< (std::ostream &out, const Vector &v); // << OPERATOR OVERLOAD (Printing vector)
    const int getSize(){return size;}
};

// + OPERATOR OVERLOADS
const Vector Vector::operator+(const Vector &v)const
{
	if(v.size == size)
	{
		int *resultValues =new int[size];
		
		int i = 0;
		for(i=0; i<size; i++)
		{
			resultValues[i] = values[i] +v.values[i];
		}
		return Vector(size, resultValues);
	}
	else
		std::cout<<"ERROR: Vectors have different sizes!"<<std::endl;
	
}

const Vector& Vector::operator=(const Vector &v)
{
	
	size = v.size;
	delete []values;
	values = new int[size];
	
	for(int i=0; i<size; i++)
	{
		values[i] = v.values[i];
	}
		
	return *this;
}

const Vector Vector::operator*(const int scalar)const
{
	int *resultValues;
	if(size >0)
	{	
		int i = 0;
		resultValues = new int[size];
		for(i=0; i<size; i++)
			resultValues[i] = values[i] * scalar;
		return Vector(size, resultValues);
	}
	else
		std::cout<<"ERROR: Vector's' size is zero!"<<std::endl;;
	
}

const int Vector::operator*(const Vector &v)const // const keyword is very important
{
	if(v.size == size)
	{
		int temp=0, i=0;
		for(i=0; i<size; i++)
			temp += values[i] * v.values[i];
		return temp;
	}
	else
		std::cout<<"ERROR: Vectors have different sizes!"<<std::endl;
}


// CONSTRUCTOR
Vector::Vector(const int s, int const * const val)
{
	size = s;
	values = new int[size];
	
	for (int i = 0; i < size; i++) 
        values[i] = val[i];
}

// DESTRUCTOR
Vector::~Vector()
{
	delete []values;
}

// COPY CONSTRUCTOR
Vector::Vector(const Vector &p)
{
	size = p.size;
	values = new int[size];
	for(int i=0; i<size; i++)
		values[i] = p.values[i];
}

// OVERLOADING << OPERATOR
std::ostream& operator<< (std::ostream &out, const Vector &v) 
{
	int i;
	out<<"(";
	for(i=0; i<v.size; i++)
	{
		if(i!=0 && i!=v.size)
			out<<", ";
	
		out<<v.values[i];
	}	
	out<<")";
	return out;
}

#endif


