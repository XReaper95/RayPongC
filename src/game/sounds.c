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

void LoadGameSounds() {
  if (!soundsManager.initialized){
    soundsManager.startWhistle = LoadSoundResource("referee_whistle.wav");
    soundsManager.paddleHit = LoadSoundResource("wood_hit.wav");
    soundsManager.borderHit = LoadSoundResource("border_hit.wav");
    soundsManager.score = LoadSoundResource("score.wav");
    soundsManager.gameWon = LoadSoundResource("game_won_clapping.wav");

    soundsManager.initialized = true;
  }
}

void PlayWhistleSound() {
  PlaySound(soundsManager.startWhistle);
}

void PlayPaddleHitSound() {
  PlaySound(soundsManager.paddleHit);
}

void PlayBorderHitSound() {
  PlaySound(soundsManager.borderHit);
}

void PlayScoreSound() {
  PlaySound(soundsManager.score);
}

void PlayGameWonSound() {
  PlaySound(soundsManager.gameWon);
}

void StopScoreSound() {
  StopSound(soundsManager.score);
}

void StopGameWonSound() {
  StopSound(soundsManager.gameWon);
}
