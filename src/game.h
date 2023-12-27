#ifndef GAME_H
#define GAME_H

typedef enum {
    MENU,
    GAME_RUNNING,
    SETTINGS,
    QUIT
} GameState;


typedef struct {
    // Exemple de structure pour le monde du jeu
    int day;
    // Autres attributs du monde du jeu...
} GameWorld;

extern GameState currentGameState;
extern GameState previousGameState;
extern GameWorld gameWorld; // Le monde du jeu

/*** Void ***/
void Game_Init();
void Game_Run();
void Game_Shutdown();
void StartNewSession(int* running);
void ChangeGameState(GameState newState);
void InitializeNewGameSession();
#endif // GAME_H
