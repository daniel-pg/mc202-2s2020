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
all: caminho

# Executável
caminho: caminho.o lista_ligada.o
	$(CC) -o caminho caminho.o lista_ligada.o $(LD_FLAGS)

# Objetos
caminho.o: caminho.c
	$(CC) -o caminho.o caminho.c $(CC_FLAGS)

lista_ligada.o: lista_ligada.c
	$(CC) -o lista_ligada.o lista_ligada.c $(CC_FLAGS)


.PHONY: clean
clean:
	rm -f caminho
	rm -f *.o
