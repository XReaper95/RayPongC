//
// Created by Luis on 13/04/2021.
//

#ifndef RAY_PONG_C_SRC_SYSTEM_GAME_H_
#define RAY_PONG_C_SRC_SYSTEM_GAME_H_

#include "../entities/paddle.h"
#include "../entities/ball.h"
#include "sounds.h"

typedef struct {
  Paddle *leftPaddle;
  Paddle *rightPaddle;
  Ball *ball;
  bool isWon;
} Game;

extern Game* game;

void createGame();

void processGameEvents();

void processWonState();

void updateScore();

void drawGame();

void cleanUpGame();

void processGameReset();

#endif //RAY_PONG_C_SRC_SYSTEM_GAME_H_
