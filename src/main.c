#include "raylib.h"
#include "entities/paddle.h"
#include <stdio.h>

int main(void)
{
  // WINDOW
  const int screenWidth = 800;
  const int screenHeight = 600;
  const int targetFPS = 144;

  char winTitle[] = "Pong with Raylib";
  InitWindow(screenWidth, screenHeight, winTitle);

  SetTargetFPS(targetFPS);               // Set desired framerate (frames-per-second)

  // INITIALIZE

  Paddle *player1 = createPaddle("XReaper", BLUE, true);
  Paddle *player2 = createPaddle("Opponent", RED, false);

  // Main game loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
  {
    // UPDATE

    SetWindowTitle(TextFormat("%s FPS - %d", winTitle, GetFPS()));

    // DRAW

    BeginDrawing();

    ClearBackground(BLACK);

    DrawPaddle(player1);
    DrawPaddle(player2);

    EndDrawing();
  }

  // DESTROY

  destroyPaddle(player1);
  destroyPaddle(player2);
  CloseWindow();        // Close window and OpenGL context


  return 0;
}