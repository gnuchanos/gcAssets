#include "Include/main.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

typedef enum GameScreen { 
    LOGO = 0, 
    MENU = 1, 
    GAMEPLAY = 2, 
    ENDING = 3 } GameScreen;


int main(void) {
    int ScreenWidth = 800;
    int ScreenHeight = 450;
    char GameTitle[50] = " Game Title ";



    InitWindow(ScreenWidth, ScreenHeight, GameTitle);











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
                if (framesCounter > 120) { currentScreen = MENU; }
            } break;
            case MENU: {
                if (IsKeyPressed(KEY_ONE)) { currentScreen = GAMEPLAY; }



            } break;
            case GAMEPLAY: {
                if (IsKeyPressed(KEY_TWO)) { currentScreen = ENDING; }



            } break;
            case ENDING: {
                if (IsKeyPressed(KEY_THREE)) { currentScreen = LOGO; }



            } break;
            default: break;
        }
        BeginDrawing();
            ClearBackground(RAYWHITE);
            switch(currentScreen) {
                case LOGO: {
                    DrawText("Logo", ScreenWidth/2, ScreenHeight/2, 30, BLACK);
                    DrawText(debugFrame, 10, 10, 30, RED);



                } break;
                case MENU: {
                    DrawText("Menu", ScreenWidth/2, ScreenHeight/2, 30, BLACK);




                } break;
                case GAMEPLAY: {
                    DrawText("GamePlay", ScreenWidth/2, ScreenHeight/2, 30, BLACK);




                } break;
                case ENDING: {
                    DrawText("Ending", ScreenWidth/2, ScreenHeight/2, 30, BLACK);




                } break;
                default: break;
            }
        EndDrawing(); }
    // Unload Thins here



    // Unload Thins here
    CloseWindow();
    return 0; }