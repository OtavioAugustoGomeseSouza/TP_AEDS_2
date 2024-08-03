#ifndef TAD_PATRICIA_H
#define TAD_PATRICIA_H

typedef struct {
	int idDoc;
	int qtde;
    struct InvertedIndexPatricia *nextInvertedIndexPatricia;
} InvertedIndexPatricia;

typedef struct PatriciaNode {
    char *key;
    struct PatriciaNode *left;
    struct PatriciaNode *right;
    InvertedIndexPatricia *InvertedIndexPatriciaRoot;
    int bit;  // Pode ser usado como uma flag
    long long seeking_count;
} PatriciaNode;


PatriciaNode* createNode(char *key); 

PatriciaNode* insertPatricia(PatriciaNode *root, char *key) ;

PatriciaNode* searchPatricia(PatriciaNode *root, char *key);

void freePatricia(PatriciaNode *root);

void insertInvertedIndexPatricia(PatriciaNode *node, int idDoc, int qtde);

InvertedIndexPatricia* createInvertedIndexPatricia(int idDoc, int qtde);

void insertInvertedIndexPatricia(PatriciaNode *node, int idDoc, int qtde);

void printPatricia(PatriciaNode *root);

int countDocumentsWithTermPatricia(PatriciaNode *node);


#endif