#include "game.h"
#include "ui.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static TTF_Font* font = NULL;
static Mix_Music* bgMusic = NULL;

void Game_Init() {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    if (TTF_Init() == -1) {
        fprintf(stderr, "TTF_Init: %s\n", TTF_GetError());
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }

    font = TTF_OpenFont("fonts/Roboto-Black.ttf", 28);
    if (!font) {
        fprintf(stderr, "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        exit(1);
    }

    bgMusic = Mix_LoadMUS("assets/sounds/Helldivers.mp3");
    if (!bgMusic) {
        fprintf(stderr, "Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }

    // Play the background music
    Mix_PlayMusic(bgMusic, -1);
    Mix_Chunk* soundEffect = Mix_LoadWAV("assets/sounds/click.wav"); // Load your sound effect
    int windowWidth = 800;
    int windowHeight = 600;

    UI_Init(renderer, font, windowWidth, windowHeight, soundEffect);


    UI_Init(renderer, font, windowWidth, windowHeight, soundEffect);

}

void Game_Run() {
    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else {
                UI_HandleEvent(&event, &running);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        UI_Render(renderer);

        SDL_RenderPresent(renderer);
    }
}

void Game_Shutdown() {
    UI_Shutdown();

    if (bgMusic != NULL) {
        Mix_FreeMusic(bgMusic);
    }

    Mix_CloseAudio();
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
