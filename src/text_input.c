// text_input.c

#include "../include/text_input.h"

char textInput[256] = "";
int cursorPosition = 0;
int inputActive = 0;

void startTextInput() {
    inputActive = 1;
    SDL_StartTextInput();
}

void stopTextInput() {
    inputActive = 0;
    SDL_StopTextInput();
}

void handleKeyboardEvent(SDL_Event* e, char* text, int* cursorPosition) {
    if (!inputActive) return;

    int len = strlen(text);
    if (e->type == SDL_KEYDOWN) {
        if (e->key.keysym.sym == SDLK_BACKSPACE && *cursorPosition > 0) {
            memmove(&text[*cursorPosition - 1], &text[*cursorPosition], len - *cursorPosition);
            text[--(*cursorPosition)] = '\0';
        } else if (e->key.keysym.sym == SDLK_LEFT && *cursorPosition > 0) {
            (*cursorPosition)--;
        } else if (e->key.keysym.sym == SDLK_RIGHT && *cursorPosition < len) {
            (*cursorPosition)++;
        }
    }
}


void handleTextInputEvent(SDL_Event* e, char* text, int* cursorPosition) {
    if (!inputActive) return;

    int len = strlen(text);
    if (e->type == SDL_TEXTINPUT && len < 255) {
        // Insère le nouveau caractère à la position du curseur
        memmove(&text[*cursorPosition + 1], &text[*cursorPosition], len - *cursorPosition + 1);
        text[*cursorPosition] = e->text.text[0];
        text[++(*cursorPosition)] = '\0'; // S'assure que la chaîne est toujours terminée par '\0'
    }
}


void renderTextWithCursor(SDL_Renderer* renderer, TTF_Font* font, SDL_Color textColor, SDL_Rect* rect, const char* text, int isSelected, Uint32 currentTime) {
    // Rendu du texte
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    // Gestion du clignotement du curseur
    if (isSelected && inputActive) {
        Uint32 cursorBlinkRate = 500; // Durée en millisecondes pour un cycle complet (visible + invisible)
        bool isCursorVisible = (SDL_GetTicks() / cursorBlinkRate) % 2; // Clignotement du curseur

        if (isCursorVisible) {
            char cursor[] = "|";
            surface = TTF_RenderText_Solid(font, cursor, textColor);
            texture = SDL_CreateTextureFromSurface(renderer, surface);

            // Calcul de la largeur du texte pour positionner le curseur
            int cursorWidth = 0;
            if (cursorPosition > 0) {
                char subbuff[cursorPosition + 1];
                memcpy(subbuff, &text[0], cursorPosition);
                subbuff[cursorPosition] = '\0';
                TTF_SizeText(font, subbuff, &cursorWidth, NULL);
            }

            SDL_Rect cursorRect = {rect->x + cursorWidth, rect->y, surface->w, surface->h};
            SDL_RenderCopy(renderer, texture, NULL, &cursorRect);

            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }
    }
}
