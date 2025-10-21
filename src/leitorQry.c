#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leitorQry.h"
#include "lista.h"
#include "disparador.h"
#include "carregador.h"
#include "arena.h"
#include "svg.h"
#include "tipos.h"
#include "processaFormas.h"

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"


// --- Função Principal do Módulo ---

void lerArqQry(ListaFormas listaFormas, char* caminhoArqQry, char* caminhoSaidaTXT, char* dirSaida, char* nomeBase, char* nomeQryBase) {
    
    FILE* arqQry = fopen(caminhoArqQry, "r");
    if (arqQry == NULL) {
        printf("Nao foi possivel abrir o arquivo de consultas %s\n", caminhoArqQry);
        return;
    }

    FILE* arqTxt = fopen(caminhoSaidaTXT, "w");
    if (arqTxt == NULL) {
        printf("Nao foi possivel criar o arquivo de saida TXT em %s\n", caminhoSaidaTXT);
        fclose(arqQry);
        return;
    }

    printf("\nIniciando simulacao: %s\n", caminhoArqQry);

    #define MAX_ARSENAL 20
    Disparador disparadores[MAX_ARSENAL];
    Carregador carregadores[MAX_ARSENAL];
    Arena arena = criarArena();

    for (int i = 0; i < MAX_ARSENAL; i++) {
        disparadores[i] = NULL;
        carregadores[i] = NULL;
    }

    char linha[512];
    char comando[10];
    
    // --- Variáveis de Estatística para o final ---
    double pontuacaoTotal = 0.0;
    int totalInstrucoes = 0;
    int totalDisparos = 0;
    int totalClones = 0;
    int totalEsmagados = 0;

    while (fgets(linha, sizeof(linha), arqQry)) {
        totalInstrucoes++;
        sscanf(linha, "%s", comando);
        fprintf(arqTxt, "%s", linha);

        if (strcmp(comando, "pd") == 0) {
            int id;
            double x, y, dx = 0.0, dy = 1.0; // Defini um padrão só para a criação correta.
            // Em outros comando isso será modificado.
            sscanf(linha, "pd %d %lf %lf", &id, &x, &y);

            if (id < 0 || id >= MAX_ARSENAL) {
                fprintf(arqTxt, "  -> ERRO: ID %d de disparador e invalido (limite e %d).\n", id, MAX_ARSENAL - 1);
                continue; // Código de segurança para acesso indevido da memória.
            }
            
            if (disparadores[id] != NULL) {
                destroiDisparador(disparadores[id]); // Caso já exista um disparador ele é substituído.
            }    
            disparadores[id] = criarDisparador(id, x, y, dx, dy);
            
            fprintf(arqTxt, "  -> OK: Disparador %d criado em (%.1f, %.1f)\n", id, x, y);

        } else if (strcmp(comando, "lc") == 0) {
            int c, n;
            sscanf(linha, "lc %d %d", &c, &n); 

            if (c < 0 || c >= MAX_ARSENAL) {
                fprintf(arqTxt, "  -> ERRO: ID %d de carregador e invalido (limite e %d).\n", c, MAX_ARSENAL - 1);
                continue; // Código de segurança para acesso indevido da memória.
            }

            if (carregadores[c] == NULL) {
                carregadores[c] = criarCarregador(); 
            }
            
            fprintf(arqTxt, "  -> OK: Carregando %d formas no carregador %d...\n", n, c); 
            for (int i = 0; i < n; i++) {
                No primeiroNo = getPrimeiroNoLista(listaFormas);
                if (primeiroNo == NULL) {
                    fprintf(arqTxt, "  -> AVISO: Nao ha mais formas no chao.\n");
                    break;
                }
                
                void* forma = removeNoLista(listaFormas, primeiroNo);
                carregaForma(carregadores[c], forma);
                fprintf(arqTxt, "      -> Forma ID %d carregada.\n", getIdFormaGenerica(forma));
            }

        } else if (strcmp(comando, "atch") == 0) {
            int d, cesq, cdir;
            sscanf(linha, "atch %d %d %d", &d, &cesq, &cdir); 

            if (d < 0 || d >= MAX_ARSENAL) {
                fprintf(arqTxt, "  -> ERRO: ID %d de disparador e invalido (limite e %d).\n", d, MAX_ARSENAL - 1);
                continue; 
            }

            if (disparadores[d] == NULL || carregadores[cesq] == NULL || carregadores[cdir] == NULL) {
                fprintf(arqTxt, "  -> ERRO: Disparador ou Carregadores nao existem.\n");
            } else {
                anexaCarregadoresDisparador(disparadores[d], carregadores[cesq], carregadores[cdir]);
                carregadores[cesq] = NULL;
                carregadores[cdir] = NULL;
                fprintf(arqTxt, "  -> OK: Disparador %d anexou carregadores %d (esq) e %d (dir)\n", d, cesq, cdir);
            }

        } else if (strcmp(comando, "shft") == 0) {
            int d, n;
            char lado[2];
            sscanf(linha, "shft %d %s %d", &d, lado, &n); 

            if (d < 0 || d >= MAX_ARSENAL) {
                fprintf(arqTxt, "  -> ERRO: ID %d de disparador e invalido (limite e %d).\n", d, MAX_ARSENAL - 1);
                continue; 
            }

            if (disparadores[d] == NULL) {
                fprintf(arqTxt, "  -> ERRO: Disparador %d nao existe.\n", d);
            } else {
                shiftDisparador(disparadores[d], lado[0], n);
                fprintf(arqTxt, "  -> OK: Disparador %d rotacionou %d vezes para o lado %c\n", d, n, lado[0]);
                void* formaArmada = getFormaArmadaDisparador(disparadores[d]);
                if (formaArmada != NULL) {
                    fprintf(arqTxt, "  -> INFO: Forma ID %d esta agora na posicao de disparo.\n", getIdFormaGenerica(formaArmada)); 
                } else {
                    fprintf(arqTxt, "  -> INFO: Posicao de disparo esta vazia.\n");
                }
            }

        } else if (strcmp(comando, "dsp") == 0) {
            int d;
            double dx, dy;
            char visualizacao[2] = ""; // Para capturar o 'v' ou 'i' opcional
            sscanf(linha, "dsp %d %lf %lf %s", &d, &dx, &dy, visualizacao); 

            if (d < 0 || d >= MAX_ARSENAL) {
                fprintf(arqTxt, "  -> ERRO: ID %d de disparador e invalido (limite e %d).\n", d, MAX_ARSENAL - 1);
                continue; 
            }

            if (disparadores[d] == NULL) {
                fprintf(arqTxt, "  -> ERRO: Disparador %d nao existe.\n", d);
            } else {
                void* formaDisparada = disparar(disparadores[d]);
                totalDisparos++;
                
                if (formaDisparada == NULL) {
                    fprintf(arqTxt, "  -> AVISO: Disparador %d tentou atirar, mas estava sem municao.\n", d);
                } else {
                    double dX = getXDisparador(disparadores[d]);
                    double dY = getYDisparador(disparadores[d]);
                    
                    double posX_final = dX + dx;
                    double posY_final = dY + dy;
                    
                    setPosFormaGenerica(formaDisparada, posX_final, posY_final);
                    inserirFormaArena(arena, formaDisparada);
                    
                    fprintf(arqTxt, "  -> OK: Disparador %d disparou forma ID %d. Posicao final: (%.1f, %.1f)\n", d, getIdFormaGenerica(formaDisparada), posX_final, posY_final); 
                    
                    if (strcmp(visualizacao, "v") == 0) { 
                        fprintf(arqTxt, "  -> SVG: Anotacao de disparo solicitada.\n");
                        
                        char caminhoSVGConsulta[512];
                        sprintf(caminhoSVGConsulta, "%s/%s-%s-%d.svg", dirSaida, nomeBase, nomeQryBase, totalInstrucoes);

                        geraSvgConsulta(caminhoSVGConsulta, listaFormas, arena, disparadores, MAX_ARSENAL, formaDisparada, dX, dY,posX_final, posY_final);
                    }
                }
            }

        } else if (strcmp(comando, "rjd") == 0) {
            int d;
            double dx, dy, ix, iy;
            char lado[2];
            sscanf(linha, "rjd %d %s %lf %lf %lf %lf", &d, lado, &dx, &dy, &ix, &iy); 

            if (d < 0 || d >= MAX_ARSENAL) {
                fprintf(arqTxt, "  -> ERRO: ID %d de disparador e invalido (limite e %d).\n", d, MAX_ARSENAL - 1);
                continue; 
            }

            if (disparadores[d] == NULL) {
                fprintf(arqTxt, "  -> ERRO: Disparador %d nao existe.\n", d);
            } else {
                fprintf(arqTxt, "  -> OK: Iniciando rajada (rjd) no disparador %d...\n", d);
                int disparoCount = 0;
                while (1) {
                    // "shft d [e|d] 1". Smepre vamos fazer esse movimento um por vez até se esgotar. 
                    shiftDisparador(disparadores[d], lado[0], 1);

                    // Verifica se o carregador se esgotou.
                    void* formaParaDisparar = getFormaArmadaDisparador(disparadores[d]);
                    if (formaParaDisparar == NULL) {
                        fprintf(arqTxt, "  -> FIM DA RAJADA: Carregador esgotado apos %d disparos.\n", disparoCount);
                        break; // Sai do loop while infinito. Condição de SAÍDA: esgotamento.
                    }
                    
                    void* formaDisparada = disparar(disparadores[d]);
                    totalDisparos++;

                    // "dsp d dx+i*ix dy+i*iy" 
                    // Incremento a cada disparo para que as peças, obviamente, não fiquem nos mesmos pontos.
                    double dx_atual = dx + (disparoCount * ix);
                    double dy_atual = dy + (disparoCount * iy);

                    // Mecanismos análogo ao disparador.
                    double dX = getXDisparador(disparadores[d]);
                    double dY = getYDisparador(disparadores[d]);
                    double posX_final = dX + dx_atual;
                    double posY_final = dY + dy_atual;

                    setPosFormaGenerica(formaDisparada, posX_final, posY_final);
                    inserirFormaArena(arena, formaDisparada);

                    fprintf(arqTxt, "      -> Disparo %d: Forma ID %d. Pos final: (%.1f, %.1f)\n", disparoCount, getIdFormaGenerica(formaDisparada), posX_final, posY_final);
                    
                    disparoCount++;
                }
            }
        
        } else if (strcmp(comando, "calc") == 0) {
            fprintf(arqTxt, "  -> OK: Processando eventos da arena (calc)...\n"); 
            
            double pontuacaoRound = 0.0;
            int formasProcessadas = 0;

            while (arenaVazia(arena) == 0) { // Enquanto a arena NÃO estiver vazia o laço vai rodar
                // Pega o primeiro elemento (I)
                void* formaI = removeFormaArena(arena);
                if (formaI == NULL) break;

                // Tenta pegar o segundo elemento (J)
                void* formaJ = removeFormaArena(arena);
                if (formaJ == NULL) {
                    // Arena com número ímpar de elementos, saí do laço.
                    /* "Último elemento não é sobreposto nem sobrepõem nenhum outro elemento 
                    Solução: volta para o chão."
                    */
                    fprintf(arqTxt, "  -> Arena com item impar. Forma ID %d volta para o chao.\n", getIdFormaGenerica(formaI));
                    insereNoComecoLista(listaFormas, formaI); // Volta pro chão
                    break; // Fim do 'calc'
                }
                
                formasProcessadas += 2;
                fprintf(arqTxt, "  -> Verificando: (I) ID %d vs (J) ID %d\n", getIdFormaGenerica(formaI), getIdFormaGenerica(formaJ));

                bool sobrepoe = verificaSobreposicao(formaI, formaJ); 

                if (sobrepoe) {
                    double areaI = calcAreaGenerica(formaI);
                    double areaJ = calcAreaGenerica(formaJ);

                    // Regra de "maior ou igual" da sua anotação
                    if (areaI < areaJ) { 
                        // I é esmagado. J volta para o chão.
                        fprintf(arqTxt, "      -> SOBREPOSICAO: I (ID %d) esmagado por J (ID %d).\n", getIdFormaGenerica(formaI), getIdFormaGenerica(formaJ));
                        destroiFormaGenerica(formaI);
                        insereNoComecoLista(listaFormas, formaJ); // Volta pro chão.
                        pontuacaoRound += areaI;
                        totalEsmagados++;
                    } else { //  Caso: areaI >= areaJ
                        // I muda cor de J. Ambos voltam pro chão. 
                        // I é clonado. Clone volta pro chão. 
                        fprintf(arqTxt, "      -> SOBREPOSICAO: I (ID %d) mudou cor de J (ID %d). Ambos voltam ao chao.\n", getIdFormaGenerica(formaI), getIdFormaGenerica(formaJ));
                        
                        char* corPreenchimentoI = getCorPGenerica(formaI);
                        // Verifica se a forma I realmente tem cor de preenchimento
                        if (strlen(corPreenchimentoI) > 0) { 
                            setCorBGenerica(formaJ, corPreenchimentoI);
                            fprintf(arqTxt, "      -> INFO: Cor da borda de J (ID %d) alterada para '%s'.\n", getIdFormaGenerica(formaJ), corPreenchimentoI);
                        } else {
                            fprintf(arqTxt, "      -> INFO: Forma I (ID %d) nao tem cor de preenchimento para transferir.\n", getIdFormaGenerica(formaI));
                        }
                        
                        insereNoComecoLista(listaFormas, formaJ);
                        insereNoComecoLista(listaFormas, formaI);
                        
                        void* cloneI = clonarFormaGenerica(formaI); 
                        if (cloneI != NULL) {
                            totalClones++;
                            insereNoComecoLista(listaFormas, cloneI); // Clone volta por último
                            fprintf(arqTxt, "      -> INFO: Forma I (ID %d) clonada com novo ID %d. Clone voltou ao chao.\n", getIdFormaGenerica(formaI), getIdFormaGenerica(cloneI));
                        } else {
                            fprintf(arqTxt, "      -> ERRO: Falha ao clonar forma I (ID %d).\n", getIdFormaGenerica(formaI));
                        }
                    }
                } else {
                    // Não sobrepõe: ambos voltam para o chão.
                    fprintf(arqTxt, "      -> SEM SOBREPOSICAO: I e J voltam para o chao.\n");
                    insereNoComecoLista(listaFormas, formaJ); // J volta primeiro
                    insereNoComecoLista(listaFormas, formaI); // I volta depois
                }
            }
            fprintf(arqTxt, "  -> Pontuacao do round: %.1f\n", pontuacaoRound);
            pontuacaoTotal += pontuacaoRound;
        }
    }

    // --- LIMPEZA FINAL ---
    printf("Fim da simulacao. Limpando memoria...\n");

    // Escreve as estatísticas finais no .txt.
    fprintf(arqTxt, "\n--- ESTATISTICAS FINAIS ---\n");
    fprintf(arqTxt, "Pontuacao Final: %.2f\n", pontuacaoTotal);
    fprintf(arqTxt, "Instrucoes Executadas: %d\n", totalInstrucoes);
    fprintf(arqTxt, "Total de Disparos: %d\n", totalDisparos); 
    fprintf(arqTxt, "Total de Formas Clonadas: %d\n", totalClones);
    fprintf(arqTxt, "Total de Formas Esmagadas: %d\n", totalEsmagados);

    fclose(arqQry);
    fclose(arqTxt);

    // Destrói todos os disparadores e carregadores que ainda existem.
    for (int i = 0; i < MAX_ARSENAL; i++) {
        if (disparadores[i] != NULL) {
            destroiDisparador(disparadores[i]);
        }
        if (carregadores[i] != NULL) {
            destroiCarregador(carregadores[i]);
        }
    }
    
    // Destrói a arena (que destruirá a fila interna). 
    // As formas do chão são destruídas no main.
    destroiArena(arena);
}