#ifndef CONFIG_H
#define CONFIG_H

// Structure pour stocker les configurations du jeu
typedef struct {
    int windowWidth;
    int windowHeight;
    int fullScreen;
} GameConfig;

// Fonctions pour gérer la configuration
GameConfig LoadGameConfig(const char* filename);
void SaveGameConfig(const char* filename, const GameConfig* config);

#endif // CONFIG_H
