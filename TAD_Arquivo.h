#ifndef TAD_ARQUIVO_H
#define TAD_ARQUIVO_H
#include "TAD_TabelaHash.h"
#include "TAD_Patricia.h"
#include <ctype.h>

typedef struct {
    char fileName[256];
    char potionName[256]; // Aloca memória suficiente para armazenar o nome do arquivo
    int idDoc;
    int ni;
} FileType;

typedef struct {
    int numArq;
    HashTable hashTable;
    PatriciaNode *root;
} SearchType;



FileType* readentradaFile(const char *fileName , SearchType *searchType);

void removeLeadingSpaces(char *str);

void removeFinalDot(char *str);

void readArquivoFile(char *fileName, SearchType *searchType, FileType *fileType);

char *strcasestr(const char *haystack, const char *needle);

void removePunctuation(char *str);

int countOccurrences(const char *a, const char *b);

void readAllFiles(const char *fileName, FileType* files ,SearchType *searchType);

#endif

