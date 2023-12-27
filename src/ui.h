#ifndef UI_H
#define UI_H

#include "game.h"
#include <SDL.h>
#include <SDL_ttf.h>

typedef struct {
    SDL_Rect rect;
    SDL_Texture* texture;
    SDL_Texture* hoverTexture;
    int isHovered;
    void (*onClick)(int* running);
} Button;

void UI_Init(SDL_Renderer* renderer, TTF_Font* font, int windowWidth, int windowHeight);
void UI_HandleEvent(SDL_Event* e, int* running);
void UI_Render(SDL_Renderer* renderer);
void UI_Shutdown();
#endif // UI_H
