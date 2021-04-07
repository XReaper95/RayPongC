//
// Created by Luis on 05/04/2021.
//

#ifndef RAYLIB_C_SRC_PLAYER_H_
#define RAYLIB_C_SRC_PLAYER_H_

typedef struct Paddle{
  const char *name;
  Vector2 pos;
  Vector2 size;
  Color color;
} Paddle;

Paddle* createPaddle(const char *name, Color color, bool leftPaddle);

void DrawPaddle(const Paddle*);

void destroyPaddle(Paddle*);

#endif //RAYLIB_C_SRC_PLAYER_H_
