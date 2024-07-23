#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TAD_TabelaHash.h"
#include "TAD_Patricia.h"
#include "TAD_Arquivo.h"

void readArquivoFile(char *fileName, SearchType *searchType, FileType *fileType) {
    
    char fullPath[512];
    snprintf(fullPath, sizeof(fullPath), "%s%s%s", BASE_DIR, "Arquivos/ArquivosEntrada/", fileName);

    //printf("Arquivo: %s\n", fullPath);  

    FILE *file = fopen(fullPath, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo interno");
        return;
    }

    fgets(fileType->potionName, sizeof(fileType->potionName), file);

    char linha[1000];

    fgets(linha, sizeof(linha), file);

    
    strtok(linha, ";");


    
    
    
}



void readentradaFile(const char *fileName , SearchType *searchType) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    int numFiles;
    if (fscanf(file, "%d", &numFiles) != 1) {
        printf("Erro ao ler o número de arquivos\n");
        fclose(file);
        return;
    }
    //printf("Número de arquivos: %d\n", numFiles);

    // Adiciona um espaço adicional para o caractere de nova linha no final da string
    FileType *files = malloc(numFiles * sizeof(FileType));
    if (files == NULL) {
        printf("Erro ao alocar memória\n");
        fclose(file);
        return;
    }

    // Limpar o buffer de nova linha que pode ter sido deixado por fscanf
    fgetc(file);

    for (int i = 0; i < numFiles; i++) {
        // Limita a leitura para o tamanho do array
        if (fgets(files[i].fileName, sizeof(files[i].fileName), file) == NULL) {
            printf("Erro ao ler o nome do arquivo\n");
            break;
        }

        // Remove o caractere de nova linha, se houver
        files[i].fileName[strcspn(files[i].fileName, "\n")] = '\0';

        files[i].idDoc = i;
        //printf("Arquivo: %s\n", files[i].fileName);
    }

    for (int i = 0; i < numFiles; i++) {
        readArquivoFile(files[i].fileName, searchType, &files[i]);
    }
    

    free(files);
    fclose(file);
}




int main() {
    HashTable hashTable;
    PatriciaNode *root = NULL;

    SearchType searchType;
    searchType.hashTable = hashTable;
    searchType.root = root;

    char *nomeArquivo = BASE_DIR "Arquivos/entrada.txt";
    readentradaFile(nomeArquivo, &searchType);
    return 0;
}
