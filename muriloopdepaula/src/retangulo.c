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
        char corBo[25];
        char corPr[25];
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
        strcpy(re->corBo, corB);
        strcpy(re->corPr, corP);

        return re;
    }

    void destroiRetangulo(Retangulo r){
        RETANGULOR* re = (RETANGULOR*) r;
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