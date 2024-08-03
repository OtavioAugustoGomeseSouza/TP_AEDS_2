#include "TAD_Arquivo.h"

typedef struct {
    char ingrediente[256];
} TermoBusca;

typedef struct {
    double wi;
    int idDoc;
}RelevanciaWi;

typedef struct {
    RelevanciaWi *w;
    double soma;
} SomatorioWi;

typedef struct {
    SomatorioWi *s;
    double ri;
} RelevanciaRi;

void menu(char *nomeArquivo, SearchType *searchType);

int getInt();

void CalculodeRelevanciaPatricia(SearchType *searchType, TermoBusca *termoBusca, int numTermos, FileType *ListaArquivos);

void CalculodeRelevanciaHash(SearchType *searchType, TermoBusca *termoBusca, int numTermos, FileType *ListaArquivos);

//void buscar(SearchType *searchType, char *ingrediente);