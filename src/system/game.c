//
// Created by Luis on 13/04/2021.
//

#include <stdlib.h>
#include "raylib.h"
#include "game.h"
#include "ui.h"

#define GAME_MAX_POINTS 5

Game* createGame(void){
  Game *g = malloc(sizeof(Game));

  g->leftPaddle = createPaddle("Player 1", BLUE, true, &SCHEME1);
  g->rightPaddle = createPaddle("Player 2", RED, false, &SCHEME2);
  g->ball = createBall();
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
  drawGameField();

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
  if (ballX  < 0 - ballRadius - 30){
    scored = true;
    g->rightPaddle->score += 1;

    checkFinishGame(g, g->rightPaddle);

  }

  // left score
  if ( ballX  > screenW + ballRadius + 30){
    scored = true;
    g->leftPaddle->score += 1;

    checkFinishGame(g, g->leftPaddle);
  }

  // reset ball position
  if (scored){
    playScoreSound();
    free(g->ball);
    g->ball = createBall();
  }
}

void checkFinishGame(Game* g, Paddle *p){
  if (p->score >= GAME_MAX_POINTS){
    playGameWonSound();
    p->won = true;
    g->isWon = true;
  }
}

Game* processGameReset(Game *g) {
  if (g->isWon && IsKeyPressed(KEY_SPACE)){
      stopGameWonSound();
      free(g);
      return createGame();
  } else {
    return g;
  }
}

void processWonState(Game *g) {
  Color msgColor;
  Paddle p;

  if (g->leftPaddle->won){
    msgColor = g->leftPaddle->color;
    p = *g->leftPaddle;
  } else {
    msgColor = g->rightPaddle->color;
    p = *g->rightPaddle;
  }

  drawWinMessage(p, msgColor);

  drawResetMessage();
}
