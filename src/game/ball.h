//
// Created by Luis on 08/04/2021.
//

#ifndef RAY_PONG_C_SRC_ENTITIES_BALL_H_
#define RAY_PONG_C_SRC_ENTITIES_BALL_H_

#include "paddle.h"

typedef struct {
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

Ball BallCreate();

void BallStateReset(Ball *b);

void BallDraw(const Ball *b);

void BallCheckBorderCollision(Ball *b);

void BallCheckPaddleCollision(Ball *b, const Paddle *p);

void BallProcessMovement(Ball *b);

#endif //RAY_PONG_C_SRC_ENTITIES_BALL_H_
