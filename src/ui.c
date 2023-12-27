#include "ui.h"
#include <stdio.h>
#include <stdio.h>

typedef struct {
    SDL_Rect rect;
    SDL_Texture* texture;
    SDL_Texture* hoverTexture;
    int isHovered;
    void (*onClick)(int* running);
} Button;

static Button startButton;
static Button quitButton;

static SDL_Renderer* uiRenderer = NULL;

static SDL_Texture* CreateButtonTexture(TTF_Font* font, const char* text, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(uiRenderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

static void StartNewSession(int* running) {
    printf("Starting a new session...\n");
}

static void QuitGame(int* running) {
    *running = 0;
}

void UI_Init(SDL_Renderer* renderer, TTF_Font* font) {
    uiRenderer = renderer;

    // Set up the start button
    startButton.rect = (SDL_Rect){100, 100, 200, 50};
    startButton.texture = CreateButtonTexture(font, "Start New Session", (SDL_Color){255, 255, 255});
    startButton.hoverTexture = CreateButtonTexture(font, "Start New Session", (SDL_Color){255, 200, 200});
    startButton.onClick = StartNewSession;

    // Set up the quit button
    quitButton.rect = (SDL_Rect){100, 200, 200, 50};
    quitButton.texture = CreateButtonTexture(font, "Quit", (SDL_Color){255, 255, 255});
    quitButton.hoverTexture = CreateButtonTexture(font, "Quit", (SDL_Color){255, 200, 200});
    quitButton.onClick = QuitGame;
}

void UI_HandleEvent(SDL_Event* e, int* running) {
    int mouseX, mouseY;
    if (e->type == SDL_MOUSEMOTION) {
        SDL_GetMouseState(&mouseX, &mouseY);
        startButton.isHovered = SDL_PointInRect(&((SDL_Point){mouseX, mouseY}), &startButton.rect);
        quitButton.isHovered = SDL_PointInRect(&((SDL_Point){mouseX, mouseY}), &quitButton.rect);
    } else if (e->type == SDL_MOUSEBUTTONDOWN) {
        if (startButton.isHovered && startButton.onClick) {
            startButton.onClick(running);
        } else if (quitButton.isHovered && quitButton.onClick) {
            quitButton.onClick(running);
        }
    }
}

void UI_Render(SDL_Renderer* renderer) {
    // Draw the start button
    SDL_Texture* currentTexture = startButton.isHovered ? startButton.hoverTexture : startButton.texture;
    SDL_RenderCopy(renderer, currentTexture, NULL, &startButton.rect);

    // Draw the quit button
    currentTexture = quitButton.isHovered ? quitButton.hoverTexture : quitButton.texture;
    SDL_RenderCopy(renderer, currentTexture, NULL, &quitButton.rect);
}

void UI_Shutdown() {
    SDL_DestroyTexture(startButton.texture);
    SDL_DestroyTexture(startButton.hoverTexture);
    SDL_DestroyTexture(quitButton.texture);
    SDL_DestroyTexture(quitButton.hoverTexture);
}
