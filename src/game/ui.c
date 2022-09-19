//
// Created by Luis on 19/04/2021.
//

#include "ui.h"

static void DrawFieldLine(int lineX, int lineY, int lineW, int lineH, Color color){
  DrawRectangle(lineX, lineY, lineW, lineH, color);
}

void DrawGameField(){
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

  // middle circle
  DrawCircle(GetScreenWidth()/2, GetScreenHeight()/2 , 10, fieldColor);

  // middle line
  DrawFieldLine(GetScreenWidth() / 2 - linesThickness / 2, 0, 10,
                GetScreenHeight(), fieldColor);

  // top line
  DrawFieldLine(0, 0, GetScreenWidth(), linesThickness, fieldColor);

  // bottom line
  DrawFieldLine(0, GetScreenHeight() - linesThickness, GetScreenWidth(),
                linesThickness, fieldColor);

  // left line
  DrawFieldLine(0, 0, linesThickness, GetScreenHeight(), Fade(BLUE, 0.4f));

  // right line
  DrawFieldLine(GetScreenWidth() - linesThickness, 0, linesThickness,
                GetScreenHeight(), Fade(RED, 0.4f));
}

void DrawScoreBoard(Paddle* leftPaddle, Paddle* rightPaddle){
  char scoreAsText[2];
  const int playerNameFontSize = 29;
  const int scoreFontSize = 60;

  // right side
  DrawText(leftPaddle->name, 75, 50 , playerNameFontSize, Fade(BLUE, 0.4f));

  snprintf(scoreAsText, 2, "%d", leftPaddle->score);
  DrawText(scoreAsText, 110, 80, scoreFontSize, Fade(BLUE, 0.4f));

  // left side
  DrawText(rightPaddle->name,
           GetScreenWidth() - MeasureText(rightPaddle->name, playerNameFontSize) - 75,
           50 ,
           playerNameFontSize,
           Fade(RED, 0.4f));

  snprintf(scoreAsText, 2, "%d", rightPaddle->score);
  DrawText(scoreAsText,
           GetScreenWidth() - MeasureText(scoreAsText, scoreFontSize) - 110,
           80,
           scoreFontSize,
           Fade(RED, 0.4f));
}

void DrawWinMessage(Paddle * p) {
  DrawText(
      TextFormat("Player \"%s\" won!!!", p->name),
      110,
      GetScreenHeight() / 3,
      50,
      Fade(p->color, 0.55f)
  );
}

void DrawResetMessage() {
  DrawText(
      "Press SPACE to reset game or ESCAPE to exit",
      40,
      400,
      30,
      Fade(WHITE, 0.55f)
  );
}
