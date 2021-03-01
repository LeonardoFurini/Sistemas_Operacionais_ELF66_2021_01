#!/bin/bash



#compilação da biblioteca
gcc -c absoluto.c
ar rvs libglobal.a absoluto.o

#Compila o código em c
# -static ----> As bibliotecas de sistema serão incluidas ao projeto
gcc -o main  main.c libglobal.a

#Encaminha os resultados do script para o arquivo resultadoMain
./main > resultadoMain
