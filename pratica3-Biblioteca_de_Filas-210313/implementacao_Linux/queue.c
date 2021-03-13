#ifndef QUEUE_INCLUDED
#define QUEUE_INCLUDED

#include "queue.h"

//Mudançaa

int queue_size(queue_t *queue)
{
    printf("###FUNÇÃO - queue_size\n");

    //Caso a esteja vazio retorne 0
    if (queue == NULL)
        return 0;

    //Guarda o primeiro elemento da fila
    int counter = 1;
    queue_t *temp = queue;
    while (queue != temp)
    {
        counter++;
        temp = temp->next;
    }
    return counter;
}

void queue_append(queue_t **queue, queue_t *elem)
{
    printf("###FUNÇÃO - queue_append\n");

    if (&queue != NULL && elem != NULL && elem->next == NULL)
    {
        if (*queue == NULL)
        {                  // Se a lista estiver vazia "queue" aponta para "elem"...
            *queue = elem; // ... e posteriormente aponta para si proprio em ambas as dire�oes.
            elem->next = elem;
            elem->prev = elem;
        }
        else if (queue[0]->next == queue[0])
        {
            queue[0]->next = elem;
            queue[0]->prev = elem;
            elem->next = queue[0];
            elem->prev = queue[0];
        }
        else
        {
            queue_t *ini = *queue;    // Inicio aponta para "elem" com anterior.
            queue_t *end = ini->prev; // Fim aponta para "elem" com proximo.

            ini->prev = elem;
            end->next = elem;

            elem->next = ini;
            elem->prev = end;
        }
    }

    if (&queue == NULL)
    {
        printf("###ERRO - A fila não existe\n");
    }
    if (elem == NULL)
    {
        printf("###ERRO - O elemento não existe\n");
    }
    if (elem->next == NULL)
    {
        printf("###ERRO - O elemento pertence a outra fila\n");
    }
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
        return NULL;
    }
    // - a fila nao deve estar vazia
    if (queue_size(queue) == 0)
    {
        printf("###ERRO - A fila está vazia\n");
        return NULL;
    }
    // - o elemento deve existir
    if (check_element_in_queue(queue, elem) == 0)
    {
        printf("###ERRO - O elemento nao foi encontrado na fila\n");
        return NULL;
    }

    //Caso o primeiro elemento da fila seja o proprio elemento
    if (queue[0] == elem)
    {
        //Modifico o next para novo elemento
        queue[0] = elem->next;
    }

    //Caso ele esteja no meio da fila
    if (elem->next != elem)
    {
        elem->next->prev = elem->prev;
        elem->prev->next = elem->next;

        elem->next = NULL;
        elem->prev = NULL;

        return elem;
    }
    //Caso o proximo elemento seja ele mesmo, ele é o unico elemento da fila
    else if (elem->next == elem)
    {
        queue[0] = NULL;
        elem->next = NULL;
        elem->prev = NULL;
        return elem;
    }
    else
    {
        return NULL;
    }
}

//Procura se o elemento está na fila
//Retorno 1 : O elemento está na fila
//Retorno 0 : O elemento não foi encontrado na fila
int check_element_in_queue(queue_t **queue, queue_t *elem)
{
    printf("###FUNÇÃO - check_element_in_queue\n");
    //Descobrimos o tamanho da fila
    int counter = 0, flag = 0;
    int size_queue = queue_size(queue);
    queue_t *aux = queue[0];
    while (counter <= size_queue)
    {
        if (aux == elem)
        {
            flag++;
            break;
        }
        aux = aux->next;
        counter++;
    }
    return flag;
}

void queue_print (char *name, queue_t *queue, void print_elem (void*) )
{
    int i = 0;
    queue_t * aux = queue;
    for(i = 0 ; i < queue_size(queue) ; i++){
        print_elem(aux);
        aux = aux->next;
    }
}

#endif