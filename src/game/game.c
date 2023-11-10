//
// Created by Luis on 13/04/2021.
//

#include <stddef.h>

#include "game.h"
#include "sounds.h"
#include "ui.h"

#define GAME_MAX_POINTS 5

static bool CheckWinner(const Paddle *p) {
    if (p->score >= GAME_MAX_POINTS) {
        SoundsPlayGameWon();
        return true;
    }

    return false;
}

static void ResetGame(Game *game) {
    game->winner = NULL;
    BallStateReset(&game->ball);
    PaddleResetState(&game->leftPaddle, true);
    PaddleResetState(&game->rightPaddle, false);
    SoundsStopScore();
    SoundsStopGameWon();
}

static void UpdateScore(Game *game) {
    const float ballX = game->ball.pos.x;
    const float ballRadius = game->ball.radius;
    const float screenW = (float) GetScreenWidth();
    bool scored = false;

    // right score
    if (ballX < 0 - ballRadius - 30) {
        scored = true;
        PaddleUpdateScore(&game->rightPaddle);
        if (CheckWinner(&game->rightPaddle)) {
            game->winner = &game->rightPaddle;
        }
    }

    // left score
    if (ballX > screenW + ballRadius + 30) {
        scored = true;
        PaddleUpdateScore(&game->leftPaddle);
        if (CheckWinner(&game->leftPaddle)) {
            game->winner = &game->leftPaddle;
        }
    }

    // reset ball position
    if (scored) {
        SoundsPlayScore();
        BallStateReset(&game->ball);
    }
}

Game GameCreate() {
    return (Game) {
            .leftPaddle = PaddleCreate("Player 1", BLUE, true, &SCHEME1),
            .rightPaddle = PaddleCreate("Player 2", RED, false, &SCHEME2),
            .ball = BallCreate()
    };
}

void GameProcessEvents(Game *game) {
    PaddleProcessInput(&game->leftPaddle);
    PaddleProcessInput(&game->rightPaddle);

    BallCheckBorderCollision(&game->ball);

    if (!game->ball.collideWithPaddleEnabled) {
        BallCheckPaddleCollision(&game->ball, &game->leftPaddle);
        BallCheckPaddleCollision(&game->ball, &game->rightPaddle);
    }

    BallProcessMovement(&game->ball);
    UpdateScore(game);
}

void GameDraw(const Game *game) {
    UIDrawGameField();

    PaddleDraw(&game->leftPaddle);
    PaddleDraw(&game->rightPaddle);
    BallDraw(&game->ball);
}

void GameReset(Game *game) {
    if (GameHasWinner(game) && IsKeyPressed(KEY_SPACE)) {
        ResetGame(game);
    }
}

void GameProcessWonState(Game *game) {
    Paddle *p;

    if (game->winner == &game->leftPaddle) {
        p = &game->leftPaddle;
    } else {
        p = &game->rightPaddle;
    }

    UIDrawWinMessage(p);
    UIDrawResetMessage();
}

bool GameHasWinner(const Game *game) { return game->winner != NULL; }
