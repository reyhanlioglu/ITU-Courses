/*
 * runtime.h
 *
 *      Author: Emre Reyhanlioglu
 *      Number: 150140126
 */


#ifndef RUNTIME_H_
#define RUNTIME_H_

#include<string>

typedef struct Statement
{
    std::string type;
    std::string arg1;
    std::string arg2;
}Statement;

typedef struct node {
	int value;
	node *next;
}node;

typedef unsigned AddressValue;
typedef int ScalarValue;

template<typename T>
struct Stack
{
    //implement your stack here
    node *head;
	node *tail;
    void create();
	void print();
	int pop();
	void push(int n);
	int getCount();
	
};

AddressValue executeStatement( const Statement & statement, const AddressValue currentAddress, 
								ScalarValue variables [5], Stack<ScalarValue> & callStack, 
								const AddressValue addressOfCalleeIfCall, bool & isDone );

#endif /* RUNTIME_H_ */
