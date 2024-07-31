all: Main.c TAD_Menu.c TAD_Arquivo.c TAD_Patricia.c TAD_TabelaHash.c 
	gcc Main.c -o ./output/exec TAD_Menu.c TAD_Arquivo.c TAD_Patricia.c TAD_TabelaHash.c 

run: ./exec

