#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define HASH_SIZE 100  // Tamanho da tabela hash
#define N 100  // Número de pesos

// Definir TipoPesos
typedef int TipoPesos[N];

// Estrutura para os nós da tabela hash
typedef struct HashNode {
    char *key;
    int idDoc;
    int qtde;
    struct HashNode *next;
} HashNode;

// Estrutura para a tabela hash
typedef struct {
    HashNode *table[HASH_SIZE];
    TipoPesos p;
} HashTable;

// Função de hash simples
unsigned int hash_function(char *key, TipoPesos p) {
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
    unsigned int hash = hash_function(key, hashTable->p);
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
void GeraPesos(TipoPesos p) {
    int i;
    struct timeval semente;
    // Utilizar o tempo como semente para a função srand()
    gettimeofday(&semente, NULL);
    srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
    for (i = 0; i < N; i++)
        p[i] = 1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0));
}

int main() {
    // Exemplo de uso da tabela hash
    HashTable hashTable;
    memset(&hashTable, 0, sizeof(HashTable));

    GeraPesos(hashTable.p);

    insertHash(&hashTable, "apple", 1);
    insertHash(&hashTable, "banana", 2);
    insertHash(&hashTable, "orange", 3);

    HashNode *result = searchHash(&hashTable, "banana");
    if (result) {
        printf("Found 'banana' in document %d\n", result->idDoc);
    } else {
        printf("'banana' not found\n");
    }

    freeHashTable(&hashTable);

    return 0;
}
