#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define HASH_SIZE 100  // Tamanho da tabela hash
#define N 100  // Número de pesos

// Definir TipoPesos
typedef int TipoPesos[N];

// Estrutura para os nós da tabela hash
typedef struct HashNode {
    char *key;
    int idDoc;
    int qtde;
    struct HashNode *next;
} HashNode;

// Estrutura para a tabela hash
typedef struct {
    HashNode *table[HASH_SIZE];
    TipoPesos p;
} HashTable;

unsigned int hash_function(char *key) {}

HashNode* createHashNode(char *key, int idDoc) {}

void insertHash(HashTable *hashTable, char *key, int idDoc) {}

HashNode* searchHash(HashTable *hashTable, char *key) {}

void freeHashTable(HashTable *hashTable) {}

void GeraPesos(TipoPesos p) {}