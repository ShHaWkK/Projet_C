#ifndef UI_H
#define UI_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

// Button structure
typedef struct {
    SDL_Rect rect;            // The rectangle defining the button's position and size
    SDL_Texture* texture;     // Texture for the button in normal state
    SDL_Texture* hoverTexture;// Texture for the button when hovered over
    int isHovered;            // Flag to indicate if the button is currently hovered over
    void (*onClick)(int* running); // Function pointer to the callback function when the button is clicked
} Button;

void UI_Init(SDL_Renderer* renderer, TTF_Font* font, int windowWidth, int windowHeight, Mix_Chunk* soundEffect);
void UI_HandleEvent(SDL_Event* e, int* running);
void UI_Render(SDL_Renderer* renderer);
void UI_Shutdown();
void StartNewSession(int* running);
void GoBack(int* running);
#endif // UI_H
