#ifndef SVG_H
#define SVG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circulo.h"
#include "linha.h"
#include "retangulo.h"
#include "texto.h"
#include "arena.h"
#include "disparador.h"
#include "lista.h"

/*
TAD que será utilizado para descrever as funcionalidades para a criação de um arquivo SVG.
Elucidando as formas expostas na descrição do projeto através de uma representação gráfica.
*/

/**
 * @brief Função que estabelece a tag SVG e determina o tamanho.
 * 
 * @param arqSVG Ponteiro para o arquivo SVG aberto.
 */
void abreSVG(FILE* arqSVG);

/**
 * @brief Função que estabelece a tag SVG de fechamento.
 * 
 * @param arqSVG Ponteiro para o arquivo SVG aberto.
 */
void fechaSVG(FILE* arqSVG);

/**
 * @brief Função que desenha um círculo no arquivo SVG.
 * 
 * @param arqSVG Ponteiro para o arquivo SVG aberto.
 * @param Circulo O círculo que, factualmente, será desenhado.
 *
 * @details Usará as funções GETs do círculo para pegar as informações.
 */
void desenhaCirculoSVG(FILE* arqSVG, Circulo c);

/**
 * @brief Função que desenha uma linha no arquivo SVG.
 * 
 * @param arqSVG Ponteiro para o arquivo SVG aberto.
 * @param Linha A linha que, factualmente, será desenhada.
 *
 * @details Usará as funções GETs da linha para pegar as informações.
 */
void desenhaLinhaSVG(FILE* arqSVG, Linha l);

/**
 * @brief Função que desenha um retângulo no arquivo SVG.
 * 
 * @param arqSVG Ponteiro para o arquivo SVG aberto.
 * @param Retangulo O retângulo que, factualmente, será desenhado.
 *
 * @details Usará as funções GETs do retângulo para pegar as informações.
 */
void desenhaRetanguloSVG(FILE* arqSVG, Retangulo r);

/**
 * @brief Função que desenha um texto no arquivo SVG.
 * 
 * @param arqSVG Ponteiro para o arquivo SVG aberto.
 * @param Texto O texto que, factualmente, será desenhado.
 *
 * @details Usará as funções GETs do texto para pegar as informações.
 */
void desenhaTextoSVG(FILE* arqSVG, Texto t);

/**
 * @brief Desenha um asterisco vermelho no local da forma esmagada.
 *
 * @param arqSVG Ponteiro para o arquivo SVG aberto.
 * @param x A coordenada X do centro do asterisco.
 * @param y A coordenada Y do centro do asterisco.
 */
void svgDesenhaAsterisco(FILE* arqSvg, double x, double y);

/**
 * @brief Desenha um retângulo tracejado que auxiliará na visualização de formas sobrepostas.
 * 
 * @param arqSVG Ponteiro para o arquivo SVG aberto.
 * @param x Indica a coordenada X (plano cartesiano) do canto inferior esquerdo do retângulo. 
 * @param y Indica a coordenada Y (plano cartesiano) do canto inferior esquerdo do retângulo. 
 * @param w Indica a largura do retângulo.
 * @param h Indica a altura do retângulo.
 * @param cor Indica a cor do contorno.
 */
void svgDesenhaBordaTracejada(FILE* arqSVG, double x, double y, double w, double h, char *cor);

/**
 * @brief Gera um SVG completo do estado da simulação até determinado, incluindo anotações.
 * 
 * @param caminhoSvg O nome completo do arquivo SVG a ser criado (ex: "saida/t1-t1-1.svg").
 * @param chao A lista de formas que estão no "chão".
 * @param arena A arena (fila) de formas.
 * @param disparadores O array de todos os disparadores.
 * @param maxDisparadores O tamanho do array (ex: MAX_ARSENAL).
 * @param formaDisparada A forma específica que foi disparada (para destacar).
 * @param x1 Ponto de origem "x" da anotação (posição do disparador).
 * @param y1 Ponto de origem "y" da anotação (posição do disparador).
 * @param x2 Ponto de destino "x" da anotação (posição final da forma).
 * @param y2 Ponto de destino "y" da anotação (posição final da forma).
 */
void geraSvgConsulta(const char* caminhoSvg, Lista chao, Arena arena, Disparador* disparadores, int maxDisparadores,void* formaDisparada, double x1, double y1, double x2, double y2);

#endif