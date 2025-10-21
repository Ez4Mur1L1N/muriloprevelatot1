#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>  
#include "processaFormas.h"

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


// Sobreposições!!!!
// Função auxiliar. Para ajudar no caso de círculo sobrepõe um retângulo.
double aux(double valor, double min, double max) {
    if (valor < min) return min;
    if (valor > max) return max;
    return valor;
}

// Verifica sobreposição Círculo-Círculo.
bool circuloSobrepoeCirculo(void* c1_void, void* c2_void) {
    Circulo c1 = (Circulo) c1_void;
    Circulo c2 = (Circulo) c2_void;
    double x1 = getXCirculo(c1), y1 = getYCirculo(c1), r1 = getRCirculo(c1);
    double x2 = getXCirculo(c2), y2 = getYCirculo(c2), r2 = getRCirculo(c2);
    double distCentroQuadrado = pow(x2 - x1, 2) + pow(y2 - y1, 2);
    double somaRQuadrado = pow(r1 + r2, 2);
    return distCentroQuadrado <= somaRQuadrado;
}

// Verifica sobreposição Retângulo-Retângulo.
bool retanguloSobrepoeRetangulo(void* r1_void, void* r2_void) {
    Retangulo r1 = (Retangulo) r1_void;
    Retangulo r2 = (Retangulo) r2_void;
    double x1 = getXRetangulo(r1), y1 = getYRetangulo(r1), w1 = getWRetangulo(r1), h1 = getHRetangulo(r1);
    double x2 = getXRetangulo(r2), y2 = getYRetangulo(r2), w2 = getWRetangulo(r2), h2 = getHRetangulo(r2);

    /*  Verifica se NÃO há sobreposição (mais fácil).
        Se r1 está totalmente à esquerda de r2 OU
        Se r1 está totalmente à direita de r2 OU
        Se r1 está totalmente abaixo de r2 OU
        Se r1 está totalmente acima de r2
    */
    if (x1 + w1 < x2 || x1 > x2 + w2 || y1 + h1 < y2 || y1 > y2 + h2) {
        return false; // Não há sobreposição.
    }
    return true;
}

// Verifica sobreposição Círculo-Retângulo.
bool circuloSobrepoeRetangulo(void* c_void, void* r_void) {
    Circulo c = (Circulo) c_void;
    Retangulo r = (Retangulo) r_void;
    double cx = getXCirculo(c), cy = getYCirculo(c), cr = getRCirculo(c);
    double rx = getXRetangulo(r), ry = getYRetangulo(r), rw = getWRetangulo(r), rh = getHRetangulo(r);

    // Encontra o ponto mais próximo no retângulo ao centro do círculo.
    double closestX = aux(cx, rx, rx + rw);
    double closestY = aux(cy, ry, ry + rh);

    // Calcula a distância ao quadrado entre o centro do círculo e esse ponto.
    double distX = cx - closestX;
    double distY = cy - closestY;
    double distQuadrado = (distX * distX) + (distY * distY);

    // Se a distância² < raio², então há sobreposição.
    // <= (Se for igual só toca, não considero sobreposição então só deixarei <).
    return distQuadrado < (cr * cr);
}

// Verifica se um ponto está dentro de um retângulo  (linha-retângulo).
bool pontoInternoRetangulo(double px, double py, void* r_void) {
    Retangulo r = (Retangulo) r_void;
    double rx = getXRetangulo(r), ry = getYRetangulo(r), rw = getWRetangulo(r), rh = getHRetangulo(r);
    return (px >= rx && px <= rx + rw && py >= ry && py <= ry + rh);
}

// Verifica sobreposição Círculo-Linha (peguei uma análise da internet para entender o caso em que as extremidades da linha não estão no círculo!).
bool circuloSobrepoeLinha(void* c_void, double x1, double y1, double x2, double y2) {
    Circulo c = (Circulo) c_void;

    double cx = getXCirculo(c);
    double cy = getYCirculo(c);
    double cr = getRCirculo(c);
    double crQuadrado = cr * cr; 

    // Calcular o vetor do segmento de linha e seu comprimento ao quadrado.
    double dx = x2 - x1;
    double dy = y2 - y1;
    double vetorQuadrado = dx*dx + dy*dy;

    // Lidar com o caso de segmento de linha ser apenas um ponto (comprimento zero).
    if (vetorQuadrado < 0.000001) { // Usar uma pequena tolerância para ponto flutuante.
        double distQuadPonto = pow(x1 - cx, 2) + pow(y1 - cy, 2);
        return distQuadPonto <= crQuadrado;
    }

    // Calcular o parâmetro 't' que representa a projeção do centro do círculo
    // na linha infinita que contém o segmento.
    double t = ((cx - x1) * dx + (cy - y1) * dy) / vetorQuadrado;

    // Usar a função aux para restringir 't' ao intervalo [0, 1].
    double t_aux = aux(t, 0.0, 1.0);

    // Calcular as coordenadas (closestX, closestY) do ponto mais próximo no segmento.
    double closestX = x1 + t_aux * dx;
    double closestY = y1 + t_aux * dy;

    // Calcular a distância ao quadrado entre o centro do círculo e o ponto mais próximo.
    double distQuadCentroPonto = pow(closestX - cx, 2) + pow(closestY - cy, 2);

    // Verificar se a distância ao quadrado é menor ou igual ao raio ao quadrado.
    return distQuadCentroPonto <= crQuadrado;
}

// Função auxiliar para o retângulo sobrepõe linha. (novamente peguei da internet para entender o caso em que as extremidades da linha não estão dentro da forma).
bool clipParametroT(double numerador, double denominador, double* tEntrada, double* tSaida) {
    const double epsilon = 1e-9; 

    if (fabs(denominador) < epsilon) {
        return !(numerador < 0);
    }

    double t = numerador / denominador;

    if (denominador > 0) { 
        if (t > *tSaida) return false; 
        if (t > *tEntrada) *tEntrada = t; 
    } else { 
        if (t < *tEntrada) return false;
        if (t < *tSaida) *tSaida = t;   
    }
    return true; 
}

// Verifica sobreposição Retângulo-linha.
bool retanguloSobrepoeLinha(void* r_void, double x1, double y1, double x2, double y2) {
    Retangulo r = (Retangulo) r_void;
    if (r == NULL) return false;

    // Coordenadas do retângulo.
    double rx = getXRetangulo(r);
    double ry = getYRetangulo(r);
    double rw = getWRetangulo(r);
    double rh = getHRetangulo(r);
    double rxMax = rx + rw;
    double ryMax = ry + rh;

    // Se um ponto final já está dentro, há colisão.
    if (pontoInternoRetangulo(x1, y1, r_void) || pontoInternoRetangulo(x2, y2, r_void)) {
        return true;
    }

    // Caso especial
    // Vetor da linha P(t) = P1 + t * V, onde V = P2 - P1, t em [0, 1].
    double dx = x2 - x1;
    double dy = y2 - y1;

    double tEntrada = 0.0;
    double tSaida = 1.0;

    //    Recorte contra a borda ESQUERDA (x >= rx).
    //    Equivalente a testar t*(-dx) <= x1 - rx.
    if (!clipParametroT(x1 - rx, -dx, &tEntrada, &tSaida)) {
        return false; // Totalmente fora ou intervalo inválido.
    }

    //    Recorte contra a borda DIREITA (x <= rxMax).
    //    Equivalente a testar t*(dx) <= rxMax - x1.
    if (!clipParametroT(rxMax - x1, dx, &tEntrada, &tSaida)) {
        return false;
    }

    //    Recorte contra a borda INFERIOR (y >= ry).
    //    Equivalente a testar t*(-dy) <= y1 - ry.
    if (!clipParametroT(y1 - ry, -dy, &tEntrada, &tSaida)) {
        return false;
    }

    //    Recorte contra a borda SUPERIOR (y <= ryMax).
    //    Equivalente a testar t*(dy) <= ryMax - y1.
    if (!clipParametroT(ryMax - y1, dy, &tEntrada, &tSaida)) {
        return false;
    }

    // Se passou por todos os testes, então o segmento cruza o retângulo
    return true;
}

// Agora vamos definir funções auxiliares para o caso linha-linha (texto também);

// Estrutura auxiliar para representar um ponto 2D
typedef struct { 
    double x, y; 
} Ponto2D;

// Função auxiliar: Calcula a orientação de 3 pontos (p, q, r)
// Retorna:
//   0 --> p, q, r são colineares
//   1 --> Sentido horário
//   2 --> Sentido anti-horário
int orientacao(Ponto2D p, Ponto2D q, Ponto2D r) {
    // Usa o produto vetorial (cross product) dos vetores (q-p) e (r-q)
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (fabs(val) < TOLERANCIA) return 0; // Colinear (usando tolerância)
    return (val > 0) ? 1 : 2; // Horário ou Anti-horário
}

// Função auxiliar: Verifica se o ponto q está no segmento pr (quando p, q, r são colineares)
bool pontoNoSegmento(Ponto2D p, Ponto2D q, Ponto2D r) {
    return (q.x <= fmax(p.x, r.x) && q.x >= fmin(p.x, r.x) &&
            q.y <= fmax(p.y, r.y) && q.y >= fmin(p.y, r.y));
}

bool retangulosDelimitadoresSobrepoem(double minAx, double minAy, double maxAx, double maxAy, double minBx, double minBy, double maxBx, double maxBy) {
    bool separado = (maxAx < minBx) || (minAx > maxBx) || (maxAy < minBy) || (minAy > maxBy);
    return !separado;
}

// Verifica sobreposição linha-linha (peguei essa análise da internet e o que foi falado em sala pelo professor!).
bool linhaSobrepoeLinha(double ax1, double ay1, double ax2, double ay2, double bx1, double by1, double bx2, double by2){

    double minAx = fmin(ax1, ax2);
    double minAy = fmin(ay1, ay2);
    double maxAx = fmax(ax1, ax2);
    double maxAy = fmax(ay1, ay2);

    double minBx = fmin(bx1, bx2);
    double minBy = fmin(by1, by2);
    double maxBx = fmax(bx1, bx2);
    double maxBy = fmax(by1, by2);


    if (!retangulosDelimitadoresSobrepoem(minAx, minAy, maxAx, maxAy, minBx, minBy, maxBx, maxBy)) {
        // Se as caixas não se sobrepõem, as linhas certamente não se sobrepõem.
        return false;
    }

    Ponto2D a1 = {ax1, ay1};
    Ponto2D a2 = {ax2, ay2};
    Ponto2D b1 = {bx1, by1};
    Ponto2D b2 = {bx2, by2};

    int o1 = orientacao(a1, a2, b1);
    int o2 = orientacao(a1, a2, b2);
    int o3 = orientacao(b1, b2, a1);
    int o4 = orientacao(b1, b2, a2);

    // Caso Geral
    if (o1 != 0 && o2 != 0 && o3 != 0 && o4 != 0 && o1 != o2 && o3 != o4) {
        return true;
    }

    // Casos Especiais (Colineares)
    if (o1 == 0 && pontoNoSegmento(a1, b1, a2)) return true;
    if (o2 == 0 && pontoNoSegmento(a1, b2, a2)) return true;
    if (o3 == 0 && pontoNoSegmento(b1, a1, b2)) return true;
    if (o4 == 0 && pontoNoSegmento(b1, a2, b2)) return true;

    return false;
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
            char ancora = getAncoraTexto(formaI);
            double xAncora = getXTexto(formaI);

            if (ancora == 'i') { // Início
                Ix1 = xAncora;
                Ix2 = xAncora + larguraTexto;
            } else if (ancora == 'm') { // Meio
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
            char ancora = getAncoraTexto(formaJ);
            double xAncora = getXTexto(formaJ);

            if (ancora == 'i') {
                Jx1 = xAncora;
                Jx2 = xAncora + larguraTexto;
            } else if (ancora == 'm') {
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