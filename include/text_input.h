#ifndef TEXT_INPUT_H
#define TEXT_INPUT_H

#include "include.h"



extern char textInput[256]; // Buffer pour stocker le texte
extern int cursorPosition;   // Position actuelle du curseur dans le texte

//void renderTextWithCursor(SDL_Renderer* renderer, TTF_Font* font, SDL_Color textColor, SDL_Rect* rect, const char* text, int isSelected, Uint32 currentTime);
void RenderText (SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color textColor, SDL_Rect* rect);
//void renderTextWithCursor(SDL_Renderer* renderer, TTF_Font* font, SDL_Color textColor, SDL_Rect* rect);
void renderTextWithCursor(SDL_Renderer* renderer, TTF_Font* font, SDL_Color textColor, SDL_Rect* rect, const char* text, int isSelected, Uint32 currentTime);

// Mettre à jour les prototypes des fonctions
void handleKeyboardEvent(SDL_Event* e, char* text, int* cursorPosition);
void handleTextInputEvent(SDL_Event* e, char* text, int* cursorPosition);


#endif // TEXT_INPUT_H
