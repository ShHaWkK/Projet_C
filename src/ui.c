#include "ui.h"
#include <stdio.h>

// Define your Button structure and other UI functions here
static Button startButton;
static Button quitButton;
static Button settingsButton;
static SDL_Renderer* uiRenderer = NULL;

static SDL_Texture* CreateButtonTexture(TTF_Font* font, const char* text, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(uiRenderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

static void StartNewSession(int* running) {
    printf("Starting a new session...\n");
    // Insert code to start a new session
}

static void QuitGame(int* running) {
    *running = 0;
}

static void OpenSettings(int* running) {
    printf("Opening settings...\n");
    // Insert code to handle opening settings
}

void UI_Init(SDL_Renderer* renderer, TTF_Font* font, int windowWidth, int windowHeight) {
    uiRenderer = renderer;

    // Set up the start button
    startButton.rect = (SDL_Rect){(windowWidth - 200) / 2, windowHeight / 2 - 75, 200, 50};
    startButton.texture = CreateButtonTexture(font, "Start New Session", (SDL_Color){255, 255, 255});
    startButton.hoverTexture = CreateButtonTexture(font, "Start New Session", (SDL_Color){255, 0, 0});
    startButton.onClick = StartNewSession;

    // Set up the quit button
    quitButton.rect = (SDL_Rect){(windowWidth - 200) / 2, windowHeight - 75, 200, 50};
    quitButton.texture = CreateButtonTexture(font, "Quit", (SDL_Color){255, 255, 255});
    quitButton.hoverTexture = CreateButtonTexture(font, "Quit", (SDL_Color){255, 0, 0});
    quitButton.onClick = QuitGame;

    // Set up the settings button
    settingsButton.rect = (SDL_Rect){(windowWidth - 200) / 2, windowHeight / 2, 200, 50};
    settingsButton.texture = CreateButtonTexture(font, "Settings", (SDL_Color){255, 255, 255});
    settingsButton.hoverTexture = CreateButtonTexture(font, "Settings", (SDL_Color){255, 0, 0});
    settingsButton.onClick = OpenSettings;
}

void UI_HandleEvent(SDL_Event* e, int* running) {
    // Handle events for the buttons
    int mouseX, mouseY;
    if (e->type == SDL_MOUSEMOTION) {
        SDL_GetMouseState(&mouseX, &mouseY);
        startButton.isHovered = SDL_PointInRect(&((SDL_Point){mouseX, mouseY}), &startButton.rect);
        quitButton.isHovered = SDL_PointInRect(&((SDL_Point){mouseX, mouseY}), &quitButton.rect);
        settingsButton.isHovered = SDL_PointInRect(&((SDL_Point){mouseX, mouseY}), &settingsButton.rect);
    } else if (e->type == SDL_MOUSEBUTTONDOWN) {
        if (startButton.isHovered && startButton.onClick) {
            startButton.onClick(running);
        }
        if (quitButton.isHovered && quitButton.onClick) {
            quitButton.onClick(running);
        }
        if (settingsButton.isHovered && settingsButton.onClick) {
            settingsButton.onClick(running);
        }
    }
}

void UI_Render(SDL_Renderer* renderer) {
    // Render the start button
    SDL_Texture* currentTexture = startButton.isHovered ? startButton.hoverTexture : startButton.texture;
    SDL_RenderCopy(renderer, currentTexture, NULL, &startButton.rect);

    // Render the quit button
    currentTexture = quitButton.isHovered ? quitButton.hoverTexture : quitButton.texture;
    SDL_RenderCopy(renderer, currentTexture, NULL, &quitButton.rect);

    // Render the settings button
    currentTexture = settingsButton.isHovered ? settingsButton.hoverTexture : settingsButton.texture;
    SDL_RenderCopy(renderer, currentTexture, NULL, &settingsButton.rect);
}

void UI_Shutdown() {
    // Free button textures and any other UI resources here
    SDL_DestroyTexture(startButton.texture);
    SDL_DestroyTexture(startButton.hoverTexture);
    SDL_DestroyTexture(quitButton.texture);
    SDL_DestroyTexture(quitButton.hoverTexture);
    SDL_DestroyTexture(settingsButton.texture);
    SDL_DestroyTexture(settingsButton.hoverTexture);
}
