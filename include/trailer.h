#ifndef TRAILER_H
#define TRAILER_H
#define TRAILER_TEXT_MAX_LENGTH 512

#include "../include/include.h"

// Define the trailer structure
typedef struct {
    char text[TRAILER_TEXT_MAX_LENGTH];
    int isActive;
} Trailer;

// Function prototypes
void Trailer_Init(Trailer* trailer);
void Trailer_Render(SDL_Renderer* renderer, TTF_Font* font, Trailer* trailer, int windowWidth, int windowHeight);
void Trailer_Update(Trailer* trailer, SDL_Event* e);

void Trailer_HandleEvent(Trailer* trailer, SDL_Event* e);

#endif // TRAILER_H