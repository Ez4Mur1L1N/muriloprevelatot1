#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linha.h"

typedef struct{
    int id;
    double x1;
    double y1;
    double x2;
    double y2;
    char cor[25];
} LINHAL;

Linha criarLinha(int id, double x1, double y1, double x2, double y2, char *cor){
    LINHAL* li = (LINHAL*) malloc(sizeof(LINHAL));
    if(li == NULL){
        printf("Erro ao alocar memoria! Programa encerrado.");
        exit(1);
    }

    li->id = id;
    li->x1 = x1;
    li->y1 = y1;
    li->x2 = x2;
    li->y2 = y2;
    strcpy(li->cor, cor);

    return li;
}

void destroiLinha(Linha l){
    LINHAL* li = (LINHAL*) l;
    free(li);
}

int getIDLinha(Linha l){
    LINHAL* li = (LINHAL*) l;
    return li->id;
}

double getX1Linha(Linha l){
    LINHAL* li = (LINHAL*) l;
    return li->x1;
}

double getY1Linha(Linha l){
    LINHAL* li = (LINHAL*) l;
    return li->y1;
}

double getX2Linha(Linha l){
    LINHAL* li = (LINHAL*) l;
    return li->x2;
}

double getY2Linha(Linha l){
    LINHAL* li = (LINHAL*) l;
    return li->y2;
}

char *getCorLinha(Linha l){
    LINHAL* li = (LINHAL*) l;
    return li->cor;
}