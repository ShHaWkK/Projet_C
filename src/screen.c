#include "../include/screen.h"
#include "../include/include.h"

ScreenManager* Screen_Init(const char* title, int width, int height, int fullScreen) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return NULL;
    }
    ScreenManager* manager = (ScreenManager*)malloc(sizeof(ScreenManager));
    if (!manager) {
        SDL_Log("Failed to allocate ScreenManager.\n");
        return NULL;
    }

    manager->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, fullScreen ? SDL_WINDOW_FULLSCREEN : 0);
    if (!manager->window) {
        SDL_Log("Window could not be created! SDL Error: %s\n", SDL_GetError());
        free(manager);
        return NULL;
    }

    manager->renderer = SDL_CreateRenderer(manager->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!manager->renderer) {
        SDL_Log("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(manager->window);
        free(manager);
        return NULL;
    }

    manager->windowWidth = width;
    manager->windowHeight = height;
    manager->scaleX = 1.0f;
    manager->scaleY = 1.0f;

    return manager;

}

void Screen_SetResolution(ScreenManager* screenManager, int width, int height) {
    if (!screenManager) return;
    SDL_SetWindowSize(screenManager->window, width, height);
    screenManager->windowWidth = width;
    screenManager->windowHeight = height;
    Screen_UpdateScale(screenManager);
}

void Screen_ToggleFullScreen(ScreenManager* screenManager) {
    if (!screenManager) return;
    Uint32 flags = SDL_GetWindowFlags(screenManager->window);
    if (flags & SDL_WINDOW_FULLSCREEN_DESKTOP) {
        SDL_SetWindowFullscreen(screenManager->window, 0);
    } else {
        SDL_SetWindowFullscreen(screenManager->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }
    Screen_UpdateScale(screenManager);
}
void Screen_UpdateScale(ScreenManager* screenManager) {
    if (!screenManager) return;
    int newWidth, newHeight;
    SDL_GetWindowSize(screenManager->window, &newWidth, &newHeight);
    screenManager->scaleX = (float)newWidth / screenManager->windowWidth;
    screenManager->scaleY = (float)newHeight / screenManager->windowHeight;
}

void Screen_ApplyScaleToRect(ScreenManager* screenManager, SDL_Rect* rect) {
    if (!screenManager || !rect) return;
    rect->x = (int)(rect->x * screenManager->scaleX);
    rect->y = (int)(rect->y * screenManager->scaleY);
    rect->w = (int)(rect->w *
                    screenManager->scaleX);
    rect->h = (int)(rect->h * screenManager->scaleY);
}

void Screen_CleanUp(ScreenManager* screenManager) {
    if (!screenManager) return;
    if (screenManager->renderer) {
        SDL_DestroyRenderer(screenManager->renderer);
    }

    if (screenManager->window) {
        SDL_DestroyWindow(screenManager->window);
    }

    free(screenManager);
}