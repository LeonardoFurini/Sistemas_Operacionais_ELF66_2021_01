#!/bin/bash


gcc -Wall ppos_core.c pingpong-tasks1.c -o task1
gcc -Wall ppos_core.c pingpong-tasks2.c -o task2
gcc -Wall ppos_core.c pingpong-tasks3.c -o task3

echo "Pratica 7 -  Gestao de Tarefas" > ResultadoSaida

echo "---------- TASK 1 ----------" >> ResultadoSaida
./task1 | ts "%.S" >> ResultadoSaida

echo "---------- TASK 2 ----------" >> ResultadoSaida
./task2 | ts "%.S" >> ResultadoSaida

echo "---------- TASK 3 ----------" >> ResultadoSaida
./task3 | ts "%.S" >> ResultadoSaida

