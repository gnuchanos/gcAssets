#include "include/main.h"


_CameraGO GOCAM() {
    _CameraGO GO;
    GO.GO.position = (Vector3){ 5.0f, 1.5f, 5.0f };    // Camera position
    GO.GO.target = (Vector3){ 5.0f, 1.5f, 0.0f };      // Camera looking at point
    GO.GO.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    GO.GO.fovy = 45.0f;                                // Camera field-of-view Y
    GO.GO.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    GO.RecordCamPosition = (Vector3){ 5.0f, 0.0f, 5.0f };
    GO.BodySize          = (Vector3){ 0.1f, 1.5,  0.1f };
    return GO;
}

void _CheckCollision3D_SolidObject(Camera3D *camera, Vector3 *RecordPlayerPosition, Vector3 PlayerSize, Vector3 *WallPosition, Vector3 *WallSize, int WallLimit, bool *WallHit) {
    *WallHit = false;

    for (int i = 0; i < WallLimit; i++) {
        if (CheckCollisionBoxes(
            (BoundingBox){
                (Vector3){ 
                    camera->position.x - PlayerSize.x/2,
                    camera->position.y - PlayerSize.y/2,
                    camera->position.z - PlayerSize.z/2 },
                (Vector3){ 
                    camera->position.x + PlayerSize.x/2,
                    camera->position.y + PlayerSize.y/2,
                    camera->position.z + PlayerSize.z/2 }
                },
            (BoundingBox){
                (Vector3){ 
                    WallPosition[i].x - WallSize->x/2,
                    WallPosition[i].y - WallSize->y/2,
                    WallPosition[i].z - WallSize->z/2 },
                (Vector3){ 
                    WallPosition[i].x + WallSize->x/2,
                    WallPosition[i].y + WallSize->y/2,
                    WallPosition[i].z + WallSize->z/2 }
                }
            )
        ) {
            *WallHit = true;
            camera->position.x = RecordPlayerPosition->x;
            camera->position.z = RecordPlayerPosition->z;
            break;
        }
    }
}

bool _CheckCollision3D_Area(Vector3 *RecordPlayerPosition, Vector3 PlayerSize, Vector3 AreaPosition, Vector3 AreaSize) {
    if (CheckCollisionBoxes(
            (BoundingBox){
                (Vector3){ 
                    RecordPlayerPosition->x - PlayerSize.x/2,
                    RecordPlayerPosition->y - PlayerSize.y/2,
                    RecordPlayerPosition->z - PlayerSize.z/2 },
                (Vector3){ 
                    RecordPlayerPosition->x + PlayerSize.x/2,
                    RecordPlayerPosition->y + PlayerSize.y/2,
                    RecordPlayerPosition->z + PlayerSize.z/2 }
            },
            (BoundingBox){
                (Vector3){ 
                    AreaPosition.x - AreaSize.x/2,
                    AreaPosition.y - AreaSize.y/2,
                    AreaPosition.z - AreaSize.z/2 },
                (Vector3){ 
                    AreaPosition.x + AreaSize.x/2,
                    AreaPosition.y + AreaSize.y/2,
                    AreaPosition.z + AreaSize.z/2 }
            }
        )) { 
            return true; 
        } else {
            return false; 
        }
    }


void FPS(Camera3D *camera, Vector3 *RecordPlayerPosition, bool *WallHit) {
    Vector3 Movement = (Vector3){0.0f, 0.0f, 0.0f};
    Vector3 Rotation = (Vector3){0.0f, 0.0f, 0.0f};
    float Zoom = 0.0f;

    if (!*WallHit) {
        RecordPlayerPosition->x = camera->position.x;
        RecordPlayerPosition->z = camera->position.z;
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

    UpdateCameraPro(camera, Movement, Rotation, Zoom);
}
