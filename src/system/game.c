//
// Created by Luis on 13/04/2021.
//

#include <stdlib.h>
#include "raylib.h"
#include "game.h"

bool checkCollisionWithBorder(Ball *b){
  float x = b->pos.x;
  float y = b->pos.y;
  float r = b->radius;

  float w = (float)GetScreenWidth();
  float h = (float)GetScreenHeight();

  if (x + r == w || x - r == w){
    TraceLog(LOG_ERROR, "Collision with border!");
    return true;
  }
  if (x + r == h || x - r == h){
    TraceLog(LOG_ERROR, "Collision with border!");
    return true;
  }

  if (x + r + 7 < 0 || x + r + 7 > w){
    b->frozen = true;
  }

  return false;
}

Game* createGame(void){
  Game *g = malloc(sizeof(Game));

  g->leftPaddle = createPaddle("XReaper", BLUE, true, &SCHEME1);
  g->rightPaddle = createPaddle("Opponent", RED, false, &SCHEME2);
  g->ball = createBall(WHITE);

  return g;
}

void processGameInput(Game* g){
  processInput(g->leftPaddle);
  processInput(g->rightPaddle);
  processBallMovement(g->ball);
}

void drawGame(const Game* g){
  drawPaddle(g->leftPaddle);
  drawPaddle(g->rightPaddle);
  drawBall(g->ball);
}

void resolveCollisions(Game* g){
  checkCollisionWithBorder(g->ball);

}

void cleanUpGame(Game* g){
  free(g->leftPaddle);
  free(g->rightPaddle);
  free(g->ball);
  free(g);
}