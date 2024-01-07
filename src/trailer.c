#include "../include/trailer.h"
int letterIndex = 0; // L'index de la lettre actuelle à afficher
float timeSinceLastLetter = 0; // Le temps depuis la dernière mise à jour de la lettre
float letterDelay = 0.05;
// Ajoutez des variables globales pour gérer le texte du trailer
const char* trailerTexts[] = {
        "Humanity has been searching for a new planet for hundreds of years."
        "You are an astronaut, who crashed on a planet similar to Earth but strangely inhabited by unusual creatures.",
        "Out of fear, you decided to hide, then take refuge in the side of a mountain.",
        "To my surprise, as I approached this mountain, I discovered a hidden base."
};
int currentTrailerPart = 0;
const int totalTrailerParts = sizeof(trailerTexts) / sizeof(trailerTexts[0]);

void Trailer_Init(Trailer* trailer) {
    strncpy(trailer->text, trailerTexts[currentTrailerPart], TRAILER_TEXT_MAX_LENGTH);
    trailer->isActive = 1;
}

void Trailer_Render(SDL_Renderer* renderer, TTF_Font* font, Trailer* trailer, int windowWidth, int windowHeight) {
    if (trailer->isActive) {
        // Utilisez la fonction appropriée pour un meilleur rendu
        SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, trailer->text, (SDL_Color){255, 255, 255, 255}, windowWidth);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        int textWidth = surface->w;
        int textHeight = surface->h;
        SDL_Rect renderQuad = {
                (windowWidth - textWidth) / 2, // Centre horizontalement
                (windowHeight - textHeight) / 2, // Centre verticalement
                textWidth,
                textHeight
        };

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
