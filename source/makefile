flag= -O1 -Wall -std=c99

mainFile: main.c
	gcc $(flag) -c main.c -o Object/main.o

final: mainFile
	gcc $(flag) Object/main.o -o uWu
	./uWu
build:final
clean: rm Object/*.o rm uWu