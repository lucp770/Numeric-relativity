//importe das bibliotecas padrão
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//definindo as equações diferenciais

double eqA(double A, double B, double r){
	double result = A*B/r - A/r;
	return result;
}

double eqB(double A, double B, double r){
	double result = -B*B/r + B/r;
	return result;
}

// método principal
int main(){

printf("%s\n \n \n", "Esse programa resolve numéricamente a métrica para o Buraco negro de Schwarzschild e compara o resultado com a sua solução analítica");

 /*o codigo abaixo sera inserido posteriormente para permitir a escolha de um raio diferente para o horizonte de eventos

printf("%s\n", "Insira o raio do horizonte de eventos para o Buraco negro de Schwarzschild: ");
double R;
scanf("%f",&R);

*/

double r0 =1 ; //teste inicial com o raio padrão 
double r[201];//define a matriz para armazenar os valores da distância radial onde o problema será resolvido
double h = 0.01;

//arrays para armazenar as soluções
double A[201];
double B[201];

//estabelecendo as condições inicais
A[0] =0.013;
B[0] = 100;//entendido como infinito
r[0] = 1;

double K1a,K1b,K2a,K2b;


printf("%s\n \n ","Resolvendo numéricamente a métrica de Schwarzschild ....");

//método de Runge-Kutta de ordem 2
for(int n=1;n<=201;n++){
	r[n] = r[n-1]+h; //preenche o array r 

	//calcula as variaveis auxiliares para o método de Runge-Kutta
	K1a = eqA(A[n-1],B[n-1],r[n-1]);
	K1b = eqB(A[n-1],B[n-1],r[n-1]);

	K2a = eqA(A[n-1]+h*K1a,B[n-1]+h*K1b,r[n-1]+h);
	K2b = eqB(A[n-1]+h*K1a,B[n-1]+h*K1b,r[n-1]+h);

	//Calculando os valors de A e B no próximo ponto
	A[n] = A[n-1]+.5*h*(K1a+K2a);//depende tanto de A e B
	B[n] = B[n-1]+.5*h*(K1b+K2b);
}

printf("termo 143 de A : %f\n",A[143] );
printf("termo 17 de B: %f\n",B[17] );

	return 0;
}