#include <stdio.h>
#include <stdlib.h>
#include "svg.h"
#include "lista.h"
#include "arena.h"
#include "disparador.h"
#include "processaFormas.h"

#define OPACIDADE 0.7

void abreSVG(FILE* arqSVG){
    if(arqSVG == NULL){
        return;
    }
    fprintf(arqSVG, "<svg width=\"1000\" height=\"1000\" xmlns=\"http://www.w3.org/2000/svg\">\n");
}

void fechaSVG(FILE* arqSVG){
    if(arqSVG == NULL){
        return; //Para caso esse arquivo não exista ou não foi aberto (fopen).
    }
    fprintf(arqSVG, "</svg>\n");
}

void desenhaCirculoSVG(FILE* arqSVG, Circulo c){
    if(arqSVG == NULL || c == NULL){
        return;
    }
    fprintf(arqSVG, "\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"%.1f\" />\n",
            getXCirculo(c),
            getYCirculo(c),
            getRCirculo(c),
            getCorBCirculo(c),
            getCorPCirculo(c),
            OPACIDADE);
}

void desenhaRetanguloSVG(FILE* arqSVG, Retangulo r){
    if (arqSVG == NULL || r == NULL){
        return;
    }
    fprintf(arqSVG, "\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"%.1f\" />\n",
            getXRetangulo(r),
            getYRetangulo(r),
            getWRetangulo(r),
            getHRetangulo(r),
            getCorBRetangulo(r),
            getCorPRetangulo(r),
            OPACIDADE);
}

void desenhaLinhaSVG(FILE* arqSVG, Linha l){
    if(arqSVG == NULL || l == NULL){
        return;
    }
    fprintf(arqSVG, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" />\n",
            getX1Linha(l),
            getY1Linha(l),
            getX2Linha(l),
            getY2Linha(l),
            getCorLinha(l));
}

void desenhaTextoSVG(FILE* arqSVG, Texto t){
    if(arqSVG == NULL || t == NULL){
        return;
    }
    // Transformar a ancora para o jeito que o SVG entende
    char *ancoraTXT;
    char* ancoraStr = getAncoraTexto(t); // Agora retorna "i", "m", ou "f"
    if (strcmp(ancoraStr, "i") == 0) {
        ancoraTXT = "start";
    } else if (strcmp(ancoraStr, "m") == 0) {
        ancoraTXT = "middle";
    } else {
        ancoraTXT = "end";
    }
    fprintf(arqSVG, "\t<text x=\"%f\" y=\"%f\" stroke=\"%s\" fill=\"%s\" text-anchor=\"%s\" font-family=\"%s\" font-weight=\"%s\" font-size=\"%s\" fill-opacity=\"%.1f\">%s</text>\n", // <-- ESPAÇO REMOVIDO AQUI
            getXTexto(t),
            getYTexto(t),
            getCorBTexto(t),
            getCorPTexto(t),
            ancoraTXT,
            getFonteFamilyTexto(t),
            getFonteWeightTexto(t),
            getFonteSizeTexto(t),
            OPACIDADE,
            getTexto_Texto(t));
}

void svgDesenhaAsterisco(FILE* arqSVG, double x, double y){
        if (arqSVG == NULL){
            return;
        }
    fprintf(arqSVG, "\t<text x=\"%f\" y=\"%f\" fill=\"red\" font-size=\"20px\" text-anchor=\"middle\" dy=\".3em\">*</text>\n", x, y);
}

void svgDesenhaBordaTracejada(FILE* arqSVG, double x, double y, double w, double h, char* cor) {
    if (arqSVG == NULL) {
        return;
    }    
    fprintf(arqSVG, "\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:none; stroke:%s; stroke-width:2; stroke-dasharray:5,5;\" />\n",
            x, y, w, h, cor);
}

void geraSvgConsulta(const char* caminhoSvg, Lista chao, Arena arena, Disparador* disparadores, int maxDisparadores,void* formaDisparada, double x1, double y1, double x2, double y2){
    FILE* arqSvg = fopen(caminhoSvg, "w");
    if (arqSvg == NULL) {
        printf("Nao foi possivel criar o arquivo SVG da consulta em %s\n", caminhoSvg);
        return;
    }

    abreSVG(arqSvg); 

    // Inicialmente desenhamos todas as formas incluídas no chão.
    for (No no = getPrimeiroNoLista(chao); no != NULL; no = getProximoNoLista(no)) {
        Conteudo forma = getConteudoNoLista(no);
        TipoForma tipo = getTipoFormaGenerica(forma); // (Função do leitorQry)!

        switch (tipo) {
            case CIRCULO:   desenhaCirculoSVG(arqSvg, forma);   break;
            case RETANGULO: desenhaRetanguloSVG(arqSvg, forma); break;
            case LINHA:     desenhaLinhaSVG(arqSvg, forma);     break;
            case TEXTO:     desenhaTextoSVG(arqSvg, forma);     break;
        }
    }

    // Depois todas as formas na "Arena" (que é uma Fila).
    // Para isso vamos "tirar" todos os itens da arena e depois "devolve-los".
    Lista listaTempArena = criarLista();
    while (arenaVazia(arena) == 0) {
        insereFinalLista(listaTempArena, removeFormaArena(arena));
    }

    // Agora desenhamos a partir dessa lista temporária.
    for (No no = getPrimeiroNoLista(listaTempArena); no != NULL; no = getProximoNoLista(no)) {
        Conteudo forma = getConteudoNoLista(no);
        TipoForma tipo = getTipoFormaGenerica(forma);
        
        switch (tipo) {
            case CIRCULO:   desenhaCirculoSVG(arqSvg, forma);   break;
            case RETANGULO: desenhaRetanguloSVG(arqSvg, forma); break;
            case LINHA:     desenhaLinhaSVG(arqSvg, forma);     break;
            case TEXTO:     desenhaTextoSVG(arqSvg, forma);     break;
        }
    }
    
    // Reposicionando os elementos na fila da arena.
    while (getTamanhoLista(listaTempArena) > 0) {
        inserirFormaArena(arena, removeNoLista(listaTempArena, getPrimeiroNoLista(listaTempArena)));
    }
    destroiLista(listaTempArena, NULL); // Destrói só a lista, não as formas.

    // Desenho dos disparadores.
    for (int i = 0; i < maxDisparadores; i++) {
        if (disparadores[i] != NULL) {
            // Desenha um asterisco vermelho para marcar o disparador
            svgDesenhaAsterisco(arqSvg, getXDisparador(disparadores[i]), getYDisparador(disparadores[i]));
        }
    }

    // Desenho das anotações do Disparo
    if (formaDisparada != NULL) {
        // Desenha a linha de deslocamento tracejada (conforme anotação do prof).
        fprintf(arqSvg, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"red\" stroke-dasharray=\"5,5\" />\n", x1, y1, x2, y2);
        
        // Desenha um retângulo tracejado ao redor da forma que aterrissou.
        double RetX, RetY, RetW, RetH;
        getRetanguloDelimitadorGenerica(formaDisparada, &RetX, &RetY, &RetW, &RetH);

        // Chama a função que você já tem para desenhar a borda.
        svgDesenhaBordaTracejada(arqSvg, RetX, RetY, RetW, RetH, "red");
    }

    fechaSVG(arqSvg);
    fclose(arqSvg);
}