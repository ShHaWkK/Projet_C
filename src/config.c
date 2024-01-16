// config.c
#include "../include/config.h"
#include "../include/include.h"
#include "../include/screen.h"

void load_configuration(const char* filename) {
    // Parsing du fichier de configuration...
}

GameConfig loadConfig(const char *filename) {
    GameConfig config;
    FILE *file = fopen(filename, "r");
    if (file) {
        fscanf(file, "windowWidth=%d\n", &config.windowWidth);
        fscanf(file, "windowHeight=%d\n", &config.windowHeight);
        fscanf(file, "fullScreen=%d\n", &config.fullScreen);
        fscanf(file, "keyUp=%s\n", config.keyUp);
        fscanf(file, "keyDown=%s\n", config.keyDown);
        fscanf(file, "keyLeft=%s\n", config.keyLeft);
        fscanf(file, "keyRight=%s\n", config.keyRight);
        fclose(file);
    } else {
        config.windowWidth = 800;
        config.windowHeight = 600;
        config.fullScreen = 0;
        strcpy(config.keyUp, "W");
        strcpy(config.keyDown, "S");
        strcpy(config.keyLeft, "A");
        strcpy(config.keyRight, "D");
    }
    return config;
}

void saveConfig(const GameConfig *config, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file) {
        fprintf(file, "windowWidth=%d\n", config->windowWidth);
        fprintf(file, "windowHeight=%d\n", config->windowHeight);
        fprintf(file, "fullScreen=%d\n", config->fullScreen);
        fprintf(file, "keyUp=%s\n", config->keyUp);
        fprintf(file, "keyDown=%s\n", config->keyDown);
        fprintf(file, "keyLeft=%s\n", config->keyLeft);
        fprintf(file, "keyRight=%s\n", config->keyRight);
        fclose(file);
    }
}

void updateResolution(ScreenManager *screenManager, GameConfig *config) {
    Screen_SetResolution(screenManager, config->windowWidth, config->windowHeight);
    if (config->fullScreen) {
        Screen_ToggleFullScreen(screenManager);
    }
}

void renderConfigOptions(SDL_Renderer *renderer, TTF_Font *font, GameConfig *config) {
    SDL_Color color = {255, 255, 255};
    SDL_Rect rect = {100, 100, 200, 30

    };
    char buffer[100];

    sprintf(buffer, "Resolution: %dx%d", config->windowWidth, config->windowHeight);
    SDL_Surface *surface = TTF_RenderText_Solid(font, buffer, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    rect.y += 40;
    sprintf(buffer, "Full Screen: %s", config->fullScreen ? "On" : "Off");
    surface = TTF_RenderText_Solid(font, buffer, color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void handleConfigurations(ScreenManager *screenManager) {
    GameConfig config = loadConfig("config.txt");
    updateResolution(screenManager, &config);
// Autres traitements de configuration si nécessaire
}