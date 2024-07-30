#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TAD_Patricia.h"

void insertInvertedIndexPatricia(PatriciaNode *node, int idDoc, int qtde) {
    InvertedIndexPatricia *new = createInvertedIndex(idDoc, qtde);
    InvertedIndexPatricia *current = node->InvertedIndexPatriciaRoot;

    if (current == NULL) {
        node->InvertedIndexPatriciaRoot = new;
    } else {
        while (current->nextInvertedIndexPatricia != NULL) {
            current = current->nextInvertedIndexPatricia;
        }
        current->nextInvertedIndexPatricia = new;
    }
}
// Cria um novo nó da árvore
PatriciaNode* createNode(char *key, int bit) {
    PatriciaNode *node = (PatriciaNode *)malloc(sizeof(PatriciaNode));
    node->key = strdup(key);
    node->bit = bit;
    node->left = node;
    node->right = node;
    return node;
}

// Compara os bits de duas strings
int bitCompare(char *key, int bit) {
    if (bit < 0 || bit >= MAX_BIT * 8) {
        return 0;
    }
    int byte = bit / 8;
    int mask = 1 << (7 - (bit % 8));
    return (key[byte] & mask) != 0;
}

// Encontra o primeiro bit diferente entre duas strings
int firstDifferentBit(char *key1, char *key2) {
    for (int i = 0; i < MAX_BIT * 8; i++) {
        if (bitCompare(key1, i) != bitCompare(key2, i)) {
            return i;
        }
    }
    return -1;  // Todas as chaves são iguais (ou uma é prefixo da outra)
}

// Insere uma chave na árvore
PatriciaNode* insert(PatriciaNode *root, char *key) {
    if (!root) {
        return createNode(key, 0);
    }

    PatriciaNode *current = root;
    PatriciaNode *parent = NULL;
    int bit = 0;

    // Encontra o nó a ser substituído
    while (current->bit > bit) {
        parent = current;
        if (bitCompare(key, current->bit)) {
            current = current->right;
        } else {
            current = current->left;
        }
        bit = current->bit;
    }

    // Encontra o primeiro bit diferente
    int diffBit = firstDifferentBit(key, current->key);
    if (diffBit == -1) {
        // A chave já existe
        return root;
    }

    // Cria um novo nó
    PatriciaNode *newNode = createNode(key, diffBit);
    if (bitCompare(key, diffBit)) {
        newNode->left = current;
        newNode->right = newNode;
    } else {
        newNode->left = newNode;
        newNode->right = current;
    }

    // Conecta o novo nó à árvore
    if (parent == NULL) {
        return newNode;
    }
    if (bitCompare(key, parent->bit)) {
        parent->right = newNode;
    } else {
        parent->left = newNode;
    }

    return root;
}

// Procura por uma chave na árvore
PatriciaNode* search(PatriciaNode *root, char *key) {
    if (!root) {
        return 0;
    }

    PatriciaNode *current = root;
    int bit = 0;

    while (current->bit > bit) {
        if (bitCompare(key, current->bit)) {
            current = current->right;
        } else {
            current = current->left;
        }
        bit = current->bit;
    }

    if (strcmp(current->key, key) == 0)
    {
        return current;
    }else{
        return NULL;
    }
     
}

// Libera a memória da árvore
void freePatricia(PatriciaNode *root) {
    if (root) {
        if (root->left != root) {
            freePatricia(root->left);
        }
        if (root->right != root) {
            freePatricia(root->right);
        }
        free(root->key);
        free(root);
    }
}

/*int main() {
    PatriciaNode *root = NULL;
    root = insert(root, "Matheus");
    root = insert(root, "Daniel");
    root = insert(root, "Otavio");
    root = insert(root, "ZEZE dasd");  

    printf("Searching for 'apple': %s\n", search(root, "Otavio") ? "Found" : "Not found");
    printf("Searching for 'ZEZE': %s\n", search(root, "ZEZE dasd") ? "Found" : "Not found");
    printf("Searching for 'Otavio': %s\n", search(root, "Daniel") ? "Found" : "Not found");
    printf("Searching for 'orange': %s\n", search(root, "orange") ? "Found" : "Not found");

    freePatricia(root);
    return 0;
}*/
