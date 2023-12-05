#include <SDL.h>
#include <stdio.h>
#include <SDL_mixer.h>

/*
int main(int argc, char* argv[]) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Création d'une fenêtre SDL
    SDL_Window* window = SDL_CreateWindow(
            "Survivor’s Colony ",                      // titre
            SDL_WINDOWPOS_CENTERED,                   // position initiale x
            SDL_WINDOWPOS_CENTERED,                   // position initiale y
            800,                                      // largeur, en pixels
            600,                                      // hauteur, en pixels
            SDL_WINDOW_SHOWN                          // flags (SDL_WINDOW_SHOWN, SDL_WINDOW_FULLSCREEN, etc.)
    );

    if (window == NULL) {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Création d'un renderer SDL
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // La couleur de fond du renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Noir

    // Boucle principale
    int game_running = 1;
    SDL_Event e;
    while (game_running) {
        // Gestion des événements
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                game_running = 0;
            }
        }

        // Effacement de l'écran avec la couleur de fond
        SDL_RenderClear(renderer);

        // Dessiner votre jeu ici

        // Présenter (afficher) le rendu
        SDL_RenderPresent(renderer);
    }

    // Nettoyage
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}*/
#include <SDL.h>
#include <stdio.h>

// Déclaration des fonctions pour le chargement des textures
SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer);

int main(int argc, char* argv[]) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Création d'une fenêtre SDL
    SDL_Window* window = SDL_CreateWindow(
            "Survivor’s Colony ",                     // titre
            SDL_WINDOWPOS_CENTERED,                   // position initiale x
            SDL_WINDOWPOS_CENTERED,                   // position initiale y
            800,                                      // largeur, en pixels
            600,                                      // hauteur, en pixels
            SDL_WINDOW_SHOWN                          // flags (SDL_WINDOW_SHOWN, SDL_WINDOW_FULLSCREEN, etc.)
    );

    if (window == NULL) {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Création d'un renderer SDL
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Charger l'image
    SDL_Texture* texture = loadTexture("path/to/your/image.bmp", renderer);

    // Vérifier si la texture a été chargée correctement
    if (texture == NULL) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // La couleur de fond du renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Noir

    // Boucle principale
    int game_running = 1;
    SDL_Event e;
    while (game_running) {
        // Gestion des événements
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                game_running = 0;
            }
            // Ajouter la gestion des autres types d'événements ici (touches, souris, etc.)
        }

        // Effacement de l'écran avec la couleur de fond
        SDL_RenderClear(renderer);

        // Dessiner votre jeu ici
        // Dessiner la texture chargée
        SDL_Rect renderQuad = { 100, 100, 200, 200 }; // Définissez la position et la taille de la texture
        SDL_RenderCopy(renderer, texture, NULL, &renderQuad);

        // Présenter (afficher) le rendu
        SDL_RenderPresent(renderer);
    }

    // Nettoyage
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

// Fonction pour charger une texture à partir d'un chemin de fichier
SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer) {
    SDL_Surface* loadedSurface = SDL_LoadBMP(path);
    if (loadedSurface == NULL) {
        fprintf(stderr, "Could not load BMP image: %s\n", SDL_GetError());
        return NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface); // N'oubliez pas de libérer la surface chargée
    return texture;
}
