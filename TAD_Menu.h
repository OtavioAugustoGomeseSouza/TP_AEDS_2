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

void CalculodeWi(SearchType *searchType, TermoBusca *termoBusca, int numTermos);

//void buscar(SearchType *searchType, char *ingrediente);