#!/bin/bash

#Executa os 3 algotimos de exemplo
gcc -Wall shared-mem.c -o shared-mem -lrt
gcc -Wall mqueue-send.c -o mqueue-send -lrt
gcc -Wall mqueue-recv.c -o mqueue-recv -lrt
gcc -Wall process-comunication-shared-mem.c -o process-comunication-shared-mem -lrt

echo "Pratica 2 - 210308" > ResultadoSaida


echo "---------- shared-mem ----------" >> ResultadoSaida
./shared-mem | ts "%.S" >> ResultadoSaida

echo "---------- mqueue-send ----------" >> ResultadoSaida
./mqueue-send | ts "%.S" >> ResultadoSaida

echo "---------- mqueue-recv ----------" >> ResultadoSaida
./mqueue-recv | ts "%.S" >> ResultadoSaida

echo "---------- process-comunication-share-mem ----------" >> ResultadoSaida
./process-comunication-share-mem | ts "%.S" >> ResultadoSaida


