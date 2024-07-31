#include "TAD_Patricia.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

InvertedIndexPatricia* createInvertedIndexPatricia(int idDoc, int qtde) {
    InvertedIndexPatricia *new = (InvertedIndexPatricia *)malloc(sizeof(InvertedIndexPatricia));
    new->idDoc = idDoc;
    new->qtde = qtde;
    new->nextInvertedIndexPatricia = NULL;

    return new;
}

void insertInvertedIndexPatricia(PatriciaNode *node, int idDoc, int qtde) {
    InvertedIndexPatricia *new = createInvertedIndexPatricia(idDoc, qtde);
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
PatriciaNode* createNode(char *key) {
    PatriciaNode *node = (PatriciaNode *)malloc(sizeof(PatriciaNode));
    if (!node) {
        perror("Failed to allocate memory for PatriciaNode");
        exit(EXIT_FAILURE);
    }
    node->key = strdup(key);
    if (!node->key) {
        perror("Failed to duplicate key string");
        exit(EXIT_FAILURE);
    }
    node->left = NULL;
    node->right = NULL;
    node->InvertedIndexPatriciaRoot = NULL;
    node->bit = 0;  // Pode ser usado como uma flag para indicar se é folha
    return node;
}


// Insere uma chave na árvore
PatriciaNode* insertPatricia(PatriciaNode *root, char *key) {
    if (!root) {
        return createNode(key);
    }

    PatriciaNode *current = root;
    PatriciaNode *parent = NULL;

    // Percorre a árvore até encontrar a posição de inserção
    while (current) {
        parent = current;
        if (strcmp(key, current->key) < 0) {
            current = current->left;
        } else if (strcmp(key, current->key) > 0) {
            current = current->right;
        } else {
            // A chave já existe
            return root;
        }
    }

    // Cria o novo nó
    PatriciaNode *newNode = createNode(key);

    // Insere o novo nó na árvore
    if (strcmp(key, parent->key) < 0) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    return root;
}


// Procura por uma chave na árvore
PatriciaNode* searchPatricia(PatriciaNode *root, char *key) {
    PatriciaNode *current = root;
    while (current) {
        if (strcmp(key, current->key) < 0) {
            current = current->left;
        } else if (strcmp(key, current->key) > 0) {
            current = current->right;
        } else {
            return current;
        }
    }

    return NULL;
}

// Libera a memória da árvore
void freePatricia(PatriciaNode *root) {
    if (!root) {
        return;
    }

    freePatricia(root->left);
    freePatricia(root->right);
    free(root->key);
    free(root);
}

/*int main() {
    PatriciaNode *root = NULL;
    root = insertPatricia(root, "Matheus");
    root = insertPatricia(root, "Daniel");
    root = insertPatricia(root, "Otavio");
    root = insertPatricia(root, "ZEZE dasd");  

    printf("Searching for 'apple': %s\n", searchPatricia(root, "Otavio") ? "Found" : "Not found");
    printf("Searching for 'ZEZE': %s\n", searchPatricia(root, "ZEZE dasd") ? "Found" : "Not found");
    printf("Searching for 'Otavio': %s\n", searchPatricia(root, "Daniel") ? "Found" : "Not found");
    printf("Searching for 'orange': %s\n", searchPatricia(root, "orange") ? "Found" : "Not found");

    freePatricia(root);
    return 0;
}*/
