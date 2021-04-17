/*
Comunicação de processos.
O algoritmo aqui escrito foi baseado no fork-print.c e no shared-mem.c
*/
 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

//Compartilhamento de memoria
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
 
int main ()
{
    int fd, value, *ptr;
   
   // Abre/cria uma area de memoria compartilhada
   fd = shm_open("/sharedmem", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
   if(fd == -1) {
      perror ("shm_open");
      exit (1) ;
   }

   //Ajusta o tamanho da area compartilhada
   if (ftruncate(fd, sizeof(value)) == -1) {
      perror ("ftruncate");
      exit (1) ;
   }
   
   // Mapeia a area no espaco de enderecamento deste processo
   ptr = mmap(NULL, sizeof(value), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
   if(ptr == MAP_FAILED) {
      perror ("mmap");
      exit (1);
   }

    //Inicia a variável compartilhada com 1
   (*ptr) = 1 ;

   int retval;
   retval = fork () ; 
   
   //O algoritmo de cara já cria um novo processo filho	  
   //printf ("No processo %5d x vale %d\n", getpid(), x) ;
 
   //Em caso de erro ao criar novo processo, temos que o programa é finalizado
   if ( retval < 0 )
   {
      perror ("Erro") ;
      exit (1) ;
   }
   else
      if ( retval > 0 )
      {
        //PAI
        value = (*ptr) ;
        while(value < 10){
            //Caso o valor seja PAR
            if(value%2==0){
                value++;
                (*ptr) = value ;
                printf ("PAI: O valor foi alterado para: %d\n", value) ;
            }
            value = (*ptr) ;
        }
      }
      else
      {
        //FILHO
        value = (*ptr) ;
        while(value < 10){
            //Caso o valor seja IMPAR
            if(value%2!=0){
                value++;
                (*ptr) = value ;
                printf ("FILHO: O valor foi alterado para: %d\n", value) ;
            }
            value = (*ptr) ;
        }
      }
 
   exit (0) ;
}
