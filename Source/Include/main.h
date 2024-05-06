#ifndef MainFile
#define MainFile

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <raylib.h>
#include <raymath.h>

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif


#define WindowWitdh 1024
#define WindowHeight 768
#define WindowTitle "UwU"

#define PurpleTrans   CLITERAL(Color){ 124, 5, 242, 90 }

#define Purple1   CLITERAL(Color){ 124, 5, 242, 255 }
#define Purple2   CLITERAL(Color){ 111, 4, 217, 255 }
#define Purple3   CLITERAL(Color){ 101, 4, 196, 255 }
#define Purple4   CLITERAL(Color){ 89, 3, 173, 255 }
#define Purple5   CLITERAL(Color){ 80, 3, 156, 255 }
#define Purple6   CLITERAL(Color){ 71, 3, 138, 255 }
#define Purple7   CLITERAL(Color){ 60, 2, 117, 255 }
#define Purple8   CLITERAL(Color){ 50, 2, 97, 255 }
#define Purple9   CLITERAL(Color){ 39, 2, 77, 255 }
#define Purple10   CLITERAL(Color){ 27, 1, 54, 255 }

typedef struct {
    char FilePath[100];
    Model Obj;
    Vector3 Position;
    Vector3 Scale;
    Vector3 Rotation;
    Texture2D Texture[10];
} Object3D;


Object3D BetaNewVegas();
Object3D TardisInside();
Object3D RedRoom();
Object3D TardisBody();





#endif