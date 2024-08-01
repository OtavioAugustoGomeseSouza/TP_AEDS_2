#include "TAD_Menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

void menu(char *nomeArquivo, SearchType *searchType) {
    char ingrediente[100];
    int opcao;
    FileType * ListaArquivos;
    while(opcao != 5){
        printf("\n\t MENU:\n [1] Receber arquivos de entrada\n [2] Construir Indice Invertido\n [3] Imprimir\n [4] Buscar ingrediente\n [5] Sair\nEscolha: ");
        opcao = getInt();
        switch (opcao) {
            case 1:
                printf("Recebendo arquivos de entrada\n");
                ListaArquivos = readentradaFile(nomeArquivo, searchType);
                break;
            case 2: 
                printf("Construindo Indice Invertido\n");  
                readAllFiles(nomeArquivo, ListaArquivos, searchType);
                break;
            case 3:
                printf("\n \t Imprimir:\n [1] Árvore Patricia \n [2] Tabela Hash \n Escolha: ");
                int opcao2 = getInt();
                switch (opcao2) {
                    case 1:
                        printf("Árvore Patricia\n");
                        printPatricia(searchType->root);
                        break;
                    case 2:
                        printf("Tabela Hash\n");
                        printHashTable(&searchType->hashTable);
                        break;
                    default:
                        printf("Opcao invalida\n");
                        break;
                }
                break;
            case 4:
                printf("Digite quantos termo deseja buscar\n");
                opcao2 = getInt();
                TermoBusca termoBusca[opcao2];
                for (int i = 0; i < opcao2; i++){
                    printf("Digite o nome do termo que deseja buscar\n");
                    scanf("%s", termoBusca[i].ingrediente);
                }
                CalculodeRelevancia(searchType, termoBusca, opcao2);
                break;
            /*case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida\n");
                break;
            */
        }
    }
}

int getInt() {
    int num;
    scanf("%d", &num);
    return num;
}

void CalculodeRelevancia(SearchType *searchType, TermoBusca *termoBusca, int numTermos) {
    int i = 0;
    RelevanciaWi *w = malloc(searchType->numArq * sizeof(RelevanciaWi));
    if (w == NULL) {
        fprintf(stderr, "Erro ao alocar memória para RelevanciaWi\n");
        exit(1);
    }

    // Inicializa a estrutura w com valores default
    for (int j = 0; j < searchType->numArq; j++) {
        w[j].idDoc = -1;  // Valor default indicando que não foi encontrado
        w[j].wi = 0.0;
    }

    while (termoBusca[i].ingrediente != NULL || i < numTermos) {
        // Procura o nó da árvore Patricia que contém o termo atual
        PatriciaNode* NoAtual = searchPatricia(searchType->root, termoBusca[i].ingrediente);
        if (NoAtual != NULL && NoAtual->InvertedIndexPatriciaRoot != NULL) {
            // Percorre a lista encadeada de índices invertidos
            InvertedIndexPatricia *current = NoAtual->InvertedIndexPatriciaRoot;
            int index = 0;
            int totalDocs = searchType->numArq;
            int numDocsWithTerm = countDocumentsWithTerm(NoAtual);
            while (index < numDocsWithTerm) {
                // Calcula a relevância para cada documento na lista encadeada
                
                w[index].idDoc = current->idDoc;
                w[index].wi = (current->qtde) * (log2(totalDocs) / numDocsWithTerm);
                printf("%i\n",w[index].idDoc);
                printf("%i\n",current->qtde);
                // Impressão para depuração
                printf("Quantidade: %d\nTotal Docs: %d\nDocs com Termo: %d\n", current->qtde, totalDocs, numDocsWithTerm);
                printf("Relevância para o documento %d: %f\n", w[index].idDoc, w[index].wi);

                current = current->nextInvertedIndexPatricia;
                index++;
            }
        }
        i++;
    }

    // Liberar memória alocada
    free(w);
}