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
  bool isWon;
} Game;

Game* createGame(void);

void processGameEvents(Game* g);

void updateScore(Game* g);

void drawGame(const Game* g);

void checkFinishGame(Game* g, Paddle *p);

void cleanUpGame(Game* g);

Game * processGameReset(Game* g);

#endif //RAY_PONG_C_SRC_SYSTEM_GAME_H_
