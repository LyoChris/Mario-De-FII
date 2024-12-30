#include "graphics.h"
#include <math.h>
#include <iostream>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include "Map.h"
#include "Enemies.h"
#include "Colissions.h"
#include "Colectibles.h"
#include "Loader.h"
#include "miniaudio.h"

using namespace std;

ma_engine engine;
ma_sound JumpEffect, CoinEffect, ColideEffect, GombaDeadEffect, BackGroundMusic, DeathEffect, StageClear, StarTheme;


void SoundInitialisation() {
    // Initialize MiniAudio engine
    if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
        printf("Failed to initialize MiniAudio engine.\n");
        exit(0);
    }

    // Initialize sound effects
    if (ma_sound_init_from_file(&engine, "jump_small.wav", 0, NULL, NULL, &JumpEffect) != MA_SUCCESS) {
        printf("Failed to load sound effect 1.\n");
        ma_sound_uninit(&JumpEffect);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "coin.wav", 0, NULL, NULL, &CoinEffect) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&CoinEffect);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "bump.wav", 0, NULL, NULL, &ColideEffect) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&ColideEffect);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "stomp.wav", 0, NULL, NULL, &GombaDeadEffect) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&GombaDeadEffect);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "LevelBackgroundMusic.wav", 0, NULL, NULL, &BackGroundMusic) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&BackGroundMusic);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "gameover.wav", 0, NULL, NULL, &DeathEffect) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&DeathEffect);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "stage_clear.wav", 0, NULL, NULL, &StageClear) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&StageClear);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "StarTheme.wav", 0, NULL, NULL, &StarTheme) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&StageClear);
        ma_engine_uninit(&engine);
        exit(0);
    }
}

void SoundUnInit() {
    ma_sound_uninit(&JumpEffect);
    ma_sound_uninit(&CoinEffect);
    ma_sound_uninit(&ColideEffect);
    ma_sound_uninit(&GombaDeadEffect);
    ma_sound_uninit(&BackGroundMusic);
    ma_sound_uninit(&DeathEffect);
    ma_sound_uninit(&StageClear);
    ma_sound_uninit(&StageClear);
    ma_engine_uninit(&engine);
}