#include "main.h"



int main() {
	// Settings
    const int ScreenWidth = 1600;
    const int ScreenHeight = 900;
    const char GameTitle[] = "UwU";
    int CurrentScene = LogoScene;
	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);

	InitWindow(ScreenWidth, ScreenHeight, GameTitle);
	SetExitKey(KEY_NULL);
	Vector2 MouseCursor = { 0.0f, 0.0f };

    _CameraGO GO = GOCAM();

	ProgressBar logoBar = CreateProgressBar( (float)ScreenWidth/2, ScreenHeight-60, (float)ScreenWidth/2, 30, Purple5, Purple8, 3);
	Button StartButton = CreateButton("This Is My Kingdom COME This Is My Kingdom COME!", "./Font/FreeSans.ttf", 30, 10, 50, YELLOW, RED, GREEN, BLUE); 
	CheckBox WindowModeButton = CreateCheckBox(10, 100, 50, 50, RED, GREEN, BLUE, YELLOW);


	ModelAndAnimation testAnimModel = CreateAnimationModel(
		"./3D/tutorialCharachter0.m3d",
		(Vector3){0.0f, 0.0f, 0.0f},
		(Vector3){5.0f, 5.0f, 5.0f},
		(Vector3){0.0f, 0.0f, 0.0f},
		0
	);



	SetTargetFPS(60);
	while (!WindowShouldClose()) {

		// Update
		switch (CurrentScene) {
			case LogoScene:
				if (UpdateProgressBar(&logoBar)) { CurrentScene = MenuScene; }
				break;
			case MenuScene:
				MouseCursor = GetMousePosition();
				UpdateButton(&StartButton, MouseCursor);
				if (StartButton.ButtonPressReady) {
					CurrentScene = GameScene;
					DisableCursor();
				}

				UpdateCheckbox(&WindowModeButton, MouseCursor);
				if (WindowModeButton.Press) {
					printf("YES \n");
				}


				break;
			case GameScene:
                FPS(&GO);
				PlayAnimation(&testAnimModel);


				break;
			case EndScene:
				break;
		
		}
		BeginDrawing();
			ClearBackground(Purple0);
			BeginMode3D(GO.GO);
				switch (CurrentScene) {
					case LogoScene:
						break;
					
                    
                    case MenuScene:



						break;
					case GameScene:
						DrawGrid(10, 1.0f);
						//DrawModelEx( testAnimModel.ThisModel, testAnimModel.ThisModelPosition, testAnimModel.ThisModelRotation, 0, testAnimModel.ThisModelScale, WHITE );
						
						DrawModelAndAnimation(&testAnimModel);

						break;
					case EndScene:



                    break;
				}
			EndMode3D();

			// UI
			switch (CurrentScene) {
				case LogoScene:
					DrawProgressBar(&logoBar);
					
					
					
					
					break;
				case MenuScene:
					DrawButton(&StartButton);
					DrawCheckbox(&WindowModeButton);


					break;
				case GameScene:
					break;
				case EndScene:
					break;
			}
			DrawFPS(10, 10);
		EndDrawing();
	}



	CloseWindow();
    return 0; }
