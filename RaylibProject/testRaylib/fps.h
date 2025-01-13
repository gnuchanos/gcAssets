#ifndef FPSFILE
#define FPSFILE

#include "main.h"

typedef struct {
    Camera3D GO;
    Vector3 RecordCamPosition;
    Vector3 BodySize;
    bool BodyHitWall;
    bool ShowMouse;
} _CameraGO;

_CameraGO GOCAM();
void FPS(_CameraGO *Player);


#endif
