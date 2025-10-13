#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circulo.h"

typedef struct{
    int id;
    double x;
    double y;
    double r;
    char *corBo;
    char *corPr;
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
    ci->corBo = (char*)malloc(sizeof(char)*(strlen(corB)+1));
    if(ci->corBo == NULL){
        printf("Erro ao alocar memoria!");
        exit(1);
    }
    strcpy(ci->corBo, corB);
    ci->corPr = (char*)malloc(sizeof(char)*(strlen(corP)+1));
    if(ci->corPr == NULL){
        printf("Erro ao alocar memoria!");
        exit(1);
    }
    strcpy(ci->corPr, corP);

    return ci;
}

void destroiCirculo(Circulo c){
    CIRCULOC* ci = (CIRCULOC*) c;
    free(ci->corBo);
    free(ci->corPr);
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