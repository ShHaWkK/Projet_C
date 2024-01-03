#include "../include/audio.h"
#include "../include/Log.h"
#include "../include/include.h"

static Mix_Music* bgMusic = NULL;
static Mix_Chunk* buttonClickSound = NULL;

void Audio_Init(const char* musicFilePath, const char* clickSoundFilePath) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        Log(LOG_ERROR, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }

    bgMusic = Mix_LoadMUS(musicFilePath);
    if (!bgMusic) {
        Log(LOG_ERROR, "Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }

    buttonClickSound = Mix_LoadWAV(clickSoundFilePath);
    if (!buttonClickSound) {
        Log(LOG_ERROR, "Failed to load click sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }
}

void Audio_PlayMusic() {
    Mix_PlayMusic(bgMusic, -1);
}

void Audio_PlayClickSound() {
    Mix_PlayChannel(-1, buttonClickSound, 0);
}

void Audio_Shutdown() {
    if (bgMusic != NULL) {
        Mix_FreeMusic(bgMusic);
    }
    if (buttonClickSound != NULL) {
        Mix_FreeChunk(buttonClickSound);
    }
    Mix_CloseAudio();
}
