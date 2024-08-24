#ifndef FPS_FILE
#define FPS_FILE

#include <raylib.h>

typedef struct {
    Camera3D GO;
} _CameraGO;

_CameraGO GO_CAM() {
    _CameraGO GO;
    GO.GO;
    GO.GO.position = (Vector3){ 5.0f, 4.0f, 5.0f };    // Camera position
    GO.GO.target = (Vector3){ 0.0f, 2.0f, 0.0f };      // Camera looking at point
    GO.GO.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    GO.GO.fovy = 45.0f;                                // Camera field-of-view Y
    GO.GO.projection = CAMERA_PERSPECTIVE;             // Camera projection type
    return GO;
}

void FPS(Camera3D *camera);



#endif