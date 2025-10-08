#ifndef PILHA_H
#define PILHA_H

/*
No contexto do projeto, a Pilha é a estrutura de dados
utilizada para implementar os Carregadores de Formas dos Disparadores.
A sua natureza LIFO(último a entrar é o primeiro a sair) modela perfeitamente a ação de colocar e remover
formas do "topo" do carregador.

O TAD Carregador utilizará esta Pilha como sua estrutura de dados principal.
*/

typedef void* PILHA;

/**
 * @brief Cria uma nova pilha vazia.
 * 
 * @return Retorna um ponteiro para pilha criada.
 *
 * @details Aloca dinamicamente memória para a pilha, atribuindo ponteiro 
 * para o topo da pilha .
 *
 * @warning Caso a alocacao de memoria dê errado, encerra o programa.
 */
PILHA criarPilha();

/**
 * @brief Libera memória da pilha e de seus nós (elementos).
 *
 * @param PILHA O ponteiro para a pilha a ser destruída.
 *
 * @details Percorre cada nó e vai desalocando memória (free).
 * Por fim, reajusta os ponteiros inicio e final para NULL.
 */
void destroiPilha(PILHA p);

/**
 * @brief Função que insere um elemento no topo da pilha (empilha).
 * 
 * @param PILHA Ponteiro que indica em qual pilha será inserido o elemento.
 *
 * @param elemento Ponteiro genérico que ndica qual forma geometrica será inserida.
 *
 * @details Função criada para a inserção, dinâmica, de um elemento.
 * Essa função cria um novo nó no final da pilha e insere a forma lá.
 * O novo nó passa a apontar para o topo 'antigo'.
 *
 * @warning Caso a alocacao de memoria dê errado, encerra o programa.
 */
void push(PILHA p, void *elemento);

/**
 * @brief Função que remove um elemento do topo da pilha (desempilha).
 *
 * @param PILHA Ponteiro que indica em qual pilha o elemento será retirado.
 * 
 * @details Remove o elemento do topo da pilha, liberando a memória e reajustando os ponteiros.
 *
 * @return Um ponteiro para a forma do topo retirado.
 * 
 * @warning Retorna NULL caso a fila esteja vazia.
 */
void *pop(PILHA p);

/**
 * @brief Função que 'pega' o primeiro elemento da pilha sem tirá-lo.
 *
 * @param PILHA Ponteiro que indica em qual pilha o elemento será obtido.
 * 
 * @return Retonar um ponteiro para o elemento do topo da pilha.
 *
 * @warning Retorna um ponteiro NULL caso pilha vazia.
 */
void *getTopo(PILHA p);

/**
 * @brief Função que verifica se a pilha está vazia. 
 * 
 * @param PILHA
 * 
 * @return 1 - para vazia 0 - para algum conteúdo dentro 
 */
int pilhaVazia(PILHA p);

#endif