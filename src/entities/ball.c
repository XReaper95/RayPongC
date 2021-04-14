//
// Created by Luis on 08/04/2021.
//

#include <malloc.h>
#include <math.h>
#include "ball.h"
#include "raylib.h"

static const float fixedBallRadius = 5.0f;
static const int maxInitialArcAngleDeg = 45;

static const double fixedBallSpeedFactor = 0.4;

static double getBallInitialAngle(){
  int result;
  int selectRightOrLeft = GetRandomValue(0, 1);

  if (selectRightOrLeft == 0){
    result = GetRandomValue(180 - maxInitialArcAngleDeg, 180 + maxInitialArcAngleDeg);
  } else {
    result = GetRandomValue(360 - maxInitialArcAngleDeg, 360 + maxInitialArcAngleDeg);
  }

  float resultInRadians = (float)(result) * PI / 180;

  return (double)resultInRadians;
}

Ball* createBall(Color color){
  Ball *b = malloc(sizeof(Ball));
  b->pos.x = (float)GetScreenWidth() / 2;
  b->pos.y = (float)GetScreenHeight() / 2;
  b->radius = fixedBallRadius;
  b->color = color;
  b->frozen = true;
  b->initialAngle = getBallInitialAngle();

  return b;
}

void drawBall(const Ball* b){
  DrawCircleV(b->pos, b->radius, b->color);
}

void processBallMovement(Ball* b){
  if (IsKeyDown(KEY_SPACE) && b->frozen){
    b->frozen = false;
  }

  if (!b->frozen){
    b->pos.x += (float)((fixedBallSpeedFactor * GetFrameTime() * 1000.0) * cos(b->initialAngle));
    b->pos.y += (float)((fixedBallSpeedFactor * GetFrameTime() * 1000.0) * sin(b->initialAngle));
  }
};
