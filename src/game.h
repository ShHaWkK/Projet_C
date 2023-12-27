#ifndef GAME_H
#define GAME_H

typedef enum {
    MENU,
    GAME_RUNNING,
    SETTINGS,
    QUIT
} GameState;

void Game_Init();
void Game_Run();
void Game_Shutdown();

#endif // GAME_H
