#include "absoluto.h"
#include <stdio.h>
#include <math.h>


float absoluto(float valor){
	float value_return;
	if(valor < 0){
		value_return = valor*-1;
	}else{
		value_return = valor;
	}
	return value_return;
}


float easy_abs(float valor){
	float retorno = fabs(valor);
	return retorno; 
}
