#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

typedef struct nos{
    void *elemento;
    struct nos *prox;
} NOS;

typedef NOS *NO;

typedef struct{
    NO inicio;
    NO fim;
    int tamanho;
} FILAF;

FILA criarFila(){
    FILAF* fi = (FILAF*) malloc(sizeof(FILAF));

    if(fi == NULL){
        printf("Erro ao alocar memoria! Programa encerrado.");
        exit(1);
    }

    fi->inicio = NULL;
    fi->fim = NULL;
    fi->tamanho = 0;
    return fi;
}

int filaVazia(FILA f){
    FILAF* fi = (FILAF*) f;

    if(fi->tamanho == 0){
        return 1;
    } else{
        return 0;
    }
}

void insereElemFila(FILA f, void *elemento){
    FILAF* fi = (FILAF*) f;

    NO novo = (NO) malloc(sizeof(NOS));
    if(novo == NULL){
        printf("Erro ao alocar memoria! Programa encerrado.");
        exit(1);
    }

    novo->elemento = elemento;
    novo->prox = NULL;
    // Para essa função vamos analisar dois casos:
    // 1º: Fila estava vazia antes;
    if(filaVazia(f)){
        fi->inicio = novo;
    } else { // 2º: Fila com algum elemento;
        fi->fim->prox = novo;
    }
    fi->fim = novo;
    fi->tamanho++;
}

void *removeElemFila(FILA f){
    FILAF* fi = (FILAF*) f;

    if(filaVazia(f)){ //Fila vazia;
        return NULL;
    }

    NO retira = fi->inicio;
    void *elementoRetirado = retira->elemento;

    fi->inicio = fi->inicio->prox;
    // Caso a fila esteja vazia após essa remoção:
    if(fi->inicio == NULL){
        fi->fim = NULL;
    }

    free(retira);
    fi->tamanho--;
    return elementoRetirado;
}

void *getFirstElem(FILA f){
    FILAF* fi = (FILAF*) f;

    if(filaVazia(f)){
        return NULL;
    } else{
        return fi->inicio->elemento;
    }
}

void destroiFila(FILA f){
    while(!filaVazia(f)){
        removeElemFila(f);
    }
    free(f);
}

int getTamanhoFila(FILA f){
    FILAF* fi = (FILAF*) f;
    return fi->tamanho;
}