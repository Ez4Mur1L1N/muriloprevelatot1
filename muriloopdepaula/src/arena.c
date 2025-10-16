#include <stdio.h>
#include <stdlib.h>
#include "arena.h"

typedef struct{
    Fila formasInseridas;
}ARENAA;

Arena criarArena(){
    ARENAA* ar = (ARENAA*) malloc(sizeof(ARENAA));
    if(ar == NULL){
        printf("Erro ao alocar memoria! Programa encerrado");
        exit(1);
    }

    ar->formasInseridas = criarFila();
    return ar;
}

void destroiArena(Arena a){
    ARENAA* ar = (ARENAA*) a;
    if(ar == NULL){
        return;
    }
    
    destroiFila(ar->formasInseridas);
    free(ar);
}

void inserirFormaArena(Arena a, void* Forma){
    ARENAA* ar = (ARENAA*) a;
    if(ar == NULL){
        return;
    }
    insereElemFila(ar->formasInseridas, Forma);
}

void *removeFormaArena(Arena a){
    ARENAA* ar = (ARENAA*) a;
    if(ar == NULL){
        return NULL;
    }
    return removeElemFila(ar->formasInseridas);
}

int arenaVazia(Arena a){
    ARENAA* ar = (ARENAA*) a;
    if(ar == NULL){
        return 1; //Considereramos vazia, caso não exista.
    }

    return filaVazia(ar->formasInseridas);
}

Fila getFilaArena(Arena a){
    ARENAA* ar = (ARENAA*) a;
    if(ar == NULL){
        return NULL;
    }
    return ar->formasInseridas;
}