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
all: listas_legais

listas_legais: listas_legais.o arvore_rb.o
	$(CC) -o listas_legais listas_legais.o arvore_rb.o $(LD_FLAGS)

listas_legais.o: listas_legais.c
	$(CC) -o listas_legais.o listas_legais.c $(CC_FLAGS)

arvore_rb.o: arvore_rb.c
	$(CC) -o arvore_rb.o arvore_rb.c $(CC_FLAGS)

.PHONY: clean
clean:
	rm -f listas_legais
	rm -f *.o
