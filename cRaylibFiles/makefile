cFlags = -Wall -Wextra -O2 -g -pedantic -lraylib -lm -std=c99

# Target: Object/main.o
Object/main.o: main.c
	gcc $(cFlags) -c main.c -o Object/main.o

# Target: Object/FPS.o
Object/FPS.o: FPS.c
	gcc $(cFlags) -c FPS.c -o Object/FPS.o

# Target: Object/2DPlayer.o
Object/2DPlayer.o: Player2D.c
	gcc $(cFlags) -c Player2D.c -o Object/2DPlayer.o	

# Target: Build_Linux
Build_Linux: Object/main.o Object/FPS.o Object/2DPlayer.o
	gcc $(cFlags) Object/*.o -o Build/debug && ./Build/debug

# Target: Clean
Clean:
	rm -f Object/*.o Build/debug