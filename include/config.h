#ifndef CONFIG_H
#define CONFIG_H

// Structure pour stocker les configurations du jeu
typedef struct GameConfig {
    int windowWidth;
    int windowHeight;
    int fullscreen;
} GameConfig;

// Fonctions pour gérer la configuration
GameConfig LoadGameConfig(const char* configFile);
void SaveGameConfig(const char* configFile, const GameConfig* config);

#endif // CONFIG_H
