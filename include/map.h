#ifndef MAP_H
#define MAP_H

#include "include.h"

#define SIZE_BLOCK 32 // Taille de bloc

typedef enum {
    CIEL, TERRE, MONTAGNE, BOIS, CAILLOU, BLE
} BlockType;

typedef enum {
    TOP, BOT, LEFT, RIGHT, DOWN
} Direction;

typedef struct {
    SDL_Rect area;
    SDL_Texture* texture;
    BlockType type;
} MapZone;

typedef struct {
    SDL_Rect position; // Position et taille du joueur
    SDL_Texture* texture; // Texture du joueur
} Player;

void initMap();
void initPlayer();
void movePlayer(int x, int y);
void renderMap(SDL_Renderer* renderer);
void renderPlayer(SDL_Renderer* renderer);
void freeMapTextures();
void freePlayerTexture();

#endif // MAP_H
