//
// Created by Luis on 05/04/2021.
//

#ifndef RAYLIB_C_SRC_PLAYER_H_
#define RAYLIB_C_SRC_PLAYER_H_

typedef struct {
  KeyboardKey UP_KEY;
  KeyboardKey DOWN_KEY;
} ControlScheme;

typedef struct {
  const char *name;
  Vector2 pos;
  Vector2 size;
  Color color;
  const ControlScheme *controlScheme;
} Paddle;


static const ControlScheme SCHEME1 = {
    .UP_KEY = KEY_W,
    .DOWN_KEY = KEY_S,
};

static const ControlScheme SCHEME2 = {
    .UP_KEY = KEY_UP,
    .DOWN_KEY = KEY_DOWN,
};


Paddle* createPaddle(const char *name, Color color, bool leftPaddle, const ControlScheme *scheme);

void drawPaddle(const Paddle* p);

void processInput(Paddle* p);

#endif //RAYLIB_C_SRC_PLAYER_H_
