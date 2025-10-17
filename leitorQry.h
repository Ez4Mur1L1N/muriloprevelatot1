#ifndef LEITORQRY_H
#define LEITORQRY_H

#include "leitorGeo.h" 
// Para ter acesso a lista genérica "ListaFormas".

/*
TAD que será utilizado para leitura e processamento do arquivo .qry.
Ele lê os comandos do arquivo .qry e utiliza os diversos TADs (Disparador, Arena, Svg, etc.)
para executar as ações da simulação, gerando as saídas .svg e .txt.
*/


/**
 * @brief Função que lê um arquivo .qry e executa as ações determinadas.
 *
 * @param listaFormas A lista de formas original, criada pelo LeitorGeo.
 * @param caminhoArquivoQry O caminho/nome do arquivo .qry a ser lido.
 * @param caminhoSaidaSVG O caminho/nome do arquivo .svg que será gerado.
 * @param caminhoSaidaTXT O caminho/nome do arquivo .txt que será gerado.
 */
void lerArqQry(ListaFormas listaFormas, char* caminhoArqQry, char* caminhoSaidaSVG, char* caminhoSaidaTXT);


#endif