/*
Comunicação de processos.
O algoritmo aqui escrito foi baseado no fork-print.c e no shared-mem.c
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

//Compartilhamento por fila
#include <mqueue.h>

#define QUEUE "/my_queue"

int main()
{
    //Criação da fila
    mqd_t queue; // descritor da fila
    int msg;     // mensagem a enviar

    // abre a fila de mensagens, se existir
    if ((queue = mq_open(QUEUE, O_RDWR)) < 0)
    {
        perror("mq_open");
        exit(1);
    }

    int retval;
    retval = fork();

    //O algoritmo de cara já cria um novo processo filho
    //printf ("No processo %5d x vale %d\n", getpid(), x) ;

    //Em caso de erro ao criar novo processo, temos que o programa é finalizado
    if (retval < 0)
    {
        perror("Erro");
        exit(1);
    }
    else if (retval > 0)
    {
        //PAI
        for (;;)
        {
            msg = random() % 100; // valor entre 0 e 99

            // envia a mensagem
            if (mq_send(queue, (void *)&msg, sizeof(msg), 0) < 0)
            {
                perror("mq_send");
                exit(1);
            }
            printf("PAI: enviando mensagem com o valor: %d\n", msg);
            sleep(1);
        }
    }
    else
    {
        sleep(1);
        //FILHO  ---> Sera responsável por retirar as mensagens colocadas na fila
        mqd_t queue;         // descritor da fila de mensagens
        struct mq_attr attr; // atributos da fila de mensagens
        int msg;             // mensagens contendo um inteiro

        // define os atributos da fila de mensagens
        attr.mq_maxmsg = 10;           // capacidade para 10 mensagens
        attr.mq_msgsize = sizeof(msg); // tamanho de cada mensagem
        attr.mq_flags = 0;

        umask(0); // mascara de permissoes (umask)

        // abre ou cria a fila com permissoes 0666
        if ((queue = mq_open(QUEUE, O_RDWR | O_CREAT, 0666, &attr)) < 0)
        {
            perror("mq_open");
            exit(1);
        }
        //COM A FILA ABERTA IREMOS ESCUTAR OS VALORES
        for (;;)
        {
            if ((mq_receive(queue, (void *)&msg, sizeof(msg), 0)) < 0)
            {
                perror("mq_receive:");
                exit(1);
            }
            printf("FILHO: recebendo mensagem com o valor: %d\n", msg);
        }
    }
    exit(0);
}
