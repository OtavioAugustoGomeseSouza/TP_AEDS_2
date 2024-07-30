#ifndef TAD_TABELAHASH_H
#define TAD_TABELAHASH_H

#define HASH_SIZE 100  // Tamanho da tabela hash
#define N 100  // Número de pesos

// Definir TipoPesos
typedef int TipoPesos[N];

//Estrutura índices invertidos
typedef struct {
	int idDoc;
	int qtde;
    struct InvertedIndex *nextInvertedIndex;
} InvertedIndex;

// Estrutura para os nós da tabela hash
typedef struct HashNode {
    char *key;
    int hashValue;
    InvertedIndex *invertedIndexRoot; //aponta horizontalmente para o primeiro elemento da lista invertida
    struct HashNode *nextHashNode;
} HashNode;

// Estrutura para a tabela hash 
typedef struct {
    HashNode *tableRoot[HASH_SIZE]; //aponta verticalmente para o primeiro elemento da tabela hash 
    TipoPesos *p;
} HashTable;

unsigned int hash_function(char *key, TipoPesos *p);

HashNode* createHashNode(char *key);

InvertedIndex* createInvertedIndex(int idDoc, int qtde);

void insertInvertedIndex(HashNode *node, int idDoc, int qtde);

void insertHash(HashTable *hashTable, char *key);

HashNode* searchHash(HashTable *hashTable, char *key);

void freeHashTable(HashTable *hashTable);

TipoPesos* GeraPesos();

void initHashTable(HashTable *hashTable);

#endif