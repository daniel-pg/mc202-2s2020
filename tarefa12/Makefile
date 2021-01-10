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
-Wextra			\
-Wcast-align

LD_FLAGS=\
-lm             \
-fuse-ld=gold

.PHONY: all
all: planilha

# Executável
planilha: planilha.o pilha.o
	$(CC) -o planilha planilha.o pilha.o $(LD_FLAGS)

# Objetos
planilha.o: planilha.c
	$(CC) -o planilha.o planilha.c $(CC_FLAGS)

pilha.o: pilha.c
	$(CC) -o pilha.o pilha.c $(CC_FLAGS)

.PHONY: clean
clean:
	rm -f planilha
	rm -f *.o
