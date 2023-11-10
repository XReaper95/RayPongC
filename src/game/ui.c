//
// Created by Luis on 19/04/2021.
//

#include "ui.h"

#include <stdio.h>

void UIDrawGameField() {
    const Color fieldColor = LIGHTGRAY;

    // middle ring
    const Vector2 center = {(float) GetScreenWidth() / 2, (float) GetScreenHeight() / 2};
    const float innerRadius = 165.0f;
    const float outerRadius = 175.0f;

    const float startAngle = 0.0f;
    const float endAngle = 360.0f;
    const int segments = 0;
    DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, segments, fieldColor);

    const int linesThickness = 10;

    // middle circle
    DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 10, fieldColor);

    // middle line
    DrawRectangle(GetScreenWidth() / 2 - linesThickness / 2, 0, 10,
                  GetScreenHeight(), fieldColor);

    // top line
    DrawRectangle(0, 0, GetScreenWidth(), linesThickness, fieldColor);

    // bottom line
    DrawRectangle(0, GetScreenHeight() - linesThickness, GetScreenWidth(),
                  linesThickness, fieldColor);

    // left line
    DrawRectangle(0, 0, linesThickness, GetScreenHeight(), Fade(BLUE, 0.4f));

    // right line
    DrawRectangle(GetScreenWidth() - linesThickness, 0, linesThickness,
                  GetScreenHeight(), Fade(RED, 0.4f));
}

void UIDrawScoreBoard(const Paddle *leftPaddle, const Paddle *rightPaddle) {
    char scoreAsText[2];
    const int playerNameFontSize = 29;
    const int scoreFontSize = 60;

    // right side
    DrawText(leftPaddle->name, 75, 50, playerNameFontSize, Fade(BLUE, 0.4f));

    snprintf(scoreAsText, 2, "%d", leftPaddle->score);
    DrawText(scoreAsText, 110, 80, scoreFontSize, Fade(BLUE, 0.4f));

    // left side
    DrawText(rightPaddle->name,
             GetScreenWidth() - MeasureText(rightPaddle->name, playerNameFontSize) - 75,
             50,
             playerNameFontSize,
             Fade(RED, 0.4f));

    snprintf(scoreAsText, 2, "%d", rightPaddle->score);
    DrawText(scoreAsText,
             GetScreenWidth() - MeasureText(scoreAsText, scoreFontSize) - 110,
             80,
             scoreFontSize,
             Fade(RED, 0.4f));
}

void UIDrawWinMessage(const Paddle *p) {
    DrawText(
            TextFormat("Player \"%s\" won!!!", p->name),
            110,
            GetScreenHeight() / 3,
            50,
            Fade(p->color, 0.55f)
    );
}

void UIDrawResetMessage() {
    DrawText(
            "Press SPACE to reset game or ESCAPE to exit",
            40,
            400,
            30,
            Fade(WHITE, 0.55f)
    );
}
