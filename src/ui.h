#ifndef UI_H
#define UI_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

typedef struct {
    SDL_Rect rect;
    SDL_Texture* texture;
    SDL_Texture* hoverTexture;
    int isHovered;
    void (*onClick)(int* running);
} Button;

// Prototypes des fonctions de l'UI
void UI_Init(SDL_Renderer* renderer, TTF_Font* font, int windowWidth, int windowHeight, Mix_Chunk* soundEffect);
void UI_HandleEvent(SDL_Event* e, int* running);
void UI_Render(SDL_Renderer* renderer);
void UI_Shutdown();

void StartNewSession(int* running);
void GoBack(int* running);
#endif // UI_H
