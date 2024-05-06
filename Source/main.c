#include "Include/main.h"


int main(void) {
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_MSAA_4X_HINT); 
    InitWindow(WindowWitdh, WindowHeight, WindowTitle);

    TraceLog(LOG_INFO, "Time After InitWindow:%f", GetTime());

    SetExitKey(KEY_NULL);
    SetWindowState(FLAG_VSYNC_HINT);

    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 2.5f, 5.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 1.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    Object3D BetaVegas = BetaNewVegas();
    int BetaVegasAnimsCount = 0, BetaVegasAnimFrameCounter = 0;
    ModelAnimation *BetaVegasAnims = LoadModelAnimations(BetaVegas.FilePath, &BetaVegasAnimsCount);

    Object3D tBody = TardisBody();
    int tBodyAnimsCount = 0, tBodyAnimFrameCounter = 0;
    ModelAnimation *tBodyAnims = LoadModelAnimations(tBody.FilePath, &tBodyAnimsCount);

    bool openTardisDoor = false;
    bool startAnimationTardisDoor = false;

    Object3D TardisScene = TardisInside();
    Object3D rRoom = RedRoom();


    // testing area
    char debug[100];
    bool cursorVisible = false;
    bool tardisVisible = false;



    // ekstra variable
    Vector2 MousePosition = { 0.0f, 0.0f};
    float Speed = 2.5f;
    bool chMove = true;
    int Scene = 1;
    bool noCameraFallow = false;
    bool jump = false;

    // unload things array
    Model UnloadModelArray[2] = {
        BetaVegas.Obj,
        TardisScene.Obj
    }; int UnloadModelArraySizeOf = sizeof(UnloadModelArray) / sizeof(UnloadModelArray[0]);

    Texture2D UnloadTextureArray[3] = {
        BetaVegas.Texture[0],
        BetaVegas.Texture[1],
        TardisScene.Texture[0]
    }; int UnloadTextureArraySizeOf = sizeof(UnloadTextureArray) / sizeof(UnloadTextureArray[0]);

    // ready for render
    Shader shader = LoadShader(0, TextFormat("./Assets/Shader/bloom.fs", GLSL_VERSION));
    RenderTexture2D target = LoadRenderTexture(WindowWitdh, WindowHeight);
    Rectangle ShaderRectangle = (Rectangle){ 0, 0, (float)target.texture.width, (float)-target.texture.height };
    Vector2 ShaderVector2 = (Vector2){ 0, 0 };
    SetTargetFPS(60); DisableCursor();
    while (!WindowShouldClose()) {

        // change scene
        if (IsKeyPressed(KEY_ONE)) { Scene = 1; noCameraFallow = false; }
        if (IsKeyPressed(KEY_TWO)) { Scene = 2; noCameraFallow = true; }
        if (IsKeyPressed(KEY_THREE)) { Scene = 3; noCameraFallow = true; }

        // move camera or body
        if (IsKeyPressed(KEY_GRAVE) && chMove) { chMove = false; } 
        else if (IsKeyPressed(KEY_GRAVE) && !chMove) { chMove = true; }

        // visible cursor
        if (IsKeyPressed(KEY_TAB) && !cursorVisible) { cursorVisible = true; EnableCursor(); }
        else if (IsKeyPressed(KEY_TAB) && cursorVisible) { cursorVisible = false; DisableCursor(); }


        // visible tardis
        if (IsKeyPressed(KEY_LEFT_ALT) && !tardisVisible) { tardisVisible = true; }
        else if (IsKeyPressed(KEY_LEFT_ALT) && tardisVisible) { tardisVisible = false; }

        // tardis door open
        if (IsKeyPressed(KEY_LEFT) && !openTardisDoor) { 
            startAnimationTardisDoor = true;
            tBodyAnimFrameCounter = 0; 
        } else if (IsKeyPressed(KEY_LEFT) && openTardisDoor) { 
            startAnimationTardisDoor = true;
            tBodyAnimFrameCounter = 0;
        }

        if (startAnimationTardisDoor) {
            if (!openTardisDoor) {
                if (tBodyAnimFrameCounter < 108) {
                    tBodyAnimFrameCounter++;
                    UpdateModelAnimation(tBody.Obj, tBodyAnims[0], tBodyAnimFrameCounter);
                }
                else { openTardisDoor = true; startAnimationTardisDoor = false; }
            } else {
                if (tBodyAnimFrameCounter < 108) {
                    tBodyAnimFrameCounter++;
                    UpdateModelAnimation(tBody.Obj, tBodyAnims[1], tBodyAnimFrameCounter);
                }
                else { openTardisDoor = false; startAnimationTardisDoor = false;}
            }
        }

        sprintf(debug, " | X:%f | Y:%f |  Z:%f | ", BetaVegas.Position.x, BetaVegas.Position.y, BetaVegas.Position.z);

        if (chMove) {
            if (IsKeyDown(KEY_S)) {
                BetaVegasAnimFrameCounter++;
                UpdateModelAnimation(BetaVegas.Obj, BetaVegasAnims[2], BetaVegasAnimFrameCounter);
            } else if (IsKeyDown(KEY_W)) {
                BetaVegasAnimFrameCounter++;
                UpdateModelAnimation(BetaVegas.Obj, BetaVegasAnims[1], BetaVegasAnimFrameCounter);
            } else {
                BetaVegasAnimFrameCounter++;
                UpdateModelAnimation(BetaVegas.Obj, BetaVegasAnims[0], BetaVegasAnimFrameCounter);
            }

            MousePosition = GetMousePosition();
            BetaVegas.Rotation.y = -MousePosition.x;

            // Cos ve sin eklenmiş hali
            float cosY = cosf(BetaVegas.Rotation.y * DEG2RAD);
            float sinY = sinf(BetaVegas.Rotation.y * DEG2RAD);

            
            if (IsKeyDown(KEY_W)) {
                BetaVegas.Position.x -= cosY * Speed * GetFrameTime();
                BetaVegas.Position.z += sinY * Speed * GetFrameTime();
            }
            if (IsKeyDown(KEY_S)) {
                BetaVegas.Position.x += cosY * Speed * GetFrameTime();
                BetaVegas.Position.z -= sinY * Speed * GetFrameTime();
            }

            // jumping
            if (IsKeyPressed(KEY_SPACE) && !jump) { jump = true; }
            if (jump) {
                BetaVegas.Position.y += 5 * GetFrameTime();
                if ((int)BetaVegas.Position.y == 1) { jump = false; }
            }
            else {
                if (BetaVegas.Position.y > 0) {
                    BetaVegas.Position.y -= 5 * GetFrameTime();
                }
            }


            BetaVegas.Obj.transform = MatrixRotateY(BetaVegas.Rotation.y * DEG2RAD);

            if (!noCameraFallow) {
                camera.target.x = BetaVegas.Position.x;
                camera.target.z = BetaVegas.Position.z;
                camera.target.y = BetaVegas.Position.y+2.0f;
            }

        }
        else {
            UpdateCamera(&camera, CAMERA_FIRST_PERSON);
            BetaVegasAnimFrameCounter++;
            UpdateModelAnimation(BetaVegas.Obj, BetaVegasAnims[0], BetaVegasAnimFrameCounter);
        }

        // render 3d Objects
        BeginTextureMode(target);
            ClearBackground(BLACK);

            BeginMode3D(camera);
                DrawModelEx(BetaVegas.Obj, BetaVegas.Position, BetaVegas.Rotation, 0, BetaVegas.Scale, WHITE);
                if (Scene == 1) {
                    DrawModelEx(TardisScene.Obj, TardisScene.Position, TardisScene.Rotation, 0, TardisScene.Scale, WHITE);
                } else if (Scene == 2) {
                    if (tardisVisible) {
                        DrawModelEx(tBody.Obj, tBody.Position, tBody.Rotation, 0, tBody.Scale, WHITE);
                    }
                    DrawModelEx(rRoom.Obj, rRoom.Position, rRoom.Rotation, 0, rRoom.Scale, WHITE);
                } else if (Scene == 3) {

                }
            EndMode3D();
        EndTextureMode();

        // uWu
        BeginDrawing();
            ClearBackground(BLACK);
            BeginShaderMode(shader);
                // NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
                DrawTextureRec(target.texture, ShaderRectangle, ShaderVector2, WHITE);
            EndShaderMode();
            // 2D Drawing
            DrawFPS(10, 15);
            DrawText(debug, 10, 40, 15, WHITE);
        EndDrawing();
    }

    UnloadShader(shader);
    for (int i = 0; i < UnloadModelArraySizeOf; i++) { UnloadModel(UnloadModelArray[i]); }
    for (int i = 0; i < UnloadTextureArraySizeOf; i++) { UnloadTexture(UnloadTextureArray[i]); }

    CloseWindow();
    return 0; }