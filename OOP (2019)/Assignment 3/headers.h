/* @Author
* Student Name: Emre Reyhanlioglu
* Student ID : 150140126 
* Date: 08.05.2019 */

using namespace std;

#ifndef HEADERS_H
#define HEADERS_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>

#define ORDER_MAX 300


float getPrice(string itemName);


class Item
{
	string name;
	int type;
	int count;
	float price;
	
	public:
		Item();
		Item(string name, int type, int itemCount);
		Item(string name, int type, int itemCount, float price);
		bool reserveItem(int n);
		string getName(){return name;}
		int getType(){return type;}
		int getCount(){return count;}
		float getPrice(){return price;}
		void setName(string n){name = n;}
		void setType(int t){type = t;}
		void setCount(int c){count = c;}
		void setPrice(float p){price = p;}
		
		
};



Item::Item(){}

Item::Item(string n, int t, int c)
{
	name = n;
	type = t;
	count = c;
}

Item::Item(string n, int t, int c, float p)
{
	name = n;
	type = t;
	count = c;
	price = p;
}

bool Item::reserveItem(int n)
{
	if(count>0)
	{
		count-=n;
		return true;
	}
	return false;
}


class ItemsInMenu
{
	string name;
	Item ingredients[10] ;
	int  numberOfIngredients;
	float price;
	
	public:
		ItemsInMenu();
		ItemsInMenu(string name, Item* ingredients, int count);
		string getName(){return name;}
		Item* getIngredients(){return ingredients;}
		bool isType2()
		{
			if(numberOfIngredients==0)
				return true;
		    else return false;	
		}
		
};



ItemsInMenu::ItemsInMenu()
{
	name = "";
	numberOfIngredients = 0;
	price = 0;
}

ItemsInMenu::ItemsInMenu(string n, Item* ingr, int count)
{
	name = n;
	numberOfIngredients = count;

	for(int i=0; i<count; i++)
	{
		ingredients[i].setName(ingr[i].getName());
		ingredients[i].setType(ingr[i].getType());
		ingredients[i].setCount(ingr[i].getCount());
		ingredients[i].setPrice(ingr[i].getPrice());
	}		
}





void readStock(Item *stockItems)
{
	//Item *stockItems = new Item[40];
	ifstream input("stock.txt");
    string line, output;
    
    //Read the first line
    getline(input, output);
	int counter = 0;
    for(int i=0; getline(input, output, '\t'); i++ )  {
        string name= output;
        
        getline(input, output, '\t');
        int type = atoi (output.c_str());
        
        getline(input, output, '\t');
        int count = atoi (output.c_str());
        
        getline(input, output, '\n');
        float price = atof (output.c_str());
        
        stockItems[i] = Item(name, type, count, price);
        
        counter++;
    }
    input.close();
    //return stockItems;	
	
}


ItemsInMenu* readMenu()
{
	ItemsInMenu *menuItems = new ItemsInMenu[20];
	Item ingredients[6];
	ifstream input("menu.txt");
    string line, output;
    
    //Read the first line
    getline(input, output);
    
    //Reading the 2 items in the menu
    for(int i=0; i<2 ; i++ )  {
    	
    	
    	getline(input, output, '\t');
        string name= output;
        
        
        getline(input, output, ' ');
        int count = atoi (output.c_str());
        int type = 1;
        getline(input, output, ' ');
        getline(input, output, ',');
        string ingName = output;
        
        ingredients[0] = Item(ingName, type, count );
        
        for(int j=0; j<4; j++)
        {
        	getline(input, output, ' ');
        	getline(input, output, ' ');
	        count = atoi (output.c_str());
	        type = 2;
	        getline(input, output, ',');
	        ingName = output;
	        ingredients[j+1] = Item(ingName, type, count );
		}
		
		getline(input, output, ' ');
		getline(input, output, ' ');
        count = atoi (output.c_str());
        type = 3;
        getline(input, output, ' ');
        getline(input, output, '\n');
        ingName = output;
        ingredients[5] = Item(ingName, type, count );
        
        
        menuItems[i] = ItemsInMenu(name, ingredients, 6);
	}
	
	
	//Reading the third item in the menu
	getline(input, output, '\t');
    string name= output;
    
    
    getline(input, output, ' ');
    int count = atoi (output.c_str());
    int type = 1;
    getline(input, output, ' ');
    getline(input, output, ',');
    string ingName = output;
    ingredients[0] = Item(ingName, type, count );
    
    for(int j=0; j<2; j++)
    {
    	getline(input, output, ' ');
    	getline(input, output, ' ');
        count = atoi (output.c_str());
        type = 2;
        getline(input, output, ',');
        ingName = output;
        ingredients[j+1] = Item(ingName, type, count );
	}
	
	for(int j=0; j<2; j++)
	{
		getline(input, output, ' ');
		getline(input, output, ' ');
        count = atoi (output.c_str());
        type = 3;
        getline(input, output, ' ');
        getline(input, output, ',');
        ingName = output;
        ingredients[j+3] = Item(ingName, type, count );
	}
	
	getline(input, output, ' ');
	getline(input, output, ' ');
    count = atoi (output.c_str());
    type = 3;
    getline(input, output, ' ');
    getline(input, output, '\n');
    ingName = output;
    ingredients[5] = Item(ingName, type, count );
    
    menuItems[2] = ItemsInMenu(name, ingredients, 6);
    
    
    //Reading the fourth item in the menu
	getline(input, output, '\t');
    name= output;
    
    
    getline(input, output, ' ');
    count = atoi (output.c_str());
    type = 1;
    getline(input, output, ' ');
    getline(input, output, ',');
    ingName = output;
    ingredients[0] = Item(ingName, type, count );
    
    for(int j=0; j<3; j++)
    {
    	getline(input, output, ' ');
    	getline(input, output, ' ');
        count = atoi (output.c_str());
        type = 2;
        getline(input, output, ',');
        ingName = output;
        ingredients[j+1] = Item(ingName, type, count );
	}
	
	for(int j=0; j<1; j++)
	{
		getline(input, output, ' ');
		getline(input, output, ' ');
        count = atoi (output.c_str());
        type = 3;
        getline(input, output, ' ');
        getline(input, output, ',');
        ingName = output;
        ingredients[j+4] = Item(ingName, type, count );
	}
	
	getline(input, output, ' ');
	getline(input, output, ' ');
    count = atoi (output.c_str());
    type = 3;
    getline(input, output, ' ');
    getline(input, output, '\n');
    ingName = output;
    ingredients[5] = Item(ingName, type, count );
    
    menuItems[3] = ItemsInMenu(name, ingredients, 6);
    
	
	
	//Reading the fifth item in the menu
	getline(input, output, '\t');
    name= output;
    
    getline(input, output, ' ');
    count = atoi (output.c_str());
    type = 1;
    getline(input, output, ' ');
    getline(input, output, ',');
    ingName = output;
    ingredients[0] = Item(ingName, type, count );
    
    for(int j=0; j<2; j++)
    {
    	getline(input, output, ' ');
    	getline(input, output, ' ');
	    int count = atoi (output.c_str());
	    int type = 1;
	    getline(input, output, ' ');
	    getline(input, output, ',');
	    string ingName = output;
	    
	    ingredients[j+1] = Item(ingName, type, count );
	}
    
    for(int j=0; j<2; j++)
    {
    	getline(input, output, ' ');
    	getline(input, output, ' ');
        count = atoi (output.c_str());
        type = 2;
        getline(input, output, ',');
        ingName = output;
        ingredients[j+3] = Item(ingName, type, count );
	}
	
	getline(input, output, ' ');
	getline(input, output, ' ');
    count = atoi (output.c_str());
    type = 3;
    getline(input, output, ' ');
    getline(input, output, '\n');
    ingName = output;
    ingredients[5] = Item(ingName, type, count );
    
    menuItems[4] = ItemsInMenu(name, ingredients, 6);
	
	
	
	//Reading the sixth item in the menu
	getline(input, output, '\t');
    name= output;
    
    
    getline(input, output, ' ');
    count = atoi (output.c_str());
    type = 1;
    getline(input, output, ' ');
    getline(input, output, ',');
    ingName = output;
    ingredients[0] = Item(ingName, type, count );
    
    for(int j=0; j<3; j++)
    {
    	getline(input, output, ' ');
    	getline(input, output, ' ');
        count = atoi (output.c_str());
        type = 2;
        getline(input, output, ',');
        ingName = output;
        ingredients[j+1] = Item(ingName, type, count );
	}
	
	for(int j=0; j<1; j++)
	{
		getline(input, output, ' ');
		getline(input, output, ' ');
        count = atoi (output.c_str());
        type = 3;
        getline(input, output, ' ');
        getline(input, output, ',');
        ingName = output;
        ingredients[j+4] = Item(ingName, type, count );
	}
	
	getline(input, output, ' ');
	getline(input, output, ' ');
    count = atoi (output.c_str());
    type = 3;
    getline(input, output, ' ');
    getline(input, output, '\n');
    ingName = output;
    ingredients[5] = Item(ingName, type, count );
    
    menuItems[5] = ItemsInMenu(name, ingredients, 6);
    
	
	//Reading the rest of the items in the menu
	for(int j=0; j<8; j++)
	{
		getline(input, output, '\t');
    	string name= output;
    	getline(input, output, '\n');
    	menuItems[j+6] = ItemsInMenu(name, NULL, 0);
	}
	
	input.close();
	return menuItems;
}

ItemsInMenu getItemFromMenu(string name)
{
	ItemsInMenu* menu = readMenu();
	for(int i=0; i<20; i++)
	{
		if(menu[i].getName() == name)
			return menu[i];
		
			
	}
	//cout<<"Item not found"<<endl;
	delete[] menu;
	return ItemsInMenu("", new Item("", 0, 0, 0), 0);
}

float getPrice(string itemName)
{
	Item items[40];
	readStock(items);
	bool found=false;
	for(int i; !found && items[i].getName()!= ""; i++)
	{
		if(items[i].getName() == itemName)
		{
			found = true;
			return items[i].getPrice();
		}	
	}
	//delete[] items;
	return -1;
}



class Table
{
	ItemsInMenu orders[ORDER_MAX];
	int numberOfOrders;
	float totalCost;
	
	public:
		Table();
		Table(ItemsInMenu* orderList, int orderCount);
		ItemsInMenu* getOrders(){return orders;}
		int getNumberOfOrders(){return numberOfOrders;}
		void setNumberOfOrders(int n){numberOfOrders=n;}
};

Table::Table(){
	numberOfOrders = 0;
	totalCost=0;
	
}

Table::Table(ItemsInMenu* orderList, int orderCount )
{
	numberOfOrders = 0;
	totalCost=0;
	
	for(int i=0; i<orderCount; i++)
	{
		orders[i] = orderList[i];
	}
		
}



float checkAndReserve(Item* stock, string menuName, int count);


void proceedOrder()
{
	Item stock[40];
	readStock(stock);
	Table tables[5];
	ifstream input("order.txt");
    string line, output;
    int numberOfTables=0;
    
    while(getline(input, output)&& numberOfTables<5) 
    {
    	getline(input, output); 
    	int numberOfOrders = atoi (output.c_str());
    	int iter=0;
    	
    	for(int i=0; i<numberOfOrders; i++)
    	{
    		getline(input, output, ' '); 
    		int itemCount = atoi (output.c_str());
    		getline(input, output); 
    		
    		for(int j=0; j<itemCount; j++, iter++)
    		{
    			tables[numberOfTables].getOrders()[iter] = getItemFromMenu(output);
			}
		}

		tables[numberOfTables].setNumberOfOrders(iter);
		numberOfTables++;
	}
	
	
	
	// Process orders
	for(int i=0; i<numberOfTables; i++)
	{
		int j=0, counter=0;
		for(j=0; j<tables[i].getNumberOfOrders();j++ )
		{
			counter = 0;
			while(tables[i].getOrders()[j].getName() == tables[i].getOrders()[j+1].getName())
			{
				counter++;
				j++;
			}
			//cout<<"Table "<<i<<" => "<<counter+1<<" "<<tables[i].getOrders()[j].getName()<<endl;
		}	
	}
	
	
	
	
	// Serve orders
	for(int i=0; i<numberOfTables; i++)
	{
		cout<<"Table"<<i+1<<" ordered:"<<endl;
		float totalCost=0;
		
		if(tables[i].getNumberOfOrders()>0) //If there is any order
		{
			for(int j=0; j<tables[i].getNumberOfOrders(); j++)
			{
				int numberOfItem = 1;
				while(tables[i].getOrders()[j].getName() == tables[i].getOrders()[j+1].getName())
				{
					numberOfItem++;
					j++;
				}
	
				totalCost += checkAndReserve(stock, tables[i].getOrders()[j].getName(), numberOfItem );		
			}
			
			cout<<"Tip is "<<totalCost*0.15 <<endl;
			cout<<"Total cost: "<< totalCost*1.23 <<" TL"<<endl;
			cout<<"**************************"<<endl;
		}
	}
	
	input.close();
	
	remove( "stock.txt" );
	
	std::ofstream outfile ("stock.txt");
	
	outfile << "Name\tType\tItemCount\tPrice" << endl;
	for(int i=0; stock[i].getType()>0; i++)
	{
		outfile << stock[i].getName()<<"\t"<<stock[i].getType()<<"\t"<<stock[i].getCount()<<"\t"<<stock[i].getPrice()<<endl;
	}
	
	outfile.close();
	input.close();
	//delete[] stock;
}


int getStockCount(Item* stock, string name)
{
	for(int i=0; i<30; i++)
	{
		if(stock[i].getName() == name)
			return stock[i].getCount();	
	}
	return -1;
}

void decreaseStockCount(Item* stock, string name, int n)
{
	for(int i=0; i<30; i++)
	{
		if(stock[i].getName() == name)
		{
			stock[i].reserveItem(n);
			return;
		}		
	}
}




float checkAndReserve(Item* stock, string menuName, int count)
{
	if(!getItemFromMenu(menuName).isType2())
	{
		
		Item* items = getItemFromMenu(menuName).getIngredients();
		
		//CHECK THE STOCK
		bool canReserve = true;
		int reservable=0;
		float totalPrice = 0;
		
		for(int k=0; k<count ; k++)
		{
			for(int i=0; i<6 ; i++)
			{
				string neededItem = items[i].getName();
				int neededNumber = items[i].getCount();
				
				int stockNumber = getStockCount(stock, neededItem);
				
				//If there is not enough item
				if(neededNumber>stockNumber)
				{
					canReserve = false;	
				}	
			}
		
			if(canReserve)
			{
				reservable++;
				
				for(int i=0; i<6; i++)
				{
					string neededItem = items[i].getName();
					int neededNumber = items[i].getCount();
					
					decreaseStockCount(stock, neededItem, neededNumber);
					totalPrice += getPrice(neededItem)*neededNumber;		
				}
					
			}
		}
		
		if(reservable>0)
		{
			cout<<reservable<<" "<<menuName<<" cost: "<<totalPrice<<endl;
		}
		if(count-reservable >0)
		{
			cout<<"We don't have enough "<<menuName<<endl;
		}
		
		//delete[] items;
		return totalPrice;	
	}
	
	
	//Its type 2 
	else
	{
		float totalPrice = 0;
		int stockNumber = getStockCount(stock, menuName);
		
		//Eðer stoktakinden daha fazlasý lazýmsa
		if(stockNumber>0 && stockNumber<count)
		{
			decreaseStockCount(stock, menuName, stockNumber);
			totalPrice = stockNumber*getPrice(menuName);
			cout<<stockNumber<<" "<<menuName<<" cost: "<<totalPrice<<endl;
			cout<<"We don't have enough "<<menuName<<endl;
		}
		else if(stockNumber>=count)
		{
			decreaseStockCount(stock, menuName, count);
			totalPrice = count*getPrice(menuName);
			cout<<count<<" "<<menuName<<" cost: "<<totalPrice<<endl;
		}
		else
		{
			cout<<"We don't have enough "<<menuName<<endl;
		}
		return totalPrice;	
	}
		
}


#endif
