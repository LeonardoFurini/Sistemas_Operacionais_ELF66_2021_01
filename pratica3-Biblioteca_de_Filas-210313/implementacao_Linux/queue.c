#ifndef QUEUE_INCLUDED
#define QUEUE_INCLUDED

#include "queue.h"

//Mudançaa

int queue_size(queue_t *queue)
{
    printf("###FUNÇÃO - queue_size\n");
    //Guarda o primeiro elemento da fila
    int counter = 0;
    queue_t *firstElement = queue;
    queue_t *temp = firstElement->next;
    while (firstElement != temp)
    {
        counter++;
        temp = firstElement->next;
    }
    return counter;
}

void queue_append(queue_t **queue, queue_t *elem)
{
    printf("###FUNÇÃO - queue_append\n");
    //Verificações
    //--A fila deve existir
    if (!queue)
    {
        printf("###ERRO - A fila não existe\n");
        return;
    }
    //--O elemento deve existir
    if (!elem)
    {
        printf("###ERRO - O elemento não existe\n");
        return 0;
    }
    //--O elemento nao pode pertencer a outra fila
    //Para isso devemos olhar o PREV e NEXT do elemento
    if (elem->next != NULL || elem->prev != NULL)
    {
        printf("###ERRO - O elemento pertence a outra fila\n");
        return 0;
    }

    //O último elemento será o prev de queue
    queue_t lastElement = queue->prev;

    //Inserindo
    elem->next = lastElement->next;
    elem->prev = lastElement;
    lastElement->next = elem;
}

// Remove o elemento indicado da fila, sem o destruir.
// Condicoes a verificar, gerando msgs de erro:
// - a fila deve existir
// - a fila nao deve estar vazia
// - o elemento deve existir
// - o elemento deve pertencer a fila indicada
// Retorno: apontador para o elemento removido, ou NULL se erro

queue_t *queue_remove(queue_t **queue, queue_t *elem)
{
    printf("###FUNÇÃO - queue_remove\n");
    // - a fila deve existir
    if (!queue)
    {
        printf("###ERRO - A fila não existe\n");
        return;
    }
    // - a fila nao deve estar vazia
    if (queue_size(queue) == 0)
    {
        printf("###ERRO - A fila está vazia\n");
        return;
    }
    // - o elemento deve existir
    if (!check_element_in_queue(queue, elem))
    {
        printf("###ERRO - O elemento nao foi encontrado na fila\n");
    }

    //Retirando o Elemento
    queue_t *temp_previous = elem->prev;
    temp_previous->next = elem->next;

    queue_t *temp_front = elem->next;
    temp_front->prev = elem->prev;

    elem->next = NULL;
    elem->prev = NULL;
    return elem;
}

//Procura se o elemento está na fila
//Retorno 1 : O elemento está na fila
//Retorno 0 : O elemento não foi encontrado na fila
int check_element_in_queue(queue_t **queue, queue_t *elem)
{
    printf("###FUNÇÃO - check_element_in_queue\n");
    //Descobrimos o tamanho da fila
    int size_queue = queue_size(queue);
    int counter = 0;
    queue_t *temp = queue;
    while (counter < size_queue)
    {
        if (temp == elem)
        {
            return 1;
        }
        counter++;
        temp = temp->next;
    }
    return 0;
}

#endif