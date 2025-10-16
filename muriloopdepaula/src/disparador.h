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
 * @param dx Coordenada 'X' da direção do disparador.
 * @param dy Coordenada 'Y' da direção do disparador.
 *
 * @return Um ponteiro para o disparador.
 *
 * @warning Caso dê erro na alocação de memória, encerra o programa.
 */
Disparador criarDisparador(int id, double x, double y, double dx, double dy);

/**
 * @brief Função que libera memória associada ao disparador e aos seus elementos.
 * 
 * @param Disparador Ponteiro do disparador analisado.
 *
 * @details Dessacocia os dois carregadores, mas NÃO a forma que está no posição de disparo.
 */
void destroiDisparador(Disparador d);

/**
 * @brief Função que encaixa carregadores externos no disparador.
 *
 * @param Disparador Ponteiro do disparador analisado.
 * @param esq O Carregador a ser encaixado na esquerda.
 * @param dir O Carregador a ser encaixado na direita.
 *
 * @details Os carregadores internos originais do disparador são destruídos.
 */
void anexaCarregadoresDisparador(Disparador d, Carregador esq, Carregador dir);

/**
 * @brief Função que vai carregar algum dos disparadores com formas no chão.
 * 
 * @param Disparador Ponteiro do disparador analisado.
 * @param elemento Ponteiro genérico para forma a ser carregada.
 * @param lado Char(e ou d) que indica o lado do disparador. 
 */
void carregaFormaDisparador(Disparador d, void *elemento, char lado);

/**
 * @brief Função que pega o elemento do topo do carregador direito e municia o disparador.
 * 
 * @param Disparador Ponteiro do disparador analisado. 
 *
 * @details Se já houver alguma forma na posição de disparo essa forma vai para o topo do carregador esquerdo.
 */
void selecionaDireitaDisparador(Disparador d);

/**
 * @brief Função que pega o elemento do topo do carregador esquerdo e municia o disparador.
 * 
 * @param Disparador Ponteiro do disparador analisado. 
 *
 * @details Se já houver alguma forma na posição de disparo essa forma vai para o topo do carregador direito.
 */
void selecionaEsquerdaDisparador(Disparador d);

/**
 * @brief Função que vai executar o comando "shft" do .qry, movendo n formas na direção que o arquivo indicar.
 * 
 * @param Disparador Ponteiro do disparador analisado.
 * @param lado A direção para onde as formas serão movidas (e - esquerda d - direita).
 * @param n Quantas formas serão movidas.
 */
void shiftDisparador(Disparador d, char lado, int n);

/**
 * @brief Função que realiza - simula - o disparo.
 * 
 * @param Disparador Ponteiro do disparador analisado.
 *
 * @return Ponteiro da forma disparada a fim de posicionar o elemento na arena. Ele remove essa forma da posição de disparo.
 *
 * @warning Retorna NULL se não havia nada na posição de disparo.
 */
void *disparar(Disparador d);

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

#endif