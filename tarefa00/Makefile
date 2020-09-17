CC_FLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LD_FLAGS = -lm

.PHONY: all clean

all: bomdia boanoite

bomdia: bomdia.c
	gcc $(CC_FLAGS) bomdia.c -o bomdia $(LD_FLAGS)

boanoite: boanoite.c
	gcc $(CC_FLAGS) boanoite.c -o boanoite $(LD_FLAGS)

clean:
	rm -f bomdia boanoite