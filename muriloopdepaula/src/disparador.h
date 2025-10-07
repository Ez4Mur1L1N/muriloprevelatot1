#ifndef DISPARADOR_H
#define DISPARADOR_H

#include "carregador.h"

/*
TAD que representa um disparador de formas.
Um disparador tem um identificador, uma posição (x, y), é municiado por dois carregadores
e possui uma forma que está na posição para disparo (tem um botão para essa ação).
*/

typedef void* Disparador;

/**
 * @brief Função que cria um disparador, o qual é municiado por dois carregadores.
 * 
 * @param id Identificador do disparador.
 * @param x Coordenada 'X' da posição do disparador.
 * @param y Coordenada 'Y' da posição do disparador.
 *
 * @return Um ponteiro para o disparador.
 */
Disparador criarDisparador(int id, double x, double y);

/**
 * @brief Função que libera memória associada ao disparador e aos seus elementos.
 * 
 * @param Disparador Ponteiro do disparador analisado.
 */
void destroiDisparador(Disparador d);

/**
 * @brief Função que 'pega' o ID do disparador.
 * 
 * @param Disparador Ponteiro do disparador analisado.
 *
 * @return Um inteiro que representa o identificador do disparador.
 */
int getIdDisparador(Disparador d);

/**
 * @brief Função que 'pega' a coordenada 'X' da posição do disparador.
 * 
 * @param Disparador Ponteiro do disparador analisado.
 *
 * @return Um double que representa a coordenada 'X' da posição do disparador.
 */
double getXDisparador(Disparador d);

/**
 * @brief Função que 'pega' a coordenada 'Y' da posição do disparador.
 * 
 * @param Disparador Ponteiro do disparador analisado.
 *
 * @return Um double que representa a coordenada 'Y' da posição do disparador.
 */
double getYDisparador(Disparador d);

/**
 * @brief Função que 'pega' o ponteiro do carregador esquerdo do disparador.
 * 
 * @param Disparador Ponteiro do disparador analisado. 
 *
 * @return Um ponteiro para o carregador esquerdo. 
 */
Carregador getCarrEsquerdaDisparador(Disparador d);

/**
 * @brief Função que 'pega' o ponteiro do carregador direito do disparador.
 * 
 * @param Disparador Ponteiro do disparador analisado. 
 *
 * @return Um ponteiro para o carregador direito. 
 */
Carregador getCarrDireitaDisparador(Disparador d);

/**
 * @brief Função que 'pega' a forma que está na posição de disparo.
 * 
 * @param Disparador Ponteiro do disparador analisado.
 *
 * @return Um ponteiro para a forma.
 *
 * @details Caso não tenha nada, retorna NULL.
 */
void *getFormaArmadaDisparador(Disparador d);

/**
 * @brief Função que muda a posição do disparador.
 * 
 * @param Disparador Ponteiro do disparador analisado.
 * @param xNovo Novo valor para coordenada 'X'.
 * @param yNovo Novo valor para coordenada 'Y'.
 */
void moveDisparador(Disparador d, double xNovo, double yNovo);

/**
 * @brief Função que pega o elemento do topo do carregador e municia o disparador.
 * 
 * @param Disparador Ponteiro do disparador analisado.
 * @param carregador Char para indicar qual carregador (esquerda ou direita - e ou d).
 *
 * @return Ponteiro para a forma selecionada na posição de disparo.
 *
 * @details Caso já exista uma forma na posição de disparo nada ocorre.
 */
void *armarDisparador(Disparador d, char carregador);

/**
 * @brief Função que realiza o disparo
 * 
 * @param Disparador Ponteiro do disparador analisado.
 *
 * @return Ponteiro da forma disparada a fim de posicionar o elemento na arena
 */
void *disparar(Disparador d);

#endif