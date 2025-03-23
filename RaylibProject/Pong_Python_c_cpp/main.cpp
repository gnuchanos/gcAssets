#include <raylib.h>
#include <string>
#include <raylib-cpp.hpp>

class GColors {
    public:
        Color Purple0 = (Color){  31,  0,  71, 255 };
        Color Purple1 = (Color){  34,  2,  77, 255 };
        Color Purple2 = (Color){  49,  3, 110, 255 };
        Color Purple3 = (Color){  67,  5, 150, 255 };
        Color Purple4 = (Color){  86,  6, 194, 255 };
        Color Purple5 = (Color){ 110, 10, 245, 255 };
};

class SimpleGame{
    public:
        const int screenWidth = 1000;
        const int screenHeight = 600;
        std::string GameTitle = "Game Title";

        GColors gc;
        raylib::Rectangle LeftPad   = (Rectangle){10,  static_cast<float>(screenHeight/2-75), 10, 150};
        raylib::Rectangle RightPad  = (Rectangle){980, static_cast<float>(screenHeight/2-75), 10, 150};
        raylib::Rectangle TopBAR    = (Rectangle){0,   0, static_cast<float>(screenWidth), 5};
        raylib::Rectangle BottomBAR = (Rectangle){0,   static_cast<float>(screenHeight-5), static_cast<float>(screenWidth), 5};

        raylib::Rectangle BALL      = (Rectangle){static_cast<float>(screenWidth/2-15), static_cast<float>(screenHeight/2-15), 30, 30};
        float             BALLSPEED = 200.0f;

        Rectangle LeftEndArea  = (Rectangle){-20, 0, 1, static_cast<float>(screenHeight)};
        Rectangle RightEndArea = (Rectangle){static_cast<float>(screenWidth+20), 0, 1, static_cast<float>(screenHeight)};

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
        std::string Points = " | Left Player: " + std::to_string(LeftPoint) + " | Right Player: " + std::to_string(RightPoint);

        Sound HitSound;
        Music BGMusic;
        Sound Point;

        std::string PlayerWin;
        bool GameOver = false;

        void GameUpdate() {
                if (GameOver) {
                    LeftPoint = RightPoint = 0;
                    Points = " | Left Player: " + std::to_string(LeftPoint) + " | Right Player: " + std::to_string(RightPoint);
                    LeftPad   = (Rectangle){10,  static_cast<float>(screenHeight/2-75), 10, 150};
                    RightPad  = (Rectangle){980, static_cast<float>(screenHeight/2-75), 10, 150};
                    if (IsKeyPressed(KEY_R)) {
                        GameOver = false;
                    }
                } else {
                    if (LeftPoint == 5) {
                        PlayerWin = "Left Player Win!";
                        GameOver = true;
                    } else if (RightPoint == 5) {
                        PlayerWin = "Right Player Win!";
                        GameOver = true;
                    }

                    UpdateMusicStream((BGMusic));
                    BALLSPEED += 10 * GetFrameTime();
                    // Player1 and Player2 Move
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

                    // Point Area
                    if (BALL.x < 0) {
                        BALL.x = screenWidth  / 2 - 15;
                        BALL.y = screenHeight / 2 - 15;
                        LeftPoint++;
                        BALLSPEED = 200.0f;
                        Points = " | Left Player: " + std::to_string(LeftPoint) + " | Right Player: " + std::to_string(RightPoint);
                    } else if (BALL.x > screenWidth-15) {
                        BALL.x = screenWidth  / 2 - 15;
                        BALL.y = screenHeight / 2 - 15;
                        RightPoint++;
                        BALLSPEED = 200.0f;
                        Points = " | Left Player: " + std::to_string(LeftPoint) + " | Right Player: " + std::to_string(RightPoint);
                    }

                    LeftEndAreaHit  = CheckCollisionRecs(LeftEndArea,  BALL);
                    RightEndAreaHit = CheckCollisionRecs(RightEndArea, BALL);
                    if (LeftEndAreaHit || RightEndAreaHit) {
                        PlaySound(Point);
                    }

                    // Paddle Hit -> Players
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

                    // Top and Bottom Hit
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

                    // ball move
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
                }
        }

        void GameDraw() {
            if (GameOver) {
                raylib::DrawText(PlayerWin, 10, 10, 30, gc.Purple5);
                raylib::DrawText("Press R play Again!!", screenWidth/2-200, screenHeight/2, 60, gc.Purple5);
            } else {
                DrawRectangle(LeftPad.x, LeftPad.y, LeftPad.width, LeftPad.height, gc.Purple4);
                DrawRectangle(RightPad.x, RightPad.y, RightPad.width, RightPad.height, gc.Purple4);
                DrawRectangle(TopBAR.x, TopBAR.y, TopBAR.width, TopBAR.height, gc.Purple3);
                DrawRectangle(BottomBAR.x, BottomBAR.y, BottomBAR.width, BottomBAR.height, gc.Purple3);
                DrawRectangle(BALL.x, BALL.y, BALL.width, BALL.height, gc.Purple3);
                raylib::DrawText(Points, 240, 10, 30, gc.Purple5);
                DrawFPS(10, 10);
            }
        }

        void UnloadALL() {
            UnloadSound(HitSound);
            UnloadSound(Point);
            UnloadMusicStream(BGMusic);
            CloseAudioDevice();
        }

        void GameLoop() {
            raylib::Window window(screenWidth, screenHeight, GameTitle);
            SetTargetFPS(60);

            InitAudioDevice();

            HitSound = LoadSound("./hitSound.wav");
            BGMusic    = LoadMusicStream("./music.mp3");
            Point    = LoadSound("./point.wav");

            PlayMusicStream(BGMusic);

            while (!window.ShouldClose()) {
                GameUpdate();
                BeginDrawing();
                    window.ClearBackground(gc.Purple0);
                    GameDraw();
                EndDrawing(); }
            UnloadALL();
            window.Close(); }
};

int main(void) {
    SimpleGame GC;
    GC.GameLoop();
    return 0; }
