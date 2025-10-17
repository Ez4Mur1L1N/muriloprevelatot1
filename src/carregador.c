#include <stdio.h>
#include <stdlib.h>
#include "carregador.h"
#include "pilha.h"

typedef struct{
    PILHA formasGeo;
} CARREGADORC;

Carregador criarCarregador(){
    CARREGADORC* ca = (CARREGADORC*) malloc(sizeof(CARREGADORC));
    if(ca == NULL){
        printf("Erro ao alocar memoria! Programa encerrado.");
        exit(1);
    }

    ca->formasGeo = criarPilha(); //Pilha que vai guardar os elementos do carregador. 'Essência' do carregador.
    return ca;
}

void destroiCarregador(Carregador c){
    CARREGADORC* ca = (CARREGADORC*) c;
    if(ca == NULL){
        return;
    }
    // Primeiro vamos dessacociar os elementos desse carregador, usando o destroiPilha.
    destroiPilha(ca->formasGeo);
    // Agora liberamos o carregador que está vazio.
    free(ca);
}

void carregaForma(Carregador c, void *Forma){
    CARREGADORC* ca = (CARREGADORC*) c; 
    if(ca == NULL){
        return;
    }
    push(ca->formasGeo, Forma);
}

void* descarregaForma(Carregador c){
    CARREGADORC* ca = (CARREGADORC*) c;
    if(ca == NULL){
        return NULL;
    }
    return pop(ca->formasGeo);
}

void *getTopoCarregador(Carregador c){
    CARREGADORC* ca = (CARREGADORC*) c;
    if(ca == NULL){
        return NULL;
    }
    return getTopo(ca->formasGeo);
}

int carregadorVazio(Carregador c){
    CARREGADORC* ca = (CARREGADORC*) c;
    if(ca == NULL){
        return 1; 
    } //Se não existe, vamos considerar vazio (1) vazio (0) alguma coisa.
    return pilhaVazia(ca->formasGeo);
}