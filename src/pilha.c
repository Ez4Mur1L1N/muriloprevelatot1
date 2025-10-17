#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

typedef struct nos{
    void *elemento; // Ponteiro genérico para receber qualquer elemento.
    struct nos *prox;
} NOS;

typedef NOS *NO;

typedef struct{
    int tamanho;
    NO topo;
} PILHAP;

/*
Estrutura da pilha definida: possui nós, que contém um elemento e um ponteiro apontando pro
próximo nó. Além disso, é definida pelo topo.
*/

PILHA criaPilha(){
    PILHAP *pi = (PILHAP*) malloc(sizeof(PILHAP));

    if(pi == NULL){
        printf("Erro ao alocar memoria! Programa encerrado.");
        exit(1);
    }
    pi->topo = NULL;
    pi->tamanho = 0;
    return pi;
}

int pilhaVazia(PILHA p){
    PILHAP* pi = (PILHAP*) p;

    if(pi->tamanho == 0){
        return 1;
    } else{
        return 0;
    }
}

void push(PILHA p, void *elemento){
    PILHAP* pi = (PILHAP*) p;

    NO novo = (NO) malloc(sizeof(NOS));
    if(novo == NULL){
        printf("Erro ao alocar memoria! Programa Encerrado.");
        exit(1);
    }
    novo->elemento = elemento;
    novo->prox = pi->topo;
    pi->topo = novo;
    pi->tamanho++;
}

void *pop(PILHA p){
    PILHAP* pi = (PILHAP*) p;
    
    if(pilhaVazia(p)){ //Pilha vazia
        return NULL;
    }


    NO retira = pi->topo;
    void *elementoRetirado = pi->topo->elemento;

    pi->topo = pi->topo->prox;
    free(retira);
    pi->tamanho--;
    return elementoRetirado;
}

void *getTopo(PILHA p){
    PILHAP* pi = (PILHAP*) p;

    if(pilhaVazia((p))){
        return NULL;
    } else{
        return pi->topo->elemento;
    }
}

void destroiPilha(PILHA p){
    while(!pilhaVazia(p)){
        pop(p);
    }
    // Enquanto NÃO estiver vazia, percorre ela dando pop e depois libera a pilha.
    free(p);
}

int getTamanhoPilha(PILHA p){
    PILHAP* pi = (PILHAP*) p;
    return pi->tamanho;
}