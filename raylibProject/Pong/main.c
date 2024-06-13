#include "Include/main.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

typedef enum GameScreen { 
    LOGO = 0, 
    MENU = 1, 
    GAMEPLAY = 2, 
    ENDING = 3 } GameScreen;

void ChangeWindowState(int ScreenWidth, int ScreenHeight, GameScreen currentScreen) {
                // Change Full Screen or Window Screen
                if (IsKeyPressed(KEY_ONE)) { currentScreen = GAMEPLAY; }
                    if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))) {
                        int display = GetCurrentMonitor();
                        if (IsWindowFullscreen()) {
                            SetWindowSize(ScreenWidth, ScreenHeight);
                        } else {
                            SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display)); }
                        ToggleFullscreen(); }
                // Change Full Screen or Window Screen
}


int main(void) {
    int ScreenWidth = 1024;
    int ScreenHeight = 800;
    char GameTitle[50] = " Game Title ";
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(ScreenWidth, ScreenHeight, GameTitle);


    Rectangle player = { 400, 280, 40, 40 };

    Camera2D camera = { 0 };
    camera.target = (Vector2){ player.x + 20.0f, player.y + 20.0f };
    camera.offset = (Vector2){ ScreenWidth/2.0f, ScreenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;



    GameScreen currentScreen = LOGO;
    int framesCounter = 0; 
    char debugFrame[50];
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        switch(currentScreen) {
            case LOGO: {
                framesCounter++;
                sprintf(debugFrame, "Time: %d", framesCounter);
                // Wait for 2 seconds (120 frames) before jumping to Menu screen
                if ( framesCounter > 120 && currentScreen == LOGO ) { 
                    currentScreen = MENU; 
                    framesCounter = 0; }

            } break;
            case MENU: {
                if (IsKeyPressed(KEY_ONE)) { currentScreen = GAMEPLAY; }
                ChangeWindowState(ScreenWidth, ScreenHeight, currentScreen);



            } break;
            case GAMEPLAY: {
                if (IsKeyPressed(KEY_TWO)) { currentScreen = ENDING; }
                ChangeWindowState(ScreenWidth, ScreenHeight, currentScreen);

                if ( IsKeyDown(KEY_A) ) {
                    player.x -= 300 * GetFrameTime();
                }
                if ( IsKeyDown(KEY_D) ) {
                    player.x += 300 * GetFrameTime();
                }
                if ( IsKeyDown(KEY_W) ) {
                    player.y -= 300 * GetFrameTime();
                }
                if ( IsKeyDown(KEY_S) ) {
                    player.y += 300 * GetFrameTime();
                }


            } break;
            case ENDING: {
                if (IsKeyPressed(KEY_THREE)) { currentScreen = LOGO; }
                ChangeWindowState(ScreenWidth, ScreenHeight, currentScreen);


            } break;
            default: break;
        }
        BeginDrawing();
            ClearBackground(BLACK);
            switch(currentScreen) {
                case LOGO: {
                    DrawText("Logo", 10, 10, 30, WHITE);
                    DrawText(debugFrame, 10, 50, 30, RED);



                } break;
                case MENU: {
                    DrawText("Menu", 10, 10, 30, WHITE);




                } break;
                case GAMEPLAY: {
                    BeginMode2D(camera);
                        DrawRectangleRec(player, RED);
                    EndMode2D();
                    DrawText("GamePlay", 10, 10, 30, WHITE);
                    DrawFPS(10, 50);



                } break;
                case ENDING: {
                    DrawText("Ending", 10, 10, 30, WHITE);




                } break;
                default: break;
            }
        EndDrawing(); }
    // Unload Thins here



    // Unload Thins here
    CloseWindow();
    return 0; }