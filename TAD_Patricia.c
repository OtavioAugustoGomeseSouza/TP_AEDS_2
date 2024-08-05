#include "TAD_Patricia.h"

// Cria um novo nó da árvore Patricia
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
    node->seeking_count = 0;
    return node;
}

// Insere uma chave na árvore Patricia
PatriciaNode* insertPatricia(PatriciaNode *root, char *key) {
    if (root == NULL) {
        return createNode(key);
    }

    PatriciaNode *current = root;
    PatriciaNode *parent = NULL;
    PatriciaNode *newNode;

    while (current) {
        parent = current;
        if (strcmp(key, current->key) < 0) {
            current = current->left;
        } else if (strcmp(key, current->key) > 0) {
            current = current->right;
        } else {
            // A chave já existe; não insere novamente
            return root;
        }
    }

    newNode = createNode(key);

    if (strcmp(key, parent->key) < 0) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    return root;
}

// Procura por uma chave na árvore Patricia
PatriciaNode* searchPatricia(PatriciaNode *root, char *key) {
    PatriciaNode *current = root;
    long long seeking_count = 0;

    while (current) {
        seeking_count++;
        if (strcmp(key, current->key) < 0) {
            current = current->left;
        } else if (strcmp(key, current->key) > 0) {
            current = current->right;
        } else {
            current->seeking_count = seeking_count;
            return current;
        }
    }

    return NULL;
}

// Libera a memória da árvore Patricia
void freePatricia(PatriciaNode *root) {
    if (!root) {
        return;
    }

    freePatricia(root->left);
    freePatricia(root->right);
    free(root->key);

    InvertedIndexPatricia *temp;
    while (root->InvertedIndexPatriciaRoot) {
        temp = root->InvertedIndexPatriciaRoot;
        root->InvertedIndexPatriciaRoot = root->InvertedIndexPatriciaRoot->next;
        free(temp);
    }

    free(root);
}

// Cria um novo índice invertido
InvertedIndexPatricia* createInvertedIndexPatricia(int idDoc, int qtde) {
    InvertedIndexPatricia *new = (InvertedIndexPatricia *)malloc(sizeof(InvertedIndexPatricia));
    if (!new) {
        perror("Failed to allocate memory for InvertedIndexPatricia");
        exit(EXIT_FAILURE);
    }
    new->idDoc = idDoc;
    new->qtde = qtde;
    new->next = NULL;
    return new;
}

// Insere um índice invertido em um nó
void insertInvertedIndexPatricia(PatriciaNode *node, int idDoc, int qtde) {
    InvertedIndexPatricia *new = createInvertedIndexPatricia(idDoc, qtde);
    InvertedIndexPatricia *current = node->InvertedIndexPatriciaRoot;
    if (current == NULL) {
        node->InvertedIndexPatriciaRoot = new;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new;
    }
}

// Imprime a árvore Patricia
void printPatricia(PatriciaNode *root) {
    if (!root) {
        return;
    }

    printPatricia(root->left);

    printf("Key: %s ->", root->key);
    printf(" (Seeking: %lld)", root->seeking_count);

    InvertedIndexPatricia *currentInvertedIndex = root->InvertedIndexPatriciaRoot;

    while (currentInvertedIndex != NULL) {
        printf(" (Doc: %d, Qtde: %d),", currentInvertedIndex->idDoc, currentInvertedIndex->qtde);
        currentInvertedIndex = currentInvertedIndex->next;
    }
    printf("\n");

    printPatricia(root->right);
}

// Conta o número de documentos com o termo na árvore Patricia
int countDocumentsWithTermPatricia(PatriciaNode *node) {
    if (node == NULL || node->InvertedIndexPatriciaRoot == NULL) {
        return 0;
    }

    int count = 0;
    InvertedIndexPatricia *aux = node->InvertedIndexPatriciaRoot;

    while (aux != NULL) {
        if (aux->qtde > 0) {
            count++;
        }
        aux = aux->next;
    }

    return count;
}