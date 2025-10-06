#ifndef CARREGADOR_H
#define CARREGADOR_H

#include "pilha.h"

/*
TAD que vai representar os carregadores de formas que municiam os disparadores.
Pensando no projeto e na descrição, um carregador vai atuar como uma pilha (LIFO).
Colocando e retirando elementos do topo.
*/

typedef void* Carregador;

/**
 * @brief Cria um carregador vazio.
 * 
 * @return Ponteiro para o novo carregador. 
 */
Carregador criaCarregador();

/**
 * @brief Libera a memória associada ao carregador e aos elementos contidos nele.
 * 
 * @param Carregador Ponteiro para o carregador analisado.
 *
 * @details Ainda preciso entender como fazer para o programa entender cada forma e cada nó e assim eliminar corretamente.
 */
void destroiCarregador(Carregador c);

/**
 * @brief Função que empilha uma forma geométrica no topo do carregador.
 * 
 * @param Carregador Ponteiro para o carregador analisado.
 * @param Forma Ponteiro genérico para a forma que será colocada.
 */
void pushForma(Carregador c, void *Forma);

/**
 * @brief Função que desempilha uma forma geométrica no topo do carregador.
 * 
 * @param Carregador Ponteiro para o carregador analisado.
 */
void* popForma(Carregador c);

/**
 * @brief Função para 'pegar' (sem tirar do carregador) do topo.
 * 
 * @param Carregador Ponteiro para o carregador analisado.
 * 
 * @return Ponteiro para a forma que está no topo.
 */
void *getForma(Carregador c);

/**
 * @brief Função que vai mostrar se o carregador está vazio ou não.
 * 
 * @param Carregador Ponteiro para o carregador analisado.
 *
 * @return True or false (1) para vazio (0) para algum elemento.
 *
 * @details Só nãpo usei bool para não ter que usar a biblioteca.
 */
int carregadorVazio(Carregador c);

#endif