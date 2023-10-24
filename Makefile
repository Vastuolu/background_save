all: BatteryCare

BatteryCare: BatteryCare.c
	gcc -o BatteryCare BatteryCare.c -I./depedencies/include -L./depedencies/lib -lmingw32 -lSDL2main -lSDL2_mixer -lSDL2

clean:
	rm -f BatteryCare
