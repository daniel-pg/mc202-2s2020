# C Compiler
CC=gcc

# Compiler flags
CC_FLAGS=\
-c             \
-O2            \
-march=native  \
-std=c18       \
-pedantic      \
-Wall          \
-Werror        \
-Wextra

# Linker flags
LD_FLAGS=\
-fuse-ld=gold


.PHONY: all
all: megasena
	@echo -e "Compilação terminou!"


# Ligar arquivo executável
megasena: megasena.o
	$(CC) -o $@ $< $(LD_FLAGS)
	strip -g $@


# Compilar objetos
megasena.o: megasena.c
	$(CC) -o $@ $< $(CC_FLAGS)


# Limpar binários
.PHONY: clean
clean:
	rm -rf megasena.o megasena
