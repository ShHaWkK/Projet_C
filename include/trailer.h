#ifndef TRAILER_H
#define TRAILER_H
#define TRAILER_TEXT_MAX_LENGTH 1024

#include "../include/include.h"

// Define the trailer structure
typedef struct {
    char text[TRAILER_TEXT_MAX_LENGTH];
    int isActive;
    Uint32 lastUpdateTime;
    Uint32 timeSinceLastLetter;
} Trailer;

//----- Function prototypes -----//
void Trailer_Init(Trailer* trailer);
void Trailer_Render(SDL_Renderer* renderer, TTF_Font* font, Trailer* trailer, int windowWidth, int windowHeight);
//void Trailer_Update(Trailer* trailer, SDL_Event* e);
void Trailer_Update(Trailer* trailer, Uint32 deltaTime);
void Trailer_HandleEvent(Trailer* trailer, SDL_Event* e);
// - -------------//
char* strndup(const char* s, size_t n);

#endif // TRAILER_H
