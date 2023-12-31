#ifndef UI_H
#define UI_H

#include "include.h"

typedef struct {
    SDL_Rect rect;
    SDL_Texture* texture;
    SDL_Texture* hoverTexture;
    int isHovered;
    void (*onClick)(int* running);
} Button;


// Define your Button structure and other UI functions here
static Button startButton;
static Button quitButton;
static Button settingsButton;
static SDL_Renderer* uiRenderer = NULL;
static Mix_Chunk* buttonClickSound = NULL; // Sound effect for button click
static Button backButton;

// ------------ Extern   ------------

extern char playerName[256];
extern char playerSurname[256];
extern int isNameSelected;
extern int isSurnameSelected;
extern SDL_Rect nameInputRect;
extern SDL_Rect surnameInputRect;

// ------------Prototype UI ------------

// Prototypes des fonctions de l'UI
void UI_Init(SDL_Renderer* renderer, TTF_Font* font, int windowWidth, int windowHeight, Mix_Chunk* soundEffect);
void UI_HandleEvent(SDL_Event* e, int* running);
void UI_Render(SDL_Renderer* renderer, TTF_Font* font);
void UI_Shutdown();
void RenderCharacterCreationUI(SDL_Renderer* renderer, TTF_Font* font);
void RenderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color textColor, SDL_Rect* rect);
void StartNewSession(int* running);
void GoBack(int* running);

// ------------Add Prototype  ------------
void HandleButtonHover(Button *button, int mouseX, int mouseY);
void HandleButtonClick(Button *button, int *running);
void RenderTextInputField(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect* rect, const char* text, int isSelected);

//----------------------------------------

#endif // UI_H
