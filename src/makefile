# Nome do projeto/executável. O ../ faz com que o executável seja criado na pasta raiz, fora de src.
PROJ_NAME=../ted

# Identificação do aluno
ALUNO=Murilo de Paula

# Bibliotecas externas (lm para a biblioteca de matemática)
LIBS=-lm

# Lista de todos os arquivos objeto (.o) necessários para esta etapa.
OBJETOS=circulo.o retangulo.o linha.o texto.o lista.o svg.o leitorGeo.o main.o

# Compilador a ser usado
CC=gcc

# Flags de compilação.
CFLAGS=-g -O0 -std=c99 -Wall -Wextra -pedantic -Werror

# Regra principal: para criar o executável, primeiro crie todos os OBJETOS
$(PROJ_NAME): $(OBJETOS)
	$(CC) -o $(PROJ_NAME) $(OBJETOS) $(LIBS)

# Regra genérica para transformar qualquer .c em um .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Comando para limpar os arquivos gerados (o executável na pasta raiz e os objetos em src)
clean:
	rm -f $(PROJ_NAME) $(OBJETOS)

#
###
# DEPENDÊNCIAS DE CADA MÓDULO
###
#

main.o: main.c leitorGeo.h svg.h lista.h tipos.h circulo.h retangulo.h linha.h texto.h

lista.o: lista.c lista.h

circulo.o: circulo.c circulo.h tipos.h
retangulo.o: retangulo.c retangulo.h tipos.h
linha.o: linha.c linha.h tipos.h
texto.o: texto.c texto.h tipos.h

leitorGeo.o: leitorGeo.c leitorGeo.h lista.h circulo.h retangulo.h linha.h texto.h

svg.o: svg.c svg.h circulo.h retangulo.h linha.h texto.h