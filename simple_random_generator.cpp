//use rand() from  stdlib.h

#include <stdlib.h>
#include <iostream>
#include <time.h>

using namespace std;


void changing_random_generator(int upper_bound){
	// this function seeds the rand() function with the srand()
	// to generate a diferent random number sequence at each time.
	// The seed used to the random function is the current time in seconds.
	int number;
	int i;

	srand(time(NULL));//seed the srand function

	for(i=1; i<=10;i++){
		number = rand()%upper_bound;
		cout << number << "\t";

	}

}


void simple_generator(){
// this function generates always the same sequence
	int number;

	for(int i=1; i <=10; i++){

	number  = rand() % 100;

	std::cout << number << "\t";

	 
	}
}


int main(){

	changing_random_generator(200);

	return 0;
}


