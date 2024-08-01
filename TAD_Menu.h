#include "TAD_Arquivo.h"

typedef struct {
    char ingrediente[256];
} TermoBusca;

typedef struct {
    double wi;
    int idDoc;
}RelevanciaWi;

void menu(char *nomeArquivo, SearchType *searchType);

int getInt();

void CalculodeRelevancia(SearchType *searchType, TermoBusca *termoBusca, int numTermos);

//void buscar(SearchType *searchType, char *ingrediente);