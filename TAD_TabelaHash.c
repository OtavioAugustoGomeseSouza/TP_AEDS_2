#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TAD_Patricia.h"
#include "TAD_TabelaHash.h"


// Função de hash simples
unsigned int hash_function(char *key) {
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = 31 * hash + key[i];
    }
    return hash % HASH_SIZE;
}

// Cria um novo nó da tabela hash
HashNode* createHashNode(char *key, int idDoc) {
    HashNode *node = (HashNode *)malloc(sizeof(HashNode));
    if (node) {
        node->key = strdup(key);
        node->idDoc = idDoc;
        node->qtde = 1;
        node->next = NULL;
    }
    return node;
}

// Inserção na tabela hash
void insertHash(HashTable *hashTable, char *key, int idDoc) {
    unsigned int hash = hash_function(key);
    HashNode *newNode = createHashNode(key, idDoc);
    
    if (hashTable->table[hash] == NULL) {
        hashTable->table[hash] = newNode;
    } else {
        HashNode *current = hashTable->table[hash];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Busca na tabela hash
HashNode* searchHash(HashTable *hashTable, char *key) {
    unsigned int hash = hash_function(key);
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