#include "include/fps.h"

_CameraGO GOCAM() {
    _CameraGO GO;
    GO.GO = (Camera3D *)malloc(sizeof(Camera3D));
    GO.GO->position = (Vector3){ -1.5, 1.5f, -7.5 };    // Camera position
    GO.GO->target = (Vector3){ -1.5, 1.5f, 10.0f };      // Camera looking at point
    GO.GO->up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    GO.GO->fovy = 70.0f;                                // Camera field-of-view Y
    GO.GO->projection = CAMERA_PERSPECTIVE;             // Camera projection type

    GO.RecordCamPosition = (Vector3){ 5.0f, 0.0f, 5.0f };
    GO.BodySize          = (Vector3){ 0.1f, 1.5,  0.1f };
    GO.BodyHitWall = false;
    GO.ShowMouse   = false;
    return GO; }

void BeFreePlayer(_CameraGO *Player) { free(Player->GO); }

void FPS(_CameraGO *Player) {
    Vector3 Movement = (Vector3){0.0f, 0.0f, 0.0f};
    Vector3 Rotation = (Vector3){0.0f, 0.0f, 0.0f};
    float Zoom = 0.0f;

    if (!Player->BodyHitWall) {
        Player->RecordCamPosition.x = Player->GO->position.x;
        Player->RecordCamPosition.z = Player->GO->position.z;
        //RecordPlayerPosition->y = camera->position.y;
    }

    if (IsKeyDown(KEY_W)) {
        Movement.x = 0.05f;
    } else if (IsKeyDown(KEY_S)) {
        Movement.x = -0.05f;
    }
    
    if (IsKeyDown(KEY_A)) {
        Movement.y = -0.05f;
    } else if (IsKeyDown(KEY_D)) {
        Movement.y = 0.05f;
    }

    Vector2 mouseDelta = GetMouseDelta();
    Rotation.x = mouseDelta.x;
    Rotation.y = mouseDelta.y;

    UpdateCameraPro(Player->GO, Movement, Rotation, Zoom);
}
