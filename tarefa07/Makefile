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
all: mensageiro

mensageiro: mensageiro.o arvore_rb.o
	$(CC) -o mensageiro mensageiro.o arvore_rb.o $(LD_FLAGS)

mensageiro.o: mensageiro.c
	$(CC) -o mensageiro.o mensageiro.c $(CC_FLAGS)

arvore_rb.o: arvore_rb.c
	$(CC) -o arvore_rb.o arvore_rb.c $(CC_FLAGS)

.PHONY: clean
clean:
	rm -f mensageiro *.o
