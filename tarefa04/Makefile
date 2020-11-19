# C Compiler
CC=gcc

# Compiler flags
CC_FLAGS=\
-g              \
-O3             \
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
all: seaofwords

seaofwords: seaofwords.c
	$(CC) $(CC_FLAGS) seaofwords.c -o seaofwords $(LD_FLAGS)

.PHONY: clean
clean:
	rm -f seaofwords
