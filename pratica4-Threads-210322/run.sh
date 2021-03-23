#!/bin/bash

#Executa os 3 algotimos e salva a saida em um arquivo
gcc -Wall thread-create.c -o thread-create -lpthread
gcc -Wall thread-join.c -o thread-join -lpthread
gcc -Wall thread-print.c -o thread-print -lpthread

echo "Pratica 2 - 210308" > ResultadoSaida


echo "---------- Exercício 1 ----------" >> ResultadoSaida
./thread-create >> ResultadoSaida

echo "---------- Exercício 2 ----------" >> ResultadoSaida
./thread-join >> ResultadoSaida

echo "---------- Exercício 3 ----------" >> ResultadoSaida
./thread-print >> ResultadoSaida


