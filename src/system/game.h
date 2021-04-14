//
// Created by Luis on 13/04/2021.
//

#ifndef RAY_PONG_C_SRC_SYSTEM_GAME_H_
#define RAY_PONG_C_SRC_SYSTEM_GAME_H_

#include "../entities/paddle.h"
#include "../entities/ball.h"

typedef struct {
  Paddle *leftPaddle;
  Paddle *rightPaddle;
  Ball *ball;
} Game;


Game* createGame(void);

void processGameInput(Game* g);

void resolveCollisions(Game* g);

void drawGame(const Game* g);

void cleanUpGame(Game* g);

#endif //RAY_PONG_C_SRC_SYSTEM_GAME_H_
