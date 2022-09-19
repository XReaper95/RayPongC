#include <stdlib.h>
#include "raylib.h"
#include "system/game.h"
#include "system/ui.h"
#include "system/sounds.h"

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
  SetTargetFPS(targetFPS); // Set desired framerate (frames-per-second)

  // INITIALIZE
  InitAudioDevice();

  LoadGameSounds();

  // Entities
  Game game = CreateGame();
  // SHADERS
  RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
  Shader shader = LoadShader(0, "../res/crt.fs");
  Color backgroundColor = ColorFromHSV(207, 0.47f, 0.15f);

  // Main game loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
  {
    // UPDATE

    SetWindowTitle(TextFormat("%s FPS - %d", winTitle, GetFPS()));

    // EVENTS
    if (game.winner == NULL) {
      ProcessGameEvents(&game);
    } else {
      ProcessGameReset(&game);
    }

    ClearBackground(backgroundColor);

    // DRAW
    BeginDrawing();
      BeginTextureMode(target);
        ClearBackground(backgroundColor);
        DrawGame(&game);
      EndTextureMode();


      BeginShaderMode(shader);
        DrawTextureRec(target.texture,
                       (Rectangle){ 0, 0, (float)target.texture.width, (float)-target.texture.height },
                       (Vector2){ 0, 0 },
                       WHITE);
      EndShaderMode();

      DrawScoreBoard(&game);

    if (game.winner != NULL){
      ProcessWonState(&game);
    }

    EndDrawing();
  }

  CloseAudioDevice();
  UnloadRenderTexture(target);
  CloseWindow();        // Close window and OpenGL context

  return 0;
}