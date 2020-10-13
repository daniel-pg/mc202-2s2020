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
main: main.o complexo.o
	$(CC) -o $@ $^ $(LD_FLAGS)

# Compilar objetos
main.o: main.c complexo.h
	$(CC) -o $@ $< $(CC_FLAGS)

complexo.o: complexo.c complexo.h
	$(CC) -o $@ $< $(CC_FLAGS)


# Limpar binários
.PHONY: clean
clean:
	rm -rf complexo.o main.o main
