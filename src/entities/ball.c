//
// Created by Luis on 08/04/2021.
//

#include <malloc.h>
#include <math.h>
#include "ball.h"
#include "raylib.h"
#include "../system/game.h"

extern Game *game;

static const float fixedBallRadius = 15.0f;
static const int maxInitialArcAngleDeg = 45;

static const double fixedBallSpeedFactor = 450.0;

static double getAngleInRadians_(int angle){
  double resultInRadians = (double)angle * PI / 180;
  return resultInRadians;
}

static double getBallInitialRandomAngle_(){
  int result;
  int selectRightOrLeft = GetRandomValue(0, 1);

  if (selectRightOrLeft == 0){
    result = GetRandomValue(180 - maxInitialArcAngleDeg, 180 + maxInitialArcAngleDeg);
  } else {
    result = GetRandomValue(360 - maxInitialArcAngleDeg, 360 + maxInitialArcAngleDeg);
  }

  return getAngleInRadians_(result);
}

Ball* createBall(){
  Ball *b = malloc(sizeof(Ball));
  b->pos.x = (float)GetScreenWidth() / 2;
  b->pos.y = (float)GetScreenHeight() / 2;
  b->radius = fixedBallRadius;

  double initialAngle = getBallInitialRandomAngle_();
  b->velX = fixedBallSpeedFactor * cos(initialAngle);
  b->velY = fixedBallSpeedFactor * sin(initialAngle);

  b->frozen = true;
  b->screenEdgeCollision = false;
  b->paddleSideCollision = false;
  b->paddleTBCollision = false;
  b->disablePaddleCollision = false;
  b->color = YELLOW;
  return b;
}

void drawBall(const Ball* b){
  DrawCircleV(b->pos, b->radius, b->color);
}

void processBallMovement(Ball* b){
  if (IsKeyPressed(KEY_SPACE) && b->frozen){
    b->frozen = false;
  }

  if (!b->frozen){
    double velocityX = b->velX * GetFrameTime();
    double velocityY = b->velY * GetFrameTime();

    if (b->screenEdgeCollision) {
      b->velY *= -1.0f;
      b->screenEdgeCollision = false;
    }
    if (b->paddleSideCollision) {
      b->velX *= -1.0f;
      b->paddleSideCollision = false;

    }
    if (b->paddleTBCollision) {
      b->velY *= -1.0f;
      b->paddleTBCollision = false;
      b->disablePaddleCollision = true;
    }

    b->pos.x += (float)velocityX;
    b->pos.y += (float)velocityY;
  }
};

void ballBorderCollision(Ball* b){
  double velocityY = b->velY * GetFrameTime();

  // collide with bottom border
  if (b->pos.y + b->radius + velocityY >= (float)GetScreenHeight()){
    b->screenEdgeCollision = true;
  }

  // collide with top border
  if (b->pos.y - b->radius + velocityY < 0){
    b->screenEdgeCollision = true;
  }

}

void ballPaddleCollision(Ball* b, Paddle *p){
  float velocityX = (float)b->velX * GetFrameTime();
  float velocityY = (float)b->velY * GetFrameTime();

  float ballX = b->pos.x + velocityX;
  float ballY = b->pos.y + velocityY;
  float paddleLeftSide = p->pos.x;
  float paddleRightSide = p->pos.x +  p->size.x;
  float paddleTopSide = p->pos.y;
  float paddleBottomSide = p->pos.y + p->size.y;

  float testX = ballX;
  float testY = ballY;

  if (ballX < paddleLeftSide)        testX = paddleLeftSide;
  else if (ballX > paddleRightSide)  testX = paddleRightSide;
  if (ballY < paddleTopSide)         testY = paddleTopSide;
  else if (ballY > paddleBottomSide) testY = paddleBottomSide;

  float distX = ballX-testX;
  float distY = ballY-testY;
  float distance = sqrtf( (distX*distX) + (distY*distY));

  if (distance <= b->radius) {
    if (distY == 0.0f){
      b->paddleSideCollision = true;
    } else {
      b->paddleTBCollision = true;
    }
  }
}
