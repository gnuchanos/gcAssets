#include "include/main.h"



int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;
    const char GameTitle[20] = "Game Title Here";
    InitWindow(screenWidth, screenHeight, GameTitle);
    SetExitKey(KEY_NULL);

    // Define the camera to look into our 3d world
    _CameraGO CAM = GOCAM();




    DisableCursor();
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        // Show Cursor or Hide
        if (IsKeyPressed(KEY_ESCAPE) && CAM.ShowMouse) {
            CAM.ShowMouse = false;
            DisableCursor();
        } else if (IsKeyPressed(KEY_ESCAPE) && !CAM.ShowMouse) {
            CAM.ShowMouse = true;
            EnableCursor(); }
        // Show Cursor or Hide

        _CameraGO CAM;    
        FPS(&CAM.GO);




        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode3D(CAM.GO);
                DrawGrid(10, 1.0f);
            


            EndMode3D();

        EndDrawing();
    }

    // unload things

    CloseWindow();
    return 0; }
