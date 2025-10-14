PROJ_NAME=ted
ALUNO=Murilo de Paula
LIBS=-lm
OBJETOS=Pilha.o Fila.o Forma.o Carregador.o Disparador.o Arena.o LeitorGeo.o LeitorQry.o Svg.o main.o

# Compilador a ser usado
CC=gcc

# Flags de compilação (regras para o compilador)
# -ggdb: para debugar
# -O0: sem otimização
# -std=c99: usar o padrão C99
# -Wall -Wextra -pedantic: mostrar TODOS os avisos possíveis (seu professor vai adorar isso)
# -Werror: tratar qualquer aviso como um erro (força você a programar direito)
CFLAGS=-ggdb -O0 -std=c99 -Wall -Wextra -pedantic -Werror

# Comando para linkar tudo e criar o executável final
$(PROJ_NAME): $(OBJETOS)
	$(CC) -o $(PROJ_NAME) $(OBJETOS) $(LIBS)

# Regra genérica para transformar qualquer .c em um .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Comando para limpar os arquivos gerados
clean:
	rm -f $(PROJ_NAME) $(OBJETOS)

#
###
# DEPENDÊNCIAS DE CADA MÓDULO 
###
#

main.o: main.c LeitorGeo.h LeitorQry.h
Pilha.o: Pilha.c Pilha.h
Fila.o: Fila.c Fila.h
Forma.o: Forma.c Forma.h
Carregador.o: Carregador.c Carregador.h Pilha.h Forma.h
Disparador.o: Disparador.c Disparador.h Carregador.h Forma.h
Arena.o: Arena.c Arena.h Fila.h Forma.h
LeitorGeo.o: LeitorGeo.c LeitorGeo.h Forma.h
LeitorQry.o: LeitorQry.c LeitorQry.h Pilha.h Fila.h Carregador.h Disparador.h Arena.h
Svg.o: Svg.c Svg.h Forma.h