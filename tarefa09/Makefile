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
all: diadeuber

diadeuber: diadeuber.o heapq.o
	$(CC) -o diadeuber diadeuber.o heapq.o $(LD_FLAGS)

diadeuber.o: diadeuber.c
	$(CC) -o diadeuber.o diadeuber.c $(CC_FLAGS)

heapq.o: heapq.c
	$(CC) -o heapq.o heapq.c $(CC_FLAGS)

.PHONY: clean
clean:
	rm -f diadeuber
	rm -f *.o
