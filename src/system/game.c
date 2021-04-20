//
// Created by Luis on 13/04/2021.
//

#include <stdlib.h>
#include "raylib.h"
#include "game.h"

#define GAME_MAX_POINTS 5

Game* createGame(void){
  Game *g = malloc(sizeof(Game));

  g->leftPaddle = createPaddle("XReaper", BLUE, true, &SCHEME1);
  g->rightPaddle = createPaddle("AI", RED, false, &SCHEME2);
  g->ball = createBall(WHITE);
  g->isWon = false;

  return g;
}

void processGameEvents(Game* g){
  processInput(g->leftPaddle);
  processInput(g->rightPaddle);

  ballBorderCollision(g->ball);

  if (!g->ball->disablePaddleCollision){

    ballPaddleCollision(g->ball, g->leftPaddle);
    ballPaddleCollision(g->ball, g->rightPaddle);
  }

  processBallMovement(g->ball);
  updateScore(g);
}

void drawGame(const Game* g){
  drawPaddle(g->leftPaddle);
  drawPaddle(g->rightPaddle);
  drawBall(g->ball);
}

void cleanUpGame(Game* g){
  free(g->leftPaddle);
  free(g->rightPaddle);
  free(g->ball);
  free(g);
}

void updateScore(Game* g){
  float ballX = g->ball->pos.x;
  float ballRadius = g->ball->radius;
  float screenW = (float)GetScreenWidth();
  bool scored = false;

  // right score
  if (ballX  > screenW + ballRadius + 30){
    scored = true;
    g->rightPaddle->score += 1;

    checkFinishGame(g, g->rightPaddle);

  }

  // left score
  if (ballX  < 0 - ballRadius - 30){
    scored = true;
    g->leftPaddle->score += 1;

    checkFinishGame(g, g->leftPaddle);
  }

  // reset ball position
  if (scored){
    free(g->ball);
    g->ball = createBall(WHITE);
  }

}

void checkFinishGame(Game* g, const Paddle* p){
  if (p->score > GAME_MAX_POINTS){
    TraceLog(LOG_INFO, "Player %s won!", p->name);
    g->isWon = true;
  }
}