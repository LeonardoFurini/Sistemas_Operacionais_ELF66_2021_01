#!/bin/bash

#Executa os 3 algotimos de exemplo
gcc -Wall share-mem.c -o share-mem -lrt
gcc -Wall mqueue-send.c -o mqueue-send -lrt
gcc -Wall mqueue-recv.c -o mqueue-recv -lrt
gcc -Wall process-comunication-share-mem.c -o process-comunication-share-mem -lrt

echo "Pratica 2 - 210308" > ResultadoSaida


echo "---------- share-mem ----------" >> ResultadoSaida
./share-mem | ts "%.S" >> ResultadoSaida

echo "---------- mqueue-send ----------" >> ResultadoSaida
./mqueue-send | ts "%.S" >> ResultadoSaida

echo "---------- mqueue-recv ----------" >> ResultadoSaida
./mqueue-recv | ts "%.S" >> ResultadoSaida

echo "---------- process-comunication-share-mem ----------" >> ResultadoSaida
./process-comunication-share-mem | ts "%.S" >> ResultadoSaida


