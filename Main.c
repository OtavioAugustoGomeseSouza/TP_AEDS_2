#include "TAD_Arquivo.h"
#include <stddef.h>
#include "TAD_TabelaHash.h"
#include "TAD_Patricia.h"
#include "TAD_Menu.h"

//gcc -Wall -Wextra -g3 TAD_TabelaHash.c TAD_Patricia.c Main.c -o output/Main.exe
//mingw32-make
// .\exec.exe

/*
 como compilar
 
 para criar o makefile precisa estar dentro da pasta C:\Users\Otavio\Desktop\TP_AEDS_2\TP_AEDS_2> e executar mingw32-make
  será criado um exec.exe que não pode ser compilado
  o exec.exe deve ser movido para a pasta output

  então entrar no output com o comando cd output
  executar o comando .\exec.exe

  se quiser compilar novamente deve sair da pasta output e voltar para a pasta C:\Users\Otavio\Desktop\TP_AEDS_2\TP_AEDS_2>
  para sair de uma pasta use o comando cd ..

*/


/*void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}*/

int main() {

    
    HashTable hashTable;
    initHashTable(&hashTable);
    

    SearchType searchType;
    searchType.hashTable = hashTable;
    searchType.root = NULL;


    char *nomeArquivo = "../Arquivos/entrada.txt";
    menu(nomeArquivo, &searchType, &hashTable, searchType.root);

    //busca dentro da pratricia
    //printf("Searching for 'Pinch of Unicorn Horn': %s\n", search(searchType.root, "Pinch of Unicorn Horn") ? "Found" : "Not found");
    
    
    return 0;
}
