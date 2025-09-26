#ifndef CIRCULO_H
#define CIRCULO_H

/*
TAD que vai representar a forma geométrica do Círculo.
A coordenada âncora dessa forma é seu centro (x,y) e sua
dimensão é definida pelo raio

*/

typedef void* Circulo;

/**
 * @brief Função que cria um círculo com os atributos indicados.
 *
 * @param id Indica o "ID" da forma geométrica.
 * @param x Indica a coordenada X (plano cartesiano) do centro. 
 * @param y Indica a coordenada Y (plano cartesiano) do centro.
 * @param r Indica o raio do círculo.
 * @param corB Indica a cor da borda do círculo.
 * @param corP Indica a cor do preenchimento.
 *
 * @return Retorna o ponteiro para o círculo criado.
 *
 * @details Cria um círculo, inicializa seus atributos e retorna um ponteiro para ele.
 */
Circulo criarCirculo(int id, double x, double y, double r, char *corB, char *corP);

/**
 * @brief Função que libera toda a memória alocada para o círculo.
 *
 * @param c Ponteiro do círculo a ser destruído.
 */
void destroiCirculo(Circulo c); 

/**
 * @brief Função que 'pega' o ID do círculo.
 *
 * @param Circulo Ponteiro do círculo analisado.
 * 
 * @return Um inteiro que representa o id da forma.
 */
int getIDCirculo(Circulo c);

/**
 * @brief Função que 'pega' a coordenada 'X' (plano cartesiano) do círculo.
 *
 * @param Circulo Ponteiro do círculo analisado.
 * 
 * @return Um double que representa a coordenada 'X' da forma.
 */
double getXCirculo(Circulo c);

/**
 * @brief Função que 'pega' a coordenada 'Y' (plano cartesiano) do círculo.
 *
 * @param Circulo Ponteiro do círculo analisado.
 * 
 * @return Um double que representa a coordenada 'Y' da forma.
 */
double getYCirculo(Circulo c);

/**
 * @brief Função que 'pega' o raio do círculo.
 *
 * @param Circulo Ponteiro do círculo analisado.
 * 
 * @return Um double que representa as dimensões do raio da forma.
 */
double getRCirculo(Circulo c);

/**
 * @brief Função que 'pega' a cor da borda do círculo.
 * 
 * @param Circulo Ponteiro do círculo analisado.
 * 
 * @return Uma string com a cor da borda da forma.  
*/
char *getCorBCirculo(Circulo c);

/**
 * @brief Função quen'pega' a cor de preenchimento do círculo.
 * 
 * @param Circulo Ponteiro do círculo analisado.
 * 
 * @return Uma string com a cor de preenchimento da forma.  
*/
char *getCorPCirculo(Circulo c);

/**
 * @brief Função que calcula a área do círculo.
 *
 * @param r Raio do círculo.
 *
 * @return A área do círculo. 
 */
double calcAreaCirculo(double r);

/**
 * @brief Função que define uma nova coordenada para 'X'.
 *
 * @param Circulo Ponteiro do círculo analisado.
 *
 * @param x Novo valor para a coordenada 'X'.
 */
void setXCirculo(Circulo c, double xNovo);

/**
 * @brief Função que define uma nova coordenada para 'Y'.
 *
 * @param Circulo Ponteiro do círculo analisado.
 *
 * @param x Novo valor para a coordenada 'Y'.
 */
void setYCirculo(Circulo c, double yNovo);

/**
 * @brief Função que define um novo valor para o raio.
 *
 * @param Circulo Ponteiro do círculo analisado.
 *
 * @param x Novo valor para o raio.
 */
void setRCirculo(Circulo c, double raioNovo);

/**
 * @brief Função que define uma nova cor para a borda do círculo.
 *
 * @param Circulo Ponteiro do círculo analisado.
 *
 * @param x Nova cor para a borda do círculo.
 */
void setCorBCirculo(Circulo c, double raioNovo);

/**
 * @brief Função que define uma nova cor para o preenchimento do círculo.
 *
 * @param Circulo Ponteiro do círculo analisado.
 *
 * @param x Nova cor para o preenchimento do círculo.
 */
void setCorPCirculo(Circulo c, double raioNovo);

#endif