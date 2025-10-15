#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "texto.h"

typedef struct estiloTexto{
    char *fFamily;
    char *fWeight;
    char *fSize;
} EstiloTexto;

typedef struct{
    int id;
    double x;
    double y;
    char *corBo;
    char *corPr;
    char a; //âncora
    char *txt;
    EstiloTexto estilo;
} TEXTOT;

Texto criarTexto(int id, double x, double y, char *corB, char *corP, char a, char *texto, char *fFamily, char *fWeight, char *fSize){
    TEXTOT* te = (TEXTOT*) malloc(sizeof(TEXTOT));
    if(te == NULL){
        printf("Erro ao alocar memoria! Programa encerrado.");
        exit(1);
    }

    te->id = id;
    te->x = x;
    te->y = y;
    te->a = a;
    te->corBo = (char*) malloc(sizeof(char)*(strlen(corB)+1));
    if(te->corBo == NULL){
        printf("Erro ao alocar memoria.");
        exit(1);
    }
    strcpy(te->corBo, corB);
    te->corPr = (char*) malloc(sizeof(char)*(strlen(corP)+1));
    if(te->corPr == NULL){
        printf("Erro ao alocar memoria.");
        exit(1);
    }
    strcpy(te->corPr, corP);
    te->texto = (char*) malloc(sizeof(char)*(strlen(texto)+1));
    if(te->texto == NULL){
        printf("Erro ao alocar memoria.");
        exit(1);
    }
    strcpy(te->texto, texto);
    te->estilo.fFamily = (char*) malloc(sizeof(char)*(strlen(fFamily)+1));
    if(te->estilo.fFamily == NULL){
        printf("Erro ao alocar memoria.");
        exit(1);
    }
    strcpy(te->estilo.fFamily, fFamily);
    te->estilo.fWeight = (char*) malloc(sizeof(char)*(strlen(fWeight)+1));
    if(te->estilo.fWeight == NULL){
        printf("Erro ao alocar memoria.");
        exit(1);
    }
    strcpy(te->estilo.fWeight, fWeight);
    te->estilo.fSize = (char*) malloc(sizeof(char)*(strlen(fSize)+1));
    if(te->estilo.fSize == NULL){
        printf("Erro ao alocar memoria.");
        exit(1);
    }
    strcpy(te->estilo.fSize, fSize);

    return te;
}

void destroiTexto(Texto t){
    TEXTOT* te = (TEXTOT*) t;
    free(te->corBo);
    free(te->corPr);
    free(te->texto);
    free(te->estilo.fFamily);
    free(te->estilo.fWeight);
    free(te->estilo.fSize);
    free(te);
}

int getIDTexto(Texto t){
    TEXTOT* te = (TEXTOT*) t;
    return te->id;
}

double getXTexto(Texto t){
    TEXTOT* te = (TEXTOT*) t;
    return te->x;
}

double getYTexto(Texto t){
    TEXTOT* te = (TEXTOT*) t;
    return te->y;
}

char *getCorBTexto(Texto t){
    TEXTOT* te = (TEXTOT*) t;
    return te->corBo;
}

char *getCorPTexto(Texto t){
    TEXTOT* te = (TEXTOT*) t;
    return te->corPr;
}

char getAncoraTexto(Texto t){
    TEXTOT* te = (TEXTOT*) t;
    return te->a;
}

char *getTexto_Texto(Texto t){
    TEXTOT* te = (TEXTOT*) t;
    return te->texto;
}

char *getFonteFamilyTexto(Texto t){
    TEXTOT* te = (TEXTOT*) t;
    return te->estilo.fFamily;
}

char *getFonteWeightTexto(Texto t){
    TEXTOT* te = (TEXTOT*) t;
    return te->estilo.fWeight;
}

char *getFonteSizeTexto(Texto t){
    TEXTOT* te = (TEXTOT*) t;
    return te->estilo.fSize;
}

void setXTexto(Texto t, double xNovo) {
    TEXTOT* te = (TEXTOT*) t;
    if (te == NULL) {
        return;
    }
    te->x = xNovo;
}

void setYTexto(Texto t, double yNovo) {
    TEXTOT* te = (TEXTOT*) t;
    if (te == NULL) {
        return;
    }
    te->y = yNovo;
}

void setCorBTexto(Texto t, char *corBNova) { 
    TEXTOT* te = (TEXTOT*) t;
    if (te == NULL) {
        return;
    }
    free(te->corBo);
    te->corBo = (char*)malloc(sizeof(char)*(strlen(corBNova)+1));
    if (te->corBo == NULL) {
        printf("Erro ao alocar memoria para nova cor!");
        exit(1);
    }
    strcpy(te->corBo, corBNova);
}

void setCorPTexto(Texto t, char *corPNova) { 
    TEXTOT* te = (TEXTOT*) t;
    if (te == NULL) {
        return;
    }
    free(te->corPr);
    te->corPr = (char*)malloc(sizeof(char)*(strlen(corPNova)+1));
    if (te->corPr == NULL) {
        printf("Erro ao alocar memoria para nova cor!");
        exit(1);
    }
    strcpy(te->corPr, corPNova);
}

double calcAreaTexto(Texto t) {
    TEXTOT* te = (TEXTOT*) t;
    if (te == NULL || te->txt == NULL) {
        return 0.0;
    }
    // Convenção do projeto: Área = 20.0 * número de caracteres
    return 20.0 * strlen(te->txt);
}