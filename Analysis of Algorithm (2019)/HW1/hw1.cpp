//     BLG 335 
//    HOMEWORK 1
// EMRE REYHANLIOGLU 
//    150140126

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib> //Converts string to int

using namespace std;

class FileOperator{
	public:
		int* readFile(char const* filename, int numberOfElements);
		void writeToFile(char const* filename, int* array, int size);
};


class SortingMachine{
	private:
		int* array; 
		int size;
		clock_t startTime;
		float requiredTime;
		void recMergeSort(int first, int last);
		void merge( int first, int last, int mid);
	
	public:	
		SortingMachine(int* list, int size);
		int bublesort();
		int mergesort();
		void printList();
		void printRequiredTime();
};



int main(int argc, char *argv[]) {
	char const* outputFile = "output.txt"; 
	char const* inputFile = argv[3];
	int size = atoi(argv[2]);
	
//  Testing variables for Windows OS
//	char const* inputFile = "unsorted.txt"; 
//	int size = 999999; 	

	if(size < 0) {
		cout<<"Size can not be negative! Terminating the program..."<<endl;
		exit(1);
	}					
	
	FileOperator fileOperator;
	int* list = fileOperator.readFile(inputFile, size); 
	
	SortingMachine* sortingMachine = new SortingMachine(list, size);
	
	if(argv[1][0] == 'b' || argv[1][0] == 'B')
		sortingMachine->bublesort();
		
	else if(argv[1][0] == 'm' || argv[1][0] == 'M')
		sortingMachine->mergesort();
	
	else{
		cout<<"Invalid parameter! You should use 'b' for buble sort or 'm' for merge sort"<<endl;
		exit(1);
	}

//	sortingMachine->printList(); // for testing 

	sortingMachine->printRequiredTime();
	
	fileOperator.writeToFile(outputFile, list, size);
}




// READ FILE METHOD OF FileOperator class
int* FileOperator::readFile(char const* filename, int numberOfElements){
	int value = 0 , i = 0;
	int* list = new int[numberOfElements];
	ifstream file;
	file.open(filename);
	
	 if (!file) {
        cout << "File could not be opened!";
        exit(1); 
    }
    
    for(i=0; i<numberOfElements && file >> value; i++) 
    	list[i] = value;
	
	if(i < numberOfElements){
		cout<<"There are not "<<numberOfElements<<" elements in the input file. Terminating the program..."<<endl;
		exit(1);
	}
	
	file.close();
	return list;
}

// WRITE TO FILE METHOD OF FileOperator class
void FileOperator::writeToFile(char const* filename, int* array, int size){
	cout<<"STATUS: Writing to file, please wait."<<endl;
	ofstream file;
    file.open(filename);
    
    for(int i=0; i<size; i++)
		file << array[i] << endl;
	
	file.close();
	cout<<"STATUS: Completed."<<endl;
}


// CONSTRUCTOR OF SortingMachine class
SortingMachine::SortingMachine(int* list, int size){
	this->size = size;
	this->array = list;
	this->requiredTime = 0;
}


// BUBLE SORT METHOD OF SortingMachine class
int SortingMachine::bublesort(){
	if(size <= 0){
		cout<<"There is not any element in the list. Program has terminated!"<<endl;
		return -1;
	}
	
	bool sorted = false;
	clock_t passedTime;
	startTime = clock();
	
	for(int i=size; i>1 && !sorted; i--){
		sorted = true;
		for(int j=1; j<=i-1; j++){
			if(array[j] < array[j-1]){
				//Exchange operations
				int temp = array[j-1];
				array[j-1] = array[j];
				array[j] = temp;
				
				sorted = false;
			}
		}
	}
	
	requiredTime = ( clock() - startTime ) / (double) CLOCKS_PER_SEC;
	return 0;
}


// MERGE SORT METHOD OF SortingMachine class
int SortingMachine::mergesort(){
	if(size <= 0){
		cout<<"There is not any element in the list. Program has terminated!"<<endl;
		return -1;
	}
	startTime = clock();
	
	recMergeSort( 0, size - 1);
	
	requiredTime = ( clock() - startTime ) / (double) CLOCKS_PER_SEC;
	return 0;
}


// Helper method of mergesort METHOD
void SortingMachine::recMergeSort(int first, int last){                     
    if(first < last){
        int mid = first + (last-first)/2;  // Precaution for overflow (instead of (first+last)/2 )
        recMergeSort(first, mid);
        recMergeSort(mid+1, last);
        merge(first, mid, last);   
    }
    
}

// Helper method of recMergeSort METHOD
void SortingMachine::merge(int first, int mid, int last)     {
    int i=0, j=0, k=0;
    
    int leftSize = mid - first +1;
    int rightSize = last - mid;
    
    int* leftArray= new int[leftSize];
	int* rightArray= new int[rightSize];
    
    // Initializing the left part of the array to the leftArray[]
    for(i=0; i < leftSize; i++)
        leftArray[i] = array[first+i];
    
    // Initializing the right part of the array to the rightArray[]
    for(i=0; i < rightSize; i++)
        rightArray[i] = array[mid+i+1];
    
    
    //Comparing and merging all elements into the array in a sorted order 
    for(i=0, k=first; i < leftSize && j < rightSize; k++){
        if(leftArray[i] < rightArray[j]){
            array[k] = leftArray[i];
            i++;
        }else{
            array[k] = rightArray[j];
            j++;
        }
    }
  
    for(; i < leftSize; i++, k++)
        array[k] = leftArray[i];
    
    
    for(; j < rightSize; j++, k++)
    	array[k] = rightArray[j];
	
    
}

// PRINT METHOD OF SortingMachine class
void SortingMachine::printList(){
	for(int i=0; i<size; i++)
		cout<<array[i]<<endl;
}

void SortingMachine::printRequiredTime(){
	cout<<"Required time for this algorithm is "<< requiredTime<< " seconds"<<endl;
}
