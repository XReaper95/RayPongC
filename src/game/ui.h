//
// Created by Luis on 19/04/2021.
//

#ifndef RAY_PONG_C_SRC_SYSTEM_UI_H_
#define RAY_PONG_C_SRC_SYSTEM_UI_H_

#include <stdio.h>
#include "raylib.h"
#include "paddle.h"

void DrawGameField();
void DrawScoreBoard(Paddle* leftPaddle, Paddle* rightPaddle);
void DrawWinMessage(Paddle * p);
void DrawResetMessage();

#endif //RAY_PONG_C_SRC_SYSTEM_UI_H_
