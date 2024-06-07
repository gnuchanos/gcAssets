#!/bin/bash


sudo pacman -S --noconfirm alsa-lib mesa libx11 libxrandr libxi libxcursor libxinerama
mkdir -p ~/tmp && cd ~/tmp
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
git pull
./emsdk install latest
./emsdk activate latest
cd ~/tmp
git clone https://github.com/raysan5/raylib.git raylib
cd raylib/src/
make PLATFORM=PLATFORM_WEB # To make web version.
#make PLATFORM=PLATFORM_DESKTOP # To make the static version.