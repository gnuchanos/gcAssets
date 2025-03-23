#include "main.h"

// Progress Bar ================================================================================================================================
ProgressBar CreateProgressBar ( float X, float Y, float SizeX, float SizeY, Color FirstBarColor, Color SecondBarColor, int Time ) {
	ProgressBar ThisProgressBar;
		ThisProgressBar.FirstBar           = (Rectangle){ X-SizeX/2, Y, SizeX, SizeY };
		ThisProgressBar.SecondBar          = (Rectangle){ X-SizeX/2+5, Y+5, SizeX-10, SizeY-10 };
		ThisProgressBar.FirstBarColor      = FirstBarColor;
		ThisProgressBar.SecondBarColor     = SecondBarColor;
		ThisProgressBar.Time               = Time;
		ThisProgressBar.wait               = GetFrameTime();
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
Button CreateButton(char *Text, char *TextFont, int TextSize, float X, float Y, Color TextColor, Color NormalColor, Color HoverColor, Color PressColor) { 
	Button ThisButton;
		ThisButton.ButtonPressReady    = false;
		ThisButton.ButtonPressCheck    = false;

		ThisButton.ButtonText          = (char *)malloc((strlen(Text) + 1));
		strcpy(ThisButton.ButtonText, Text);

		ThisButton.TextColor = TextColor;

		ThisButton.CurrentButtonColor  = NormalColor;
		ThisButton.ButtonNormalColor   = NormalColor;
		ThisButton.ButtonHoverColor    = HoverColor;
		ThisButton.ButtonPressColor    = PressColor;
		ThisButton.ButtonPressWaitTime = 2.0f;
		
		ThisButton.ButtonTextSize      = TextSize;
		ThisButton.ButtonTextFont      = LoadFont(TextFont);
		ThisButton.ButtonFontSize      = MeasureTextEx(ThisButton.ButtonTextFont, Text, ThisButton.ButtonTextSize, 1); 
		ThisButton.ButtonSize          = (Rectangle){X, Y, ThisButton.ButtonFontSize.x+20, ThisButton.ButtonFontSize.y+10 };
	return ThisButton;
}

void DrawButton(Button *ThisButton) {
	DrawRectangleRounded(ThisButton->ButtonSize, 3, 8, ThisButton->CurrentButtonColor);
	DrawTextEx(
		ThisButton->ButtonTextFont, 
		ThisButton->ButtonText, 
		(Vector2){ThisButton->ButtonSize.x+10, ThisButton->ButtonSize.y+5}, 
		ThisButton->ButtonTextSize, 
		1.0f, 
		ThisButton->TextColor	
	);
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
// Button =====================================================================================================================================


// Checkbox ========================================================================================================================================================
CheckBox CreateCheckBox(float x, float y, float SizeX, float SizeY, Color CheckboxButtonColor, Color TickBoxNormalColor, Color TickBoxColorHover, Color TickBoxActiveColor) {
	CheckBox ThisCheckbox;

	ThisCheckbox.CheckButton         = (Rectangle){ x, y, SizeX, SizeY };
	ThisCheckbox.TickBox             = (Rectangle){ x+5, y+5, SizeX-10, SizeY-10 };
	ThisCheckbox.CheckButtonColor    = CheckboxButtonColor;
	ThisCheckbox.TickBoxColorNormal  = TickBoxNormalColor;
	ThisCheckbox.TickBoxColorHover   = TickBoxColorHover;
	ThisCheckbox.TickBoxCurrentColor = TickBoxNormalColor;
	ThisCheckbox.TickBoxActiveColor  = TickBoxActiveColor;
	ThisCheckbox.Press               = false;

	return ThisCheckbox;
}

void DrawCheckbox(CheckBox *ThisCheckbox) {
	DrawRectangle(
		ThisCheckbox->CheckButton.x,
		ThisCheckbox->CheckButton.y,
		ThisCheckbox->CheckButton.width,
		ThisCheckbox->CheckButton.height,
		ThisCheckbox->CheckButtonColor
	);
	DrawRectangle(
		ThisCheckbox->TickBox.x,
		ThisCheckbox->TickBox.y,
		ThisCheckbox->TickBox.width,
		ThisCheckbox->TickBox.height,
		ThisCheckbox->TickBoxCurrentColor
	);
}

void UpdateCheckbox(CheckBox *ThisCheckbox, Vector2 MousePosition) {
	if (CheckCollisionPointRec(MousePosition, ThisCheckbox->CheckButton)) {	
		if (!ThisCheckbox->Press) { ThisCheckbox->TickBoxCurrentColor = ThisCheckbox->TickBoxColorHover; }
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			if (!ThisCheckbox->Press) {
				ThisCheckbox->Press = true;
				ThisCheckbox->TickBoxCurrentColor = ThisCheckbox->TickBoxActiveColor;
			} else {
				ThisCheckbox->Press = false;
			}
		}
	} else {
		if (!ThisCheckbox->Press){
			ThisCheckbox->TickBoxCurrentColor = ThisCheckbox->TickBoxColorNormal;
		}
	}
}
// Checkbox ========================================================================================================================================================













