//
// Created by Luis on 22/04/2021.
//

#include "sounds.h"

typedef struct {
  Sound startWhistle;
  Sound paddleHit;
  Sound borderHit;
  Sound score;
  Sound gameWon;

  bool initialized;
} SoundsSingleton;

static SoundsSingleton soundsManager;

static Sound LoadSoundResource(const char * path) {
  Sound snd = LoadSound(TextFormat("../res/%s", path));

  if (snd.frameCount == 0) {
    TraceLog(LOG_ERROR, "Error loading sound from: ../res/%s", path);
  }

  return snd;
}

void SoundsLoadAll() {
  if (!soundsManager.initialized){
    soundsManager.startWhistle = LoadSoundResource("referee_whistle.wav");
    soundsManager.paddleHit = LoadSoundResource("wood_hit.wav");
    soundsManager.borderHit = LoadSoundResource("border_hit.wav");
    soundsManager.score = LoadSoundResource("score.wav");
    soundsManager.gameWon = LoadSoundResource("game_won_clapping.wav");

    soundsManager.initialized = true;
  }
}

void SoundsPlayWhistle() {
  PlaySound(soundsManager.startWhistle);
}

void SoundsPlayPaddleHit() {
  PlaySound(soundsManager.paddleHit);
}

void SoundsPlayBorderHit() {
  PlaySound(soundsManager.borderHit);
}

void SoundsPlayScore() {
  PlaySound(soundsManager.score);
}

void SoundsPlayGameWon() {
  PlaySound(soundsManager.gameWon);
}

void SoundsStopScore() {
  StopSound(soundsManager.score);
}

void SoundsStopGameWon() {
  StopSound(soundsManager.gameWon);
}
