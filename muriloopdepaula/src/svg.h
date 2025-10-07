#ifndef SVG_H
#define SVG_H

#include <stdio.h>
#include <stdlib.h>
#include "circulo.h"
#include "linha.h"
#include "retangulo.h"
#include "texto.h"

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
 * @param arqSvg Ponteiro para o arquivo SVG aberto.
 * @param x A coordenada X do centro do asterisco.
 * @param y A coordenada Y do centro do asterisco.
 */
void svgDesenhaAsterisco(FILE* arqSvg, double x, double y);


#endif