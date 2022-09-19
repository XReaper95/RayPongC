//
// Created by Luis on 13/04/2021.
//

#ifndef RAY_PONG_C_SRC_SYSTEM_GAME_H_
#define RAY_PONG_C_SRC_SYSTEM_GAME_H_

#include "../entities/paddle.h"
#include "../entities/ball.h"

typedef struct{
  Paddle leftPaddle;
  Paddle rightPaddle;
  Ball ball;
  Paddle* winner;
} Game;

Game createGame();
void processGameEvents(Game* game);
void processWonState(Game* game);
void drawGame(Game* game);
void processGameReset(Game* game);

#endif //RAY_PONG_C_SRC_SYSTEM_GAME_H_
