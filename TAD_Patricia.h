#ifndef TAD_PATRICIA_H
#define TAD_PATRICIA_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#define D 8 

typedef struct InvertedIndexPatricia {
    int idDoc;
    int qtde;
    struct InvertedIndexPatricia *nextInvertedIndexPatricia;
} InvertedIndexPatricia;

typedef char* TipoChave;
typedef unsigned int TipoIndexAmp;
typedef unsigned char TipoDib;
typedef enum {
    Interno, Externo
} TipoNo;

typedef struct TipoPatNo* TipoArvore;
typedef struct TipoPatNo {
    TipoNo nt;
    union {
        struct {
            TipoIndexAmp Index;
            char Char_maior;
            TipoArvore Esq, Dir;
        } NInterno;
        TipoChave Chave;
    } NO;
    InvertedIndexPatricia *InvertedIndexPatriciaRoot;
} TipoPatNo;

TipoDib Bit(TipoIndexAmp i, TipoChave k);
short EExterno(TipoArvore p);
TipoArvore CriaNoInt(int i,char Char_maior, TipoArvore Esq, TipoArvore Dir);
TipoArvore CriaNoExt(TipoChave k);
TipoArvore Pesquisa(TipoChave k, TipoArvore t);
TipoArvore InsereEntre(TipoChave k, TipoArvore t, int i);
TipoArvore Insere(TipoChave k, TipoArvore t);
InvertedIndexPatricia* createInvertedIndexPatricia(int idDoc, int qtde);
void insertInvertedIndexPatricia(TipoArvore node, int idDoc, int qtde);
void ImprimeArvoreOrdemAlfabeticaComSeekings(TipoArvore t);
int countDocumentsWithTermPatricia(TipoArvore node);

#endif