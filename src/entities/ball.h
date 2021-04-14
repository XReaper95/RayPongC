//
// Created by Luis on 08/04/2021.
//

#ifndef RAY_PONG_C_SRC_ENTITIES_BALL_H_
#define RAY_PONG_C_SRC_ENTITIES_BALL_H_

#include "raylib.h"

typedef struct {
  Vector2 pos;
  float radius;
  Color color;
  bool frozen;

  double initialAngle;
} Ball;

Ball* createBall(Color color);

void drawBall(const Ball* b);

void processBallMovement(Ball* b);

#endif //RAY_PONG_C_SRC_ENTITIES_BALL_H_
