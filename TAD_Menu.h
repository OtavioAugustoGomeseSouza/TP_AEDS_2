#include "TAD_Arquivo.h"
#include <math.h>

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

void CalculodeWiPatricia(SearchType *searchType, TermoBusca *termoBusca, int numTermos, FileType *ListaArquivos);

void CalculodeWiHash(SearchType *searchType, TermoBusca *termoBusca, int numTermos, FileType *ListaArquivos);

void CalculoRi(SearchType *searchType, TermoBusca *termoBusca, RelevanciaRi *r, SomatorioWi *s, FileType *ListaArquivos)
//void buscar(SearchType *searchType, char *ingrediente);