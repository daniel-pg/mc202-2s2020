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
-Werror         \
-Werror=vla     \
-Wextra

LD_FLAGS=\
-lm             \
-fuse-ld=gold

.PHONY: all
all: calculadora

calculadora: calculadora.o int_grande.o lista_ligada.o
	$(CC) -o calculadora calculadora.o int_grande.o lista_ligada.o $(LD_FLAGS)

calculadora.o: calculadora.c
	$(CC) calculadora.c -o calculadora.o $(CC_FLAGS)

int_grande.o: int_grande.c
	$(CC) int_grande.c -o int_grande.o $(CC_FLAGS)

lista_ligada.o: lista_ligada.c
	$(CC) lista_ligada.c -o lista_ligada.o $(CC_FLAGS)

.PHONY: clean
clean:
	rm -f calculadora *.o
