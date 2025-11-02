#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>  
#include "processaFormas.h"
#include "colisao.h"

#define TOLERANCIA 1e-9

TipoForma getTipoFormaGenerica(void* forma) {
    if (forma == NULL) {
        return -1;
    }
    // Por padrão de construção temos que o tipo será o segundo [1] valor, sendo o identificador (id) o primeiro[0]. 
    return ((int*)forma)[1];
}

int getIdFormaGenerica(void* forma) {
    if (forma == NULL) {
        return -1;
    }
    // O ID é o primeiro campo (int) da struct.
    return ((int*)forma)[0];
}

void destroiFormaGenerica(void* forma) {
    if (forma == NULL) {
        return;
    }

    TipoForma tipo = getTipoFormaGenerica(forma);
    switch (tipo) {
        case CIRCULO:   destroiCirculo(forma);   break;
        case RETANGULO: destroiRetangulo(forma); break;
        case LINHA:     destroiLinha(forma);     break;
        case TEXTO:     destroiTexto(forma);     break;
    }
}

void setPosFormaGenerica(void* forma, double x, double y) {
    if (forma == NULL) return;

    TipoForma tipo = getTipoFormaGenerica(forma);
    switch (tipo) {
        case CIRCULO:
            setXCirculo(forma, x);
            setYCirculo(forma, y);
            break;
        case RETANGULO:
            setXRetangulo(forma, x);
            setYRetangulo(forma, y);
            break;
        case LINHA: {
            // Move a linha inteira, preservando seu comprimento/ângulo
            double deltaX = x - getX1Linha(forma);
            double deltaY = y - getY1Linha(forma);
            setX2Linha(forma, getX2Linha(forma) + deltaX);
            setY2Linha(forma, getY2Linha(forma) + deltaY);
            setX1Linha(forma, x); // Define a nova âncora (x1, y1)
            setY1Linha(forma, y);
            break;
        }
        case TEXTO: {
            setXTexto(forma, x);
            setYTexto(forma, y);
            break;
        }
    }
}

char* getCorPGenerica(void* forma) {
    if (forma == NULL) {
        return ""; // Retorna string vazia para segurança.
    }
    
    TipoForma tipo = getTipoFormaGenerica(forma);
    switch (tipo) {
        case CIRCULO:   return getCorPCirculo(forma);
        case RETANGULO: return getCorPRetangulo(forma);
        case TEXTO:     return getCorPTexto(forma);
        // Linhas não têm cor de preenchimento!!!
        case LINHA:     return ""; 
    }
    return "";
}

void setCorBGenerica(void* forma, char* novaCorB) {
    if (forma == NULL || novaCorB == NULL) {
        return;
    }

    TipoForma tipo = getTipoFormaGenerica(forma);
    switch (tipo) {
        case CIRCULO:   setCorBCirculo(forma, novaCorB);   break;
        case RETANGULO: setCorBRetangulo(forma, novaCorB); break;
        case TEXTO:     setCorBTexto(forma, novaCorB);     break;
        case LINHA:     setCorLinha(forma, novaCorB);      break; // Linha só tem cor de borda (stroke no padrão SVG)!!
    }
}

double calcAreaGenerica(void* forma) {
    if (forma == NULL) return 0.0;
    
    TipoForma tipo = getTipoFormaGenerica(forma);
    switch (tipo) {
        case CIRCULO:
            return calcAreaCirculo(forma);
        case RETANGULO:
            return calcAreaRetangulo(forma);
        case LINHA: {
            // 2.0 * comprimento
            double dx = getX2Linha(forma) - getX1Linha(forma);
            double dy = getY2Linha(forma) - getY1Linha(forma);
            double comprimento = sqrt(dx*dx + dy*dy);
            return 2.0 * comprimento;
        }
        case TEXTO: {
            // 20.0 * num_caracteres
            char* str = getTexto_Texto(forma);
            return 20.0 * strlen(str);
        }
    }
    return 0.0;
}

void getRetanguloDelimitadorGenerica(void* forma, double* x, double* y, double* w, double* h) {
    if (forma == NULL) {
        *x = 0; *y = 0; *w = 0; *h = 0;
        return;
    }
    
    TipoForma tipo = getTipoFormaGenerica(forma);
    switch (tipo) {
        case CIRCULO: {
            double r = getRCirculo(forma);
            *x = getXCirculo(forma) - r;
            *y = getYCirculo(forma) - r;
            *w = 2 * r;
            *h = 2 * r;
            break;
        }
        case RETANGULO: {
            *x = getXRetangulo(forma);
            *y = getYRetangulo(forma);
            *w = getWRetangulo(forma);
            *h = getHRetangulo(forma);
            break;
        }
        case LINHA: {
            double x1 = getX1Linha(forma);
            double y1 = getY1Linha(forma);
            double x2 = getX2Linha(forma);
            double y2 = getY2Linha(forma);
            *x = fmin(x1, x2);
            *y = fmin(y1, y2);
            *w = fabs(x2 - x1);
            *h = fabs(y2 - y1);
            break;
        }
        case TEXTO: {
            *x = getXTexto(forma);
            *y = getYTexto(forma); 
            *w = calcAreaGenerica(forma) / 20.0; 
            *h = 1.0; 
            break;
        }
    }
}

// Variável estática para gerar IDs únicos para os clones.
// Começa em 100 para evitar interferência com IDs do .geo (geralmente bem baixos).
static int proximoIdClone = 100; 

void* clonarFormaGenerica(void* forma) {
    if (forma == NULL) {
        return NULL;
    }

    TipoForma tipo = getTipoFormaGenerica(forma);
    void* clone = NULL;
    int novoId = proximoIdClone++; // Pega o ID atual e incrementa para o próximo clone

    switch (tipo) {
        case CIRCULO:   clone = clonarCirculo(forma, novoId);   break;
        case RETANGULO: clone = clonarRetangulo(forma, novoId); break;
        case LINHA:     clone = clonarLinha(forma, novoId);     break;
        case TEXTO:     clone = clonarTexto(forma, novoId);     break;
    }
    
    return clone;
}

// Função principal e final

bool verificaSobreposicao(void* formaI, void* formaJ) {
    if (formaI == NULL || formaJ == NULL) {
        return false;
    }

    TipoForma tipoI = getTipoFormaGenerica(formaI);
    TipoForma tipoJ = getTipoFormaGenerica(formaJ);

    // Simplifica a lógica tratando Texto como Linha para colisões!!
    TipoForma tipoColisaoI = (tipoI == TEXTO) ? LINHA : tipoI;
    TipoForma tipoColisaoJ = (tipoJ == TEXTO) ? LINHA : tipoJ;

    if (tipoColisaoI == CIRCULO && tipoColisaoJ == CIRCULO) {
        return circuloSobrepoeCirculo(formaI, formaJ);
    }
    else if (tipoColisaoI == RETANGULO && tipoColisaoJ == RETANGULO) {
        return retanguloSobrepoeRetangulo(formaI, formaJ);
    }
    else if (tipoColisaoI == CIRCULO && tipoColisaoJ == RETANGULO) {
        return circuloSobrepoeRetangulo(formaI, formaJ);
    }
    else if (tipoColisaoI == RETANGULO && tipoColisaoJ == CIRCULO) {
        return circuloSobrepoeRetangulo(formaJ, formaI);
    }
    else { // Pelo menos uma das formas é LINHA ou TEXTO

        // Calcula as coordenadas do segmento para Forma I. 
        double Ix1, Iy1, Ix2, Iy2;
        if (tipoI == LINHA) {
            Ix1 = getX1Linha(formaI);
            Iy1 = getY1Linha(formaI);
            Ix2 = getX2Linha(formaI);
            Iy2 = getY2Linha(formaI);
        } else { // tipoI == TEXTO
            Iy1 = getYTexto(formaI);
            Iy2 = Iy1; // Texto é tratado como linha horizontal
            char* textoStr = getTexto_Texto(formaI);
            double larguraTexto = textoStr ? strlen(textoStr) : 0.0; // Largura simplificada (ignora fonte/tamanho)
            char* ancora = getAncoraTexto(formaI);
            double xAncora = getXTexto(formaI);

            if (strcmp(ancora, "i") == 0) { // Início
                Ix1 = xAncora;
                Ix2 = xAncora + larguraTexto;
            } else if (strcmp(ancora, "m") == 0) { // Meio
                Ix1 = xAncora - larguraTexto / 2.0;
                Ix2 = xAncora + larguraTexto / 2.0;
            } else { // Fim ('f' ou 'e')
                Ix1 = xAncora - larguraTexto;
                Ix2 = xAncora;
            }
        }

        // Calcula as coordenadas do segmento para Forma J.
        double Jx1, Jy1, Jx2, Jy2;
        if (tipoJ == LINHA) {
            Jx1 = getX1Linha(formaJ);
            Jy1 = getY1Linha(formaJ);
            Jx2 = getX2Linha(formaJ);
            Jy2 = getY2Linha(formaJ);
        } else { // tipoJ == TEXTO
            Jy1 = getYTexto(formaJ);
            Jy2 = Jy1;
            char* textoStr = getTexto_Texto(formaJ);
            double larguraTexto = textoStr ? strlen(textoStr) : 0.0;
            char* ancora = getAncoraTexto(formaJ);
            double xAncora = getXTexto(formaJ);

            if (strcmp(ancora, "i") == 0) {
                Jx1 = xAncora;
                Jx2 = xAncora + larguraTexto;
            } else if (strcmp(ancora, "m") == 0) {
                Jx1 = xAncora - larguraTexto / 2.0;
                Jx2 = xAncora + larguraTexto / 2.0;
            } else {
                Jx1 = xAncora - larguraTexto;
                Jx2 = xAncora;
            }
        }

        // Chama a função de colisão apropriada com as coordenadas calculadas.
        if (tipoColisaoI == LINHA && tipoColisaoJ == LINHA) {
            return linhaSobrepoeLinha(Ix1, Iy1, Ix2, Iy2, Jx1, Jy1, Jx2, Jy2);
        }
        else if (tipoColisaoI == CIRCULO && tipoColisaoJ == LINHA) {
            return circuloSobrepoeLinha(formaI, Jx1, Jy1, Jx2, Jy2);
        }
        else if (tipoColisaoI == LINHA && tipoColisaoJ == CIRCULO) {
            return circuloSobrepoeLinha(formaJ, Ix1, Iy1, Ix2, Iy2);
        }
         else if (tipoColisaoI == RETANGULO && tipoColisaoJ == LINHA) {
            return retanguloSobrepoeLinha(formaI, Jx1, Jy1, Jx2, Jy2);
        }
         else if (tipoColisaoI == LINHA && tipoColisaoJ == RETANGULO) {
            return retanguloSobrepoeLinha(formaJ, Ix1, Iy1, Ix2, Iy2);
        }
    }

    return false; // Caso não previsto (segurança).
}