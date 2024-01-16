// screen.h

#ifndef SCREEN_H
#define SCREEN_H

#include "include.h"


typedef struct ScreenManager {
    SDL_Window* window;
    SDL_Renderer* renderer;
    int windowWidth;
    int windowHeight;
    float scaleX;
    float scaleY;
} ScreenManager;

ScreenManager* Screen_Init(const char* title, int width, int height, int fullScreen);
void Screen_SetResolution(ScreenManager* screenManager, int width, int height);
void Screen_ToggleFullScreen(ScreenManager* screenManager);
void Screen_UpdateScale(ScreenManager* screenManager);
void Screen_ApplyScaleToRect(ScreenManager* screenManager, SDL_Rect* rect);
void Screen_CleanUp(ScreenManager* screenManager);

#endif // SCREEN_H