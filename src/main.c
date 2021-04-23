#include "raylib.h"
#include "system/game.h"

int main(void)
{
  SetTraceLogLevel(LOG_INFO);

  // WINDOW
  static const int screenWidth = 800;
  static const int screenHeight = 600;
  static const int targetFPS = 0;

  char winTitle[] = "Pong with Raylib";
  InitWindow(screenWidth, screenHeight, winTitle);
  SetTargetFPS(targetFPS);               // Set desired framerate (frames-per-second)

  // INITIALIZE

  Game *game = createGame();

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

    // DRAW
    BeginDrawing();
    ClearBackground(BLACK);

    drawGame(game);

    EndDrawing();
  }

  // DESTROY
  cleanUpGame(game);

  CloseWindow();        // Close window and OpenGL context


  return 0;
}