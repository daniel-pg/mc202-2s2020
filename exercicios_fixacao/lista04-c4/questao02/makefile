# C Compiler
CC=gcc

# Compiler flags
CC_FLAGS=\
-c             \
-g            \
-march=native  \
-std=c18       \
-pedantic      \
-Wall          \
-Werror        \
-Wextra

# Linker flags
LD_FLAGS=\
-fuse-ld=gold\
-lm


.PHONY: all
all: main
	@echo -e "Compilação terminou!"


# Ligar arquivo executável
main: main.o poligono.o
	$(CC) -o $@ $^ $(LD_FLAGS)

# Compilar objetos
main.o: main.c poligono.h
	$(CC) -o $@ $< $(CC_FLAGS)

poligono.o: poligono.c poligono.h
	$(CC) -o $@ $< $(CC_FLAGS)


# Limpar binários
.PHONY: clean
clean:
	rm -rf poligono.o main.o main
