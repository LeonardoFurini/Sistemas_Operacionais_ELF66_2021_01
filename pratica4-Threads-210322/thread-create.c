/*
Criação de threads POSIX em UNIX.

Compilar com gcc -Wall thread-create.c -o thread-create -lpthread

Carlos Maziero, DINF/UFPR 2020
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 16

void *threadBody (void *id)
{
   long tid = (long) id ;

   printf ("t%02ld: Olá!\n", tid) ;
   sleep (3) ;   
   printf ("t%02ld: Tchau!\n", tid) ;
   
   pthread_exit (NULL) ;
}

int main (int argc, char *argv[])
{
   pthread_t thread [NUM_THREADS] ;
   long i, status ;
   
   for (i=0; i<NUM_THREADS; i++)
   {
      printf ("Main: criando thread %02ld\n", i) ;
      
      /*
      int pthread_create( pthread_t *restrict thread,                //
                          const pthread_attr_t *restrict attr,       //O argumento attr aponta para uma estrutura pthread_attr_t cujo os conteúdos são usados ​​no momento da criação do thread para determinar os atributos para o novo segmento;esta estrutura é inicializada usando pthread_attr_init (3) e funções relacionadas. Se attr for NULL, em seguida, o encadeamento é criado com atributos padrão.
                          void *(*start_routine)(void *),            //O novo thread começa a execução invocando start_routine ();
                          void *restrict arg);                       //arg é passado como o único argumento de start_routine ().
      */
      status = pthread_create (&thread[i], NULL, threadBody, (void *) i) ;

      //Em caso de sucesso status = 0, caso contrario:
      if (status)
      {
         perror ("pthread_create") ;
         exit (1) ;
      }
   }
   pthread_exit (NULL) ;
}