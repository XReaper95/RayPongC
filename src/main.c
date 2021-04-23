#include "raylib.h"
#include "system/game.h"
#include "system/ui.h"

int main(void)
{
  SetTraceLogLevel(LOG_INFO);

  // WINDOW
  static const int screenWidth = 800;
  static const int screenHeight = 600;
  static const int targetFPS = 60;

  SetConfigFlags(FLAG_MSAA_4X_HINT);

  char winTitle[] = "Pong with Raylib";
  InitWindow(screenWidth, screenHeight, winTitle);
  SetTargetFPS(targetFPS);               // Set desired framerate (frames-per-second)

  // INITIALIZE
  InitAudioDevice();

  loadSounds();

  // Create a RenderTexture2D to be used for render to texture
  RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
  Shader shader = LoadShader(0, "../res/crt.fs");

  Game *game = createGame();
  Color backgroundColor = ColorFromHSV(4, 0.16f, 0.18f);

  // Main game loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
  {
    // UPDATE

    SetWindowTitle(TextFormat("%s FPS - %d", winTitle, GetFPS()));

    // EVENTS
    if (!game->isWon) {
      processGameEvents(game);
    } else {
      game = processGameReset(game);
    }

    ClearBackground(backgroundColor);

    // DRAW
    BeginDrawing();
      BeginTextureMode(target);
        ClearBackground(backgroundColor);
        drawGame(game);
      EndTextureMode();

      BeginShaderMode(shader);
        DrawTextureRec(target.texture,
                       (Rectangle){ 0, 0, (float)target.texture.width, (float)-target.texture.height },
                       (Vector2){ 0, 0 },
                       WHITE);
      EndShaderMode();

      drawScoreBoard(game);

    EndDrawing();
  }

  // DE-INITIALIZE
  cleanUpGame(game);

  unloadSounds(game->sounds);
  CloseAudioDevice();
  UnloadRenderTexture(target);
  CloseWindow();        // Close window and OpenGL context


  return 0;
}