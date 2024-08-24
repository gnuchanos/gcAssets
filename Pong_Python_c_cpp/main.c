#include <stdio.h>
#include <raylib.h>

#define GPurple0 CLITERAL(Color){   31,  0,  71, 255 } 
#define GPurple1 CLITERAL(Color){   34,  2,  77, 255 } 
#define GPurple2 CLITERAL(Color){   49,  3, 110, 255 } 
#define GPurple3 CLITERAL(Color){   67,  5, 150, 255 } 
#define GPurple4 CLITERAL(Color){   86,  6, 194, 255 } 
#define GPurple5 CLITERAL(Color){  110, 10, 245, 255 } 

int main(void) {
    const int screenWidth = 1000;
    const int screenHeight = 600;
    const char GameTitle[128] = "Game Title";
    InitWindow(screenWidth, screenHeight, GameTitle);

    Rectangle LeftPad   = (Rectangle){10,  (float)screenHeight/2-75, 10, 150};
    Rectangle RightPad  = (Rectangle){980, (float)screenHeight/2-75, 10, 150};
    Rectangle TopBAR    = (Rectangle){0,   0, screenWidth, 5};
    Rectangle BottomBAR = (Rectangle){0,   screenHeight-5, screenWidth, 5};

    Rectangle BALL      = (Rectangle){(float)screenWidth/2-15, (float)screenHeight/2-15, 30, 30};

    bool TopBAR_Hit     = false;
    bool BottomBAR_Hit  = false;
    bool LeftPad_Hit    = false;
    bool RightPad_Hit   = false;

    bool LeftHit = false;
    bool UpHit   = false;
    bool DownHit = false;
    bool KeyW    = false;
    bool KeyS    = false;

    bool LeftPoint  = 0;
    bool RightPoint = 0;
    char Points[128];
    sprintf(Points, " | Left Player: %d | Right Player: %d", LeftPoint, RightPoint);

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        if (BALL.x < 0) {
            BALL.x = (float)screenWidth  / 2 - 15;
            BALL.y = (float)screenHeight / 2 - 15;
            LeftPoint += 1;
            sprintf(Points, " | Left Player: %d | Right Player: %d", LeftPoint, RightPoint);
        }
        else if (BALL.x > screenWidth-15) {
            BALL.x = (float)screenWidth  / 2 - 15;
            BALL.y = (float)screenHeight / 2 - 15;
            RightPoint += 1;
            sprintf(Points, " | Left Player: %d | Right Player: %d", LeftPoint, RightPoint);
        }

        LeftPad_Hit = CheckCollisionRecs(LeftPad, BALL);
        RightPad_Hit = CheckCollisionRecs(RightPad, BALL);

        if (LeftPad_Hit) {
            LeftHit = true;
            if (IsKeyDown(KEY_W)) {
                KeyW = true;
            } else if (IsKeyDown(KEY_S)) {
                KeyS = true;
            } else {
                KeyW = KeyS = false;
            }
        } else if (RightPad_Hit) {
            LeftHit = false;
            if (IsKeyDown(KEY_UP)) {
                KeyW = true;
            } else if (IsKeyDown(KEY_DOWN)) {
                KeyS = true;
            } else {
                KeyW = KeyS = false;
            }
        }

        TopBAR_Hit = CheckCollisionRecs(TopBAR, BALL);
        BottomBAR_Hit = CheckCollisionRecs(BottomBAR, BALL);

        if (TopBAR_Hit) {
            UpHit = true;
            DownHit = false;
            KeyW = KeyS = false;
        } else if (BottomBAR_Hit) {
            UpHit = false;
            DownHit = true;
            KeyW = KeyS = false;
        }

        if (LeftHit) {
            BALL.x += 200 * GetFrameTime();
        } else {
            BALL.x -= 200 * GetFrameTime();
        }

        if (KeyW) {
            BALL.y -= 200 * GetFrameTime();
        } else if (KeyS) {
            BALL.y += 200 * GetFrameTime();
        } else if (UpHit) {
            BALL.y += 200 * GetFrameTime();
        } else if (DownHit) {
            BALL.y -= 200 * GetFrameTime();
        }

        if (IsKeyDown(KEY_W)) {
            if (LeftPad.y > 0) {
                LeftPad.y -= 200 * GetFrameTime();
            }
        } else if (IsKeyDown(KEY_S)) {
            if (LeftPad.y  < screenHeight-150) {
                LeftPad.y += 200 * GetFrameTime();
            }
        }

        if (IsKeyDown(KEY_UP)) {
            if (RightPad.y > 0) {
                RightPad.y -= 200 * GetFrameTime();
            }
        } else if (IsKeyDown(KEY_DOWN)) {
            if (RightPad.y < screenHeight-150) {
                RightPad.y += 200 * GetFrameTime();
            }
        }

        BeginDrawing();
            ClearBackground(GPurple0);
            DrawRectangle(LeftPad.x, LeftPad.y, LeftPad.width, LeftPad.height, GPurple4);
            DrawRectangle(RightPad.x, RightPad.y, RightPad.width, RightPad.height, GPurple4);
            DrawRectangle(TopBAR.x, TopBAR.y, TopBAR.width, TopBAR.height, GPurple3);
            DrawRectangle(BottomBAR.x, BottomBAR.y, BottomBAR.width, BottomBAR.height, GPurple3);

            DrawRectangle(BALL.x, BALL.y, BALL.width, BALL.height, GPurple3);

            DrawText(Points, 240, 10, 30, GPurple5);

            DrawFPS(10, 10);

        EndDrawing(); }

    CloseWindow();
    return 0; }
