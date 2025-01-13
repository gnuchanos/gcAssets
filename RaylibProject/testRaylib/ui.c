#include "ui.h"
#include "main.h"

// Progress Bar ================================================================================================================================
ProgressBar CreateProgressBar ( float X, float Y, float SizeX, float SizeY, Color FirstBarColor, Color SecondBarColor, int Time ) {
	ProgressBar ThisProgressBar;
		ThisProgressBar.FirstBar       = (Rectangle){ X-SizeX/2, Y, SizeX, SizeY };
		ThisProgressBar.SecondBar      = (Rectangle){ X-SizeX/2+5, Y+5, SizeX-10, SizeY-10 };
		ThisProgressBar.FirstBarColor  = Purple5;
		ThisProgressBar.SecondBarColor = Purple8;
		ThisProgressBar.Time  = Time;
		ThisProgressBar.wait  = GetFrameTime();
		ThisProgressBar.divideTimeAndWidth = ThisProgressBar.SecondBar.width/ThisProgressBar.Time;
	return ThisProgressBar;
}

void DrawProgressBar(ProgressBar *ThisProgressBar) {
	DrawRectangleRounded(ThisProgressBar->FirstBar, 8, 4, ThisProgressBar->FirstBarColor);
	DrawRectangleRounded(ThisProgressBar->SecondBar, 8, 4, ThisProgressBar->SecondBarColor);
}

bool UpdateProgressBar(ProgressBar *ThisProgressBar) { 
	// width / time
	if (ThisProgressBar->wait > 0) {
		ThisProgressBar->wait -= GetFrameTime();
	} else {
		ThisProgressBar->SecondBar.width -= ThisProgressBar->divideTimeAndWidth;
		ThisProgressBar->wait = 0.5;
	}
	
	if ( ThisProgressBar->SecondBar.width <= 0 ) {
		return true;
	} 
	return false;
}



// Button =====================================================================================================================================
Button CreateButton(char *Text, char *TextFont, int TextSize, float X, float Y, Color NormalColor, Color HoverColor, Color PressColor) { 
	Button ThisButton;
		ThisButton.ButtonPressReady = false;
		ThisButton.ButtonPressCheck = false;

		ThisButton.ButtonText = (char *)malloc((strlen(Text) + 1));
		strcpy(ThisButton.ButtonText, Text);

		ThisButton.CurrentButtonColor = NormalColor;
		ThisButton.ButtonNormalColor = NormalColor;
		ThisButton.ButtonHoverColor  = HoverColor;
		ThisButton.ButtonPressColor  = PressColor;
		ThisButton.ButtonPressWaitTime = 2.0f;
		
		ThisButton.ButtonTextSize = TextSize;
		ThisButton.ButtonTextFont = LoadFont(TextFont);
		ThisButton.ButtonFontSize = MeasureTextEx(ThisButton.ButtonTextFont, Text, ThisButton.ButtonTextSize, 1); 
		ThisButton.ButtonSize = (Rectangle){X, Y, ThisButton.ButtonFontSize.x+20, ThisButton.ButtonFontSize.y+10 };
	return ThisButton;
}

void DrawButton(Button *ThisButton) {
	DrawRectangleRounded(ThisButton->ButtonSize, 3, 8, ThisButton->CurrentButtonColor);
	DrawTextEx(ThisButton->ButtonTextFont, ThisButton->ButtonText, (Vector2){ThisButton->ButtonSize.x+10, ThisButton->ButtonSize.y+5}, ThisButton->ButtonTextSize, 1.0f, WHITE);
}

void UpdateButton(Button *ThisButton, Vector2 MouseCursor) {
	if (CheckCollisionPointRec(MouseCursor, ThisButton->ButtonSize)) {
		ThisButton->CurrentButtonColor = ThisButton->ButtonHoverColor;
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			ThisButton->CurrentButtonColor = ThisButton->ButtonPressColor;
			ThisButton->ButtonPressCheck = true;
		}
	} else { ThisButton->CurrentButtonColor = ThisButton->ButtonNormalColor; }

	if (ThisButton->ButtonPressCheck) {
		if (ThisButton->ButtonPressWaitTime > 1) {
			ThisButton->ButtonPressWaitTime -= GetFrameTime();
		} else {
			ThisButton->ButtonPressReady = true;
			ThisButton->ButtonPressCheck = false;
		}
	}
	
}
