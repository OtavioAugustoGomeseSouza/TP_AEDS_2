#include "TAD_Patricia.h"

//Cria um novo index invertido
InvertedIndexPatricia* createInvertedIndexPatricia(int idDoc, int qtde) {
    InvertedIndexPatricia *new = (InvertedIndexPatricia *)malloc(sizeof(InvertedIndexPatricia));
    new->idDoc = idDoc;
    new->qtde = qtde;
    new->nextInvertedIndexPatricia = NULL;
    return new;
}

//Função para inserir um índice invertido na raiz do nó
void insertInvertedIndexPatricia(TipoArvore node, int idDoc, int qtde) {
    InvertedIndexPatricia *new = createInvertedIndexPatricia(idDoc, qtde);
    InvertedIndexPatricia *current = node->InvertedIndexPatriciaRoot;

    if (current == NULL) {
        node->InvertedIndexPatriciaRoot = new;
    } else {
        while (current->nextInvertedIndexPatricia != NULL) {
        current = current->nextInvertedIndexPatricia;
        }
        current->nextInvertedIndexPatricia = new;
    }
}

short EExterno(TipoArvore p)
{ //Verifica se p é um nodo externo
  return (p->nt == Externo);
}

//Cria um nó interno
TipoArvore CriaNoInt(int i,char Char_maior, TipoArvore Esq, TipoArvore Dir)
{
  TipoArvore p = (TipoArvore)malloc(sizeof(TipoPatNo));
  p->nt = Interno; 
  p->NO.NInterno.Index = i;
  p->NO.NInterno.Char_maior = Char_maior;
  p->NO.NInterno.Esq = Esq;
  p->NO.NInterno.Dir = Dir;
  return p;
} 

//Cria um nó externo
TipoArvore CriaNoExt(TipoChave k)
{
  TipoArvore p = (TipoArvore)malloc(sizeof(TipoPatNo));
  p->nt = Externo; 
  p->InvertedIndexPatriciaRoot = NULL;
  p->NO.Chave = strdup(k);  //Aloca memória para a string
  return p;
}  

//Pesquisa na árvore Patricia e retorna o nó contem a chave buscada
TipoArvore Pesquisa(TipoChave k, TipoArvore t)
{
  if (EExterno(t)) 
  {
    //return t;
    if (strcmp(k, t->NO.Chave) == 0)
    {
        //printf("chave encontrada %s\n",k);
        return t;
    }
     else{
        //printf("chave nao encontrada %s\n",k);
        return NULL;
     }
      
  }
   
  if (k[t->NO.NInterno.Index] < t->NO.NInterno.Char_maior) 
    return Pesquisa(k, t->NO.NInterno.Esq);
  else 
    return Pesquisa(k, t->NO.NInterno.Dir);
} 

//Percorre a arvore e encontra a posição adequada para inserir os novos nós internos e externos
TipoArvore InsereEntre(TipoChave k, TipoArvore t, int i)
{
  TipoArvore p;
    if (EExterno(t))
    { //cria um novo nodo externo
        p = CriaNoExt(k);
        char char_maior = (k[i] > t->NO.Chave[i]) ? k[i] : t->NO.Chave[i]; //Assume k tem um caractere na posição i
        if (k[i] > t->NO.Chave[i]) 
            return CriaNoInt(i, char_maior, t, p);
        else 
            return CriaNoInt(i, char_maior, p, t);
    } 
    else 
    {
        if (k[t->NO.NInterno.Index] < t->NO.NInterno.Char_maior)
            t->NO.NInterno.Esq = InsereEntre(k, t->NO.NInterno.Esq, i);
        else
            t->NO.NInterno.Dir = InsereEntre(k, t->NO.NInterno.Dir, i);
        return t;
    }

}

//Percorre a arvore ate encontrar o no externo e verifica se a chave já existe, caso n o exista insere a chave
TipoArvore Insere(TipoChave k, TipoArvore t)
{
    //printf("inserindo %s\n", k);
    if (t == NULL) 
        return CriaNoExt(k);
    else 
    {
        TipoArvore p = t;
        TipoArvore p_ultimo =t;
        while (!EExterno(p)) 
        {
            if (k[p->NO.NInterno.Index] >= p->NO.NInterno.Char_maior)
            {
                p = p->NO.NInterno.Dir;
            }
            else if (k[p->NO.NInterno.Index] < p->NO.NInterno.Char_maior)
                {
                    p = p->NO.NInterno.Esq;
                }
            else 
                p = p->NO.NInterno.Dir;
        }
        //acha o primeiro caractere diferente
        int i = 0;
        while (k[i] == p->NO.Chave[i])
            i++;
        if (strcoll(k, p->NO.Chave) == 0)
        { 
            return t; 
        } 
        else
            return InsereEntre(k, t, i);
    }
}

//Conta quantos documentos tem a palavra
int countDocumentsWithTermPatricia(TipoArvore node) {
   // printf("countDocumentsWithTermPatricia\n");
    if (node == NULL || node->InvertedIndexPatriciaRoot == NULL) {
        return 0;
    }

    int count = 0;
    InvertedIndexPatricia *aux = node->InvertedIndexPatriciaRoot;

    while (aux != NULL) {
        if (aux->qtde > 0) {  // Verifica se o termo aparece no documento
            count++;
        }
        aux = aux->nextInvertedIndexPatricia;
    }

    return count;
}

//Calcula o número de seekings da árvore Patricia
int calculateSeekingsPatricia(TipoArvore root, TipoChave term) {
    if (root == NULL) {
        return 0;
    }

    int seekings = 0;
    TipoArvore node = Pesquisa(term, root);

    if (node != NULL && EExterno(node)) {
        InvertedIndexPatricia *current = node->InvertedIndexPatriciaRoot;
        while (current != NULL) {
            seekings += current->qtde;
            current = current->nextInvertedIndexPatricia;
        }
    }

    return seekings;
}

//Imprime a árvore Patricia ordenada por ordem alfabética com o número de seekings
void ImprimeArvoreOrdemAlfabeticaComSeekings(TipoArvore t) {
    if (t == NULL)
        return;
    if (!EExterno(t)) {
        ImprimeArvoreOrdemAlfabeticaComSeekings(t->NO.NInterno.Esq);
        ImprimeArvoreOrdemAlfabeticaComSeekings(t->NO.NInterno.Dir);
    } else {
        int seekings = calculateSeekingsPatricia(t, t->NO.Chave);
        printf("Chave: %s ->", t->NO.Chave);
        printf(" (Seekings: %d) ", seekings);

        if (t->InvertedIndexPatriciaRoot != NULL) {
            InvertedIndexPatricia *currentInvertedIndex = t->InvertedIndexPatriciaRoot;

            while (currentInvertedIndex != NULL) {
                printf(" (Doc: %d, Qtde: %d),", currentInvertedIndex->idDoc, currentInvertedIndex->qtde);
                currentInvertedIndex = currentInvertedIndex->nextInvertedIndexPatricia;
            }
        }
        printf("\n");
    }
}