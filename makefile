all: Main.c TAD_Patricia.c TAD_TabelaHash.c
	gcc Main.c -o exec TAD_Patricia.c TAD_TabelaHash.c

run: ./exec

