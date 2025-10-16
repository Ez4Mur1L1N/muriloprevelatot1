#ifndef ARENA_H
#define ARENA_H

#include "fila.h"

/*
TAD que representa a arena do jogo.
Pensando no projeto e na descrição, a arena vai atuar como uma fila (FIFO).
*/

typedef void* Arena;

/**
 * @brief Função que cria uma arena.
 * 
 * @return Ponteiro para a arena criada vazia.
 *
 * @warning Caso dê erro na alocação de memória, encerra o programa. 
 */
Arena criarArena();

/**
 * @brief Função que libera memória da arena.
 * 
 * @param Arena Ponteira para a arena analisada.
 *
 * @details Libera a memórias da fila interna, mas não das formas contidas nela.
 */
void destroiArena(Arena a);

/**
 * @brief Função que insere uma forma na arena.
 * 
 * @param Arena Ponteiro para a arena analisada. 
 * @param Forma Ponteiro (genérico) que indica a forma a ser inserida.
 */
void inserirFormaArena(Arena a, void* Forma);

/**
 * @brief Função que retira as formas do chão da arena na ordem em que foram colocadas.
 * 
 * @param Arena Ponteiro para a arena analisada.
 * 
 * @return Ponteiro para a forma retirada. **MAIS ANTIGA (FIFO).
 *
 * @warning Retorna NULL se a arena estiver vazia.
 */
void *removeFormaArena(Arena a);

/**
 * @brief Função que verifica se a arena está vazia ou não.
 * 
 * @param Arena Ponteiro para a arena analisada.
 *
 * @return True or false (1) para vazio (0) para algum elemento.
 *
 * @details Só nãpo usei bool para não ter que usar a biblioteca.
 */
int arenaVazia(Arena a);

/**
 * @brief Função que retorna a fila de formas da arena.
 * 
 * @param Arena Ponteiro para a arena analisada. 
 *
 * @return Um ponteiro para a fila que contém as formas. 
 */
Fila getFilaArena(Arena a);

#endif