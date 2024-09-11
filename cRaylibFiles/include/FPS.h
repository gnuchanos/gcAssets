#ifndef FPS_FILE
#define FPS_FILE

#include "main.h"

typedef struct {
    Camera3D GO;
    Vector3 RecordCamPosition;
    Vector3 BodySize;
} _CameraGO;

_CameraGO GOCAM();
void FPS(Camera3D *camera, Vector3 *PlayerPosition, bool *WallHit);
void _CheckCollision3D_SolidObject(Camera3D *camera, Vector3 *RecordPlayerPosition, Vector3 PlayerSize, Vector3 *WallPosition, Vector3 *WallSize, int WallLimit, bool *WallHit);
bool _CheckCollision3D_Area(Vector3 *RecordPlayerPosition, Vector3 PlayerSize, Vector3 AreaPosition, Vector3 AreaSize);

#endif
