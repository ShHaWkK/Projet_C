#ifndef GAME_H
#define GAME_H

#include "include.h"

typedef enum {
    MENU,
    GAME_RUNNING,
    GAME_STATE_NEW_SESSION,
    GAME_STATE_CHARACTER_CREATION,
    SETTINGS,
    QUIT
} GameState;

typedef enum {
    INPUT_FIELD_NONE,
    INPUT_FIELD_NAME,
    INPUT_FIELD_SURNAME
} ActiveInputField;

extern ActiveInputField currentInputField;

typedef struct {
    int day;
    // Add other attributes for the game world here
} GameWorld;

// Global variables declarations
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

// Function prototypes
void Game_Init();
void Game_Run();
void Game_Shutdown();
void StartNewSession(int* running);
void ChangeGameState(GameState newState);
void InitializeNewGameSession();
void Game_HandleCharacterNameInput(const char* name);
void RenderCharacterCreationUI(SDL_Renderer* renderer, TTF_Font* font);
void handleKeyboardEvent(SDL_Event* e);
void handleTextInputEvent(SDL_Event* e);
#endif // GAME_H
