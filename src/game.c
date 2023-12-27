#include "include.h"
#include "game.h"
#include "ui.h"
#include "character.h"
#include "Log.h"

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static TTF_Font* font = NULL;
static Mix_Music* bgMusic = NULL;
GameState currentGameState = MENU;
GameState previousGameState = MENU;

// Prototype des fonctions
void InitializeGameWorld();
void InitializeCharacters();
void UpdateGameWorld();
void UpdateCharacters();

GameWorld gameWorld;



void ChangeGameState(GameState newState) {
    previousGameState = currentGameState;
    currentGameState = newState;
    // Ajoutez ici toute autre logique nécessaire lors du changement d'état
}

void InitializeNewGameSession() {
    // Implémentez ici la logique pour initialiser une nouvelle session de jeu
}
void InitializeGameWorld() {
    gameWorld.day = 1; // Commence au jour 1
    // Initialisation d'autres éléments du monde ici
}

void UpdateGameWorld() {
    // Mettre à jour le monde du jeu
    // Par exemple, gérer les cycles jour/nuit, les événements aléatoires...
}



void RenderGameUI(SDL_Renderer* renderer) {
    // Implémenter le rendu de l'interface de jeu ici
    // Afficher les personnages, les ressources, le monde...
}


void Game_Init() {
    // Initialisation du système de logs
    Log_Init("game.log");

    // Log de l'initialisation du jeu
    Log(LOG_INFO, "Initialisation du jeu...");

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        Log(LOG_ERROR, "SDL could not initialize!");
        exit(1);
    }

    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        Log(LOG_ERROR, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    if (TTF_Init() == -1) {
        Log(LOG_ERROR, "TTF_Init: %s\n", TTF_GetError());
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        Log(LOG_ERROR, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }

    font = TTF_OpenFont("fonts/Roboto-Black.ttf", 28);
    if (!font) {
        Log(LOG_ERROR, "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        exit(1);
    }

    bgMusic = Mix_LoadMUS("assets/sounds/Helldivers.mp3");
    if (!bgMusic) {
        Log(LOG_ERROR, "Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }

    // Play the background music
    Mix_PlayMusic(bgMusic, -1);
    Mix_Chunk* soundEffect = Mix_LoadWAV("assets/sounds/click.wav"); // Load your sound effect
    int windowWidth = 800;
    int windowHeight = 600;

    UI_Init(renderer, font, windowWidth, windowHeight, soundEffect);

    // Log de la fin de l'initialisation du jeu
    Log(LOG_INFO, "Jeu initialisé avec succès.");

    /***********************************************************************/
    Character player = CreateCharacter("Player 1");
    AssignTask(&player, "Collect Wood");
    IncreaseHunger(&player);
    CompleteTask(&player);

    currentGameState = MENU;
}

void Game_Run() {
    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else {
                UI_HandleEvent(&event, &running);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        switch (currentGameState) {
            case MENU:
                UI_Render(renderer);
                break;
            case GAME_RUNNING:
                UpdateGameWorld();
                UpdateCharacters();
                RenderGameUI(renderer);
                break;
                // Gérer les autres états si nécessaire
        }

        SDL_RenderPresent(renderer);
    }
}


void Game_Shutdown() {
    UI_Shutdown();

    if (bgMusic != NULL) {
        Mix_FreeMusic(bgMusic);
    }

    Mix_CloseAudio();
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    // Fermeture du système de logs
    Log_Close();

    Log(LOG_INFO, "Jeu fermé.");
}
