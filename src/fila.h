#ifndef FILA_H
#define FILA_H

/*
Pensando no intuito do projeto, a Fila é a estrutura de dados
fundamental para o gerenciamento da Arena. Ela garante que as formas
geométricas sejam processadas na ordem exata em que foram lançadas,
obedecendo à regra "primeiro a entrar, primeiro a sair" (FIFO).

- Ao serem lançadas por um Disparador, as Formas são inseridas no fim da Fila da Arena.
- Para o processamento de colisões ou outras ações, as Formas são removidas do início da Fila.

O TAD Arena, portanto, utilizará esta Fila como sua principal estrutura de dados interna.
*/

typedef void* FILA;

/**
 * @brief Cria uma nova fila vazia.
 * 
 * @return Retorna um ponteiro para fila criada.
 *
 * @details Aloca dinamicamente memória para a fila, atribuindo ponteiros 
 * para o início e fim da fila.
 *
 * @warning Caso a alocacao de memoria dê errado, encerra o programa.
 */
FILA criarFila();

/**
 * @brief Insere um elemento no final da fila (Modelo FIFO).
 * 
 * @param FILA Ponteiro que indica em qual fila o elemento será inserido.
 *
 * @param elemento Ponteiro genérico que indica qual forma geometrica será inserida.
 *
 * @details Função criada para a inserção, dinâmica, de um elemento.
 * Essa função cria um novo nó no final da fila e insere a forma lá.
 * Caso a fila esteja vazia esse nó passa a ser o primeiro e último elemento.
 *
 * @warning Caso a alocacao de memoria dê errado, encerra o programa.
 */
void insereElemFila(FILA f, void *elemento);

/**
 * @brief Remove um elemento do início da fila (Modelo FIFO).
 *
 * @param FILA Ponteiro que indica em qual fila o elemento será retirado.
 * 
 * @details Remove o primeiro elemento da fila, liberando a memória e reajustando os ponteiros.
 * Se a fila só tinha um elemento antes de remoção, corrige o ponteiro do final da fila também.
 *
 * @warning Retorna NULL caso a pilha esteja vazia.
 */
void *removeElemFila(FILA f);

/**
 * @brief 'Pega' o primeiro elemento da fila sem tirá-lo.
 *
 * @param FILA Ponteiro que indica em qual fila o elemento será obtido.
 * 
 * @return Retonar um ponteiro para o primeiro elemento da fila.
 *
 * @warning Retorna um ponteiro NULL caso fila vazia.
 */
void *getFirstElem(FILA f);

/**
 * @brief Libera memória da fila e de seus nós (elementos).
 * 
 * @param FILA Ponteiro que indica qual fila será destruída.
 *
 * @details Percorre cada nó e vai desalocando memória (free).
 * Por fim, reajusta os ponteiros inicio e final para NULL.
 */
void destroiFila(FILA f);

/**
 * @brief Função que indica se a fila está vazia 
 * 
 * @param FILA Ponteiro para a fila analisada. 
 *
 * @return 1 - para vazia 0 - para algum elemento.
 */
int filaVazia(FILA f);

/**
 * @brief Função que mostra o número total de elementos da fila.
 * 
 * @param FILA Ponteiro para a fila analisada.
 *
 * @return Um inteiro que representa o total de elementos. 
 */
int getTamanhoFila(FILA f);

#endif