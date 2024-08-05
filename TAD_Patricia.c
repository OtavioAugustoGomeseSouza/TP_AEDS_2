#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "TAD_Patricia.h"


InvertedIndexPatricia* createInvertedIndexPatricia(int idDoc, int qtde) {
    InvertedIndexPatricia *new = (InvertedIndexPatricia *)malloc(sizeof(InvertedIndexPatricia));
    new->idDoc = idDoc;
    new->qtde = qtde;
    new->nextInvertedIndexPatricia = NULL;
    return new;
}

// Função para inserir um índice invertido na raiz do nó
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
{ /* Verifica se p é um nodo externo */
  return (p->nt == Externo);
}

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

TipoArvore CriaNoExt(TipoChave k)
{
  TipoArvore p = (TipoArvore)malloc(sizeof(TipoPatNo));
  p->nt = Externo; 
  p->InvertedIndexPatriciaRoot = NULL;
  p->NO.Chave = strdup(k);  // Aloca memória para a string
  return p;
}  

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
        //printf("chave %s , chave externo %s\n",k,t->NO.Chave);
        //printf("chave nao encontrada %s\n",k);
        return NULL;
     }
      
  }
   
  if (k[t->NO.NInterno.Index] < t->NO.NInterno.Char_maior) 
    return Pesquisa(k, t->NO.NInterno.Esq);
  else 
    return Pesquisa(k, t->NO.NInterno.Dir);
} 

TipoArvore InsereEntre(TipoChave k, TipoArvore t, int i)
{
   // printf("inserindo %s no interno\n", k);
  TipoArvore p;
 // printf("i = %d, index = %d\n", i, t->NO.NInterno.Index);
    if (EExterno(t))
    { /* cria um novo nodo externo */
    //printf("inserindo %s no ||externo|| k[i]=%c e t->NO.Chave[i]=%c\n", k, k[i], t->NO.Chave[i]);
        // printf("é externo\n");
        p = CriaNoExt(k);
        char char_maior = (k[i] > t->NO.Chave[i]) ? k[i] : t->NO.Chave[i]; // Assume k tem um caractere na posição i
        if (k[i] > t->NO.Chave[i]) 
            return CriaNoInt(i, char_maior, t, p);
        else 
            return CriaNoInt(i, char_maior, p, t);
    } 
    else 
    {
       // printf("iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii\n");
       //printf("inserindo %s no interno\n", k);
       //printf("k[t->NO.NInterno.Index]=%c e t->NO.NInterno.Char_maior=%c\n",k[t->NO.NInterno.Index], t->NO.NInterno.Char_maior);
        /*if (k[t->NO.NInterno.Index] > t->NO.NInterno.Char_maior)
        {
            t->NO.NInterno.Char_maior = k[t->NO.NInterno.Index];
        }*/
        if (k[t->NO.NInterno.Index] < t->NO.NInterno.Char_maior)
            t->NO.NInterno.Esq = InsereEntre(k, t->NO.NInterno.Esq, i);
        else
            t->NO.NInterno.Dir = InsereEntre(k, t->NO.NInterno.Dir, i);
        return t;
    }

}

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
            //printf("k[p->NO.NInterno.Index]=%c e p->NO.NInterno.Char_maior=%c\n",k[p->NO.NInterno.Index], p->NO.NInterno.Char_maior);
            if (k[p->NO.NInterno.Index] >= p->NO.NInterno.Char_maior)
            {
                //p_ultimo = p;
                p = p->NO.NInterno.Dir;
                //printf("foi para direira\n");
            }
               // p->NO.NInterno.Char_maior = k[p->NO.NInterno.Index];
            else if (k[p->NO.NInterno.Index] < p->NO.NInterno.Char_maior)
                {
                    //printf("foi para esquerda\n");
                    //p_ultimo = p;
                    p = p->NO.NInterno.Esq;
                }
            else 
                //p_ultimo = p;
                p = p->NO.NInterno.Dir;
        }
        /* acha o primeiro caractere diferente */
        int i = 0;
        //printf("palavra %s k[i]=%c e p->NO.Chave[i]=%c\n",k, k[i], p->NO.Chave[i]);
        while (k[i] == p->NO.Chave[i])
            i++;

       //printf("palavra %s k[i]=%c e p->NO.Chave[i]=%c\n",k, k[i], p->NO.Chave[i]);
       //printf("p_ultimo->NO.NInterno.Index=%d , p_ultimo->NO.NInterno.Char_maior=%c\n",p_ultimo->NO.NInterno.Index, p_ultimo->NO.NInterno.Char_maior);
        if (strcoll(k, p->NO.Chave) == 0)
        { 
            //printf("Erro: chave %s já está na árvore\n", k);
            return t; 
        } 
        else
            /*if (k[i]>p->NO.Chave[i])
            {
                
                p_ultimo = CriaNoInt(i,k[i],p,CriaNoExt(k));


            }*/
            
            return InsereEntre(k, t, i);
            //return p;
    }
}

void ImprimeArvore(TipoArvore t, int nivel)
{
  if (t == NULL)
        return;
    for (int i = 0; i < nivel; i++)
        printf("  ");
    if (EExterno(t)){
        printf("Externo: %s ->", t->NO.Chave);

        if (t->InvertedIndexPatriciaRoot != NULL)
        {
            InvertedIndexPatricia *currentInvertedIndex = t->InvertedIndexPatriciaRoot;

        while (currentInvertedIndex != NULL) {
        printf(" (Doc: %d, Qtde: %d),", currentInvertedIndex->idDoc, currentInvertedIndex->qtde);
        currentInvertedIndex = currentInvertedIndex->nextInvertedIndexPatricia;
        }
        printf("\n");
        }
        
        
    }
    else
    {
       printf("Interno: Index %d, Char_maior %c\n", t->NO.NInterno.Index, t->NO.NInterno.Char_maior);
        ImprimeArvore(t->NO.NInterno.Esq, nivel + 1);
        ImprimeArvore(t->NO.NInterno.Dir, nivel + 1);
    }
}

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

/*int main()
{
  TipoArvore a = NULL;
  TipoChave c;
  char *strings[] = {"apple", "banana", "cherry", "date", "fig", "grape", "lemon"};
  int n = sizeof(strings) / sizeof(strings[0]);

  // Insere cada chave na árvore 
  for (int i = 0; i < n; i++) 
  {
    printf("Inserindo chave: %s\n", strings[i]);
    a = Insere(strings[i], a);
  }

  // Pesquisa cada chave na árvore 
  for (int i = 0; i < n; i++) 
  {
    printf("Pesquisando chave: %s\n", strings[i]);
    TipoArvore resultado = Pesquisa(strings[i], a);
    if (resultado != NULL)
      printf("Elemento encontrado: %s\n", resultado->NO.Chave);
    else
      printf("Elemento nao encontrado: %s\n", strings[i]);
  }

  // Pesquisa uma chave não existente 
  char *naoExistente = "orange";
  printf("Pesquisando chave: %s\n", naoExistente);
  TipoArvore resultado = Pesquisa(naoExistente, a);
  if (resultado != NULL)
    printf("Elemento encontrado: %s\n", resultado->NO.Chave);
  else
    printf("Elemento nao encontrado: %s\n", naoExistente);

    ImprimeArvore(a, 0);

  return 0;
}*/
