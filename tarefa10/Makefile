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
-Wextra         \
-Wcast-align

LD_FLAGS=\
-lm             \
-fuse-ld=gold


.PHONY: all
all: corretor


# Executável
corretor: corretor.o hash_table.o lista_ligada.o
	$(CC) -o corretor corretor.o hash_table.o lista_ligada.o $(LD_FLAGS)


# Objetos
corretor.o: corretor.c
	$(CC) -o corretor.o corretor.c $(CC_FLAGS)

hash_table.o: hash_table.c
	$(CC) -o hash_table.o hash_table.c $(CC_FLAGS)

lista_ligada.o: lista_ligada.c
	$(CC) -o lista_ligada.o lista_ligada.c $(CC_FLAGS)


.PHONY: clean
clean:
	rm -f corretor
	rm -f *.o
