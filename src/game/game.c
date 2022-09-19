//
// Created by Luis on 13/04/2021.
//

#include <stdlib.h>
#include "raylib.h"
#include "paddle.h"
#include "ball.h"
#include "game.h"
#include "sounds.h"
#include "ui.h"

#define GAME_MAX_POINTS 5

static bool CheckWinner(Paddle *p){
  if (p->score >= GAME_MAX_POINTS){
    PlayGameWonSound();
    return true;
  } else {
    return false;
  }
}

static void ResetGame(Game *game){
  game->winner = NULL;
  ResetBallState(&game->ball);
  ResetPaddleState(&game->leftPaddle, true);
  ResetPaddleState(&game->rightPaddle, false);
  StopScoreSound();
  StopGameWonSound();
}

static void UpdateScore(Game* game){
  float ballX = game->ball.pos.x;
  float ballRadius = game->ball.radius;
  float screenW = (float)GetScreenWidth();
  bool scored = false;

  // right score
  if (ballX  < 0 - ballRadius - 30){
    scored = true;
    UpdatePlayerScore(&game->rightPaddle);
    if (CheckWinner(&game->rightPaddle)){
      game->winner = &game->rightPaddle;
    }
  }

  // left score
  if ( ballX  > screenW + ballRadius + 30){
    scored = true;
    UpdatePlayerScore(&game->leftPaddle);
    if (CheckWinner(&game->leftPaddle)){
      game->winner = &game->leftPaddle;
    }
  }

  // reset ball position
  if (scored){
    PlayScoreSound();
    ResetBallState(&game->ball);
  }
}

Game CreateGame() {
  return (Game){
    .leftPaddle = CreatePaddle("Player 1", BLUE, true, &SCHEME1),
    .rightPaddle = CreatePaddle("Player 2", RED, false, &SCHEME2),
    .ball = CreateBall()
  };
}

void ProcessGameEvents(Game* game){
  ProcessInput(&game->leftPaddle);
  ProcessInput(&game->rightPaddle);

  CheckBallBorderCollision(&game->ball);

  if (!game->ball.collideWithPaddleEnabled) {
    CheckBallPaddleCollision(&game->ball, &game->leftPaddle);
    CheckBallPaddleCollision(&game->ball, &game->rightPaddle);
  }

  ProcessBallMovement(&game->ball);
  UpdateScore(game);
}

void DrawGame(Game * game){
  DrawGameField();

  DrawPaddle(&game->leftPaddle);
  DrawPaddle(&game->rightPaddle);
  DrawBall(&game->ball);
}

void ProcessGameReset(Game* game) {
  if (game->winner != NULL && IsKeyPressed(KEY_SPACE)){
    ResetGame(game);
  }
}

void ProcessWonState(Game*  game) {
  Paddle* p;

  if (game->winner == &game->leftPaddle){
    p = &game->leftPaddle;
  } else {
    p = &game->rightPaddle;
  }

  DrawWinMessage(p);
  DrawResetMessage();
}
