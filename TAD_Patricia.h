#ifndef TAD_PATRICIA_H
#define TAD_PATRICIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct InvertedIndexPatricia {
    int idDoc;
    int qtde;
    struct InvertedIndexPatricia *next;
} InvertedIndexPatricia;

typedef struct PatriciaNode {
    char *key;  // A chave armazenada no nó (prefixo)
    struct PatriciaNode *left;  // Filho à esquerda
    struct PatriciaNode *right; // Filho à direita
    InvertedIndexPatricia *InvertedIndexPatriciaRoot; // Lista de índices invertidos
    long long seeking_count; // Contador de buscas
} PatriciaNode;

// Funções para a árvore Patricia
PatriciaNode* createNode(char *key);
PatriciaNode* insertPatricia(PatriciaNode *root, char *key);
PatriciaNode* searchPatricia(PatriciaNode *root, char *key);
void freePatricia(PatriciaNode *root);
void insertInvertedIndexPatricia(PatriciaNode *node, int idDoc, int qtde);
InvertedIndexPatricia* createInvertedIndexPatricia(int idDoc, int qtde);
void printPatricia(PatriciaNode *root);
int countDocumentsWithTermPatricia(PatriciaNode *node);

#endif
