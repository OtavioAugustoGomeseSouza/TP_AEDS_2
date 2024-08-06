# TP_AEDS_2

## Descrição
Este projeto é parte da disciplina de Algoritmos e Estruturas de Dados II e consiste na implementação de uma tabela hash, árvore Patricia e funções relacionadas para manipulação de arquivos e menus. 

## Estrutura do Projeto
- **Main.c**: Arquivo principal que contém a função `main` e inicializa o programa.
- **TAD_Arquivo.c / TAD_Arquivo.h**: Implementação e definição das funções para manipulação de arquivos.
- **TAD_Menu.c / TAD_Menu.h**: Implementação e definição das funções relacionadas ao menu do programa.
- **TAD_Patricia.c / TAD_Patricia.h**: Implementação e definição da árvore Patricia.
- **TAD_TabelaHash.c / TAD_TabelaHash.h**: Implementação e definição da tabela hash.
- **makefile**: Arquivo de automação de compilação.
- **output/**: Diretório para saída dos resultados.
- **Arquivos/**: Diretório para armazenar arquivos que serão lidos pelo programa.

## Instalação
Certifique-se que a pasta chamada "Arquivos" contendo os "ArquivosEntrada" e "entrada.txt" está na mesma pasta que o arquivo "Main.c". A nomeclatura deve estar conforme indicada ou não será possível ler os arquivos.

## Compilação
Com o terminal dentro da pasta "TP_AEDS_2" utilize o comando: make(ou mingw32-make dependendo da instalçao do MinGW) para gerar um executável chamado exec.exe. Este executável será gerado dentro da parta output, então certifiquese-se que que você está dentro da pasta "output". No window a pasta pode ser acessada utilizando o comando: "cd output" no terminal. Em seguida basta executar o executável com o comando ".\exec.exe".

## Como utilizar o programa
Após executar o executável um menu será apresentado. conforme o esquema abaixo:

   MENU:
 [1] Receber arquivos de entrada
 [2] Construir ├ìndice Invertido
 [3] Imprimir
 [4] Buscar ingrediente
 [5] Sair

 Ao escolher o item [1] os arquivos de entrada serão lidos e o número de documentos será impresso;
 Ao escolher o item [2] as tablas hash e árvore Patricia serão construídas, e os indices invertidos serão criados;
 Ao escolher o item [3] Aparecerá a opção para imprimir as tabelas hash e árvore Patricia;
 Ao escolher o item [4] será apresentado a opção para buscars ingredientes, será perguntado a quantidade de palavras a serem buscadas e serão apresentados, em seguida devem ser inseridas as palavras uma a uma, após inserir todas as palavras será apresentado o resultado da busca;
 Ao escolher o item [5] o programa será encerrado.




