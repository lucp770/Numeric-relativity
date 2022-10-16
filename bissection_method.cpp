//generating a bissection method using simple non-linear functions.
//the function test_function_1 is monototicaly decreasing and test_function_2 is not
//the method should work to solve both the equations, using random sampling in a interval.
#include <iostream>
#include <cmath>
#include <time.h>


using namespace std;

double test_function_1(double x){
	//cos(x)-x =0
	//sol 0.739085
	double result = cos(x) - x;
	return result;

}

double test_function_2(double x){
	//x²-2x-2 =0
	//solution x= +- 1 - sqrt(3): -0.7320508075688772 and 2.732050807568877
	double result = x*x - 2*x -2;

	return result;
}


double root_finding_by_bissection(double inferior_limit, double superior_limit, double (*func)(double)){
/* execute bissection method in a given interval, for at maximum 1000 steps 
or until the error reaches 1e-6  the function is executed assuming that the the function results in diferent signs
on the values of inferior_limit and superior_limit */

 double tolerance  = 1e-8;
 int max_iteration_number = 1000;

 //avaliate the function in the limits of the interval
double f_superior = func(superior_limit);
double f_inferior = func(inferior_limit);
double f_c = 0;
double c = 0;
int iteration = 0;	

// do while f_superior - f_inferior > tolerance && max iterations 

do{
	//start the iterator
	
	if (f_superior > 0 && f_inferior <0){

		c = (superior_limit + inferior_limit)/2;
		f_c = func(c);

		if(f_c > 0){
			superior_limit = c;
			f_superior = f_c;

		}
		else if (f_c <0){
			inferior_limit = c;
			f_inferior = f_c;

		}
		else {
			//if c is in fact the root
			return c;
		}
	}

	else if (f_superior <0 && f_inferior >0){

		c = (superior_limit + inferior_limit)/2;
		f_c = func(c);

		if(f_c > 0){
			inferior_limit = c;
			f_inferior = f_c;
		}

		else if (f_c <0){
			superior_limit = c;
			f_superior = f_c;

		}

		else {
			//if c is in fact the root
			cout << "c is the root" << endl;
			return c;
		}

	}

	else{
		cout << "condition not satisfied, please redefine the interval" << endl;
	}

	iteration++;

	}while((abs(f_superior - f_inferior) > tolerance) && (iteration <= max_iteration_number));


	if(iteration > max_iteration_number){
		cout << "Bissection method failed to converge ..... " << endl;	
	}

	double root = c;
	return root;

}


// double search_positive_values((*func)(double)){



// 	return 0.0;
// }

double random_search_positive_values(double (*func)(double)){

//search in the interval with a 1000 numbers positive and negative.

	//1st seed the random generator it the instant of time.
	srand(time(NULL));

	for(int i=0; i < 1000; i++){

		double number = rand() % 1000;
		double number2 = - rand() % 1000;

		if(func(number) >0){
			cout << "positive_value found" << endl;
			return number;
		}

		if(func(number2) >0){
			cout << "positive_value found" << endl;
			return number2;
		}

	}

	cout << "positive_value not found" << endl;
	return 0.0;

}

double random_search_negative_values( double (*func)(double) ){
	//search in the interval with a 1000 numbers positive and negative.

	//1st seed the random generator it the instant of time.
	srand(time(NULL));

	for(int i=0; i < 1000; i++){

		double number = rand() % 1000;
		double number2 = - rand() % 1000;

		if(func(number) <0){
			cout << "negative value found" << endl;
			return number;
		}

		if(func(number2) < 0){
			cout << "negative value found" << endl;
			return number2;
		}
	}
	
	cout << "positive_value not found" << endl;
	return 0.0;
}



int main(){
	// double root = root_finding_by_bissection(0,10.0,&test_function_1);
	// cout <<" \n \n root value: " << to_string(root) << endl;
	// cout << to_string(test_function_2(0));

	double positivo = random_search_positive_values(&test_function_1);
	double negativo = random_search_negative_values(&test_function_1);

	cout << "valor positivo: " << to_string(positivo) << endl;
	cout << "funcao aplicada no positivo : " << to_string(test_function_1(positivo)) << endl;

	cout << "valor negativo: " << to_string(negativo) << endl;
	cout << "funcao aplicada no negativo " << to_string(test_function_1(negativo)) << endl;

	cout << " \n \n testando o método da bissecao com os valores encontrados ....." << endl;

	double root = root_finding_by_bissection(negativo,positivo,&test_function_1);
	cout <<" \n \n root value: " << to_string(root) << endl;


	return 0;
}

/* to do in sfcollaspe:
	-implement this tested method to find the bissection
	-solvers */



