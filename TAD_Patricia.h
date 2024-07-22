#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BIT 128  // Número máximo de bits de uma chave (ajustável conforme necessário)

typedef struct PatriciaNode {
    char *key;
    int bit;
    struct PatriciaNode *left;
    struct PatriciaNode *right;
} PatriciaNode;


PatriciaNode* createNode(char *key, int bit); 

int bitCompare(char *key, int bit); 

int firstDifferentBit(char *key1, char *key2);

PatriciaNode* insert(PatriciaNode *root, char *key) ;

int search(PatriciaNode *root, char *key);

void freePatricia(PatriciaNode *root);