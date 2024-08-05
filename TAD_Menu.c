#include "TAD_Menu.h"

//Função para ler os inteiros do menu
int getInt() {
    int num;
    if (scanf("%d", &num) != 1) {
        //Como estava dando Bug, fiz isso para limpar buffer
        while (getchar() != '\n');
        num = -1;
    }
    return num;
}

void CalculoRi(SearchType *searchType, TermoBusca *termoBusca, RelevanciaRi *r, SomatorioWi *s, FileType *ListaArquivos) {
    //Parte para calculo da R(i) de cada doc
    int contador=0; //Para saber qntas R(i) é != 0
    for (int x = 0; x < searchType->numArq; x++) {
        int ni = ListaArquivos[x].ni;
        if (searchType->numArq > 0) {
            r[x].ri = (1.0 / ni) * s[x].soma;
            //printf("Relevância total para o documento %d: %.2f\n", x, r[x].ri);
            if(r[x].ri>0.0){
                contador++;
            }
        }
    }

    //Parte q determina a ordem do mais relevante
    float vetMaior[contador];
    int idArqMaiorRelev[contador];
    int idMaior;
    for (int i = 0; i < contador; i++) {
        float maiorRelev = 0.0;
        for (int x = 0; x < searchType->numArq; x++) {
            if (r[x].ri > 0.0 && r[x].ri > maiorRelev) {
                maiorRelev = r[x].ri;
                idMaior = x;
            }
        }
        vetMaior[i] = maiorRelev;
        idArqMaiorRelev[i] = idMaior;
        //printf("Relevância total para o documento %d: %.2f\n", idArqMaiorRelev[i]+1, r[idArqMaiorRelev[i]].ri);
        r[idMaior].ri = 0.0;
    
    }

    //parte para printar os mais relevantes
    for (int i = 0; i < contador; i++) {
        printf("Texto %i (arquivo%i.txt)\n",idArqMaiorRelev[i]+1,idArqMaiorRelev[i]+1);
    }

    //Libera a memória
    free(r);
    free(s);
}

// Função para calcular W(i) para a árvore Patricia
void CalculodeWiPatricia(SearchType *searchType, TermoBusca *termoBusca, int numTermos, FileType *ListaArquivos) {
    if (searchType == NULL || termoBusca == NULL || ListaArquivos == NULL) {
        fprintf(stderr, "Argumentos inválidos.\n");
        return;
    }

    // Alocar memória
    RelevanciaWi *w = malloc(searchType->numArq * sizeof(RelevanciaWi));
    RelevanciaRi *r = malloc(searchType->numArq * sizeof(RelevanciaRi));
    SomatorioWi *s = calloc(searchType->numArq, sizeof(SomatorioWi));

    if (w == NULL || r == NULL || s == NULL) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        free(w);
        free(r);
        free(s);
        exit(1);
    }

    // Inicializar estruturas
    for (int j = 0; j < searchType->numArq; j++) {
        w[j].idDoc = -1;
        w[j].wi = 0.0;
        s[j].soma = 0.0;
    }

    // Calcular W(i) para cada termo de busca
    for (int i = 0; i < numTermos; i++) {
        TipoArvore noAtual = Pesquisa(termoBusca[i].ingrediente,searchType->root);
        //printf("passou da pesquisa\n");
        if (noAtual != NULL && noAtual->InvertedIndexPatriciaRoot != NULL) {
            //Conta o total de arq q tem o termo
            int numDocsWithTerm = countDocumentsWithTermPatricia(noAtual);
            InvertedIndexPatricia *current = noAtual->InvertedIndexPatriciaRoot;
            int totalDocs = searchType->numArq;

            while (current != NULL) {
                //Calculo do W(i)
                double peso = current->qtde * log2((double)totalDocs) / numDocsWithTerm;
                
                //Armazena o W(i) e ++no somatorio
                int docIndex = current->idDoc;
                if (docIndex >= 0 && docIndex < searchType->numArq) {
                    w[docIndex].idDoc = docIndex;
                    w[docIndex].wi = peso;
                    s[docIndex].soma += peso;
                }
                /*Prints para teste do valor de W(i)
                printf("Termo: %s\n", termoBusca[i].ingrediente);
                printf("Documento: %d\n", w[docIndex].idDoc);
                printf("Quantidade no documento: %d\n", current->qtde);
                printf("Total de documentos: %d\n", totalDocs);
                printf("Número de documentos com o termo: %d\n", numDocsWithTerm);
                printf("Peso calculado: %.2f\n", peso);
                */
                //Avança na lista encadeada
                current = current->nextInvertedIndexPatricia;
            }
        } else {
            printf("Termo '%s' não encontrado.\n", termoBusca[i].ingrediente);
        }
    }

    printf("Calculando R(i) pela árvore Patricia\n");
    CalculoRi(searchType, termoBusca, r, s, ListaArquivos);

    free(w);
}

//Calcular a Relevancia da Tabela Hash
void CalculodeWiHash(SearchType *searchType, TermoBusca *termoBusca, int numTermos, FileType *ListaArquivos) {
    //Aloca memória
    RelevanciaWi *w = malloc(searchType->numArq * sizeof(RelevanciaWi));
    RelevanciaRi *r = malloc(searchType->numArq * sizeof(RelevanciaRi));
    SomatorioWi *s = calloc(searchType->numArq, sizeof(SomatorioWi));

    if (w == NULL || r == NULL || s == NULL) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        exit(1);
    }

    //Iniciar a Estruturas
    for (int j = 0; j < searchType->numArq; j++) {
        w[j].idDoc = -1;
        w[j].wi = 0.0;
        s[j].soma = 0.0;
    }

    //calculo de cada termo de busca
    for (int i = 0; i < numTermos; i++) {
        HashNode* noAtual = searchHash(&searchType->hashTable, termoBusca[i].ingrediente);
        if (noAtual != NULL && noAtual->invertedIndexRoot != NULL) {
            //Conta qntos arq tem o termo
            int numDocsWithTerm = countDocumentsWithTermHash(noAtual);
            InvertedIndex *current = noAtual->invertedIndexRoot;
            int totalDocs = searchType->numArq;

            while (current != NULL) {
                //Calcula o W(i)
                double peso = current->qtde * log2((double)totalDocs) / numDocsWithTerm;
                
                //Armazena os W(i) e ++somatorio
                int docIndex = current->idDoc;
                if (docIndex >= 0 && docIndex < searchType->numArq) {
                    w[docIndex].idDoc = docIndex;
                    w[docIndex].wi = peso;
                    s[docIndex].soma += peso;
                }
                /*Prints para teste
                printf("Termo: %s\n", termoBusca[i].ingrediente);
                printf("Documento: %d\n", w[docIndex].idDoc);
                printf("Quantidade no documento: %d\n", current->qtde);
                printf("Total de documentos: %d\n", totalDocs);
                printf("Número de documentos com o termo: %d\n", numDocsWithTerm);
                printf("Peso calculado: %.2f\n", peso);
                */
                
                //continua na lista encadeada
                current = current->nextInvertedIndex;
            }
        } else {
            printf("Termo '%s' não encontrado.\n", termoBusca[i].ingrediente);
        }
    }
    printf("Calculando R(i) pela Tabela Hash\n");
    CalculoRi(searchType, termoBusca, r, s, ListaArquivos);
    free(w);
}

void readTermosBusca(TermoBusca *termoBusca, int numTermos) {
    //Limpa o buffer de entrada
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
                        ImprimeArvore(searchType->root, 0);
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
                CalculodeWiPatricia(searchType, termoBusca, numTermos, ListaArquivos);
                CalculodeWiHash(searchType, termoBusca, numTermos, ListaArquivos);
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
