#include "TAD_Menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
                printf("Arquivos inseridos\n");
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
                for (int i = 0; i < opcao2; i++){
                    printf("Digite o nome do termo que deseja buscar\n");
                    scanf("%s", ingrediente);
                }
                scanf("%s", ingrediente);
                TermoBusca *termoBusca[opcao2];
                printf("Buscando ingrediente: %s\n", ingrediente);
                for (int i = 0; i < opcao2; i++){
                    scanf("%s", termoBusca[i]->ingrediente);
                }
                //buscar(searchType, ingrediente);
                break;
            case 5:
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

