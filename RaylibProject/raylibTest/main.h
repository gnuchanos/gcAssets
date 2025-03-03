#ifndef MAINFILE
#define MAINFILE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <raylib.h>
#include <raymath.h>

// Colors
#define Purple0 CLITERAL(Color){  11, 0,  20, 255 }
#define Purple1 CLITERAL(Color){  20, 0,  38, 255 }
#define Purple2 CLITERAL(Color){  28, 0,  51, 255 }
#define Purple3 CLITERAL(Color){  43, 0,  79, 255 }
#define Purple4 CLITERAL(Color){  61, 0, 112, 255 }
#define Purple5 CLITERAL(Color){  84, 2, 153, 255 }
#define Purple6 CLITERAL(Color){ 103, 2, 190, 255 }
#define Purple7 CLITERAL(Color){ 117, 2, 214, 255 }
#define Purple8 CLITERAL(Color){ 129, 0, 237, 255 }
#define Purple9 CLITERAL(Color){ 139, 3, 252, 255 }

// Scenes
typedef enum {
    LogoScene = 0,
    MenuScene = 1,
    GameScene = 2,
    EndScene  = 3
} GC_Scenes;



// FPS =======================================================================================================================================
typedef struct {
    Camera3D GO;
    Vector3 RecordCamPosition;
    Vector3 BodySize;
    bool BodyHitWall;
    bool ShowMouse;
} _CameraGO;

_CameraGO GOCAM();
void FPS(_CameraGO *Player);




// Progress Bar ==============================================================================================================================
typedef struct {
    Rectangle FirstBar;
	Rectangle SecondBar;
	Color FirstBarColor;
	Color SecondBarColor;
	int Time;
	float divideTimeAndWidth;
	float wait;
} ProgressBar;

ProgressBar CreateProgressBar ( float X, float Y, float SizeX, float SizeY, Color FirstBarColor, Color SecondBarColor, int Time ); 
void DrawProgressBar ( ProgressBar *ThisProgressBar );
bool UpdateProgressBar ( ProgressBar *ThisProgressBar );

// Button ====================================================================================================================================
typedef struct {
	char   *ButtonText;
	Color   TextColor;
	int     ButtonTextSize;
	Rectangle ButtonSize;
	Color   CurrentButtonColor;
	Color   ButtonNormalColor;
	Color   ButtonHoverColor;
	Color   ButtonPressColor;
	float   ButtonPressWaitTime;
	bool    ButtonPressCheck;
	Font    ButtonTextFont;
	Vector2 ButtonFontSize;
	bool    ButtonPressReady;
} Button;

Button CreateButton(char *Text, char *TextFont, int TextSize, float X, float Y, Color TextColor, Color NormalColor, Color HoverColor, Color PressColor); 
void UpdateButton(Button *ThisButton, Vector2 MouseCursor); 
void DrawButton(Button *ThisButton);


typedef struct {
	bool       Press;
	Rectangle  CheckButton;
	Rectangle  TickBox;
	Color      CheckButtonColor;
	Color      TickBoxCurrentColor;
	Color      TickBoxColorNormal;
	Color      TickBoxColorHover;
	Color      TickBoxActiveColor;
} CheckBox;


CheckBox CreateCheckBox(float x, float y, float SizeX, float SizeY, Color CheckboxButtonColor, Color TickBoxNormalColor, Color TickBoxColorHover, Color TickBoxActiveColor);
void DrawCheckbox(CheckBox *ThisCheckbox);
void UpdateCheckbox(CheckBox *ThisCheckbox, Vector2 MousePosition);

// Model.C ====================================================================================================================================

typedef struct {
	char    *ModelPath;
	Model    ThisModel;
	int      ThisModelAnimsCount;
	int      ThisModelAnimIndex;
	int      ThisModelAnimsCurrentFrame;
	ModelAnimation *ThisModelAnimations;	
} ModelAndAnimation;

typedef struct {
	char    *ModelPath;
	Model    ThisModel;
	Vector3  ThisModelPosition;
	Vector3  ThisModelBody;
} JustModel; // regular model no animation

// CreateModel
JustModel CreateJustModel_Object(char *ModelPath, Vector3 Position, Vector3 Scale);
ModelAndAnimation CreateModelAndAnimation_Object (char *ModelPath, int ThisModelAnimIndex);
void AddTextureToIndex(JustModel *ThisModel, int index, Texture ThisTexture);

void DrawJustModel(JustModel *ThisModel);
void DrawModelAndAnimation(ModelAndAnimation *ThisModelAndAnimation);

// Collision
void CheckModelCollision(_CameraGO ThisPlayer, JustModel ThisModel);
void CheckWallCollision(_CameraGO  ThisPlayer, Vector3 WallsPosition, Vector3 WallsScale);





















#endif
