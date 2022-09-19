//
// Created by Luis on 19/04/2021.
//

#ifndef RAY_PONG_C_SRC_SYSTEM_UI_H_
#define RAY_PONG_C_SRC_SYSTEM_UI_H_

#include "raylib.h"
#include "game.h"
#include "../entities/paddle.h"

void drawGameField();
void drawScoreBoard(Game* g);
void drawWinMessage(Paddle * p);
void drawResetMessage();

#endif //RAY_PONG_C_SRC_SYSTEM_UI_H_
