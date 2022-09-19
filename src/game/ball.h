//
// Created by Luis on 08/04/2021.
//

#ifndef RAY_PONG_C_SRC_ENTITIES_BALL_H_
#define RAY_PONG_C_SRC_ENTITIES_BALL_H_

#include "paddle.h"

typedef struct{
  Vector2 pos;
  float radius;
  Color color;
  bool frozen;
  double velX;
  double velY;

  bool screenEdgeCollision;
  bool paddleSideCollision;
  bool paddleTBCollision;
  bool collideWithPaddleEnabled;
} Ball;

Ball CreateBall();
void ResetBallState(Ball *b);
void DrawBall(const Ball *b);
void CheckBallBorderCollision(Ball *b);
void CheckBallPaddleCollision(Ball *b, const Paddle *p);
void ProcessBallMovement(Ball *b);

#endif //RAY_PONG_C_SRC_ENTITIES_BALL_H_
