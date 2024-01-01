#ifndef TEXT_INPUT_H
#define TEXT_INPUT_H

#include "include.h"

void handleKeyboardEvent(SDL_Event* e);
void handleTextInputEvent(SDL_Event* e);

void renderTextWithCursor(SDL_Renderer* renderer, TTF_Font* font, SDL_Color textColor, SDL_Rect* rect, const char* text, int isSelected);


#endif // TEXT_INPUT_H
