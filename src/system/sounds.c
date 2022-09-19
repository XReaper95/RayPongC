//
// Created by Luis on 22/04/2021.
//

#include <malloc.h>
#include "sounds.h"

typedef struct {
  Sound startWhistle;
  Sound paddleHit;
  Sound borderHit;
  Sound score;
  Sound gameWon;
} SoundsSingleton;

SoundsSingleton* soundsManager = NULL;

static Sound LoadSoundResource(const char * path) {
  Sound snd = LoadSound(TextFormat("../res/%s", path));

  if (snd.frameCount == 0) {
    TraceLog(LOG_ERROR, "Error loading sound from: ../res/%s", path);
  }

  return snd;
}

void LoadGameSounds() {
  if (!soundsManager){
    SoundsSingleton *s = malloc(sizeof(SoundsSingleton));

    s->startWhistle = LoadSoundResource("referee_whistle.wav");
    s->paddleHit = LoadSoundResource("wood_hit.wav");
    s->borderHit = LoadSoundResource("border_hit.wav");
    s->score = LoadSoundResource("score.wav");
    s->gameWon = LoadSoundResource("game_won_clapping.wav");

    soundsManager = s;
  }
}

void UnloadGameSounds() {
  UnloadSound(soundsManager->startWhistle);
  UnloadSound(soundsManager->paddleHit);
  UnloadSound(soundsManager->borderHit);
  UnloadSound(soundsManager->score);
  UnloadSound(soundsManager->gameWon);
  free(soundsManager);
}

void PlayWhistleSound() {
  PlaySound(soundsManager->startWhistle);
}

void PlayPaddleHitSound() {
  PlaySound(soundsManager->paddleHit);
}

void PlayBorderHitSound() {
  PlaySound(soundsManager->borderHit);
}

void PlayScoreSound() {
  PlaySound(soundsManager->score);
}

void PlayGameWonSound() {
  PlaySound(soundsManager->gameWon);
}

void StopScoreSound() {
  StopSound(soundsManager->score);
}

void StopGameWonSound() {
  StopSound(soundsManager->gameWon);
}
