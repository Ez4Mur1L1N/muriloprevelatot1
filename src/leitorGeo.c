#include <stdio.h>
#include <stdlib.h>
#include "leitorGeo.h"

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

ListaFormas lerArqGeo(char *caminhoAqrGeo) {
    FILE* arqGeo = fopen(caminhoAqrGeo, "r"); // Como indicado, só vamos ler!! esse arquivo.
    if (arqGeo == NULL) {
        printf("Erro ao abrir o arquivo .geo em: %s  !! Programa encerrado.", caminhoAqrGeo);
        exit(1);
    }

    Lista formas = criarLista(); // Usando nosso TAD Lista

    char linha[512];
    int id;
    double x, y, r, w, h, x2, y2;
    char corB[32], corP[32], ancora, texto[256], fFamily[64], fWeight[32], fSize[16];

    while (fgets(linha, sizeof(linha), arqGeo)) {
        linha[strcspn(linha, "\n")] = 0;
        char comando = linha[0];
        
        switch (comando) {
            case 'c':
                sscanf(linha, "c %d %lf %lf %lf %s %s", &id, &x, &y, &r, corB, corP);
                insereFinalLista(formas, criarCirculo(id, x, y, r, corB, corP));
                break;
            case 'r':
                sscanf(linha, "r %d %lf %lf %lf %lf %s %s", &id, &x, &y, &w, &h, corB, corP);
                insereFinalLista(formas, criarRetangulo(id, x, y, w, h, corB, corP));
                break;
            case 'l':
                sscanf(linha, "l %d %lf %lf %lf %lf %s", &id, &x, &y, &x2, &y2, corB);
                insereFinalLista(formas, criarLinha(id, x, y, x2, y2, corB));
                break;
            case 't':
                sscanf(linha, "t %d %lf %lf %s %s %c %s %s %s %[^\n]", &id, &x, &y, corB, corP, &ancora, fFamily, fWeight, fSize, texto);
                insereFinalLista(formas, criarTexto(id, x, y, corB, corP, ancora, texto, fFamily, fWeight, fSize));
                break;
        }
    }

    fclose(arqGeo);
    return (ListaFormas) formas; // Faz o cast para o seu tipo
}

void destroiListaFormasGeo(ListaFormas lst) {
    //Para não dar vazamento ou acesso indevido de memória, farei essa iteração no main!.
    Lista lista = (Lista) lst;
    destroiLista(lista, NULL); // Passa NULL para não tentar destruir o conteúdo aqui.
}