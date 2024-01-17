#ifndef CONFIG_H
#define CONFIG_H

#include "include.h"

typedef struct {
    int windowWidth;
    int windowHeight;
    int fullScreen;
    char keyUp[5];
    char keyDown[5];
    char keyLeft[5];
    char keyRight[5];
    int supportedResolutionsCount;
    int (*supportedResolutions)[2];
} GameConfig;

//  ------------     Functions      ------------   //

void initGameConfig(GameConfig *config);
GameConfig loadConfig(const char *filename);
void saveConfig(const GameConfig *config, const char *filename);
void updateResolution(ScreenManager *screenManager, GameConfig *config);
void renderConfigOptions(SDL_Renderer *renderer, TTF_Font *font, GameConfig *config);
void handleConfigurations(ScreenManager *screenManager);
void selectResolution(GameConfig *config, int index);
void toggleFullScreen(GameConfig *config);
void saveCurrentConfig(const GameConfig *config);

#endif // CONFIG_H
