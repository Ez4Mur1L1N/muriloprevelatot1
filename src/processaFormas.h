#ifndef PROCESSAFORMAS_H
#define PROCESSAFORMAS_H

#include <stdbool.h>
#include "lista.h" 
#include "tipos.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

/*
 * Este módulo contém funções genéricas para auxiliar na
 * manipulação de formas (void*) sem saber seu tipo exato.
 * Vai ser usado pelo leitorQry.c (para a lógica) e pelo svg.c (para o desenho).
 */


/* Ressalta-se que esse módulo foi criado para facilitar o manuseio das formas,
uma vez que dentro dos comandos, muitas vezes é necessário a manipulação das formas
sem saber do que elas se tratam. */

/**
 * @brief Função que pega o "tipo" da forma.
 * 
 * @param forma Ponteiro para a forma genérica analisada.
 * 
 * @return Uma "etiqueta" para o tipo da forma.
 */
TipoForma getTipoFormaGenerica(void* forma);

/**
 * @brief Função que pega o ID da forma
 * 
 * @param forma Ponteiro para a forma genérica analisada.
 * 
 * @return Um inteiro que representa o identificador da forma.
 */
int getIdFormaGenerica(void* forma);

/**
 * @brief Função que identifica e chama o destruidor correto da forma.
 * 
 * @param forma Ponteiro para a forma genérica analisada.
 */
void destroiFormaGenerica(void* forma);

/**
 * @brief Função que define uma nova posição para o ancorâ da forma.
 * 
 * @param forma Ponteiro para a forma genérica analisada.
 * @param x Novo valor para a coordenada "x" da âncora. 
 * @param y Novo valor para a coordenada "y" da âncora.
 */
void setPosFormaGenerica(void* forma, double x, double y);

// As 2 funções subsequentes são de grande valia para o caso das sobreposições.

/**
 * @brief Função que pega a cor de preenchimento de uma forma genérica.
 * 
 * @param forma Ponteiro para a forma genérica analisada.
 * 
 * @return Ponteiro para a string da cor. 
 * 
 * @details Retorna "" se forma for NULL.
 */
char* getCorPGenerica(void* forma);

/**
 * @brief Define a cor da BORDA (stroke) de uma forma genérica.
 * 
 * @param forma Ponteiro para a forma genérica analisada.
 * @param novaCorB Ponteiro para a string da nova cor.
 * 
 * @details Libera a memória da cor antiga e aloca memória para a nova.
 */
void setCorBGenerica(void* forma, char* novaCorB);

/**
 * @brief Função que calcula a área da forma.
 * 
 * @param forma Ponteiro para a forma genérica analisada.
 * 
 * @return Um double que representa o valor da área.
 * 
 * @details Importante para o cálculo da pontuação
 */
double calcAreaGenerica(void* forma);

// TODO: Você precisará disso para o 'calc'
// bool verificaSobreposicao(void* formaI, void* formaJ);

/**
 * @brief Função que pega o "retangulo delimitador" de uma forma genérica.
 * 
 * @param forma Ponteiro para a forma genérica analisada.
 * @param x Ponteiro para uma variável double onde o 'x' da caixa será salvo.
 * @param y Ponteiro para uma variável double onde o 'y' da caixa será salvo.
 * @param w Ponteiro para uma variável double onde o 'w' (largura) será salvo.
 * @param h Ponteiro para uma variável double onde o 'h' (altura) será salvo.
 */
void getRetanguloDelimitadorGenerica(void* forma, double* x, double* y, double* w, double* h);

/**
 * @brief Função que clona uma forma genérica.
 * 
 * @param forma Ponteiro para a forma original analisada.
 * 
 * @return Ponteiro para a nova forma clonada. 
 * 
 * @details Retorna NULL se a forma original for NULL. 
 * O clone recebe um ID novo e único. Aloca a memória necessária.
 * Função que basicamente copia a forma incrementando um ID novo.
 */
void* clonarFormaGenerica(void* forma);

/**
 * @brief Função que verifica se duas formas genéricas se sobrepõem geometricamente.
 * 
 * @param formaI Ponteiro para a primeira forma.
 * @param formaJ Ponteiro para a segunda forma.
 * 
 * @return true (1) se as formas se sobrepõem, false (0) caso contrário.
 * 
 * @details Leva em conta as regras de colisão do projeto (texto como linha)!
 */
bool verificaSobreposicao(void* formaI, void* formaJ); 

#endif