#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leitorGeo.h"
#include "svg.h"
#include "lista.h"
#include "tipos.h"

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

/**
 * @brief Desenha todas as formas de uma lista em um arquivo SVG.
 *
 * @param formas A lista contendo as formas a serem desenhadas.
 * @param caminhoSvg O caminho do arquivo .svg a ser criado.
 */
void gerarSvg(ListaFormas formas, const char* caminhoSvg) {
    FILE* arqSvg = fopen(caminhoSvg, "w");
    if (arqSvg == NULL) {
        printf("Erro: nao foi possivel criar o arquivo SVG de saida em %s\n", caminhoSvg);
        return;
    }

    abreSVG(arqSvg);

    // Loop para percorrer a lista de formas
    for (No no = getPrimeiroNoLista(formas); no != NULL; no = getProximoNoLista(no)) {
        Conteudo forma = getConteudoNoLista(no);
        
        /*
        // O segundo campo de TODAS as structs de formas é o
        // enum 'TipoForma' (que no fundo é um int), podemos fazer um cast do
        // ponteiro genérico (void*) para um ponteiro de inteiro (int*) e ler
        // o valor na segunda posição de memória (índice 1).
        */
        TipoForma tipo = ((int*)forma)[1];

        // Com base no tipo, chama a função de desenho correta
        switch (tipo) {
            case CIRCULO:
                desenhaCirculoSVG(arqSvg, forma);
                break;
            case RETANGULO:
                desenhaRetanguloSVG(arqSvg, forma);
                break;
            case LINHA:
                desenhaLinhaSVG(arqSvg, forma);
                break;
            case TEXTO:
                desenhaTextoSVG(arqSvg, forma);
                break;
        }
    }

    fechaSVG(arqSvg);
    fclose(arqSvg);
}

int main(int argc, char *argv[]) {
    char* dirEntrada = NULL;
    char* arqGeoNome = NULL;
    char* dirSaida = NULL;

    // --- 1. Processamento dos Argumentos da Linha de Comando ---
    for (int i = 1; i < argc; i++) {
        // strcmp retorna 0 se as strings são iguais
        if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
            dirEntrada = argv[++i];
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            arqGeoNome = argv[++i];
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            dirSaida = argv[++i];
        }
    }

    if (arqGeoNome == NULL || dirSaida == NULL) {
        printf("Argumentos obrigatorios -f e -o nao foram fornecidos.\n");
        printf("Uso: ./programa -f <arq.geo> -o <dir_saida> [-e <dir_entrada>]\n");
        return 1;
    }

    // --- 2. Montagem dos Caminhos dos Arquivos ---
    char caminhoGeo[512];
    if (dirEntrada != NULL) {
        sprintf(caminhoGeo, "%s/%s", dirEntrada, arqGeoNome);
    } else {
        strcpy(caminhoGeo, arqGeoNome);
    }

    char nomeBase[256];
    strcpy(nomeBase, arqGeoNome);
    char* ponto = strrchr(nomeBase, '.'); // Encontra o último '.' no nome do arquivo
    if (ponto != NULL) {
        *ponto = '\0'; // Remove a extensão colocando um final de string no lugar do '.'
    }
    
    char caminhoSvg[512];
    sprintf(caminhoSvg, "%s/%s.svg", dirSaida, nomeBase);

    // --- 3. Execução Principal ---
    printf("Lendo arquivo GEO: %s\n", caminhoGeo);
    ListaFormas formas = lerArqGeo(caminhoGeo);

    printf("Gerando SVG inicial: %s\n", caminhoSvg);
    gerarSvg(formas, caminhoSvg);
    
    printf("Processo concluido!\n");

    // --- 4. Limpeza Final (Memory Cleanup) ---
    printf("Liberando memoria das formas...\n");
    for (No no = getPrimeiroNoLista(formas); no != NULL; no = getProximoNoLista(no)) {
        Conteudo forma = getConteudoNoLista(no);
        // Usamos o mesmo truque para descobrir o tipo e chamar o destrutor correto
        TipoForma tipo = ((int*)forma)[1];
        
        switch (tipo) {
            case CIRCULO:   destroiCirculo(forma);   break;
            case RETANGULO: destroiRetangulo(forma); break;
            case LINHA:     destroiLinha(forma);     break;
            case TEXTO:     destroiTexto(forma);     break;
        }
    }
    
    printf("Liberando memoria da lista...\n");
    // Esta função destrói apenas o contêiner da lista (os nós)
    destroiListaFormasGeo(formas);

    return 0;
}