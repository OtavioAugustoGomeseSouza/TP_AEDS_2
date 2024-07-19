#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TAD_Patricia.h"

#define MAX_BIT 128  // Número máximo de bits de uma chave (ajustável conforme necessário)
#define HASH_SIZE 10007  // Tamanho da tabela hash (um número primo)

typedef struct HashNode {
    char *key;
    int idDoc;
    int qtde;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode *table[HASH_SIZE];
} HashTable;

unsigned int hash_function(char *key) {}

HashNode* createHashNode(char *key, int idDoc) {}

void insertHash(HashTable *hashTable, char *key, int idDoc) {}

HashNode* searchHash(HashTable *hashTable, char *key) {}

void freeHashTable(HashTable *hashTable) {}