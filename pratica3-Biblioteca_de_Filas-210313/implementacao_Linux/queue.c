#ifndef QUEUE_INCLUDED
#define QUEUE_INCLUDED

#include "queue.h"

int queue_size(queue_t *queue)
{
    //printf("###FUNÇÃO - queue_size\n");
    if (queue != NULL)
    {
        queue_t *aux = queue;
        int size = 1;
        while (aux->next != queue)
        {
            aux = aux->next;
            size++;
        }
        return size;
    }
    else
    {
        return 0;
    }
}

void queue_append(queue_t **queue, queue_t *elem)
{
    //printf("###FUNÇÃO - queue_append\n");

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
    if(queue != NULL && elem != NULL && queue[0] != NULL)
    {
            queue_t * aux  = queue[0];
            int flag = 0 ;
            do{                 // Verifica se o elemento existe na fila;
                if(aux == elem){
                    flag++;
                    break;
                }
                aux = aux->next;
            }while(aux != queue[0]);

            if(queue[0] == elem && flag > 0)
            {
                queue[0] = elem->next ;
            }

            if( flag > 0  && elem->next != elem ){
                elem->next->prev = elem->prev;
                elem->prev->next = elem->next;

                elem->next = NULL;
                elem->prev = NULL;

                return elem;
            }else if(flag > 0 && elem->next == elem){
                    queue[0] = NULL ;
                    elem->next = NULL;
                    elem->prev = NULL;
                    return elem;
            }else
                return NULL;
    }else
        return NULL;
}

//Procura se o elemento está na fila
//Retorno 1 : O elemento está na fila
//Retorno 0 : O elemento não foi encontrado na fila
int check_element_in_queue(queue_t **queue, queue_t *elem)
{
    //printf("###FUNÇÃO - check_element_in_queue\n");
    //Descobrimos o tamanho da fila
    int counter = 0, flag = 0;
    int size_queue = queue_size((queue_t*) queue);
    queue_t *aux = queue[0];
    while (counter < size_queue)
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

void queue_print(char *name, queue_t *queue, void print_elem(void *))
{
    if(queue != NULL){
        int i = 0;
        queue_t *aux = queue;
        for (i = 0; i < queue_size(queue); i++)
        {
            print_elem(aux);
            aux = aux->next;
        }
    }
}

#endif