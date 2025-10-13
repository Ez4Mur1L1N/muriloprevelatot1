#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retangulo.h"

typedef struct{
    int id;
    double x;
    double y;
    double w;
    double h;
    char *corBo;
    char *corPr;
} RETANGULOR;

Retangulo criarRetangulo(int id, double x, double y, double w, double h, char *corB, char *corP){
    RETANGULOR* re = (RETANGULOR*) malloc(sizeof(RETANGULOR));
    if(re == NULL){
        printf("Erro ao alocar memoria! Programa encerrado.");
        exit(1);
    }

    re->id = id;
    re->x = x;
    re->y = y;
    re->w = w;
    re->h = h;
    re->corBo = (char*) malloc(sizeof(char)*(strlen(corB)+1));
    if(re->corBo == NULL){
        printf("Erro ao alocar memoria!");
        exit(1);
    }
    strcpy(re->corBo, corB);
    re->corPr = (char*) malloc(sizeof(char)*(strlen(corP)+1));
    if(re->corBo == NULL){
        printf("Erro ao alocar memoria!");
        exit(1);
    }
    strcpy(re->corPr, corP);

    return re;
}

void destroiRetangulo(Retangulo r){
    RETANGULOR* re = (RETANGULOR*) r;
    free(re->corBo);
    free(re->corPr);
    free(re);
}

int getIDRetangulo(Retangulo r){
    RETANGULOR* re = (RETANGULOR*) r;
    return re->id;
}

double getXRetangulo(Retangulo r){
    RETANGULOR* re = (RETANGULOR*) r;
    return re->x;
}

double getYRetangulo(Retangulo r){
    RETANGULOR* re = (RETANGULOR*) r;
    return re->y;
}

double getWRetangulo(Retangulo r){
    RETANGULOR* re = (RETANGULOR*) r;
    return re->w;
}

double getHRetangulo(Retangulo r){
    RETANGULOR* re = (RETANGULOR*) r;
    return re->h;
}

char *getCorBRetangulo(Retangulo r){
    RETANGULOR* re = (RETANGULOR*) r;
    return re->corBo;
}

char *getCorPRetangulo(Retangulo r){
    RETANGULOR* re = (RETANGULOR*) r;
    return re->corPr;
}