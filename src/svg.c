#include <stdio.h>
#include <stdlib.h>
#include "svg.h"

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
    fprintf(arqSVG, "\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\" />\n",
            getXCirculo(c),
            getYCirculo(c),
            getRCirculo(c),
            getCorBCirculo(c),
            getCorPCirculo(c));
}

void desenhaRetanguloSVG(FILE* arqSVG, Retangulo r){
    if (arqSVG == NULL || r == NULL){
        return;
    }
    fprintf(arqSVG, "\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" stroke=\"%s\" fill=\"%s\" />\n",
            getXRetangulo(r),
            getYRetangulo(r),
            getWRetangulo(r),
            getHRetangulo(r),
            getCorBRetangulo(r),
            getCorPRetangulo(r));
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
    char ancoraC = getAncoraTexto(t);
    if(ancoraC == 'i'){
        ancoraTXT = "start";
    } else if(ancoraC == 'm'){
        ancoraTXT = "middle";
    } else{
        ancoraTXT = "end";
    }
    fprintf(arqSVG, "\t<text x=\"%f\" y=\"%f\" stroke=\"%s\" fill=\"%s\" text-anchor=\"%s\" font-family=\"%s\" font-weight=\"%s\" font-size=\"%s\">%s</text>\n",
            getXTexto(t),
            getYTexto(t),
            getCorBTexto(t),
            getCorPTexto(t),
            ancoraTXT,
            getFonteFamilyTexto(t),
            getFonteWeightTexto(t),
            getFonteSizeTexto(t),
            getTexto_Texto(t));
}

void svgDesenhaAsterisco(FILE* arqSvg, double x, double y){
        if (arqSvg == NULL){
            return;
        }
    fprintf(arqSvg, "\t<text x=\"%f\" y=\"%f\" fill=\"red\" font-size=\"20px\" text-anchor=\"middle\" dy=\".3em\">*</text>\n", x, y);
}

void svgDesenhaBordaTracejada(FILE* arqSVG, double x, double y, double w, double h, char* cor) {
    if (arqSVG == NULL) {
        return;
    }    
    fprintf(arqSvg, "\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:none; stroke:%s; stroke-width:2; stroke-dasharray:5,5;\" />\n",
            x, y, w, h, cor);
}