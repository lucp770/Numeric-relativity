#include <stdio.h>
#include <stdlib.h>


int main(){

printf("%s\n \n \n", "Esse programa resolve numéricamente a métrica para o Buraco negro de Schwarzschild e compara o resultado com a sua solução analítica");

 /*o codigo abaixo sera inserido posteriormente para permitir a escolha de um raio diferente para o horizonte de eventos

printf("%s\n", "Insira o raio do horizonte de eventos para o Buraco negro de Schwarzschild: ");
double R;
scanf("%f",&R);

*/

double R =1 ; //teste inicial com o raio padrão 
double r[1000];

//preenchendo o array r com os pontos 

for(int i=1;i<1000;i=i++){
	r[i] = r[i-1]+0.1; //preenche o array r com incrementos de 0.1 a partir do raio do horizonte de eventos
}

printf("%s\n","Resolvendo numéricamente a métrica de Schwarzschild ...." );

//inserir aqui a solução pelo método das diferenças finitas



	return 0;
}