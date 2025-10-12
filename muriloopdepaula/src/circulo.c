#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circulo.h"

typedef struct{
    int id;
    double x;
    double y;
    double r;
    char corBo[25];
    char corPr[25];
} CIRCULOC;

Circulo criarCirculo(int id, double x, double y, double r, char *corB, char *corP){
    CIRCULOC* ci = (CIRCULOC*) malloc(sizeof(CIRCULOC));
    if(ci == NULL){
        printf("Erro ao alocar memoria! Programa encerrado.");
        exit(1);
    }

    ci->id = id;
    ci->x = x;
    ci->y = y;
    ci->r = r;
    strcpy(ci->corBo, corB);
    strcpy(ci->corPr, corP);

    return ci;
}

void destroiCirculo(Circulo c){
    CIRCULOC* ci = (CIRCULOC*) c;
    free(ci);
}

int getIDCirculo(Circulo c){
    CIRCULOC* ci = (CIRCULOC*) c;
    return ci->id;
}

double getXCirculo(Circulo c){
    CIRCULOC* ci = (CIRCULOC*) c;
    return ci->x;
}

double getYCirculo(Circulo c){
    CIRCULOC* ci = (CIRCULOC*) c;
    return ci->y;
}

double getRCirculo(Circulo c){
    CIRCULOC* ci = (CIRCULOC*) c;
    return ci->r;
}

char *getCorBCirculo(Circulo c){
    CIRCULOC* ci = (CIRCULOC*) c;
    return ci->corBo;
}

char *getCorPCirculo(Circulo c){
    CIRCULOC* ci = (CIRCULOC*) c;
    return ci->corPr;
}