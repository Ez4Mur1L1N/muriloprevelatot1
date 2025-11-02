#ifndef COLISAO_H
#define COLISAO_H

#include <stdbool.h>
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

/*
 Módulo específico para tratar as sobreposições. Detectando-as e encaminhando suas respectivas respostas. 
*/

/**
 * @brief Função que verifica se um círculo se sobrepõe (geometricamente) a outro círculo.
 * 
 * @param c1 Ponteiro para a primeira forma.
 * @param c2 Ponteiro para a segunda forma.
 * 
 * @return true - há sobreposição.
 * @return false - não há sobreposição.
 */
bool circuloSobrepoeCirculo(void *c1_void, void *c2_void);

/**
 * @brief Função que verifica se um retângulo se sobrepõe (geometricamente) a outro retângulo.
 * 
 * @param r1 Ponteiro para a primeira forma.
 * @param r2 Ponteiro para a segunda forma.
 * 
 * @return true - há sobreposição.
 * @return false - não há sobreposição.
 */
bool retanguloSobrepoeRetangulo(void *r1_void, void *r2_void);

/**
 * @brief Função que verifica se um círculo se sobrepõe (geometricamente) a um retângulo.
 * 
 * @param c Ponteiro para a primeira forma.
 * @param r Ponteiro para a segunda forma.
 * 
 * @return true - há sobreposição.
 * @return false - não há sobreposição.
 */
bool circuloSobrepoeRetangulo(void *c_void, void *r_void);

/**
 * @brief Função que verifica se um círculo se sobrepõe (geometricamente) a uma linha.
 * 
 * @param c Ponteiro para a primeira forma.
 * @param x1 Valores que delimitam uma linha.
 * @param y1 Valores que delimitam uma linha.
 * @param x2 Valores que delimitam uma linha.
 * @param y2 Valores que delimitam uma linha.
 * 
 * @details Deve-se levar em conta que de acordo com a descrição do projeto um texto é tratado como linha
 * na verifição de sobreposição.
 * 
 * @return true - há sobreposição.
 * @return false - não há sobreposição.
 */
bool circuloSobrepoeLinha(void *c_void, double x1, double y1, double x2, double y2);

/**
 * @brief Função que verifica se um retângulo se sobrepõe (geometricamente) a uma linha.
 * 
 * @param r Ponteiro para a primeira forma.
 * @param x1 Valores que delimitam uma linha.
 * @param y1 Valores que delimitam uma linha.
 * @param x2 Valores que delimitam uma linha.
 * @param y2 Valores que delimitam uma linha.
 * 
 * @details Deve-se levar em conta que de acordo com a descrição do projeto um texto é tratado como linha
 * na verifição de sobreposição.
 * 
 * @return true - há sobreposição.
 * @return false - não há sobreposição.
 */
bool retanguloSobrepoeLinha(void *r_void, double x1, double y1, double x2, double y2);

/**
 * @brief Função que verifica se uma linha se sobrepõe (geometricamente) a outra linha.
 * 
 * @param ax1 Valores que delimitam a primeira linha.
 * @param ay1 Valores que delimitam a primeira linha.
 * @param ax2 Valores que delimitam a primeira linha.
 * @param ay2 Valores que delimitam a primeira linha.
 * @param bx1 Valores que delimitam a segunda linha.
 * @param by1 Valores que delimitam a segunda linha.
 * @param bx2 Valores que delimitam a segunda linha.
 * @param by2 Valores que delimitam a segunda linha.
 * 
 * @return true - há sobreposição.
 * @return false - não há sobreposição.
 */
bool linhaSobrepoeLinha(double ax1, double ay1, double ax2, double ay2, double bx1, double by1, double bx2, double by2);

#endif