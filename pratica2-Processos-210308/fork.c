/*
Criação de processos em UNIX.
 
Compilar com gcc -Wall fork.c -o fork
 
Carlos Maziero, DINF/UFPR 2020
*/
 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
 
int main ()
{
	int retval ;

	//Primeiramente apresentamos uma mensagem que só será mostrada pelo processo pai, apresentando o seu PID  
   	printf ("Ola, sou o processo %5d\n", getpid()) ;
 
	//Criamos um novo processo filho que irá iniciar exatamento de onde o pai parou
	//O seu retorno da chamada de função será o PID do filho
	//Caso o valor seja menor que zero temos que chamada da função deu um problema
	retval = fork () ;

	//Neste momento temos duas instancias do processo
	//O pai com o retval igual ao do seu filho
	//e o filho com valor de retval igual a 0

	//Ambos processos irao apresentar suas informações
 	printf ("[retval: %5d] sou %5d, filho de %5d\n",
        retval, getpid(), getppid()) ;
 
	//Caso seja negativo irá apresentar uma mensagem de erro e finalizar
	if ( retval < 0 )
	{
		perror ("Erro") ;
		exit (1) ;
	}
	else{
		//Caso nao tenha dado problemas  e o "retval" seja maior que 0 temos que o processo é o pai
		//Uma chamada para wait () bloqueia o processo de chamada até que um de seus processos filho saia ou um sinal seja recebido
		if ( retval > 0 )
 			wait (0) ;
     		//Caso seja o filho ele irá esperar 5 segundos
		else
         		sleep (5) ;
 
	}

	//Dessas maneira temos que o processo pai só irá finalizar após o filho
	printf ("Tchau de %5d!\n", getpid()) ;
 
	exit (0) ;
}
