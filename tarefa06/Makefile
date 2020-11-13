# C Compiler
CC=gcc

# Compiler flags
CC_FLAGS=\
-c              \
-g              \
-O2             \
-march=native   \
-std=c99        \
-pedantic       \
-Wall           \
-Werror=vla     \
-Wextra

LD_FLAGS=\
-lm             \
-fuse-ld=gold

.PHONY: all
all: sala_de_espera

sala_de_espera: sala_de_espera.o lista_ligada.o
	$(CC) -o sala_de_espera sala_de_espera.o lista_ligada.o $(LD_FLAGS)

sala_de_espera.o: sala_de_espera.c
	$(CC) sala_de_espera.c -o sala_de_espera.o $(CC_FLAGS)

lista_ligada.o: lista_ligada.c
	$(CC) lista_ligada.c -o lista_ligada.o $(CC_FLAGS)

.PHONY: clean
clean:
	rm -f sala_de_espera *.o
