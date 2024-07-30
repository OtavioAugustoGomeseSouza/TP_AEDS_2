# Makefile para o projeto TP_AEDS_2

# Defina o compilador
CC = gcc

# Defina as opções de compilação
CFLAGS = -Wall -Wextra -g3

# Defina os arquivos de origem
SRCS = Main.c TAD_Arquivo.c TAD_Patricia.c TAD_TabelaHash.c

# Converte arquivos .c para arquivos .o
OBJS = $(SRCS:.c=.o)

# Nome do executável final
EXEC = output/Main.exe

# Regra padrão para construir o executável
all: $(EXEC)

# Como construir o executável a partir dos arquivos objeto
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

# Como compilar arquivos .c em arquivos .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpa os arquivos gerados pela compilação
clean:
	rm -f $(OBJS) $(EXEC)
