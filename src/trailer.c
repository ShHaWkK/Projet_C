#include "../include/trailer.h"

// Ajoutez des variables globales pour gérer le texte du trailer
const char* trailerTexts[] = {
        "L’humanité cherche depuis des centaines d’année une nouvelle planète.",
        "Vous êtes un astronaute, qui s’est écrasé sur une planète similaire à la Terre mais étrangement habitée par des créatures inhabituelles.",
        "Par peur, vous avez décidé de vous cacher, puis de vous réfugier dans le flanc d'une montagne.",
        "À ma grande surprise, en m'approchant de cette montagne, j'ai découvert une base dissimulée."
};
int currentTrailerPart = 0;
const int totalTrailerParts = sizeof(trailerTexts) / sizeof(trailerTexts[0]);

void Trailer_Init(Trailer* trailer) {
    strncpy(trailer->text, trailerTexts[currentTrailerPart], TRAILER_TEXT_MAX_LENGTH);
    trailer->isActive = 1;
}

void Trailer_Render(SDL_Renderer* renderer, TTF_Font* font, Trailer* trailer, int windowWidth, int windowHeight) {
    if (trailer->isActive) {
        SDL_Color textColor = {255, 255, 255, 255};
        SDL_Surface* surface = TTF_RenderText_Solid(font, trailer->text, textColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        int textWidth = surface->w;
        int textHeight = surface->h;
        SDL_Rect renderQuad = { (windowWidth - textWidth) / 2, (windowHeight - textHeight) / 2, textWidth, textHeight };

        SDL_FreeSurface(surface);
        SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
        SDL_DestroyTexture(texture);
    }
}

void Trailer_Update(Trailer* trailer, SDL_Event* e) {
    // Par exemple, passer à la partie suivante du texte en appuyant sur la touche espace
    if (e->type == SDL_KEYDOWN) {
        if (e->key.keysym.sym == SDLK_SPACE) {
            currentTrailerPart++;
            if (currentTrailerPart >= totalTrailerParts) {
                trailer->isActive = 0; // Fin du trailer
                currentTrailerPart = 0; // Réinitialiser pour une prochaine lecture
            } else {
                strncpy(trailer->text, trailerTexts[currentTrailerPart], TRAILER_TEXT_MAX_LENGTH);
            }
        }
    }
}
