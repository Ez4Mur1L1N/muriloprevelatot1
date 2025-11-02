#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <stdbool.h>
#include "colisao.h"

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

#define TOLERANCIA 1e-9

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