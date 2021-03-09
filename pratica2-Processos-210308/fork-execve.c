/*
Criação de processos em UNIX, com execução de outro binário
 
Compilar com gcc -Wall fork-execve.c -o fork-execve
 
Carlos Maziero, DINF/UFPR 2020
*/
 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
 
int main (int argc, char *argv[], char *envp[])
{
   int retval ;
 
   printf ("Ola, sou o processo %5d\n", getpid()) ;
 
   retval = fork () ;
 
   printf ("[retval: %5d] sou %5d, filho de %5d\n",
           retval, getpid(), getppid()) ;
 
   if ( retval < 0 )
   {
      perror ("Erro: ") ;
      exit (1) ;
   }
   else 
      if ( retval > 0 )
         wait (0) ;
      else
      {
         //O funcionamento desse algoritmo é bastante semelhante ao anterior
	 //Porém  nessa etapa do código temos que o filho criado pelo processo será imediatamente substituido por um novo código
	 //O código em questão é passado atraves do comando execv
         execve ("/bin/date", argv, envp) ;
         perror ("Erro") ;
	 //Caso o procedimento seja realizado com sucesso, todo código do clase filha será substituido
	 //E a mensagem de erro aprenstada acima, nunca será mostrada ao usuário
      }
   //Dessa maneira somente o PAI irá apresentar o código abaixo 
   printf ("Tchau de %5d!\n", getpid()) ;
 
   exit (0) ;
}
