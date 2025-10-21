#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leitorGeo.h"
#include "leitorQry.h"
#include "svg.h"
#include "lista.h"
#include "tipos.h"

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

void geraSvg(ListaFormas formas, const char* caminhoSvg) {
    FILE* arqSvg = fopen(caminhoSvg, "w");
    if (arqSvg == NULL) {
        printf("Erro: nao foi possivel criar o arquivo SVG de saida em %s\n", caminhoSvg);
        return;
    }

    abreSVG(arqSvg);

    for (No no = getPrimeiroNoLista(formas); no != NULL; no = getProximoNoLista(no)) {
        Conteudo forma = getConteudoNoLista(no);
        TipoForma tipo = ((int*)forma)[1];

        switch (tipo) {
            case CIRCULO:   desenhaCirculoSVG(arqSvg, forma);   break;
            case RETANGULO: desenhaRetanguloSVG(arqSvg, forma); break;
            case LINHA:     desenhaLinhaSVG(arqSvg, forma);     break;
            case TEXTO:     desenhaTextoSVG(arqSvg, forma);     break;
        }
    }

    fechaSVG(arqSvg);
    fclose(arqSvg);
}

int main(int argc, char *argv[]) {
    char* dirEntrada = NULL;
    char* arqGeoNome = NULL;
    char* dirSaida = NULL;
    char* arqQryNome = NULL;

    // --- 1. Processamento dos Argumentos da Linha de Comando ---
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
            dirEntrada = argv[++i];
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            arqGeoNome = argv[++i];
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            dirSaida = argv[++i];
        } else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc) {
            arqQryNome = argv[++i];
        }
    }

    if (arqGeoNome == NULL || dirSaida == NULL) {
        printf("Argumentos obrigatorios -f e -o nao foram fornecidos.\n");
        printf("Uso: ./programa -f <arq.geo> -o <dir_saida> [-e <dir_entrada> -q <arq.qry>]\n");
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
    char* ponto = strrchr(nomeBase, '.');
    if (ponto != NULL) {
        *ponto = '\0';
    }
    
    char caminhoSvg[512];
    sprintf(caminhoSvg, "%s/%s.svg", dirSaida, nomeBase);

    char caminhoTxt[512];
    char nomeQrySemExt[256];
    nomeQrySemExt[0] = '\0';
    if (arqQryNome != NULL) {
        strcpy(nomeQrySemExt, arqQryNome);
        ponto = strrchr(nomeQrySemExt, '.');
        if (ponto != NULL) {
            *ponto = '\0';
        }
        // Cria um nome de arquivo combinado, ex: saida/t1-consultas.txt
        sprintf(caminhoTxt, "%s/%s-%s.txt", dirSaida, nomeBase, nomeQrySemExt);
    }


    // --- 3. Execução Principal ---
    printf("Lendo arquivo GEO: %s\n", caminhoGeo);
    ListaFormas formas = lerArqGeo(caminhoGeo);

    printf("Gerando SVG inicial: %s\n", caminhoSvg);
    geraSvg(formas, caminhoSvg);

    // --- 4. Processamento de Consultas ---
    if (arqQryNome != NULL) {
        char caminhoQry[512];
        if (dirEntrada != NULL) {
            sprintf(caminhoQry, "%s/%s", dirEntrada, arqQryNome);
        } else {
            strcpy(caminhoQry, arqQryNome);
        }
        // Agora a variável caminhoTxt existe e podemos usá-la para gerar a saída textual;
        lerArqQry(formas, caminhoQry, caminhoTxt, dirSaida, nomeBase, nomeQrySemExt);
    }

    printf("\nProcesso concluido!\n");

    // --- 5. Limpeza Final (Memory Cleanup) ---
    printf("Liberando memoria das formas...\n");
    for (No no = getPrimeiroNoLista(formas); no != NULL; no = getProximoNoLista(no)) {
        Conteudo forma = getConteudoNoLista(no);
        TipoForma tipo = ((int*)forma)[1];
        
        switch (tipo) {
            case CIRCULO:   destroiCirculo(forma);   break;
            case RETANGULO: destroiRetangulo(forma); break;
            case LINHA:     destroiLinha(forma);     break;
            case TEXTO:     destroiTexto(forma);     break;
        }
    }
    
    printf("Liberando memoria da lista...\n");
    destroiListaFormasGeo(formas);

    return 0;
}