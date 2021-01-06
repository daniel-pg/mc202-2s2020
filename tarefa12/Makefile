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
planilha: planilha.o
	$(CC) -o planilha planilha.o $(LD_FLAGS)

# Objetos
planilha.o: planilha.c
	$(CC) -o planilha.o planilha.c $(CC_FLAGS)


.PHONY: clean
clean:
	rm -f planilha
	rm -f *.o
