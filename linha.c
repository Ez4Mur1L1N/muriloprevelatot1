#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "linha.h"
#include "tipos.h"

typedef struct{
    int id;
    TipoForma tipo;
    double x1;
    double y1;
    double x2;
    double y2;
    char *cor;
} LINHAL;

Linha criarLinha(int id, double x1, double y1, double x2, double y2, char *cor){
    LINHAL* li = (LINHAL*) malloc(sizeof(LINHAL));
    if(li == NULL){
        printf("Erro ao alocar memoria! Programa encerrado.");
        exit(1);
    }

    li->id = id;
    li->tipo = LINHA;
    li->x1 = x1;
    li->y1 = y1;
    li->x2 = x2;
    li->y2 = y2;
    li->cor = (char*) malloc(sizeof(char)*(strlen(cor)+1));
    if(li->cor == NULL){
        printf("Erro ao alocar memoria");
        exit(1);
    }
    strcpy(li->cor, cor);

    return li;
}

void destroiLinha(Linha l){
    LINHAL* li = (LINHAL*) l;
    if(li == NULL){
        return;
    }
    free(li->cor);
    free(li);
}

int getIDLinha(Linha l){
    LINHAL* li = (LINHAL*) l;
    if (li == NULL) {
        return -1;
    }
    return li->id;
}

TipoForma getTipoLinha(Linha l){
    LINHAL* li = (LINHAL*) l;
    if (li == NULL) {
        return -1;
    }
    return li->tipo;
}

double getX1Linha(Linha l){
    LINHAL* li = (LINHAL*) l;
    if (li == NULL) {
        return 0.0;
    }
    return li->x1;
}

double getY1Linha(Linha l){
    LINHAL* li = (LINHAL*) l;
    if (li == NULL) {
        return 0.0;
    }
    return li->y1;
}

double getX2Linha(Linha l){
    LINHAL* li = (LINHAL*) l;
    if (li == NULL) {
        return 0.0;
    }
    return li->x2;
}

double getY2Linha(Linha l){
    LINHAL* li = (LINHAL*) l;
    if (li == NULL) {
        return 0.0;
    }
    return li->y2;
}

char *getCorLinha(Linha l){
    LINHAL* li = (LINHAL*) l;
    if (li == NULL) {
        return "";
    }
    return li->cor;
}

void setX1Linha(Linha l, double x1Novo){
    LINHAL* li = (LINHAL*) l;
    if (li == NULL) {
        return;
    }
    li->x1 = x1Novo;
}

void setY1Linha(Linha l, double y1Novo){
    LINHAL* li = (LINHAL*) l;
    if (li == NULL) {
        return;
    }
    li->y1 = y1Novo;
}

void setX2Linha(Linha l, double x2Novo){
    LINHAL* li = (LINHAL*) l;
    if (li == NULL) {
        return;
    }
    li->x2 = x2Novo;
}

void setY2Linha(Linha l, double y2Novo){
    LINHAL* li = (LINHAL*) l;
    if (li == NULL) {
        return;
    }
    li->y2 = y2Novo;
}

void setCorLinha(Linha l, char *corNova){
    LINHAL* li = (LINHAL*) l;
    if (li == NULL) {
        return;
    }
    free(li->cor);
    li->cor = (char*)malloc(sizeof(char)*(strlen(corNova)+1));
    if (li->cor == NULL) {
        printf("Erro ao alocar memoria para nova cor!");
        exit(1);
    }
    strcpy(li->cor, corNova);
}

double calcAreaLinha(Linha l){
    LINHAL* li = (LINHAL*) l;
    if (li == NULL) {
        return 0.0;
    }
    // Fórmula da distância entre dois pontos para o comprimento
    double dx = li->x2 - li->x1;
    double dy = li->y2 - li->y1;
    double comprimento = sqrt(dx*dx + dy*dy); 

    // Convenção do projeto: Área = 2.0 * comprimento
    return 2.0 * comprimento;
}