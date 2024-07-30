#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "TAD_TabelaHash.h"

#define HASH_SIZE 100  // Tamanho da tabela hash
#define N 100  // Número de pesos

// Definir TipoPesos
typedef int TipoPesos[N];

// Função de hash simples
unsigned int hash_function(char *key, TipoPesos *p) {
    printf("entrou na função hash_function\n");
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = hash + key[i] * (*p)[i];
        printf("%d\n", (*p)[i]);
    }
    return hash % HASH_SIZE;
}

// Cria um novo nó da tabela hash
HashNode* createHashNode(char *key) {
    HashNode *node = (HashNode *)malloc(sizeof(HashNode));
    if (node) {
        node->key = strdup(key);
        node->invertedIndexRoot = NULL;
        node->nextHashNode = NULL;
        node->hashPosição = 0;
    }
    return node;
}

InvertedIndex* createInvertedIndex(int idDoc, int qtde) {
    InvertedIndex *new = (InvertedIndex *)malloc(sizeof(InvertedIndex));
    new->idDoc = idDoc;
    new->qtde = qtde;
    new->next = NULL;

    return new;
}

void insertInvertedIndex(HashNode *node, int idDoc, int qtde) {
    InvertedIndex *new = createInvertedIndex(idDoc, qtde);
    InvertedIndex *current = node->invertedIndexRoot;

    if (current == NULL) {
        node->invertedIndexRoot = new;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new;
    }
}

// Inserção na tabela hash
void insertHash(HashTable *hashTable, char *key) {
    printf("entrou na função inserir hash\n");
   
    unsigned int hash = hash_function(key, hashTable->p);

    HashNode *newNode = createHashNode(key);
    printf("entrou no primeiro if\n");
    /*if (searchHash(hashTable, key) == NULL) {
        newNode->hashPosição = hash;
    } else {
        //contador
    }*/

    
}

// Busca na tabela hash
HashNode* searchHash(HashTable *hashTable, char *key) {
    unsigned int hash = hash_function(key, hashTable->p);
    HashNode *current = hashTable->table[hash];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

// Libera a memória da tabela hash
void freeHashTable(HashTable *hashTable) {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode *current = hashTable->table[i];
        while (current != NULL) {
            HashNode *temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
}

// Função para gerar pesos aleatórios
TipoPesos* GeraPesos() {

    struct timeval semente;
    TipoPesos *p = (TipoPesos *)malloc(sizeof(TipoPesos));
    // Utilizar o tempo como semente para a função srand()
    gettimeofday(&semente, NULL);
    srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
    for (int i = 0; i < N; i++)
        (*p)[i] = 1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0));

}   

/*int main() {
    // Exemplo de uso da tabela hash
    HashTable hashTable;
    memset(&hashTable, 0, sizeof(HashTable));

    GeraPesos(hashTable.p);

    insertHash(&hashTable, "apple");
    insertHash(&hashTable, "banana");
    insertHash(&hashTable, "orange");

    HashNode *result = searchHash(&hashTable, "banana");
    if (result) {
    printf("Found 'banana' with key: %s\n", result->key);
    } else {
        printf("'banana' not found\n");
    }


    freeHashTable(&hashTable);

    return 0;
}*/
