cFlag = -std=c99 -O1 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11


mainFile:main.c
	gcc $(cFlag) -c main.c -o Objects/main.o

build: mainFile
	gcc $(cFlag) $(wildcard Objects/*.o) -o Build/debug.x86_64
	