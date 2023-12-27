#ifndef UI_H
#define UI_H

#include <SDL.h>
#include <SDL_ttf.h>

void UI_HandleEvent(SDL_Event* e, int* running);
void UI_Init(SDL_Renderer* renderer, TTF_Font* font);
void UI_Render(SDL_Renderer* renderer);
void UI_Shutdown();

#endif // UI_H
