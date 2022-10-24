//
// Created by Luis on 05/04/2021.
//

#ifndef RAYLIB_C_SRC_PLAYER_H_
#define RAYLIB_C_SRC_PLAYER_H_

#include "raylib.h"

typedef struct {
    KeyboardKey UP_KEY;
    KeyboardKey DOWN_KEY;
} ControlScheme;

static const ControlScheme SCHEME1 = {
        .UP_KEY = KEY_W,
        .DOWN_KEY = KEY_S,
};

static const ControlScheme SCHEME2 = {
        .UP_KEY = KEY_UP,
        .DOWN_KEY = KEY_DOWN,
};

typedef struct {
    const char *name;
    Vector2 pos;
    Vector2 size;
    Color color;
    int score;
    const ControlScheme *controlScheme;
} Paddle;

Paddle PaddleCreate(const char *name, Color color, bool isLeftPaddle, const ControlScheme *scheme);

void PaddleResetState(Paddle *p, bool isLeftPaddle);

void PaddleUpdateScore(Paddle *p);

void PaddleDraw(const Paddle *p);

void PaddleProcessInput(Paddle *p);


#endif //RAYLIB_C_SRC_PLAYER_H_
