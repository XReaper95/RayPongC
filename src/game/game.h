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

typedef struct {
    Paddle leftPaddle;
    Paddle rightPaddle;
    Ball ball;
    Paddle *winner;
} Game;

Game GameCreate();

void GameProcessEvents(Game *game);

void GameProcessWonState(Game *game);

void GameDraw(Game *game);

void GameReset(Game *game);

bool GameHasWinner(Game *game);

#endif //RAY_PONG_C_SRC_SYSTEM_GAME_H_
