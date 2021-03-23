/*
Criação de threads POSIX em UNIX, com operação join().

Compilar com gcc -Wall thread-join.c -o thread-join -lpthread

Carlos Maziero, DINF/UFPR 2020
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 16

void *threadBody(void *id)
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
   pthread_attr_t attr ;   
   long i, status ;
   
   pthread_attr_init (&attr) ;
   //int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
   pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE) ; //função define o estado de desanexação atributo do objeto de atributos de thread referido por attr para o valor especificado em detachstate.

   for(i=0; i<NUM_THREADS; i++)
   {
      printf ("Main: criando thread %02ld\n", i) ;
      
      status = pthread_create (&thread[i], &attr, threadBody, (void *) i) ;
      if (status)
      {
         perror ("pthread_create") ;
         exit (1) ;
      }
   }
   
   for (i=0; i<NUM_THREADS; i++)
   {
      printf ("Main: aguardando thread %02ld\n", i);

      //A função pthread_join () deve suspender a execução do thread de chamada até que o thread de destino termine, a menos que o thread de destino já tenha terminado.
      status = pthread_join (thread[i], NULL) ;
      if (status)
      {
         perror ("pthread_join") ;
         exit (1) ;
      }
   }
   
   pthread_attr_destroy (&attr) ;
   
   pthread_exit (NULL) ;
}