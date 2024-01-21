//
// Created by alexa on 21/01/2024.
//
#include "../include/include.h"
#include "../include/buildMenu.h"
void RenderText1(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y) {
    SDL_Color textColor = {255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

   
    SDL_Rect textRect;
    SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
    textRect.x = x - textRect.w / 2;
    textRect.y = y - textRect.h / 2;

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);
}

typedef void (*ClickCallback)(void);

void RenderClickableText1(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, ClickCallback onClick) {
    SDL_Color textColor = {255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    SDL_Rect textRect;
    SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
    textRect.x = x - textRect.w / 2;
    textRect.y = y - textRect.h / 2;

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &textRect)) {
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            if (onClick != NULL) {
                onClick();
            }
        }
    }

    SDL_DestroyTexture(textTexture);
}

void YourCallbackFunction() {
    SDL_Log("Redirection");
}