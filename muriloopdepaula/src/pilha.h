#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
No contexto do projeto, a Pilha é a estrutura de dados
utilizada para implementar os Carregadores de Formas dos Disparadores.
A sua natureza LIFO(último a entrar é o primeiro a sair) modela perfeitamente a ação de colocar e remover
formas do "topo" do carregador.

O TAD Carregador utilizará esta Pilha como sua estrutura de dados principal.
*/

typedef void* PILHA;
typedef void* Forma;

/**
 * @brief Cria uma nova pilha vazia.
 * 
 * @return Retorna um ponteiro para pilha criada.
 *
 * @details Aloca dinamicamente memória para a pilha, atribuindo ponteiro 
 * para o fim da Fila.
 *
 * @warning Caso a alocacao de memoria dê errado, encerra o programa.
 */
PILHA criarPilha();

/**
 * @brief Insere um elemento no topo da pilha (empilha).
 * 
 * @param PILHA ponteiro que indica em qual pilha será inserido o elemento.
 *
 * @param Forma Indica qual forma geometrica será inserida.
 *
 * @details Função criada para a inserção, dinâmica, de um elemento.
 * Essa função cria um novo nó no final da pilha e insere a forma lá.
 * O novo nó passa a apontar para o topo 'antigo'.
 *
 * @warning Caso a alocacao de memoria dê errado, encerra o programa.
 */
void push(PILHA p, Forma g);

/**
 * @brief Remove um elemento do topo da pilha (desempilha).
 *
 * @param PILHA Ponteiro que indica em qual pilha o elemento será retirado.
 * 
 * @details Remove o elemento do topo da pilha, liberando a memória e reajustando os ponteiros.
 * 
 * @warning Fecha o programa caso a fila esteja vazia.
 */
void pop(PILHA p);

/**
 * @brief 'Pega' o primeiro elemento da pilha sem tirá-lo.
 *
 * @param PILHA Ponteiro que indica em qual pilha o elemento será obtido.
 * 
 * @return Retonar um ponteiro para o elemento do topo da pilha.
 *
 * @warning Retorna um ponteiro NULL caso pilha vazia.
 */
Form getTopo(PILHA p);

/**
 * @brief Libera memória da pilha e de seus nós (elementos).
 *
 * @param PILHA O ponteiro para a pilha a ser destruída.
 *
 * @details Percorre cada nó e vai desalocando memória (free).
 * Por fim, reajusta os ponteiros inicio e final para NULL.
 */
void apagaPilha(PILHA p);

#endif