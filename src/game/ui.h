//
// Created by Luis on 19/04/2021.
//

#ifndef RAY_PONG_C_SRC_SYSTEM_UI_H_
#define RAY_PONG_C_SRC_SYSTEM_UI_H_

#include "paddle.h"

void UIDrawGameField();

void UIDrawScoreBoard(const Paddle *leftPaddle, const Paddle *rightPaddle);

void UIDrawWinMessage(const Paddle *p);

void UIDrawResetMessage();

#endif //RAY_PONG_C_SRC_SYSTEM_UI_H_
