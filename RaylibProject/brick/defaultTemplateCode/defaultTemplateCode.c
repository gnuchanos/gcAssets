#include "raylib.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define GPurple0 CLITERAL(Color){   31,  0,  71, 255 } 
#define GPurple1 CLITERAL(Color){   34,  2,  77, 255 } 
#define GPurple2 CLITERAL(Color){   49,  3, 110, 255 } 
#define GPurple3 CLITERAL(Color){   67,  5, 150, 255 } 
#define GPurple4 CLITERAL(Color){   86,  6, 194, 255 } 
#define GPurple5 CLITERAL(Color){  110, 10, 245, 255 }

typedef enum {
    LOGO     = 0,
    MENU     = 1,
    GAMEPLAY = 2,
    END      = 3
} Scene;

typedef struct {
    char      *Text;
    Rectangle ButtonRectangle;
    Vector2 ButtonPosition;
    Vector2 TextPosition_DontUseThis;
    int       FontSize;
    Color     TextColor;
    Color     ButtonColor;
    bool      PressButton;
} Button;

void CreateButton(Button *ThisButton, char *Text, Font font, Vector2 ButtonPosition, Color TextColor, Color ButtonColor, bool PressButton) {
    ThisButton->Text = (char *)malloc(strlen(Text) + 1);
    strcpy(ThisButton->Text, Text);

    ThisButton->FontSize = 30;

    float TextWith   = MeasureTextEx(font, ThisButton->Text, ThisButton->FontSize, 1).x + 10;
    float TextHeight = MeasureTextEx(font, ThisButton->Text, ThisButton->FontSize, 1).y + 10;

    ThisButton->ButtonPosition.x = ButtonPosition.x+TextWith/2-TextWith/2+5;
    ThisButton->ButtonPosition.y = ButtonPosition.y+TextHeight/2-TextHeight/2+5;

    ThisButton->ButtonRectangle = (Rectangle){ButtonPosition.x, ButtonPosition.y, TextWith, TextHeight};
    ThisButton->ButtonColor     = (Color)ButtonColor;
    ThisButton->TextColor       = (Color)TextColor;
    ThisButton->PressButton     = (bool)PressButton;
}

void DrawButton(Button *ThisButton, Font TEXTFONT) {
    DrawRectangle( ThisButton->ButtonRectangle.x, ThisButton->ButtonRectangle.y, ThisButton->ButtonRectangle.width, ThisButton->ButtonRectangle.height, ThisButton->ButtonColor );
    DrawTextEx( TEXTFONT, ThisButton->Text, ThisButton->ButtonPosition, ThisButton->FontSize, 1, ThisButton->TextColor );
}

void PressButton(bool *ButtonPress, Vector2 *MousePoint, Rectangle ButtonRectangle, Color *ChangeColor) {
    *ButtonPress = false;
    if (CheckCollisionPointRec(*MousePoint, ButtonRectangle)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            *ButtonPress = true;
            *ChangeColor = GPurple4;
        } else {
            *ChangeColor = GPurple3;
        }
    } else {
        *ChangeColor = GPurple2;
    }
}

int main(void) {
    const int screenWidth = 1000;
    const int screenHeight = 600;
    const char GameTitle[] = "Game Title UwU";
    InitWindow(screenWidth, screenHeight, GameTitle);

    // Settings
        SetExitKey(KEY_NULL);
        bool ShowMouse = false;
        int CurrentScene = LOGO;
        int Level = 0;
        float LogoTimer = 2;
        Font DefaultFont = LoadFont("./Sans.ttf");
    // Settings

    // Default
        Texture2D BackGroundImage = LoadTexture("./bg.png");
        BackGroundImage.width = screenWidth;
        BackGroundImage.height = screenHeight;
    // Default

    // Menu
        // Start Button
            Texture2D MainMenuLogo = LoadTexture("./logo.png");

            // Ready To Create Button
            Button StartButton;
            CreateButton( &StartButton, (char *)"Start Game", DefaultFont, (Vector2){100, 100}, GPurple5, GPurple1, false );
            int StartGameTimer = 5;
        // Start Button
    // Menu

    // GamePlay

    // GamePlay
    Vector2 mousePoint = { 0.0f, 0.0f };
    SetTargetFPS(60);
    while (!WindowShouldClose()) {

        // Show Cursor or Hide
        if (ShowMouse) {
            if (IsKeyPressed(KEY_ESCAPE)) {
                ShowMouse = false;
                DisableCursor();
            }
        } else {
            if (IsKeyPressed(KEY_ESCAPE)) {
                ShowMouse = true;
                EnableCursor();
            }
        }
        // Show Cursor or Hide

        if (CurrentScene == LOGO) {
            //Lo
            if (LogoTimer > 0) {
                LogoTimer -= GetFrameTime();
            } else {
                CurrentScene = MENU;
            }
        } else if (CurrentScene == MENU) {
            mousePoint = GetMousePosition();
            PressButton( &StartButton.PressButton, &mousePoint, StartButton.ButtonRectangle, &StartButton.ButtonColor );
            if (StartButton.PressButton) {
                CurrentScene = GAMEPLAY;
            }

        } else if (CurrentScene == GAMEPLAY) {


        } else if (CurrentScene == END) {


        }
        BeginDrawing();
            ClearBackground(GPurple0);
            if (CurrentScene == LOGO) {
                DrawTexture(BackGroundImage, 0, 0, WHITE);
            } else if (CurrentScene == MENU) {
                DrawTexture(MainMenuLogo, 600, 200, WHITE);
                DrawButton(&StartButton, DefaultFont);
            } else if (CurrentScene == GAMEPLAY) {
                DrawText("This is GamePlay Scene", 10, 10, 30, GPurple5);
            } else if (CurrentScene == END) {
                
            }
            DrawRectangle(0, screenHeight-35, 90, 35, GPurple2);
            DrawFPS(10, screenHeight-25);
        EndDrawing();
    }
    // Unload ALL Here
    UnloadTexture(BackGroundImage);
    UnloadTexture(MainMenuLogo);
    free(StartButton.Text);

    CloseWindow();
    return 0; }