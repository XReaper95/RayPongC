//
// Created by Luis on 13/04/2021.
//

#include <stdlib.h>
#include "raylib.h"
#include "game.h"


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

    if (g->rightPaddle->score >= 5){
      finishGame(g, g->rightPaddle);
    }
  }

  // left score
  if (ballX  < 0 - ballRadius - 30){
    scored = true;
    g->leftPaddle->score += 1;

    if (g->leftPaddle->score >= 5){
      finishGame(g, g->leftPaddle);
    }
  }

  // reset ball position
  if (scored){
    free(g->ball);
    g->ball = createBall(WHITE);
  }

}

void finishGame(Game* g, const Paddle* p){
  TraceLog(LOG_INFO, "Player %s won!", p->name);
  g->isWon = true;
}