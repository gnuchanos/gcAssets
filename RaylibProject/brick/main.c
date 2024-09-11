#include "raylib.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void DrawFPS_RectangleBackGround(int ScreenHeight, int TextPositionX, int TextPositionY_Minus, Color Color) {
    DrawRectangle(0, ScreenHeight-35, 90, 35, Color);
    DrawFPS(TextPositionX, ScreenHeight-TextPositionY_Minus);
}

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
    float       FontSize;
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

typedef struct {
    Rectangle BrickBody;
    Color     BrickBodyColor;
    bool      BrickBodyDraw;
} brick;



int main(void) {
    const int screenWidth = 1000;
    const int screenHeight = 600;
    const char GameTitle[] = "Game Title UwU";
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, GameTitle);
    InitAudioDevice();

    // Settings
        SetExitKey(KEY_NULL);
        bool FPSMODE = true;
        bool ShowMouse = true;
        int CurrentScene = LOGO;
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
        // Start Button
    // Menu

    // GamePlay
        // only level 1 brick

        int Point = 0;
        int Lives = 3;
        char PointAndLive[128];
        sprintf(PointAndLive, " | Point:%d | Lives:%d", Point, Lives);
        int PointAndLiveWidth = MeasureTextEx(DefaultFont, PointAndLive, 30, 1).x;

        int MaxRow = 30;
        int MaxColumn = 10;
        brick Bricks_level0[MaxRow][MaxColumn];
        for (int i = 0; i < MaxRow; i++) {
            for (int a = 0; a < MaxColumn; a++) {
                Bricks_level0[i][a].BrickBody      = (Rectangle){55+(30*i), 50+20*a, 25, 10};
                Bricks_level0[i][a].BrickBodyColor = (Color)GPurple5;
                Bricks_level0[i][a].BrickBodyDraw  = (bool)true;
            }
        }

        // Player
        Rectangle Player = (Rectangle){(float)screenWidth/2-100, screenHeight-25-10, 200, 25};
        Rectangle BALL   = (Rectangle){(float)screenWidth/2-10,  (float)screenHeight/2+50, 20, 20};
        // Walls
        Rectangle LeftWall  = (Rectangle){0, 0, 10, screenHeight};
        Rectangle RightWall = (Rectangle){screenWidth-10, 0, 10, screenHeight};
        Rectangle TopWall   = (Rectangle){0, 0, screenWidth, 10};
        Rectangle EndArea   = (Rectangle){0, screenHeight-10, screenWidth, 10};

        // Hit COllision
        bool topBarHit   = false;
        bool LeftBarHit  = false;
        bool RightBarHit = false;
        bool PaddleHit   = false;
        bool BrickHit    = false;
        bool EndAreaHit  = false;

        bool TopHit      = true;
        bool LeftHit     = false;
        bool RightHit    = false;
        bool PlayerHit   = false;
        bool BrickActiveHit = false;

        Sound HitSound     = LoadSound("./hitSound.wav");
        Music BG_Music        = LoadMusicStream("./music.mp3");
        Sound OutSideSound = LoadSound("./point.wav");

        PlayMusicStream(BG_Music);
        

    Vector2 mousePoint = { 0.0f, 0.0f };
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        UpdateMusicStream(BG_Music);
    
        // Show Cursor or Hide
        if (IsKeyPressed(KEY_ESCAPE) && ShowMouse) {
            ShowMouse = false;
            DisableCursor();
        } else if (IsKeyPressed(KEY_ESCAPE) && !ShowMouse) {
            ShowMouse = true;
            EnableCursor(); }
        // Show Cursor or Hide

        if (CurrentScene == LOGO) {
            //Lo
            if (LogoTimer > 0) {
                LogoTimer -= GetFrameTime();
            } else {
                CurrentScene = MENU; }

        } else if (CurrentScene == MENU) {
            mousePoint = GetMousePosition();
            PressButton( &StartButton.PressButton, &mousePoint, StartButton.ButtonRectangle, &StartButton.ButtonColor );
            if (StartButton.PressButton) {
                CurrentScene = GAMEPLAY;
            }

        } else if (CurrentScene == GAMEPLAY) {
            if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
                if (Player.x > 10) {
                    Player.x -= 200 * GetFrameTime(); }
            } else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
                if (Player.x+Player.width+10 < screenWidth) {
                    Player.x += 200 * GetFrameTime();
                }
            }

            topBarHit   = CheckCollisionRecs(TopWall,   BALL);
            LeftBarHit  = CheckCollisionRecs(LeftWall,  BALL);
            RightBarHit = CheckCollisionRecs(RightWall, BALL);
            PaddleHit   = CheckCollisionRecs(Player,    BALL);
            EndAreaHit  = CheckCollisionRecs(EndArea,   BALL);

            if (topBarHit) {
                PlaySound(HitSound);
                TopHit = true;
                PlayerHit = BrickActiveHit = false;

            } else if (LeftBarHit) {
                PlaySound(HitSound);
                LeftHit  = true;
                RightHit = false;

            } else if (RightBarHit) {
                PlaySound(HitSound);
                RightHit = true;
                LeftHit  = false;

            } else if (PaddleHit) {
                PlaySound(HitSound);
                PlayerHit = true;
                BrickActiveHit = false;
                if (IsKeyDown(KEY_A)) {
                    TopHit = LeftHit = BrickActiveHit = false;
                    RightHit = true;
                } else if (IsKeyDown(KEY_D)) {
                    TopHit = RightHit = BrickActiveHit = false;
                    LeftHit = true;
                } else {
                    TopHit = LeftHit = RightHit = BrickActiveHit = false;
                }

            } else if (EndAreaHit) {
                PlaySound(OutSideSound);
                BALL.x = (float)screenWidth/2-10;
                BALL.y = (float)screenHeight/2+50;
                LeftHit = RightHit = BrickActiveHit = false;
 
                if (Lives != 1) {    
                    Lives--;
                    sprintf(PointAndLive, " | Point:%d | Lives:%d", Point, Lives);
                    PointAndLiveWidth = MeasureTextEx(DefaultFont, PointAndLive, 30, 1).x; 
                } else {
                    CurrentScene = END;
                }
            }

            for (int i = 0; i < MaxRow; i++) {
                for (int a = 0; a < MaxColumn; a++) {
                    if (Bricks_level0[i][a].BrickBodyDraw) {
                        BrickHit = CheckCollisionRecs(Bricks_level0[i][a].BrickBody, BALL);
                        if (BrickHit) {
                            BrickActiveHit = true;
                            Bricks_level0[i][a].BrickBodyDraw = false;
                            //Point += rand() % (1000 - 10) + 10;
                            Point += GetRandomValue(10, 1000);
                            sprintf(PointAndLive, " | Point:%d | Lives:%d", Point, Lives);
                            PointAndLiveWidth = MeasureTextEx(DefaultFont, PointAndLive, 30, 1).x; 
                            PlaySound(HitSound);
                            break;
                        }
                    }
                }
            }

            if (TopHit) {
                BALL.y += 200 * GetFrameTime();
                if (LeftHit) {
                    BALL.x += 200 * GetFrameTime();
                } else if (RightHit) {
                    BALL.x -= 200 * GetFrameTime();
                }

            } else if (PlayerHit) {
                if (!BrickActiveHit) {
                    BALL.y -= 200 * GetFrameTime();
                    if (LeftHit) {
                        BALL.x += 200 * GetFrameTime();
                    } else if (RightHit) {
                        BALL.x -= 200 * GetFrameTime(); }
                } else {
                    BALL.y += 200 * GetFrameTime();
                    if (LeftHit) {
                        BALL.x += 200 * GetFrameTime();
                    } else if (RightHit) {
                        BALL.x -= 200 * GetFrameTime(); }
                }

            } else if (BrickActiveHit) {
                BALL.y += 200 * GetFrameTime();
            }


        } else if (CurrentScene == END) {
            if (IsKeyPressed(KEY_R)) {
                Lives = 3; Point = 0;
                LogoTimer = 2; CurrentScene = LOGO;
            }
        }
        BeginDrawing();
            ClearBackground(GPurple0);
            if (CurrentScene == LOGO) {
                DrawTexture(BackGroundImage, 0, 0, WHITE);
                if (FPSMODE) {
                    DrawFPS_RectangleBackGround(screenHeight, 10, 25, GPurple5);
                }

            } else if (CurrentScene == MENU) {
                if (FPSMODE) {
                    DrawFPS_RectangleBackGround(screenHeight, 10, 25, GPurple5);
                }
                DrawTexture(MainMenuLogo, 600, 200, WHITE);
                DrawButton(&StartButton, DefaultFont);

            } else if (CurrentScene == GAMEPLAY) {
                for (int i = 0; i < MaxRow; i++) {
                    for (int a = 0; a < MaxColumn; a++) {
                        if (Bricks_level0[i][a].BrickBodyDraw) {
                            DrawRectangle(
                                    Bricks_level0[i][a].BrickBody.x, Bricks_level0[i][a].BrickBody.y, 
                                    Bricks_level0[i][a].BrickBody.width,Bricks_level0[i][a].BrickBody.height,
                                    Bricks_level0[i][a].BrickBodyColor );
                        }
                    }
                }

                DrawRectangle(LeftWall.x, LeftWall.y, LeftWall.width, LeftWall.height, GPurple3);
                DrawRectangle(RightWall.x, RightWall.y, RightWall.width, RightWall.height, GPurple3);
                DrawRectangle(TopWall.x, TopWall.y, TopWall.width, TopWall.height, GPurple4);
                DrawRectangle(EndArea.x, EndArea.y, EndArea.width, EndArea.height, GPurple4);

                DrawRectangle(Player.x, Player.y-10, Player.width, Player.height, GPurple3);
                DrawRectangle(BALL.x, BALL.y, BALL.width, BALL.height, GPurple4);

                if (FPSMODE) {
                    DrawFPS_RectangleBackGround(screenHeight, 10, 25, GPurple5);
                }

                DrawText(PointAndLive, screenWidth/2-PointAndLiveWidth/2, 15, 30, GPurple5);


            } else if (CurrentScene == END) {
                if (FPSMODE) {
                    DrawFPS_RectangleBackGround(screenHeight, 10, 25, GPurple5);
                }
                DrawText("Press R Play Again!", 10, 10, 30, GPurple5);
                DrawText("Game Over", screenWidth/2-200, screenHeight/2, 60, GPurple5);
                
            }
        EndDrawing(); }
    // Unload ALL Here
    UnloadSound(HitSound);
    UnloadMusicStream(BG_Music);
    UnloadSound(OutSideSound);

    UnloadTexture(BackGroundImage);
    UnloadTexture(MainMenuLogo);
    free(StartButton.Text);

    CloseWindow();
    return 0; }
