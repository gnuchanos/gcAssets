#ifndef MAINFILE
#define MAINFILE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <raylib.h>
#include <raymath.h>

#include "fps.h"
#include "ui.h"



#define Purple0 CLITERAL(Color){  11, 0,  20, 255 }
#define Purple1 CLITERAL(Color){  20, 0,  38, 255 }
#define Purple2 CLITERAL(Color){  28, 0,  51, 255 }
#define Purple3 CLITERAL(Color){  43, 0,  79, 255 }
#define Purple4 CLITERAL(Color){  61, 0, 112, 255 }
#define Purple5 CLITERAL(Color){  84, 2, 153, 255 }
#define Purple6 CLITERAL(Color){ 103, 2, 190, 255 }
#define Purple7 CLITERAL(Color){ 117, 2, 214, 255 }
#define Purple8 CLITERAL(Color){ 129, 0, 237, 255 }
#define Purple9 CLITERAL(Color){ 139, 3, 252, 255 }

typedef enum {
    LogoScene = 0,
    MenuScene = 1,
    GameScene = 2,
    EndScene  = 3
} GC_Scenes;



#endif
