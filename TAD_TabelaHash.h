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
    struct InvertedIndex *next;
} InvertedIndex;

// Estrutura para os nós da tabela hash
typedef struct HashNode {
    char *key;
    InvertedIndex *invertedIndexRoot;
    struct HashNode *next;
} HashNode;

// Estrutura para a tabela hash
typedef struct {
    HashNode *table[HASH_SIZE];
    TipoPesos p;
} HashTable;

unsigned int hash_function(char *key, TipoPesos p);

HashNode* createHashNode(char *key);

InvertedIndex* createInvertedIndex(int idDoc, int qtde);

void insertInvertedIndex(HashNode *node, int idDoc, int qtde);

void insertHash(HashTable *hashTable, char *key);

HashNode* searchHash(HashTable *hashTable, char *key);

void freeHashTable(HashTable *hashTable);

void GeraPesos(TipoPesos p);

#endif