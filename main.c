#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>

// Déclaration des fonctions
SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer);
SDL_Texture* renderText(const char* message, const char* fontFile, SDL_Color color, int fontSize, SDL_Renderer* renderer);
void closeSDL(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture, TTF_Font* font);
int pointInRect(int x, int y, SDL_Rect* rect);

// Fonction principale
int main(int argc, char* argv[]) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Initialisation de TTF
    if (TTF_Init() == -1) {
        fprintf(stderr, "TTF_Init: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    // Initialisation de Mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        fprintf(stderr, "Mix_OpenAudio: %s\n", Mix_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Création d'une fenêtre SDL
    SDL_Window* window = SDL_CreateWindow(
            "Survivor’s Colony",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            800,
            600,
            SDL_WINDOW_SHOWN
    );

    if (!window) {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        closeSDL(window, NULL, NULL, NULL);
        return 1;
    }

    // Création d'un renderer SDL
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
        closeSDL(window, renderer, NULL, NULL);
        return 1;
    }

    // Charger la musique
    Mix_Music* bgMusic = Mix_LoadMUS("path/to/music.mp3");
    if (!bgMusic) {
        fprintf(stderr, "Failed to load background music: %s\n", Mix_GetError());
        closeSDL(window, renderer, NULL, NULL);
        return 1;
    }

    // Jouer la musique
    Mix_PlayMusic(bgMusic, -1);

    // Définition de la couleur de fond
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Noir

    // Charger la texture du bouton de démarrage
    SDL_Color buttonColor = {255, 255, 255}; // Blanc
    TTF_Font* font = TTF_OpenFont("path/to/font.ttf", 28);
    if (!font) {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
        closeSDL(window, renderer, NULL, NULL);
        return 1;
    }
    SDL_Texture* startBtnTexture = renderText("Start", "path/to/font.ttf", buttonColor, 28, renderer);
    SDL_Rect startBtnRect = {350, 250, 100, 50}; // Position et taille du bouton

    // Boucle principale
    int game_running = 1;
    SDL_Event e;
    while (game_running) {
        // Gestion des événements
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                game_running = 0;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (pointInRect(x, y, &startBtnRect)) {
                    // Le bouton Start a été cliqué, démarrer le jeu...
                    printf("Start button clicked!\n");
                }
            }
        }

        // Effacement de l'écran
        SDL_RenderClear(renderer);

        // Dessiner le bouton Start
        SDL_RenderCopy(renderer, startBtnTexture, NULL, &startBtnRect);

        // Affichage du rendu
        SDL_RenderPresent(renderer);
    }

    // Nettoyage
    closeSDL(window, renderer, startBtnTexture, font);
    Mix_FreeMusic(bgMusic);
    Mix_CloseAudio();

    return 0;
}

// Fonction pour charger une texture à partir d'un chemin de fichier
SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer) {
    SDL_Surface* loadedSurface = SDL_LoadBMP(path);
    if (!loadedSurface) {
        fprintf(stderr, "Could not load BMP image: %s\n", SDL_GetError());
        return NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    return texture;
}

// Fonction pour créer une texture de texte
SDL_Texture* renderText(const char* message, const char* fontFile, SDL_Color color, int fontSize, SDL_Renderer* renderer) {
    TTF_Font* font = TTF_OpenFont(fontFile, fontSize);
    if (!font) {
        fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());
        return NULL;
    }
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, message, color);
    if (!textSurface) {
        TTF_CloseFont(font);
        fprintf(stderr, "TTF_RenderText: %s\n", TTF_GetError());
        return NULL;
    }
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
    return textTexture;
}

// Fonction pour vérifier si un point est dans un rectangle
int pointInRect(int x, int y, SDL_Rect* rect) {
    return (x >= rect->x) && (x <= (rect->x + rect->w)) &&
           (y >= rect->y) && (y <= (rect->y + rect->h));
}

// Fonction pour fermer SDL proprement
void closeSDL(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture, TTF_Font* font) {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
