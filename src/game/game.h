//
// Created by Luis on 13/04/2021.
//

#ifndef RAY_PONG_C_SRC_SYSTEM_GAME_H_
#define RAY_PONG_C_SRC_SYSTEM_GAME_H_

#include <stdlib.h>
#include "paddle.h"
#include "ball.h"
#include "sounds.h"
#include "ui.h"

typedef struct{
  Paddle leftPaddle;
  Paddle rightPaddle;
  Ball ball;
  Paddle* winner;
} Game;

Game CreateGame();
void ProcessGameEvents(Game* game);
void ProcessWonState(Game* game);
void DrawGame(Game* game);
void ProcessGameReset(Game* game);
bool GameHasWinner(Game* game);

#endif //RAY_PONG_C_SRC_SYSTEM_GAME_H_
