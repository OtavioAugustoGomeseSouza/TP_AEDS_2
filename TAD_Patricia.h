#ifndef TAD_PATRICIA_H
#define TAD_PATRICIA_H


#define D 8   /* depende de TipoChave */

typedef struct InvertedIndexPatricia {
    int idDoc;
    int qtde;
    struct InvertedIndexPatricia *nextInvertedIndexPatricia;
} InvertedIndexPatricia;

typedef char* TipoChave; /* a definir, dependendo da aplicacao */
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
void ImprimeArvore(TipoArvore t, int nivel);
InvertedIndexPatricia* createInvertedIndexPatricia(int idDoc, int qtde);
void insertInvertedIndexPatricia(TipoPatNo *node, int idDoc, int qtde);
void ImprimeArvore(TipoArvore t, int nivel);
int countDocumentsWithTerm(TipoArvore node);

#endif