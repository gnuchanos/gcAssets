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
        std::string Points = " | Left Player: " + std::to_string(LeftPoint) + " | Right Player: " + std::to_string(RightPoint);

        void GameUpdate() {
            if (BALL.x < 0) {
                BALL.x = screenWidth  / 2 - 15;
                BALL.y = screenHeight / 2 - 15;
                LeftPoint += 1;
                Points = " | Left Player: " + std::to_string(LeftPoint) + " | Right Player: " + std::to_string(RightPoint);
            }
            else if (BALL.x > screenWidth-15) {
                BALL.x = screenWidth  / 2 - 15;
                BALL.y = screenHeight / 2 - 15;
                RightPoint += 1;
                Points = " | Left Player: " + std::to_string(LeftPoint) + " | Right Player: " + std::to_string(RightPoint);
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
        }

        void GameDraw() {
            DrawRectangle(LeftPad.x, LeftPad.y, LeftPad.width, LeftPad.height, gc.Purple4);
            DrawRectangle(RightPad.x, RightPad.y, RightPad.width, RightPad.height, gc.Purple4);
            DrawRectangle(TopBAR.x, TopBAR.y, TopBAR.width, TopBAR.height, gc.Purple3);
            DrawRectangle(BottomBAR.x, BottomBAR.y, BottomBAR.width, BottomBAR.height, gc.Purple3);

            DrawRectangle(BALL.x, BALL.y, BALL.width, BALL.height, gc.Purple3);

            raylib::DrawText(Points, 240, 10, 30, gc.Purple5);

            DrawFPS(10, 10);
        }

        void UnloadALL() {
        }

        void GameLoop() {
            raylib::Window window(screenWidth, screenHeight, GameTitle);
            SetTargetFPS(60);
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
