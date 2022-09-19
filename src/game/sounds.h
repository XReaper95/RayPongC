//
// Created by Luis on 22/04/2021.
//

#ifndef RAY_PONG_C_SRC_SYSTEM_SOUNDS_H_
#define RAY_PONG_C_SRC_SYSTEM_SOUNDS_H_

#include <raylib.h>

void LoadGameSounds();
void PlayWhistleSound();
void PlayPaddleHitSound();
void PlayBorderHitSound();
void PlayScoreSound();
void PlayGameWonSound();
void StopScoreSound();
void StopGameWonSound();

#endif //RAY_PONG_C_SRC_SYSTEM_SOUNDS_H_
