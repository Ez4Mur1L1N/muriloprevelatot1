#include <stdio.h>
#include <stdlib.h>
#include "disparador.h"

typedef struct{
    int id;
    double x;
    double y;
    Carregador caEsquerdo;
    Carregador caDireito;
    void* formaDisparo; //Elemento na posição de disparo.
} DISPARADORD;

Disparador criarDisparador(int id, double x, double y){
    DISPARADORD* di = (DISPARADORD*) malloc(sizeof(DISPARADORD));
    if(di == NULL){
        printf("Erro ao alocar memoria! Programa encerrado");
        exit(1);
    }

    di->id = id;
    di->x = x;
    di->y = y;
    di->caEsquerdo = criarCarregador();
    di->caDireito = criarCarregador();
    // Inicialmente a posição de disparo está vazia.
    di->formaDisparo = NULL;

    return di;
}

void destroiDisparador(Disparador d){
    DISPARADORD* di = (DISPARADORD*) d;
    if(di == NULL){
        return;
    }
    destroiCarregador(di->caEsquerdo);
    destroiCarregador(di->caDireito);
    free(di);
}

void anexaCarregadoresDisparador(Disparador d, Carregador esq, Carregador dir) {
    DISPARADORD* di = (DISPARADORD*) d;
    if (di == NULL) return;

    // Destruímos os carregadores vazios que foram criados junto com o disparador.
    destroiCarregador(di->caEsquerdo);
    destroiCarregador(di->caDireito);

    // Anexamos os novos carregadores que vieram de fora.
    di->caEsquerdo = esq;
    di->caDireito = dir;
}

void carregaFormaDisparador(Disparador d, void *elemento, char lado){
    DISPARADORD* di = (DISPARADORD*) d;
    if(di == NULL){
        return;
    }
    if(lado == 'e' || lado == 'E'){
        carregaForma(di->caEsquerdo, elemento);
    } else if (lado == 'd' || lado == 'D'){
        carregaForma(di->caDireito, elemento);
    }
}

void selecionaDireitaDisparador(Disparador d){
    DISPARADORD* di = (DISPARADORD*) d;
    if(di == NULL){
        return;
    }
    // Vamos pegar o elemento do topo do carregador direito.
    void* novaFormaGeo = descarregaForma(di->caDireito);
    if(novaFormaGeo != NULL){ // Só pra garatir que pegamos realmente algo e que o carregador não estava vazio.
        if(di->formaDisparo != NULL){ // Vamos tratar o caso em que já existia uma forma na posição de disparo.
            carregaForma(di->caEsquerdo, di->formaDisparo);
        }
        di->formaDisparo = novaFormaGeo;
    }
}

void selecionaEsquerdaDisparador(Disparador d){
    DISPARADORD* di = (DISPARADORD*) d;
    if(di == NULL){
        return;
    }
    // Vamos pegar o elemento do topo do carregador esquerdo.
    void* novaFormaGeo = descarregaForma(di->caEsquerdo);
    if(novaFormaGeo != NULL){ // Só pra garatir que pegamos realmente algo e que o carregador não estava vazio.
        if(di->formaDisparo != NULL){ // Vamos tratar o caso em que já existia uma forma na posição de disparo.
            carregaForma(di->caDireito, di->formaDisparo);
        }
        di->formaDisparo = novaFormaGeo;
    }
}

void shiftDisparador(Disparador d, char lado, int n){
    DISPARADORD* di = (DISPARADORD*) d;
    if(di == NULL){
        return;
    }

    for(int i = 0; i < n; i++){
        if(lado == 'e' || lado == 'E'){
            if(di->formaDisparo != NULL){ //Caso já tenha algo no disparador.
                carregaForma(di->caEsquerdo, di->formaDisparo);
            }
            di->formaDisparo = descarregaForma(di->caDireito);

        } else if(lado == 'd' || lado == 'D'){
            if(di->formaDisparo != NULL){
                carregaForma(di->caDireito, di->formaDisparo);
            }
            di->formaDisparo = descarregaForma(di->caEsquerdo);
        }

    }
}

void *disparar(Disparador d){
    DISPARADORD* di = (DISPARADORD*) d;
    if(di == NULL){
        return NULL;
    }

    void* formaAtirada = di->formaDisparo;
    di->formaDisparo = NULL;
    return formaAtirada;
}

int getIdDisparador(Disparador d){
    DISPARADORD* di = (DISPARADORD*) d;
    return di->id;
}

double getXDisparador(Disparador d){
    DISPARADORD* di = (DISPARADORD*) d;
    return di->x;
}

double getYDisparador(Disparador d){
    DISPARADORD* di = (DISPARADORD*) d;
    return di->y;
}

Carregador getCarrEsquerdaDisparador(Disparador d){
    DISPARADORD* di = (DISPARADORD*) d;
    return di->caEsquerdo;
}

Carregador getCarrDireitaDisparador(Disparador d){
    DISPARADORD* di = (DISPARADORD*) d;
    return di->caDireito;
}

void *getFormaArmadaDisparador(Disparador d){
    DISPARADORD* di = (DISPARADORD*) d;
    return di->formaDisparo;
}