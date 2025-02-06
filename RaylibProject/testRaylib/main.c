#include "main.h"
#include <raylib.h>

// don't touch this or light not working in main.h must in here
#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif
// don't touch this or light not working in main.h must in here


int main(int argc, char const *argv[]) {
	// Settings
    const int ScreenWidth = 1600;
    const int ScreenHeight = 900;
    const char GameTitle[] = "UwU";
    int CurrentScene = LogoScene;
	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);

	InitWindow(ScreenWidth, ScreenHeight, GameTitle);
	SetExitKey(KEY_NULL);
	Vector2 MouseCursor = { 0.0f, 0.0f };

	// Extra Func 
 	_CameraGO GO = GOCAM();
	ProgressBar logoBar = CreateProgressBar( (float)ScreenWidth/2, ScreenHeight-60, (float)ScreenWidth/2, 30, Purple5, Purple8, 3);
	Button StartButton = CreateButton("This Is My Kingdom COME This Is My Kingdom COME!", "./Font/FreeSans.ttf", 30, 10, 50, RED, GREEN, BLUE); 



	// don't touch it
    Shader shader = LoadShader(
		TextFormat("./shaders/lighting.vs", GLSL_VERSION),
        TextFormat("./shaders/lighting.fs", GLSL_VERSION)
	); shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
    int ambientLoc = GetShaderLocation(shader, "ambient");
    SetShaderValue(shader, ambientLoc, (float[4]){ 0.1f, 0.1f, 0.1f, 1.0f }, SHADER_UNIFORM_VEC4);
	// don't touch it

    // Create lights
    Light lights[MAX_LIGHTS] = { 0 };
    lights[0] = CreateLight(LIGHT_POINT, (Vector3){ 3.0,  3.0, 0.0 }, Vector3Zero(), WHITE, shader);
	lights[1] = CreateLight(LIGHT_POINT, (Vector3){ -3.0, 3.0, 0.0 }, Vector3Zero(), WHITE, shader);
	lights[2] = CreateLight(LIGHT_POINT, (Vector3){ 0.0,  3.0, 3.0 }, Vector3Zero(), WHITE, shader);
	lights[3] = CreateLight(LIGHT_POINT, (Vector3){ 0.0,  3.0, -3.0 }, Vector3Zero(), WHITE, shader);


	// models
	JustModel TestModel = CreateJustModel_Object("./3D/Cardis.m3d", (Vector3){0.0f, 0.0f, 0.0f}, (Vector3){10.0f, 10.0f, 10.0f});

	Texture TestModelTextures[1] = {
		LoadTexture("./3D/fullColorAtlas.png"),    };

	AddTextureToIndex(&TestModel, 1, TestModelTextures[0]); // Default Color Atlas
	AddTextureToIndex(&TestModel, 2, TestModelTextures[0]); // Screen
	AddTextureToIndex(&TestModel, 3, TestModelTextures[0]); // center
	AddTextureToIndex(&TestModel, 4, TestModelTextures[0]); // not finish screen
	AddTextureToIndex(&TestModel, 5, TestModelTextures[0]); // tesseract

	// TestModel.materials[2].maps[MATERIAL_MAP_ALBEDO].color = RED;

	// add light shader in model materials
	for (int i = 0; i < TestModel.ThisModel.materialCount; i++) {
	 	TestModel.ThisModel.materials[i].shader = shader;
	}


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


				break;
			case GameScene:
				FPS(&GO);




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
						BeginShaderMode(shader);
							DrawModelEx(
								TestModel.ThisModel,
								TestModel.ThisModelPosition,
								(Vector3){0.0f, 0.0f, 0.0f},
								0,
								TestModel.ThisModelBody,
								WHITE
							);
							DrawGrid(10, 1.0f);

						EndShaderMode();

						// Draw spheres to show where the lights are
						for (int i = 0; i < MAX_LIGHTS; i++) {
							DrawSphereEx(lights[i].position, 0.2f, 8, 8, lights[i].color);
						}



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


					break;
				case GameScene:
					break;
				case EndScene:
					break;
			}
			DrawFPS(10, 10);
		EndDrawing();
	}

	// Unload ALL or i will KILL YOU!!!
	UnloadShader(shader);

	CloseWindow();
    return 0; }
