#include "TAD_Menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void menu(char *nomeArquivo, SearchType *searchType, HashTable *hashTable, PatriciaNode *root) {
    char ingrediente[100];
    int opcao;
    while(opcao != 4){
        printf("\n\t MENU:\n [1] Receber arquivos de entrada\n [2] Imprimir\n [3] Buscar ingrediente\n [4] Sair\nEscolha: ");
        opcao = getInt();
        switch (opcao) {
            case 1:
                printf("Recebendo arquivos de entrada\n");
                readentradaFile(nomeArquivo, searchType);
                break;
            case 2:
                printf("\n \t Imprimir:\n 1. Árvore Patricia \n 2. Tabela Hash \n Escolha: ");
                int opcao2 = getInt();
                switch (opcao2) {
                    case 1:
                        printf("Árvore Patricia\n");
                        //printPatricia(root);
                        break;
                    case 2:
                        printf("Tabela Hash\n");
                        printHashTable(hashTable);
                        break;
                    default:
                        printf("Opcao invalida\n");
                        break;
                }
                break;
            case 3:
                printf("Digite o nome do ingrediente que deseja buscar\n");
                scanf("%s", ingrediente);
                printf("Buscando ingrediente: %s\n", ingrediente);
                HashNode *currentHashNode = searchHash(hashTable, ingrediente);
                if (currentHashNode == NULL) {
                    printf("Ingrediente não encontrado\n");
                } else {
                    InvertedIndex *currentInvertedIndex = currentHashNode->invertedIndexRoot;
                    printf("ID do ingrediente: %d\n", currentHashNode->key);
                    printf("Quantidade de ocorrências: %d\n", currentInvertedIndex->qtde);
                    printf("ID do arquivo: %d\n", currentInvertedIndex->idDoc);
                }
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida\n");
                break;
        }
    }
}

int getInt() {
    int num;
    scanf("%d", &num);
    return num;
}