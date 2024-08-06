#include "TAD_TabelaHash.h"

#define HASH_SIZE 100  // Tamanho da tabela hash
#define N 100  // Número de pesos

//Definir TipoPesos
typedef int TipoPesos[N];

void initHashTable(HashTable *hashTable) {
    for (int i = 0; i < HASH_SIZE; i++) {
        hashTable->tableRoot[i] = NULL;
    }
    hashTable->p = GeraPesos();
}

//Função de hash simples
unsigned int hash_function(char *key, TipoPesos *p) {  
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = hash + key[i] * (*p)[i];
    }
    return hash % HASH_SIZE;
}

//Cria um novo nó da tabela hash
HashNode* createHashNode(char *key) {
    HashNode *node = (HashNode *)malloc(sizeof(HashNode));
    if (node) {
        node->key = strdup(key);
        node->invertedIndexRoot = NULL;
        node->nextHashNode = NULL;
        node->hashValue = 0;
        node->colisoes = 0;
    }
    return node;
}

//Cria um novo index invertido
InvertedIndex* createInvertedIndex(int idDoc, int qtde) {
    InvertedIndex *new = (InvertedIndex *)malloc(sizeof(InvertedIndex));
    new->idDoc = idDoc;
    new->qtde = qtde;
    new->nextInvertedIndex = NULL;

    return new;
}

//Insere um index invertido na tabela hash
void insertInvertedIndexHash(HashNode *node, int idDoc, int qtde) {
    InvertedIndex *new = createInvertedIndex(idDoc, qtde);
    InvertedIndex *current = node->invertedIndexRoot;

    if (current == NULL) {
        node->invertedIndexRoot = new;
    } else {
        while (current->nextInvertedIndex != NULL) {
            current = current->nextInvertedIndex;
        }
        current->nextInvertedIndex = new;
    }
}

//Busca um index invertido na tabela hash
InvertedIndex* searchInvertedIndex(HashNode *node, int idDoc) {
    InvertedIndex *current = node->invertedIndexRoot;

    while (current != NULL) {
        if (current->idDoc == idDoc) {
            return current;
        }
        current = current->nextInvertedIndex;
    }

    return NULL;
}

//Inserção na tabela hash
void insertHash(HashTable *hashTable, char *key, int idDoc) {
    unsigned int hash = hash_function(key, hashTable->p);
    HashNode *currentHashNode = hashTable->tableRoot[hash];

    while (currentHashNode != NULL) {
        if (strcmp(currentHashNode->key, key) == 0) {
            return;
        }
        currentHashNode = currentHashNode->nextHashNode;
        //colisoes++;
    }
    //currentHashNode->colisoes = colisoes;
    HashNode *newNode = createHashNode(key);
    newNode->nextHashNode = hashTable->tableRoot[hash];
    hashTable->tableRoot[hash] = newNode;
}

//Busca na tabela hash
HashNode* searchHash(HashTable *hashTable, char *key) {
    unsigned int hash = hash_function(key, hashTable->p);
    HashNode *current = hashTable->tableRoot[hash];
    long long colisoes=0;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current;
        }
        //contador de colisoes
        colisoes++;
        //atualiza o campo de colisões
        current->colisoes = colisoes;
        current = current->nextHashNode;
    }
    
    return NULL;
}

//Libera a memória da tabela hash
void freeHashTable(HashTable *hashTable) {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode *current = hashTable->tableRoot[i];
        while (current != NULL) {
            HashNode *temp = current;
            current = current->nextHashNode;
            free(temp->key);
            free(temp);
        }
    }
    free(hashTable->p);
}

//Função para gerar pesos aleatórios
TipoPesos* GeraPesos() {

    struct timeval semente;
    TipoPesos *p = (TipoPesos *)malloc(sizeof(TipoPesos));
    //Utilizar o tempo como semente para a função srand()
    gettimeofday(&semente, NULL);
    srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
    for (int i = 0; i < N; i++)
        (*p)[i] = 1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0));

}   

int compareStrings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}


void printHashTable(HashTable *hashTable){
    //Contar número de chaves na tabela hash
    int count = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode *current = hashTable->tableRoot[i];
        while (current != NULL) {
            count++;
            current = current->nextHashNode;
        }
    }

    //Armazenar chaves em um array
    char **keys = (char **)malloc(count * sizeof(char *));
    int index = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode *current = hashTable->tableRoot[i];
        while (current != NULL) {
            keys[index++] = current->key;
            current = current->nextHashNode;
        }
    }

    
    //Ordenar o array de chaves
    qsort(keys, count, sizeof(char *), compareStrings);



    //Imprimir chaves e índices invertidos em ordem alfabética
    printf("Chaves inseridas na tabela hash em ordem alfabética:\n");
    for (int i = 0; i < count; i++) {
        HashNode *node = searchHash(hashTable, keys[i]);
        printf("Chave: %s ->", node->key);
       printf(" (Colisoes: %d)", node->colisoes);
        InvertedIndex *currentInvertedIndex = node->invertedIndexRoot;
        while (currentInvertedIndex != NULL) {
            printf(" (Doc: %d, Qtde: %d)", currentInvertedIndex->idDoc, currentInvertedIndex->qtde);
            currentInvertedIndex = currentInvertedIndex->nextInvertedIndex;
        }
        printf("\n");
    }

    //Liberar memória alocada para o array de chaves
    free(keys);  
}

//Conta quantos documentos tem a palavra
int countDocumentsWithTermHash(HashNode *node) {
    if (node == NULL || node->invertedIndexRoot == NULL) {
        return 0;
    }

    int count = 0;
    InvertedIndex *aux = node->invertedIndexRoot;

    while (aux != NULL) {
        if (aux->qtde > 0) {  //Verifica se o termo aparece no documento
            count++;
        }
        aux = aux->nextInvertedIndex;
    }

    return count;
}
