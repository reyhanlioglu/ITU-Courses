#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

int main() {
	
	int r = 0, n=5;
	
	for(int i=1; i<= n; i++) {
		for(int j=i+1; j<= n; j++) {
			for(int k=1; k<=j; k++){
				r++;
			
			}
		}	
	}
	cout<<"Result is "<<r;
}
