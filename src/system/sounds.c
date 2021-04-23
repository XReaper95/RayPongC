//
// Created by Luis on 22/04/2021.
//

#include <malloc.h>
#include "sounds.h"

Sounds* soundsManager = NULL;

void loadSounds() {
  if (!soundsManager){
    Sounds *s = malloc(sizeof(Sounds));

    s->startWhistle = loadSoundResource_("referee_whistle.wav");
    s->paddleHit = loadSoundResource_("wood_hit.wav");
    s->borderHit = loadSoundResource_("border_hit.wav");
    s->score = loadSoundResource_("score.wav");
    s->gameWon = loadSoundResource_("game_won_clapping.wav");

    soundsManager = s;
  }
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

void unloadSounds() {
  UnloadSound(soundsManager->startWhistle);
  free(soundsManager);
}

Sound loadSoundResource_(const char * path) {
  Sound snd = LoadSound(TextFormat("../res/%s", path));

  if (snd.sampleCount == 0){
    TraceLog(LOG_ERROR, "Error loading sound from: ../res/%s", path);
  }

  return snd;
}

