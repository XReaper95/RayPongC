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

static Sound loadSoundResource(const char * path) {
  Sound snd = LoadSound(TextFormat("../res/%s", path));

  if (snd.frameCount == 0) {
    TraceLog(LOG_ERROR, "Error loading sound from: ../res/%s", path);
  }

  return snd;
}

void loadSounds() {
  if (!soundsManager){
    SoundsSingleton *s = malloc(sizeof(SoundsSingleton));

    s->startWhistle = loadSoundResource("referee_whistle.wav");
    s->paddleHit = loadSoundResource("wood_hit.wav");
    s->borderHit = loadSoundResource("border_hit.wav");
    s->score = loadSoundResource("score.wav");
    s->gameWon = loadSoundResource("game_won_clapping.wav");

    soundsManager = s;
  }
}

void unloadSounds() {
  UnloadSound(soundsManager->startWhistle);
  UnloadSound(soundsManager->paddleHit);
  UnloadSound(soundsManager->borderHit);
  UnloadSound(soundsManager->score);
  UnloadSound(soundsManager->gameWon);
  free(soundsManager);
}

void playWhistleSound() {
  PlaySound(soundsManager->startWhistle);
}

void playPaddleHitSound() {
  PlaySound(soundsManager->paddleHit);
}

void playBorderHitSound() {
  PlaySound(soundsManager->borderHit);
}

void playScoreSound() {
  PlaySound(soundsManager->score);
}

void playGameWonSound() {
  PlaySound(soundsManager->gameWon);
}

void stopScoreSound() {
  StopSound(soundsManager->score);
}

void stopGameWonSound() {
  StopSound(soundsManager->gameWon);
}
