#include <stdio.h>
#include <raylib.h>
#include <string.h>

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
    InitAudioDevice(); 

    // Sound
    Sound HitSound = LoadSound("./hitSound.wav");
    Music BGMusic    = LoadMusicStream("./music.mp3");
    Sound Point    = LoadSound("./point.wav");
    // Sound

    PlayMusicStream(BGMusic);

    Rectangle LeftPad   = (Rectangle){10,  (float)screenHeight/2-75, 10, 150};
    Rectangle RightPad  = (Rectangle){980, (float)screenHeight/2-75, 10, 150};
    Rectangle TopBAR    = (Rectangle){0,   0, screenWidth, 5};
    Rectangle BottomBAR = (Rectangle){0,   screenHeight-5, screenWidth, 5};

    Rectangle BALL      = (Rectangle){(float)screenWidth/2-15, (float)screenHeight/2-15, 30, 30};
    float     BALLSPEED = 200.0f;

    Rectangle LeftEndArea  = (Rectangle){-20, 0, 1, screenHeight};
    Rectangle RightEndArea = (Rectangle){screenWidth+20, 0, 1, screenHeight};

    bool LeftEndAreaHit  = false;
    bool RightEndAreaHit = false;


    bool TopBAR_Hit     = false;
    bool BottomBAR_Hit  = false;
    bool LeftPad_Hit    = false;
    bool RightPad_Hit   = false;

    bool LeftHit = false;
    bool UpHit   = false;
    bool DownHit = false;
    bool KeyW    = false;
    bool KeyS    = false;

    int LeftPoint  = 0;
    int RightPoint = 0;
    char Points[128];
    sprintf(Points, " | Left Player: %d | Right Player: %d", LeftPoint, RightPoint);

    bool GameOver = false;
    char PlayerWin[64];


    SetTargetFPS(60);
    while (!WindowShouldClose()) {
            if (GameOver) {
                if (IsKeyPressed(KEY_R)) {
                    LeftPoint = RightPoint = 0;
                    sprintf(Points, " | Left Player: %d | Right Player: %d", LeftPoint, RightPoint);
                    LeftPad   = (Rectangle){10,  (float)screenHeight/2-75, 10, 150};
                    RightPad  = (Rectangle){980, (float)screenHeight/2-75, 10, 150};                    
                    GameOver = false;
                }
            } else {
                UpdateMusicStream(BGMusic);
                BALLSPEED += 10 * GetFrameTime();

            // Player1 And Player2 Move
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

            // Point System
            // Point +1 Sound
            LeftEndAreaHit  = CheckCollisionRecs(LeftEndArea,  BALL);
            RightEndAreaHit = CheckCollisionRecs(RightEndArea, BALL);

            if (RightEndAreaHit) {
                BALL.x = (float)screenWidth  / 2 - 15;
                BALL.y = (float)screenHeight / 2 - 15;
                LeftPoint++;
                BALLSPEED = 200.0f;
                sprintf(Points, " | Left Player: %d | Right Player: %d", LeftPoint, RightPoint);
                PlaySound(Point); 
            } else if (LeftEndAreaHit) {
                BALL.x = (float)screenWidth  / 2 - 15;
                BALL.y = (float)screenHeight / 2 - 15;
                RightPoint++;
                BALLSPEED = 200.0f;
                sprintf(Points, " | Left Player: %d | Right Player: %d", LeftPoint, RightPoint);
                PlaySound(Point); 
            }


            // Paddle Players Hit
            LeftPad_Hit = CheckCollisionRecs(LeftPad, BALL);
            RightPad_Hit = CheckCollisionRecs(RightPad, BALL);

            if (LeftPad_Hit) {
                PlaySound(HitSound);
                LeftHit = true;
                if (IsKeyDown(KEY_W)) {
                    KeyW = true;
                } else if (IsKeyDown(KEY_S)) {
                    KeyS = true;
                } else {
                    KeyW = KeyS = false;
                    UpHit = DownHit = false;
                }

            } else if (RightPad_Hit) {
                PlaySound(HitSound);
                LeftHit = false;
            if (IsKeyDown(KEY_UP)) {
                KeyW = true;
            } else if (IsKeyDown(KEY_DOWN)) {
                KeyS = true;
            } else {
                    KeyW = KeyS = false;
                    UpHit = DownHit = false;
                }
            }

            // Top And Bottom Limit Hit
            TopBAR_Hit = CheckCollisionRecs(TopBAR, BALL);
            BottomBAR_Hit = CheckCollisionRecs(BottomBAR, BALL);

            if (TopBAR_Hit) {
                PlaySound(HitSound);
                UpHit = true;
                DownHit = false;
                KeyW = KeyS = false;

            } else if (BottomBAR_Hit) {
                PlaySound(HitSound);
                UpHit = false;
                DownHit = true;
                KeyW = KeyS = false;
            }

            // Ball Moves
            if (LeftHit) {
                BALL.x += BALLSPEED * GetFrameTime();
            } else {
                BALL.x -= BALLSPEED * GetFrameTime();
            }

            if (KeyW) {
                BALL.y -= BALLSPEED * GetFrameTime();
            } else if (KeyS) {
                BALL.y += BALLSPEED * GetFrameTime();
            } else if (UpHit) {
                BALL.y += BALLSPEED * GetFrameTime();
            } else if (DownHit) {
                BALL.y -= BALLSPEED * GetFrameTime();
            }

            // Game Finish
            if (LeftPoint == 5) {
                GameOver = true;
                strcpy(PlayerWin, "Left Player Win!");
            } else if (RightPoint == 5) {
                GameOver = true;
                strcpy(PlayerWin, "Right Player Win!");
            }
        }


        BeginDrawing();
            ClearBackground(GPurple0);

            if (GameOver) {
                DrawText(PlayerWin, 10, 10, 30, GPurple5);
                DrawText("Press R Play Again!!", screenWidth/2-200, screenHeight/2, 60, GPurple5);
            } else {
                // Paddles
                DrawRectangle(LeftPad.x, LeftPad.y, LeftPad.width, LeftPad.height, GPurple4);
                DrawRectangle(RightPad.x, RightPad.y, RightPad.width, RightPad.height, GPurple4);
                // up and down wall
                DrawRectangle(TopBAR.x, TopBAR.y, TopBAR.width, TopBAR.height, GPurple3);
                DrawRectangle(BottomBAR.x, BottomBAR.y, BottomBAR.width, BottomBAR.height, GPurple3);
                // Players Score Text
                DrawText(Points, 240, 10, 30, GPurple5);
                // BALLLLLLL
                DrawRectangle(BALL.x, BALL.y, BALL.width, BALL.height, GPurple3);
                // FPS
                DrawFPS(10, 10); }


        EndDrawing(); }
        UnloadSound(HitSound);
        UnloadSound(Point);
        UnloadMusicStream(BGMusic);
        CloseAudioDevice();

    CloseWindow();
    return 0; }
