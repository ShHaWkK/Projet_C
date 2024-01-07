#include "../include/logo.h"

void SetWindowIcon(SDL_Window* window, const char* filepath) {
    if (!window || !filepath) {
        // Gérer l'erreur si la fenêtre ou le chemin du fichier n'est pas valide
        fprintf(stderr, "Invalid window or filepath provided to SetWindowIcon\n");
        return;
    }

    // Charger l'image pour l'icône
    SDL_Surface* icon = IMG_Load(filepath);
    if (icon == NULL) {
        // Gérer l'erreur si l'image n'a pas pu être chargée
        fprintf(stderr, "Unable to load icon: %s\n", IMG_GetError());
        return;
    }

    // Définir l'icône pour la fenêtre
    SDL_SetWindowIcon(window, icon);

    // Libérer la surface de l'icône
    SDL_FreeSurface(icon);
}
