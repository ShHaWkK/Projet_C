//
// Created by alexa on 21/01/2024.
//

#ifndef C_BUILDMENU_H
#define C_BUILDMENU_H


#include "include.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void RenderText1(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y);

typedef void (*ClickCallback)(void);

void RenderClickableText1(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, ClickCallback onClick);
void YourCallbackFunction();




#endif // BUILDMENU_H


