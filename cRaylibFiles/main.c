#include <stdio.h>
#include <string.h>
#include "include/main.h"



int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;
    const char GameTitle[20] = "Game Title Here";
    InitWindow(screenWidth, screenHeight, GameTitle);
    SetExitKey(KEY_NULL);

    // Define the camera to look into our 3d world
    _CameraGO CAM = GOCAM();
    Vector3 RecordPlayerPosition = CAM.RecordCamPosition;
    Vector3 PlayerSize     = CAM.BodySize;
    bool ShowMouse = false;

    Vector3 Walls_Position[] = {
        (Vector3){0.0f, 0.5f, 0.0f},
        (Vector3){2.0f, 0.5f, 0.0f},
    };
    Vector3 Walls_Size[] = {
        (Vector3){1.0f, 1.0f, 1.0f},
        (Vector3){1.0f, 1.0f, 1.0f},
    };
    int WallLimit = sizeof(Walls_Position) / sizeof(Walls_Position[0]);
    bool WallHit = false;
    Color gColor;

    char PlayerPosition_Debug[128];
    sprintf(PlayerPosition_Debug, " | Player Position X:%f | Player Position Z:%f | ", CAM.GO.position.x, CAM.GO.position.z);

    bool AreaTestHit = false;
    Vector3 AreaPosition = (Vector3){0.0f, 0.0f, 0.0f};
    Vector3 AreaSize = (Vector3){5.0f, 1.0f, 5.0f};
    char AreaTestHit_Debug[20];
    strcpy(AreaTestHit_Debug, "False");

    DisableCursor();
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        // Show Cursor or Hide
        if (IsKeyPressed(KEY_ESCAPE) && ShowMouse) {
            ShowMouse = false;
            DisableCursor();
        } else if (IsKeyPressed(KEY_ESCAPE) && !ShowMouse) {
            ShowMouse = true;
            EnableCursor(); }
        // Show Cursor or Hide


        FPS(&CAM.GO, &RecordPlayerPosition, &WallHit);
        _CheckCollision3D_SolidObject(&CAM.GO, &RecordPlayerPosition, PlayerSize, Walls_Position, Walls_Size, WallLimit, &WallHit);
        sprintf(PlayerPosition_Debug, " | Player Position X:%f | Player Position Z:%f | ", CAM.GO.position.x, CAM.GO.position.z);

        if (!WallHit) {
            gColor = RED;
        } else {
            gColor = YELLOW;
        }

        AreaTestHit = _CheckCollision3D_Area(&RecordPlayerPosition, PlayerSize, AreaPosition, AreaSize);
        if (AreaTestHit) {
            strcpy(AreaTestHit_Debug, " True");
        } else {
            strcpy(AreaTestHit_Debug, " False");
        }


        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode3D(CAM.GO);
                DrawGrid(10, 1.0f);
                for (int i = 0; i < WallLimit; i++) {
                    DrawCube(Walls_Position[i], Walls_Size[i].x, Walls_Size[i].y, Walls_Size[i].z, gColor);
                }
                DrawCube(AreaPosition, AreaSize.x, AreaSize.y, AreaSize.z, WHITE);
                DrawCube(RecordPlayerPosition, PlayerSize.x, PlayerSize.y, PlayerSize.z, RED);
            EndMode3D();
            DrawText(PlayerPosition_Debug, 10, 10, 27.5, GPurple4);
            DrawText(AreaTestHit_Debug, 10, 35, 30, GPurple4);
            DrawFPS(10, 10);

        EndDrawing();
    }

    // unload things

    CloseWindow();
    return 0; }
