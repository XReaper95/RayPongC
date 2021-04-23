//
// Created by Luis on 19/04/2021.
//

#include <stdio.h>
#include "ui.h"

void drawFieldLine_(int lineX, int lineY, int lineW, int lineH, Color color){
  DrawRectangle(lineX, lineY, lineW, lineH, color);
}

void drawGameField(){
  Color fieldColor = LIGHTGRAY;

  // middle ring
  Vector2 center = {(float)GetScreenWidth()/2, (float)GetScreenHeight()/2 };
  float innerRadius = 165.0f;
  float outerRadius = 175.0f;

  float startAngle = 0.0f;
  float endAngle = 360.0f;
  int segments = 0;
  DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, segments, fieldColor);

  int linesThickness = 10;

  // middle line
  drawFieldLine_(
      GetScreenWidth()/2 - linesThickness / 2,
      0,
      10,
      GetScreenHeight(),
      fieldColor
      );

  // top line
  drawFieldLine_(
      0,
      0 ,
      GetScreenWidth(),
      linesThickness,
      fieldColor);

  // bottom line
  drawFieldLine_(
      0,
      GetScreenHeight() - linesThickness,
      GetScreenWidth(),
      linesThickness,
      fieldColor);

  // left line
  drawFieldLine_(
      0,
      0,
      linesThickness,
      GetScreenHeight(),
      Fade(BLUE, 0.4f)
      );

  // right line
  drawFieldLine_(
      GetScreenWidth() - linesThickness,
      0,
      linesThickness,
      GetScreenHeight(),
      Fade(RED, 0.4f)
  );
}

void drawScoreBoard(const Game* g){
  char scoreAsText[2];
  const int playerNameFontSize = 29;
  const int scoreFontSize = 60;

  // right side
  DrawText(g->leftPaddle->name, 75, 50 , playerNameFontSize, Fade(BLUE, 0.4f));

  snprintf(scoreAsText, 2, "%d", g->leftPaddle->score);
  DrawText(scoreAsText, 110, 80, scoreFontSize, Fade(BLUE, 0.4f));

  // left side
  DrawText(g->rightPaddle->name,
           GetScreenWidth() - MeasureText(g->rightPaddle->name, playerNameFontSize) - 75,
           50 ,
           playerNameFontSize,
           Fade(RED, 0.4f));

  snprintf(scoreAsText, 2, "%d", g->rightPaddle->score);
  DrawText(scoreAsText,
           GetScreenWidth() - MeasureText(scoreAsText, scoreFontSize) - 110,
           80,
           scoreFontSize,
           Fade(RED, 0.4f));
}

void drawWinMessage(Paddle p, Color msgColor) {
  DrawText(
      TextFormat("Player \"%s\" won!!!", p.name),
      110,
      GetScreenHeight() / 3,
      50,
      msgColor
  );
}

void drawResetMessage() {
  DrawText(
      "Press SPACE to reset game or ESCAPE to exit",
      40,
      400,
      30,
      WHITE
  );
}
