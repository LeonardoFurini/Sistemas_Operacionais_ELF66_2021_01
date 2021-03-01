#!/bin/bash

#Compila o código em c
gcc -Wall main.c -o main

#Encaminha os resultados do script para o arquivo resultadoMain
./main > resultadoMain
