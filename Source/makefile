f = -Wall -O1 -std=c99 -lraylib -lX11 -lGL -lm

mainFile:main.c
	gcc $(f) -c main.c -o Object/main.o
objectfile:objects.c
	gcc $(f) -c objects.c -o Object/objects.o




final: mainFile objectfile
	gcc $(f) $(wildcard Object/*.o) -o Build/debug

build: final
