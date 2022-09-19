//
// Created by Luis on 13/04/2021.
//

#include <stdlib.h>
#include "raylib.h"
#include "../entities/paddle.h"
#include "../entities/ball.h"
#include "game.h"
#include "sounds.h"
#include "ui.h"

#define GAME_MAX_POINTS 5

static bool checkWinner(Paddle *p){
  if (p->score >= GAME_MAX_POINTS){
    playGameWonSound();
    return true;
  } else {
    return false;
  }
}

static void resetGame(Game *game){
  game->winner = NULL;
  resetBallState(&game->ball);
  resetPaddleState(&game->leftPaddle, true);
  resetPaddleState(&game->rightPaddle, false);
  stopScoreSound();
  stopGameWonSound();
}

static void updateScore(Game* game){
  float ballX = game->ball.pos.x;
  float ballRadius = game->ball.radius;
  float screenW = (float)GetScreenWidth();
  bool scored = false;

  // right score
  if (ballX  < 0 - ballRadius - 30){
    scored = true;
    UpdatePlayerScore(&game->rightPaddle);
    if (checkWinner(&game->rightPaddle)){
      game->winner = &game->rightPaddle;
    }
  }

  // left score
  if ( ballX  > screenW + ballRadius + 30){
    scored = true;
    UpdatePlayerScore(&game->leftPaddle);
    if (checkWinner(&game->leftPaddle)){
      game->winner = &game->leftPaddle;
    }
  }

  // reset ball position
  if (scored){
    playScoreSound();
    resetBallState(&game->ball);
  }
}

Game createGame() {
  return (Game){
    .leftPaddle = createPaddle("Player 1", BLUE, true, &SCHEME1),
    .rightPaddle = createPaddle("Player 2", RED, false, &SCHEME2),
    .ball = createBall()
  };
}

void processGameEvents(Game* game){
  processInput(&game->leftPaddle);
  processInput(&game->rightPaddle);

  checkBallBorderCollision(&game->ball);

  if (!game->ball.collideWithPaddleEnabled) {
    checkBallPaddleCollision(&game->ball, &game->leftPaddle);
    checkBallPaddleCollision(&game->ball, &game->rightPaddle);
  }

  processBallMovement(&game->ball);
  updateScore(game);
}

void drawGame(Game * game){
  drawGameField();

  drawPaddle(&game->leftPaddle);
  drawPaddle(&game->rightPaddle);
  drawBall(&game->ball);
}

void processGameReset(Game* game) {
  if (game->winner != NULL && IsKeyPressed(KEY_SPACE)){
    resetGame(game);
  }
}

void processWonState(Game*  game) {
  Paddle* p;

  if (game->winner == &game->leftPaddle){
    p = &game->leftPaddle;
  } else {
    p = &game->rightPaddle;
  }

  drawWinMessage(p);
  drawResetMessage();
}
