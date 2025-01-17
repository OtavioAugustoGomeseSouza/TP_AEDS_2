#include "TAD_Arquivo.h"

//Le o primeiro arquivo da entrada
FileType* readentradaFile(const char *fileName, SearchType *searchType) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    int numFiles;
    if (fscanf(file, "%d", &numFiles) != 1) {
        printf("Erro ao ler o número de arquivos\n");
        fclose(file);
        return NULL;
    }

    //Adiciona um espaço adicional para o caractere de nova linha no final da string
    FileType *files = malloc(numFiles * sizeof(FileType));
    if (files == NULL) {
        printf("Erro ao alocar memória\n");
        fclose(file);
        return NULL;
    }

    //Limpar o buffer de nova linha que pode ter sido deixado por fscanf
    fgetc(file);

    for (int i = 0; i < numFiles; i++) {
        if (fgets(files[i].fileName, sizeof(files[i].fileName), file) == NULL) {
            printf("Erro ao ler o nome do arquivo\n");
            free(files);
            fclose(file);
            return NULL;
        }

        //Remove o caractere de nova linha, se houver
        files[i].fileName[strcspn(files[i].fileName, "\n")] = '\0';

        files[i].idDoc = i;
    }

    searchType->numArq = numFiles;
    printf("Existem %d arquivos a serem lidos\n", numFiles);

    fclose(file);

    return files;
}

void readAllFiles(const char *fileName, FileType* files, SearchType *searchType) {
    for (int i = 0; i < searchType->numArq; i++) {
        readArquivoFile(files[i].fileName, searchType, &files[i]);
        // Considerando que readArquivoFile já trata os erros internamente
    }
    
    free(files);
}


//Remove espaços iniciais
void removeLeadingSpaces(char *str) {
    char *start = str;

    // Encontra o primeiro caractere não espaço
    while (isspace((unsigned char)*start)) {
        start++;
    }

    // Move os caracteres restantes para o início da string
    if (start != str) {
        char *dst = str;
        while (*start) {
            *dst++ = *start++;
        }
        *dst = '\0'; // Finaliza a string
    }
}

//Remove ponto final
void removeFinalDot(char *str) {
    int len = strlen(str);
    // Verifica se a última posição tem um ponto final e, se sim, remove-o
    for (int i = 0; i < len; i++)
    {
        if (str[i] == '.') 
        {
            str[i] = '\0';
        }   

    }
}

//Le os arquivos internos
void readArquivoFile(char *fileName, SearchType *searchType, FileType *fileType) {
    char fullPath[512];
    snprintf(fullPath, sizeof(fullPath), "%s%s", "../Arquivos/ArquivosEntrada/", fileName);

    FILE *file = fopen(fullPath, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo interno");
        return;
    }

    fgets(fileType->potionName, sizeof(fileType->potionName), file);

    char ingredientes[1000];
    char *token;
    char *tokens[100];
    fgets(ingredientes, sizeof(ingredientes), file);
    int i = 0;
    //Separa os ingredientes por ponto e vírgula
    token = strtok(ingredientes, ";");
    while (token != NULL && i < 100) {
        tokens[i] = malloc((strlen(token) + 1) * sizeof(char));
        if (tokens[i] == NULL) {
            printf("Erro ao alocar memória\n");
            break;
        }
        strcpy(tokens[i], token);
        removeLeadingSpaces(tokens[i]);
        removeFinalDot(tokens[i]);

         searchType->root = Insere(tokens[i],searchType->root);

        insertHash(&searchType->hashTable, tokens[i], fileType->idDoc);

        i++;
        token = strtok(NULL, ";");
    }
    //Salva o número de ingredientes
    fileType->ni = i;
    //Lê o preparo
    char Preparo[1000];
    fgets(Preparo, sizeof(Preparo), file);
    removePunctuation(Preparo);

    for (int j = 0; j < i; j++) {
        int timesAppeared = countOccurrences(Preparo, tokens[j]);
        HashNode *currentHashNode = searchHash(&searchType->hashTable, tokens[j]);
        insertInvertedIndexHash(currentHashNode, fileType->idDoc, timesAppeared);
        //printf("inseriu %s\n", tokens[j]);
        insertInvertedIndexPatricia(Pesquisa(tokens[j],searchType->root), fileType->idDoc, timesAppeared);
        free(tokens[j]);
    }

    fclose(file);
}

//Remove pontuação
void removePunctuation(char *str) {
    char *src = str, *dst = str;
    while (*src) {
        if (!ispunct((unsigned char)*src)) {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}


//Implementação própria de strcasestr, responsavel por comparar as palavras ignorando maiúsculas e minúsculas
char *strcasestr(const char *haystack, const char *needle) {
    if (!*needle) {
        return (char *)haystack;  //Se needle é uma string vazia, retorna haystack.
    }

    while (*haystack) {
        if (tolower((unsigned char)*haystack) == tolower((unsigned char)*needle)) {
            const char *h = haystack;
            const char *n = needle;

            while (*h && *n && tolower((unsigned char)*h) == tolower((unsigned char)*n)) {
                ++h;
                ++n;
            }

            if (!*n) {
                return (char *)haystack;
            }
        }
        ++haystack;
    }

    return NULL;  //Se não encontrou a string needle em haystack.
}


//Conta a ocorrência da palavra dentro do arquivo
int countOccurrences(const char *a, const char *b){
    int count = 0;
    size_t lenb = strlen(b);
    const char *p = a;
    while(NULL != (p = strcasestr(p, b))){
        ++count;
        p += lenb;
    }
    return count;
}

