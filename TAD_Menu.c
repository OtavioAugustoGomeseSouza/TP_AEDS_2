#include "TAD_Menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Função para ler um número inteiro com verificação de erros
int getInt() {
    int num;
    if (scanf("%d", &num) != 1) {
        // Limpa o buffer de entrada se a leitura falhar
        while (getchar() != '\n');
        num = -1; // Valor inválido
    }
    return num;
}

// Função para calcular a relevância dos documentos com base nos termos de busca
void CalculodeWi(SearchType *searchType, TermoBusca *termoBusca, int numTermos) {
    // Aloca memória para armazenar a relevância de cada documento
    RelevanciaWi *w = malloc(searchType->numArq * sizeof(RelevanciaWi));
    RelevanciaRi *r = malloc(searchType->numArq * sizeof(RelevanciaRi));
    SomatorioWi *s = calloc(searchType->numArq, sizeof(SomatorioWi)); // Inicializa s com zeros

    if (w == NULL || r == NULL || s == NULL) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        exit(1);
    }

    // Inicializa a estrutura w e s com valores padrão
    for (int j = 0; j < searchType->numArq; j++) {
        w[j].idDoc = -1;
        w[j].wi = 0.0;
        s[j].soma = 0.0;
    }

    // Itera sobre cada termo de busca
    for (int i = 0; i < numTermos; i++) {
        PatriciaNode* noAtual = searchPatricia(searchType->root, termoBusca[i].ingrediente);
        if (noAtual != NULL && noAtual->InvertedIndexPatriciaRoot != NULL) {
            // Conta o número de documentos contendo o termo
            int numDocsWithTerm = countDocumentsWithTerm(noAtual);
            InvertedIndexPatricia *current = noAtual->InvertedIndexPatriciaRoot;
            int totalDocs = searchType->numArq;

            while (current != NULL) {
                // Calcula o peso do termo no documento
                double peso = current->qtde * log2((double)totalDocs) / numDocsWithTerm;
                
                // Armazena o peso no vetor w e atualiza o somatório
                int docIndex = current->idDoc;
                if (docIndex >= 0 && docIndex < searchType->numArq) {
                    w[docIndex].idDoc = docIndex;
                    w[docIndex].wi = peso;
                    s[docIndex].soma += peso; // Adiciona o peso ao somatório do documento
                }
                printf("Termo: %s\n", termoBusca[i].ingrediente);
                printf("Documento: %d\n", w[docIndex].idDoc);
                printf("Quantidade no documento: %d\n", current->qtde);
                printf("Total de documentos: %d\n", totalDocs);
                printf("Número de documentos com o termo: %d\n", numDocsWithTerm);
                printf("Peso calculado: %.2f\n", peso);
                // Avança para o próximo índice invertido
                current = current->nextInvertedIndexPatricia;
            }
        } else {
            printf("Termo '%s' não encontrado.\n", termoBusca[i].ingrediente);
        }
    }

    for (int x = 0; x < searchType->numArq; x++) {
        int ni = searchType->numArq; // Assuming this function exists
        if (ni > 0) {
            r[x].ri = (1.0 / ni) * s[x].soma;
            printf("Relevância total para o documento %d: %.2f\n", x, r[x].ri);
        }
    }

    // Libera a memória alocada
    free(w);
    free(r);
    free(s);
}

void readTermosBusca(TermoBusca *termoBusca, int numTermos) {
    // Limpa o buffer de entrada
    while (getchar() != '\n');
    
    for (int i = 0; i < numTermos; i++) {
        printf("Digite o nome do termo que deseja buscar\n");
        if (fgets(termoBusca[i].ingrediente, sizeof(termoBusca[i].ingrediente), stdin) != NULL) {
            // Remove o caractere de nova linha, se presente
            size_t len = strlen(termoBusca[i].ingrediente);
            if (len > 0 && termoBusca[i].ingrediente[len - 1] == '\n') {
                termoBusca[i].ingrediente[len - 1] = '\0';
            }
        } else {
            fprintf(stderr, "Erro ao ler a entrada.\n");
            exit(1);
        }
    }
}


void menu(char *nomeArquivo, SearchType *searchType) {
    int opcao = 0; // Inicializa a variável opcao
    FileType *ListaArquivos = NULL; // Inicializa a variável ListaArquivos

    while (opcao != 5) {
        printf("\n\t MENU:\n [1] Receber arquivos de entrada\n [2] Construir Índice Invertido\n [3] Imprimir\n [4] Buscar ingrediente\n [5] Sair\nEscolha: ");
        opcao = getInt(); // Lê a opção do usuário
        
        switch (opcao) {
            case 1:
                printf("Recebendo arquivos de entrada\n");
                ListaArquivos = readentradaFile(nomeArquivo, searchType);
                break;
            case 2:
                printf("Construindo Índice Invertido\n");
                readAllFiles(nomeArquivo, ListaArquivos, searchType);
                break;
            case 3:
                printf("\n\t Imprimir:\n [1] Árvore Patricia \n [2] Tabela Hash \n Escolha: ");
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
                        printf("Opção inválida\n");
                        break;
                }
                break;
            case 4:
                printf("Digite quantos termos deseja buscar\n");
                int numTermos = getInt();
                TermoBusca *termoBusca = malloc(numTermos * sizeof(TermoBusca));
                if (termoBusca == NULL) {
                    fprintf(stderr, "Erro ao alocar memória para TermoBusca\n");
                    exit(1);
                }

                readTermosBusca(termoBusca, numTermos); // Lê os termos compostos
                CalculodeWi(searchType, termoBusca, numTermos);
                free(termoBusca);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida\n");
                break;
        }
    }
}
