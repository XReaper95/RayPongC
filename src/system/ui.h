//
// Created by Luis on 19/04/2021.
//

#ifndef RAY_PONG_C_SRC_SYSTEM_UI_H_
#define RAY_PONG_C_SRC_SYSTEM_UI_H_

#include "raylib.h"
#include "../entities/paddle.h"

void drawFieldLine_(int lineX, int lineY, int LineW, int LineH, Color color);

void drawGameField();

void drawScoreBoard();

void drawWinMessage(Paddle p, Color color);

void drawResetMessage();

#endif //RAY_PONG_C_SRC_SYSTEM_UI_H_
