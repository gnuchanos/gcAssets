#!/bin/bash




# source ./emsdk_env.sh <-- every time not in fish





emcc main.c -o Build/index.html -O3 -s ASYNCIFY -s USE_GLFW=3 -s FULL_ES2=1 -s FULL_ES3=1 -s ALLOW_MEMORY_GROWTH=1 -s ASSERTIONS=1 -I. -I/home/archkubi/tmp/raylib/src -Iexternal/glfw/include -L/home/archkubi/tmp/raylib/src -lraylib 

#-sASYNCIFY

