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

void BeFreePlayer(_CameraGO *Player);
void FPS(_CameraGO *Player);

#endif
