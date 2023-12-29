#include "include.h"

#ifndef GAME_H
#define GAME_H


typedef enum {
    MENU,
    GAME_RUNNING,
    GAME_STATE_NEW_SESSION,
    GAME_STATE_CHARACTER_CREATION,
    SETTINGS,
    QUIT
} GameState;

typedef struct {
    // ...attributs du monde du jeu...
    int day;
} GameWorld;

extern GameState currentGameState;
extern GameState previousGameState;
extern GameWorld gameWorld; // Le monde du jeu
extern char playerName[256];
extern char playerSurname[256];
extern int inputActive;
extern TTF_Font* font;

// Prototypes des fonctions
void Game_Init();
void Game_Run();
void Game_Shutdown();
void StartNewSession(int* running);
void ChangeGameState(GameState newState);
void InitializeNewGameSession();
void Game_HandleCharacterNameInput(const char* name);
void RenderCharacterCreationUI(SDL_Renderer* renderer, TTF_Font* font);
#endif // GAME_H
