#include "../include/trailer.h"
int letterIndex = 0; // L'index de la lettre actuelle à afficher
float timeSinceLastLetter = 0; // Le temps depuis la dernière mise à jour de la lettre
float letterDelay = 0.01;


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

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - trailer->lastUpdateTime > letterDelay * 1000) {
        letterIndex++;
        trailer->lastUpdateTime = currentTime;
    }

    if (letterIndex > strlen(trailerTexts[currentTrailerPart])) {
        letterIndex = strlen(trailerTexts[currentTrailerPart]);
    }

    char displayedText[TRAILER_TEXT_MAX_LENGTH] = {0};
    strncpy(displayedText, trailerTexts[currentTrailerPart], letterIndex);

    SDL_Color textColor = {255, 255, 255, 255}; // White color for the text
    int y = 50; // Start position on the Y axis

    // We render text line by line
    char* context = NULL;
    char* line = strtok_r(displayedText, "\n", &context);
    while (line != NULL) {
        int lineLength = strlen(line);
        if (lineLength > 0) {
            SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, line, textColor, windowWidth);
            if (surface == NULL) {
                fprintf(stderr, "Unable to render text surface: %s\n", TTF_GetError());
                return;
            }
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (texture == NULL) {
                fprintf(stderr, "Unable to create texture from rendered text: %s\n", SDL_GetError());
                SDL_FreeSurface(surface);
                return;
            }

            // Calculate position to center the text
            SDL_Rect renderQuad = { (windowWidth - surface->w) / 2, y, surface->w, surface->h };

            SDL_FreeSurface(surface); // Don't need the surface after texture creation
            SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
            SDL_DestroyTexture(texture); // Don't need the texture after rendering

            // Move down for the next line of text
            y += TTF_FontHeight(font) + 5; // Adjust the 5 to increase/decrease line spacing
        }

        // Get the next line
        line = strtok_r(NULL, "\n", &context);
    }

    SDL_RenderPresent(renderer); // Update the screen with rendering performed
}





/*
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
 */
void Trailer_Update(Trailer* trailer, Uint32 deltaTime) {

    trailer->timeSinceLastLetter += deltaTime;

    if (trailer->timeSinceLastLetter > letterDelay) {
        if (letterIndex < strlen(trailerTexts[currentTrailerPart])) {
            letterIndex++; // Incrémentez pour afficher la lettre suivante
        } else {
            // Passez à la partie suivante du texte du trailer
            currentTrailerPart++;
            if (currentTrailerPart >= totalTrailerParts) {
                trailer->isActive = 0; // Le trailer est terminé
            } else {
                letterIndex = 0; // Réinitialisez pour la nouvelle partie
            }
        }
        trailer->timeSinceLastLetter = 0; // Réinitialisez le compteur
    }
}
