/*
Criação de processos em UNIX, com impressão de valores de variável.
 
Compilar com gcc -Wall fork-print.c -o fork-print
 
Carlos Maziero, DINF/UFPR 2020
*/
 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
 
int main ()
{
   int retval, x ;
   x = 0 ; 
   retval = fork () ; 
   
   //O algoritmo de cara já cria um novo processo filho	  
   printf ("No processo %5d x vale %d\n", getpid(), x) ;
 

   //Em caso de erro ao criar novo processo, temos que o programa é finalizado
   if ( retval < 0 )
   {
      perror ("Erro") ;
      exit (1) ;
   }
   else
      if ( retval > 0 )
      {
         x = 0 ;
         wait (0) ;
      }
      else
      {
	 //Temos que no processo filho e somente nele a variável  x será incrementada
	 //E logo após o processo irá esperar 5 segundos
         x++ ;
         sleep (5) ;
      }
 
   //ao finalizar o processo filho, temos que a variável x foi incrementada somente para ele.
   //Isso nos mostra que as variávei entre processos são independentes
   printf ("No processo %5d x vale %d\n", getpid(), x) ;
 
   exit (0) ;
}
