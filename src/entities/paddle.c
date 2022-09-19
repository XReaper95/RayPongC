//
// Created by Luis on 05/04/2021.
//
#include "paddle.h"

static const float paddleFixedHeight = 100.0f;
static const float paddleFixedWidth = 30.0f;
static const float paddleWidthMargin = 15.0f;
static const float paddleMovementFactor = 300.0f;

Paddle createPaddle(const char *name, Color color, bool isLeftPaddle, const ControlScheme *scheme){
  Paddle p = {
      .name = name,
      .color = color,
      .controlScheme = scheme,
      .size = {paddleFixedWidth, paddleFixedHeight}
  };

  resetPaddleState(&p, isLeftPaddle);

  p.size.x = paddleFixedWidth;
  p.size.y = paddleFixedHeight;

  return p;
}

void resetPaddleState(Paddle *p, bool isLeftPaddle){
  if (isLeftPaddle){
    p->pos.x = paddleWidthMargin;
  } else {
    p->pos.x = (float)GetScreenWidth() - paddleWidthMargin - paddleFixedWidth;
  }
  p->pos.y = ((float)GetScreenHeight() / 2) - (paddleFixedHeight / 2);

  p->score = 0;
}

void drawPaddle(const Paddle * p) {
  DrawRectangleV(p->pos, p->size, p->color);
}

void processInput(Paddle * p){
  if (IsKeyDown(p->controlScheme->UP_KEY) && p->pos.y > 0.0f) { // UP
    p->pos.y -= paddleMovementFactor * (float)GetFrameTime();
  }
  if (IsKeyDown(p->controlScheme->DOWN_KEY) && p->pos.y + p->size.y< (float)GetScreenHeight()) { // Down
    p->pos.y += paddleMovementFactor * (float)GetFrameTime();
  }
}

void UpdatePlayerScore(Paddle *p) { p->score++; }
