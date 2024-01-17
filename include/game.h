#ifndef GAME_H
#define GAME_H

#include "include.h"

//--------  --------//

typedef enum {
    MENU,
    GAME_RUNNING,
    GAME_STATE_NEW_SESSION,
    GAME_STATE_CHARACTER_CREATION,
    GAME_STATE_TRAILER,
    SETTINGS,
    RESSOURCE,
    QUIT
} GameState;

//--------  --------//
typedef enum {
    INPUT_FIELD_NONE,
    INPUT_FIELD_NAME,
    INPUT_FIELD_SURNAME
} ActiveInputField;

extern ActiveInputField currentInputField;

//--------  --------//
typedef struct {
    int day;
} GameWorld;

//-------- Global variables declarations --------//
extern GameState currentGameState;
extern GameState previousGameState;
extern GameWorld gameWorld; // The game world
extern char playerName[256];
extern char playerSurname[256];
extern int isNameSelected;
extern int isSurnameSelected;
extern SDL_Rect nameInputRect;
extern SDL_Rect surnameInputRect;
extern ActiveInputField currentInputField;
extern int inputActive;

//--------  Function prototypes --------//

void Game_Init();
void Game_Run();
void Game_Shutdown();
void StartNewSession(int* running);
void ChangeGameState(GameState newState);
void InitializeNewGameSession();
void Game_HandleCharacterNameInput(const char* name);
void RenderCharacterCreationUI(SDL_Renderer* renderer, TTF_Font* font);


#endif // GAME_H
