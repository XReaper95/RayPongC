//
// Created by Luis on 22/04/2021.
//

#ifndef RAY_PONG_C_SRC_SYSTEM_SOUNDS_H_
#define RAY_PONG_C_SRC_SYSTEM_SOUNDS_H_

#include <raylib.h>

typedef struct {
  Sound startWhistle;
  Sound paddleHit;
  Sound borderHit;
  Sound score;
  Sound gameWon;
}Sounds;

void loadSounds();

void unloadSounds();

void playWhistleSound();

void playPaddleHitSound();

void playBorderHitSound();

void playScoreSound();

void playGameWonSound();

void stopScoreSound();

void stopGameWonSound();

#endif //RAY_PONG_C_SRC_SYSTEM_SOUNDS_H_
