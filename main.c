#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const char* WINDOW_TITLE = "Menu SDL";

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;

SDL_Rect startButtonRect = {150, 200, 200, 50};
SDL_Rect quitButtonRect = {450, 200, 200, 50};

void initialize();
void shutdown();
void drawButton(SDL_Rect* rect, const char* text);
void handleButtonPress(SDL_Rect* rect, int mouseX, int mouseY);
void startNewSession();
void quit();

int main(int argc, char* argv[]) {
    initialize();

    SDL_Event event;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                handleButtonPress(&startButtonRect, mouseX, mouseY);
                handleButtonPress(&quitButtonRect, mouseX, mouseY);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawButton(&startButtonRect, "Nouvelle session");
        drawButton(&quitButtonRect, "Quitter");

        SDL_RenderPresent(renderer);
    }

    shutdown();
    return 0;
}

void initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    if (TTF_Init() == -1) {
        printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
        exit(1);
    }

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    font = TTF_OpenFont("fonts/Roboto-Black.ttf", 24);
    if (!font) {
        printf("Failed to load font! TTF_Error: %s\n", TTF_GetError());
        exit(1);
    }
}

void shutdown() {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void drawButton(SDL_Rect* rect, const char* text) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, rect);

    SDL_Surface* surface = TTF_RenderText_Blended(font, text, (SDL_Color){0, 0, 0});
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void handleButtonPress(SDL_Rect* rect, int mouseX, int mouseY) {
    if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, rect)) {
        if (rect == &startButtonRect) {
            startNewSession();
        } else if (rect == &quitButtonRect) {
            quit();
        }
    }
}

void startNewSession() {
    printf("Starting new session...\n");
    // Insert code to start a new session
}

void quit() {
    printf("Quitting...\n");
    exit(0);
}
