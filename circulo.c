#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> //Para o cálculo da área.
#include "circulo.h"
#include "tipos.h"

typedef struct{
    int id;
    TipoForma tipo;
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
    ci->tipo = CIRCULO;
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
    if (ci == NULL){
        return;
    }
    free(ci->corBo);
    free(ci->corPr);
    free(ci);
}

int getIDCirculo(Circulo c){
    CIRCULOC* ci = (CIRCULOC*) c;
    if (ci == NULL) {
        return -1;
    }
    return ci->id;
}

TipoForma getTipoCirculo(Circulo c){
    CIRCULOC* ci = (CIRCULOC*) c;
    if (ci == NULL) {
        return -1;
    }
    return ci->tipo;
}

double getXCirculo(Circulo c){
    CIRCULOC* ci = (CIRCULOC*) c;
    if (ci == NULL) {
        return 0.0;
    }
    return ci->x;
}

double getYCirculo(Circulo c){
    CIRCULOC* ci = (CIRCULOC*) c;
    if (ci == NULL) {
        return 0.0;
    }
    return ci->y;
}

double getRCirculo(Circulo c){
    CIRCULOC* ci = (CIRCULOC*) c;
    if (ci == NULL) {
        return 0.0;
    }
    return ci->r;
}

char *getCorBCirculo(Circulo c){
    CIRCULOC* ci = (CIRCULOC*) c;
    if (ci == NULL) {
        return "";
    }
    return ci->corBo;
}

char *getCorPCirculo(Circulo c){
    CIRCULOC* ci = (CIRCULOC*) c;
    if (ci == NULL) {
        return "";
    }
    return ci->corPr;
}

void setXCirculo(Circulo c, double xNovo){
    CIRCULOC* ci = (CIRCULOC*) c;
    if (ci == NULL){
        return;
    } 
    ci->x = xNovo;
}

void setYCirculo(Circulo c, double yNovo){
    CIRCULOC* ci = (CIRCULOC*) c;
    if (ci == NULL) {
        return;
    }   
    ci->y = yNovo;
}

void setCorBCirculo(Circulo c, char *corBNova){
    CIRCULOC* ci = (CIRCULOC*) c;
    if (ci == NULL) {
        return;
    }
    free(ci->corBo);

    ci->corBo = (char*)malloc(sizeof(char)*(strlen(corBNova)+1));
    if (ci->corBo == NULL) {
        printf("Erro ao alocar memoria para nova cor!");
        exit(1);
    }
    strcpy(ci->corBo, corBNova);
}

void setCorPCirculo(Circulo c, char *corPNova){
    CIRCULOC* ci = (CIRCULOC*) c;
    if (ci == NULL) {
        return;
    }
    free(ci->corPr);

    ci->corPr = (char*)malloc(sizeof(char)*(strlen(corPNova)+1));
    if (ci->corPr == NULL) {
        printf("Erro ao alocar memoria para nova cor!");
        exit(1);
    }
    strcpy(ci->corPr, corPNova);
}

double calcAreaCirculo(Circulo c){
    CIRCULOC* ci = (CIRCULOC*) c;
    if (ci == NULL) {
        return 0.0;
    }   
    // Fórmula da área do círculo: pi * r²
    return M_PI * ci->r * ci->r;
}
