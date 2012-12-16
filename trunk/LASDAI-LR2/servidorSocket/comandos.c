#include <stdio.h>
#include "comandos.h"

/*******************************************************/

int comandos(struct tipoComando comando){
	return 0;
}

/*******************************************************/

short int deSerializeShort(unsigned char *buf){
    union{
        unsigned char c[2];
        short int val;
    }short_int;
    if(buf == NULL){
    	return -1;
    }
    short_int.c[1] = *buf;
    short_int.c[0] = *(buf + 1);
    return short_int.val;
}

/*******************************************************/

void serializeShort(unsigned char *buf, short int value){
    if (buf == NULL){
        return;
    }
    union{
        unsigned char c[2];
        short int val;
    }short_int;
    short_int.val = value;
    *buf = short_int.c[1];
}

/*******************************************************/

double deSerializeDouble(unsigned char *buf){
	int k;
    union{
        unsigned char c[8];
        double d;
    }doubling;
    for (k = 0; k < 8; k++){
        doubling.c[7 - k] = *(buf + k);
    }
    return doubling.d;
}

/*******************************************************/

void serializeDouble(unsigned char *buf, double value){
    int k;
	if (buf == NULL){
        return;
    }
    union {
    	unsigned char c[8];
        double d;
    } doubling;
    doubling.d = value;
    for (k = 0; k < 8; k++){
        *(buf + k) = doubling.c[7 - k];
    }
}

/*******************************************************/
