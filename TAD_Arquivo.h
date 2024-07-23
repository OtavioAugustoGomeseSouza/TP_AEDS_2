#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TAD_TabelaHash.h"
#include "TAD_Patricia.h"

typedef struct {
    char fileName[256];
    char potionName[256]; // Aloca memória suficiente para armazenar o nome do arquivo
    int idDoc;
} FileType;

typedef struct {
    HashTable hashTable;
    PatriciaNode *root;
} SearchType;

void readArquivoFile(char *fileName, SearchType *searchType, FileType *fileType);

void readentradaFile(const char *fileName , SearchType *searchType);

