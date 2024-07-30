#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "TAD_TabelaHash.h"
#include "TAD_Patricia.h"
//gcc -Wall -Wextra -g3 TAD_TabelaHash.c TAD_Patricia.c Main.c -o output/Main.exe
//mingw32-make
// .\exec.exe

/*
 como compilar
 
 para criar o makefile precisa estar dentro da pasta C:\Users\Otavio\Desktop\TP_AEDS_2\TP_AEDS_2> e executar mingw32-make
  será criado um exec.exe que não pode ser compilado
  o exec.exe deve ser movido para a pasta output

  então entrar no output com o comando cd output
  executar o comando .\exec.exe

  se quiser compilar novamente deve sair da pasta output e voltar para a pasta C:\Users\Otavio\Desktop\TP_AEDS_2\TP_AEDS_2>
  para sair de uma pasta use o comando cd ..

*/


typedef struct {
    char fileName[256];
    char potionName[256]; // Aloca memória suficiente para armazenar o nome do arquivo
    int idDoc;
} FileType;

typedef struct {
    HashTable hashTable;
    PatriciaNode *root;
} SearchType;

/*void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}*/

char *strcasestr(const char *haystack, const char *needle) {
    if (!*needle) {
        return (char *)haystack; // Se needle é uma string vazia, retorna haystack.
    }

    for (; *haystack; ++haystack) {
        // Compara caracteres de haystack e needle ignorando a diferença entre maiúsculas e minúsculas.
        if (tolower((unsigned char)*haystack) == tolower((unsigned char)*needle)) {
            const char *h, *n;
            for (h = haystack, n = needle; *h && *n; ++h, ++n) {
                if (tolower((unsigned char)*h) != tolower((unsigned char)*n)) {
                    break;
                }
            }
            if (!*n) { // Se a string needle inteira foi encontrada.
                return (char *)haystack;
            }
        }
    }
    return NULL; // Se não encontrou a string needle em haystack.
}

void removePunctuation(char *str) {
    char *src = str, *dst = str;
    while (*src) {
        if (!ispunct((unsigned char)*src)) {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

int countOccurrences(const char *a, const char *b){
    int count = 0;
    size_t lenb = strlen(b);
    const char *p = a;
    while(NULL != (p = strcasestr(p, b))){
        ++count;
        p += lenb;
    }
    return count;
}

void printHashTable(HashTable *hashTable){
    printf("Chaves inseridas na tabela hash:\n");
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode *currentHashNode = hashTable->tableRoot[i];
        while (currentHashNode != NULL) {
            printf("Chave: %s ->", currentHashNode->key);
            InvertedIndex *currentInvertedIndex = currentHashNode->invertedIndexRoot;

            while (currentInvertedIndex != NULL) {
                printf("(Doc: %d, Qtde: %d),", currentInvertedIndex->idDoc, currentInvertedIndex->qtde);
                currentInvertedIndex = currentInvertedIndex->nextInvertedIndex;
            }
            printf("\n");
            
            currentHashNode = currentHashNode->nextHashNode;
        }
    }   
}

/*void printPatricia(PatriciaNode *root){
    printf("Chaves inseridas na tabela Patricia:\n");
    for (int i = 0; i < MAX_BIT * 8; i++) {
        PatriciaNode *current = root;
        while (current != NULL) {
            printf("Chave: %s ->", current->key);
            InvertedIndexPatricia *currentInvertedIndex = current->InvertedIndexPatriciaRoot;

            while (currentInvertedIndex != NULL) {
                printf("(Doc: %d, Qtde: %d),", currentInvertedIndex->idDoc, currentInvertedIndex->qtde);
                currentInvertedIndex = currentInvertedIndex->nextInvertedIndexPatricia;
            }
            printf("\n");
            
            current = current->right;
        }
    }   
}*/

void removeLeadingSpaces(char *str) {
    char *start = str;

    // Encontra o primeiro caractere não espaço
    while (isspace((unsigned char)*start)) {
        start++;
    }

    // Move os caracteres restantes para o início da string
    if (start != str) {
        char *dst = str;
        while (*start) {
            *dst++ = *start++;
        }
        *dst = '\0'; // Finaliza a string
    }
}

void removeFinalDot(char *str) {
    int len = strlen(str);
    // Verifica se a última posição tem um ponto final e, se sim, remove-o
    for (int i = 0; i < len; i++)
    {
        if (str[i] == '.') 
        {
            str[i] = '\0';
        }   

    }
}


void readArquivoFile(char *fileName, SearchType *searchType, FileType *fileType) {
    
    char fullPath[512];
    snprintf(fullPath, sizeof(fullPath), "%s%s", "../Arquivos/ArquivosEntrada/", fileName);
 

    FILE *file = fopen(fullPath, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo interno");
        return;
    }
    //printf("chegou na potion\n");

    fgets(fileType->potionName, sizeof(fileType->potionName), file);
    
    //printf("%s\n", fileType->potionName);

    char ingredientes[1000];
    char *token;
    char *tokens[100];
    fgets(ingredientes, sizeof(ingredientes), file);
    //printf("%s\n", ingredientes);
    int i = 0;

    token = strtok(ingredientes, ";");
    while (token != NULL && i < 100) {
        tokens[i] = malloc((strlen(token) + 1) * sizeof(char));
        if (tokens[i] == NULL) {
            printf("Erro ao alocar memória\n");
        }
        strcpy(tokens[i], token);
        removeLeadingSpaces(tokens[i]);
        removeFinalDot(tokens[i]);
        //printf("%s\n", tokens[i]);
        

        searchType->root = insert(searchType->root, tokens[i]);
        insertHash(&searchType->hashTable, tokens[i], fileType->idDoc);


        //printf("inseriu \n");

        i++;
        token = strtok(NULL, ";");   
    }

    

    char Preparo[1000];
    fgets(Preparo, sizeof(Preparo), file);
    removePunctuation(Preparo);
    
    


    for (int j = 0; j < i; j++)
    {
      
        int timesAppeared = countOccurrences(Preparo, tokens[j]);
        HashNode *currentHashNode = searchHash(&searchType->hashTable, tokens[j]);
        insertInvertedIndexHash(currentHashNode, fileType->idDoc, timesAppeared);
        //insertInvertedIndexPatricia(searchType->root, fileType->idDoc, timesAppeared);

    }
    
   


    token = strtok(ingredientes, ";");


    
    
    
}



void readentradaFile(const char *fileName , SearchType *searchType) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    int numFiles;
    if (fscanf(file, "%d", &numFiles) != 1) {
        printf("Erro ao ler o número de arquivos\n");
        fclose(file);
        return;
    }
    //printf("Número de arquivos: %d\n", numFiles);

    // Adiciona um espaço adicional para o caractere de nova linha no final da string
    FileType *files = malloc(numFiles * sizeof(FileType));
    if (files == NULL) {
        printf("Erro ao alocar memória\n");
        fclose(file);
        return;
    }

    // Limpar o buffer de nova linha que pode ter sido deixado por fscanf
    fgetc(file);

    for (int i = 0; i < numFiles; i++) {
        // Limita a leitura para o tamanho do array
        if (fgets(files[i].fileName, sizeof(files[i].fileName), file) == NULL) {
            printf("Erro ao ler o nome do arquivo\n");
            break;
        }

        // Remove o caractere de nova linha, se houver
        files[i].fileName[strcspn(files[i].fileName, "\n")] = '\0';

        files[i].idDoc = i;
        //printf("Arquivo: %s\n", files[i].fileName);
    }

    for (int i = 0; i < numFiles; i++) {
        readArquivoFile(files[i].fileName, searchType, &files[i]);
        //printf("Nome arquivo: %s, Nome da pocao:%s, idDoc:%d inserido\n", files[i].fileName,files[i].potionName, files[i].idDoc);
    }
    

    free(files);
    fclose(file);
}




int main() {

    
    HashTable hashTable;
    initHashTable(&hashTable);
    PatriciaNode *root = NULL;

    

    SearchType searchType;
    searchType.hashTable = hashTable;
    searchType.root = root;

    
    

    

    char *nomeArquivo = "../Arquivos/entrada.txt";
    readentradaFile(nomeArquivo, &searchType);
    printPatricia(&searchType.root);
    printHashTable(&searchType.hashTable);

    //busca dentro da pratricia
    //printf("Searching for 'Pinch of Unicorn Horn': %s\n", search(searchType.root, "Pinch of Unicorn Horn") ? "Found" : "Not found");
    
    
    return 0;
}
