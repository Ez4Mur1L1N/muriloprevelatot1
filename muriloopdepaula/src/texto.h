#ifndef TEXTO_H
#define TEXTO_H

/*
TAD que vai representar um texto. Deve-se ressaltar que a representação desse texto
se dará dentro de um plano bidimensional.
Além disso, reitera-se que o texto pode ter sua coordenada âncora 
tanto no início, como no meio ou no final.
Esse TAD também guardará algumas informações estilísticas.
*/

typedef void* Texto;

/**
 * @brief 
 * 
 * @param id Indica o ID da forma.
 * @param x Indica a coordenada 'X' da âncora do texto.
 * @param y Indica a coordenada 'Y' da âncora do texto.
 * @param corB Indica a cor da borda do texto.
 * @param corP Indica a cor de preenchimento do texto.
 * @param a Indica a posição da coordenada âncora (i-inicio/m-meio/f-final).
 * @param texto Indica a mensagem em si.
 * @param fFamily Indica a família da fonte do texto;
 * @param fWeight Indica o 'peso' da fonte do texto.
 * @param fSize Indica o tamanho da fonte do texto.
 *
 * @return Retorna um ponteiro para o texto criado.
 *
 * @warning Caso dê erro de alocação de memória, o programa encerra.
 */
Texto criarTexto(int id, double x, double y, char *corB, char *corP, char a, char *texto, char *fFamily, char *fWeight, char *fSize);

/**
 * @brief Função que libera toda memória alocada para o texto.
 * 
 * @param Texto Ponteiro do texto analisado.
 */
void destroiTexto(Texto t);

/**
 * @brief Função que 'pega' o ID do texto.
 * 
 * @param Texto Ponteiro do texto analisado.
 *
 * @return Um inteiro que representa o id do texto.
 */
int getIDTexto(Texto t);

/**
 * @brief Função que 'pega' a coordenada âncora 'X' do texto.
 * 
 * @param Texto Ponteiro do texto analisado.
 *
 * @return Um double que representa a coordenada 'X' da âncora do texto.
 */
double getXTexto(Texto t);

/**
 * @brief Função que 'pega' a coordenada âncora 'Y' do texto.
 * 
 * @param Texto Ponteiro do texto analisado.
 *
 * @return Um double que representa a coordenada 'Y' da âncora do texto.
 */
double getYTexto(Texto t);

/**
 * @brief Função que 'pega' a cor de borda do texto.
 * 
 * @param Texto Ponteiro do texto analisado.
 *
 * @return Uma string que representa a cor de borda do texto.
 */
char *getCorBTexto(Texto t);

/**
 * @brief Função que 'pega' a cor de preenchimento do texto.
 * 
 * @param Texto Ponteiro do texto analisado.
 *
 * @return Uma string que representa a cor de preenchimento do texto.
 */
char *getCorPTexto(Texto t);

/**
 * @brief Função que 'pega' a âncora do texto.
 * 
 * @param Texto Ponteiro do texto analisado.
 *
 * @return Um char que representa a posição da coordenada âncora.
 */
char getAncoraTexto(Texto t);

/**
 * @brief Função que 'pega' o texto em si (mensagem).
 * 
 * @param Texto Ponteiro do texto analisado.
 *
 * @return Uma string que representa o texto em si (mensagem).
 */
char *getTexto_Texto(Texto t);

/**
 * @brief Função que 'pega' a família da fonte do texto.
 * 
 * @param Texto Ponteiro do texto analisado.
 *
 * @return Uma string que representa a família da fonte do texto.
 */
char *getFonteFamilyTexto(Texto t);

/**
 * @brief Função que 'pega' o 'peso' da fonte do texto.
 * 
 * @param Texto Ponteiro do texto analisado.
 *
 * @return Uma string que representa o 'peso' da fonte do texto.
 */
char *getFonteWeightTexto(Texto t);

/**
 * @brief Função que 'pega' o tamanho da fonte do texto.
 * 
 * @param Texto Ponteiro do texto analisado.
 *
 * @return Uma string que representa o tamanho da fonte do texto.
 */
char *getFonteSizeTexto(Texto t);

#endif