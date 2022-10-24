#include "raylib.h"
#include "game/game.h"
#include "game/ui.h"
#include "game/sounds.h"

int main() {
    // CONFIGURATION
    static const int screenWidth = 800;
    static const int screenHeight = 600;
    static const int targetFPS = 60;
    const char *windowsTitle = "Pong with Raylib";

    // INITIALIZATION
    SetTraceLogLevel(LOG_INFO);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, windowsTitle);
    SetTargetFPS(targetFPS); // Set desired framerate (frames-per-second)
    InitAudioDevice();
    SoundsLoadAll();

    // SHADERS
    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
    Shader shader = LoadShader(0, "../res/crt.fs");
    Color backgroundColor = ColorFromHSV(207, 0.47f, 0.15f);

    Game game = GameCreate();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // UPDATE
        SetWindowTitle(TextFormat("%s FPS - %d", windowsTitle, GetFPS()));

        // EVENTS
        if (!GameHasWinner(&game)) {
            GameProcessEvents(&game);
        } else {
            GameReset(&game);
        }

        ClearBackground(backgroundColor);

        // DRAW
        BeginDrawing();
        BeginTextureMode(target);
        ClearBackground(backgroundColor);
        GameDraw(&game);
        EndTextureMode();


        BeginShaderMode(shader);
        DrawTextureRec(target.texture,
                       (Rectangle) {0, 0, (float) target.texture.width, (float) -target.texture.height},
                       (Vector2) {0, 0},
                       WHITE);
        EndShaderMode();

        UIDrawScoreBoard(&game.leftPaddle, &game.rightPaddle);

        if (GameHasWinner(&game)) {
            GameProcessWonState(&game);
        }

        EndDrawing();
    }

    // DE-INITIALIZATION
    CloseAudioDevice();
    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}