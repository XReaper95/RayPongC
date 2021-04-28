//
// Created by Luis on 13/04/2021.
//

#include <stdlib.h>
#include "raylib.h"
#include "game.h"
#include "ui.h"

#define GAME_MAX_POINTS 5

Game* game = NULL;

void createGame() {
  Game *g = malloc(sizeof(Game));

  g->leftPaddle = createPaddle("Player 1", BLUE, true, &SCHEME1);
  g->rightPaddle = createPaddle("Player 2", RED, false, &SCHEME2);
  g->ball = createBall();
  g->isWon = false;

  game = g;
}

void processGameEvents(){
  processInput(game->leftPaddle);
  processInput(game->rightPaddle);

  checkBallBorderCollision(game->ball);

  if (!game->ball->disablePaddleCollision){

    checkBallPaddleCollision(game->ball, game->leftPaddle);
    checkBallPaddleCollision(game->ball, game->rightPaddle);
  }

  processBallMovement(game->ball);
  updateScore(game);
}

void drawGame(){
  drawGameField();

  drawPaddle(game->leftPaddle);
  drawPaddle(game->rightPaddle);
  drawBall(game->ball);
}

void cleanUpGame(){
  free(game->leftPaddle);
  free(game->rightPaddle);
  free(game->ball);
  free(game);
}

void updateScore(){
  float ballX = game->ball->pos.x;
  float ballRadius = game->ball->radius;
  float screenW = (float)GetScreenWidth();
  bool scored = false;

  // right score
  if (ballX  < 0 - ballRadius - 30){
    scored = true;
    game->rightPaddle->score += 1;
    game->isWon = checkWon(game->rightPaddle, GAME_MAX_POINTS);
  }

  // left score
  if ( ballX  > screenW + ballRadius + 30){
    scored = true;
    game->leftPaddle->score += 1;
    game->isWon = checkWon(game->leftPaddle, GAME_MAX_POINTS);
  }

  // reset ball position
  if (scored){
    playScoreSound();
    free(game->ball);
    game->ball = createBall();
  }
}

void processGameReset() {
  if (game->isWon && IsKeyPressed(KEY_SPACE)){
      stopGameWonSound();
      free(game);
      createGame();
  }
}

void processWonState() {
  Color msgColor;
  Paddle p;

  if (game->leftPaddle->won){
    msgColor = game->leftPaddle->color;
    p = *game->leftPaddle;
  } else {
    msgColor = game->rightPaddle->color;
    p = *game->rightPaddle;
  }

  drawWinMessage(p, msgColor);

  drawResetMessage();
}
