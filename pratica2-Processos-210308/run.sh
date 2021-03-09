#!/bin/bash

#Executa os 3 algotimos e salva a saida em um arquivo
gcc -Wall fork.c -o fork
gcc -Wall fork-execve.c -o forkexec
gcc -Wall fork-print.c -o fork-print

echo "Pratica 2 - 210308" > ResultadoSaida


echo "---------- Exercício 1 ----------" >> ResultadoSaida
./fork >> ResultadoSaida

echo "---------- Exercício 2 ----------" >> ResultadoSaida
./forkexec >> ResultadoSaida

echo "---------- Exercício 3 ----------" >> ResultadoSaida
./fork-print >> ResultadoSaida


