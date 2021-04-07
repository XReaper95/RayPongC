//
// Created by Luis on 05/04/2021.
//

#include <stdlib.h>

#include "raylib.h"
#include "paddle.h"

#define PADDLE_FIXED_HEIGHT 100.0f
#define PADDLE_FIXED_WIDTH 30.0f

#define PADDLE_WIDTH_MARGIN 15.0f


Paddle* createPaddle(const char *name, Color color, bool leftPaddle){
  Paddle *paddle = malloc(sizeof(Paddle));
  paddle->name = name;
  paddle->color = color;

  if (leftPaddle){
    paddle->pos.x = PADDLE_WIDTH_MARGIN;
  } else {
    paddle->pos.x = (float)GetScreenWidth() - PADDLE_WIDTH_MARGIN - PADDLE_FIXED_WIDTH;
  }
  paddle->pos.y = ((float)GetScreenHeight() / 2) - (PADDLE_FIXED_HEIGHT / 2);

  paddle->size.x = PADDLE_FIXED_WIDTH;
  paddle->size.y = PADDLE_FIXED_HEIGHT;
  CheckCollisionCircleRec()
  return paddle;
}
void DrawPaddle(const Paddle* paddle) {
  DrawRectangleV(
      paddle->pos,
      paddle->size,
      paddle->color
      );
}
void destroyPaddle(Paddle * paddle) {
  free(paddle);
}


