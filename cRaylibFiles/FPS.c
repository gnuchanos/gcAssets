#include <FPS.h>




void FPS(Camera3D *camera) {
    Vector3 Movement = (Vector3){0.0f, 0.0f, 0.0f};
    Vector3 Rotation = (Vector3){0.0f, 0.0f, 0.0f};
    float Zoom = 0.0f;

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

    UpdateCameraPro(camera, Movement, Rotation, Zoom);
}