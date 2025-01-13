#ifndef  UIFILE
#define UIFILE

#include "main.h"
#include <raylib.h>

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

Button CreateButton(char *Text, char *TextFont, int TextSize, float X, float Y, Color NormalColor, Color HoverColor, Color PressColor); 
void UpdateButton(Button *ThisButton, Vector2 MouseCursor); 
void DrawButton(Button *ThisButton);




#endif
