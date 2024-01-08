#include "../include/trailer.h"
int letterIndex = 0; // L'index de la lettre actuelle à afficher
float timeSinceLastLetter = 0; // Le temps depuis la dernière mise à jour de la lettre
float letterDelay = 0.05;


const char* trailerTexts[] = {
        "Humanity has been searching for a new planet for hundreds of years."
        "You are an astronaut, who crashed on a planet similar to Earth but strangely inhabited by unusual creatures.",
        "Out of fear, you decided to hide, then take refuge in the side of a mountain.",
        "To my surprise, as I approached this mountain, I discovered a hidden base."
};
int currentTrailerPart = 0;
const int totalTrailerParts = sizeof(trailerTexts) / sizeof(trailerTexts[0]);

void Trailer_Init(Trailer* trailer) {
    letterIndex = 0;
    currentTrailerPart = 0;
    trailer->isActive = 1;
    trailer->lastUpdateTime = SDL_GetTicks();

    strncpy(trailer->text, trailerTexts[currentTrailerPart], TRAILER_TEXT_MAX_LENGTH);
}

void Trailer_Render(SDL_Renderer* renderer, TTF_Font* font, Trailer* trailer, int windowWidth, int windowHeight) {
    if (!trailer->isActive) {
        return;
    }

    // Obtenez le temps actuel
    Uint32 currentTime = SDL_GetTicks();

    // Si suffisamment de temps s'est écoulé depuis la dernière mise à jour, avancez l'index de la lettre
    if (currentTime - trailer->lastUpdateTime > letterDelay * 1000) {
        letterIndex++;
        trailer->lastUpdateTime = currentTime; // Mise à jour du dernier temps d'actualisation
    }

    // Ne dépassez pas la longueur du texte actuel
    if (letterIndex > strlen(trailerTexts[currentTrailerPart])) {
        letterIndex = 0;
        currentTrailerPart++;
        if (currentTrailerPart >= totalTrailerParts) {
            trailer->isActive = 0; // Nous avons terminé le trailer
            return;
        }
    }

    // Préparez le texte à afficher jusqu'à l'index actuel de la lettre
    char displayedText[TRAILER_TEXT_MAX_LENGTH] = {0};
    strncpy(displayedText, trailerTexts[currentTrailerPart], letterIndex);

    // Configurez la couleur du texte et rendez le texte
    SDL_Color textColor = {255, 255, 255, 255}; // Couleur du texte en blanc
    SDL_Surface* surface = TTF_RenderText_Solid(font, displayedText, textColor);
    if (!surface) {
        fprintf(stderr, "Unable to render text surface: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        fprintf(stderr, "Unable to create texture from surface: %s\n", SDL_GetError());
        SDL_FreeSurface(surface); // Libérez la surface si la création de la texture échoue
        return;
    }

    // Centrez le texte à l'écran
    int textWidth = 0;
    int textHeight = 0;
    SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);
    SDL_Rect renderQuad = {(windowWidth - textWidth) / 2, (windowHeight - textHeight) / 2, textWidth, textHeight};

    // Rendez la texture à l'écran et libérez les ressources
    SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
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