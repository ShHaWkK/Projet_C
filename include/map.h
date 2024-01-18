/*
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
*/

#ifndef MAP_H
#define MAP_H

#include <SDL.h>

// Définitions pour les zones de la carte
#define EXTERIOR_ZONE_WIDTH 800
#define EXTERIOR_ZONE_HEIGHT 600

#define ENTRANCE_ZONE_WIDTH 200
#define ENTRANCE_ZONE_HEIGHT 200

#define BASE_ZONE_WIDTH 400
#define BASE_ZONE_HEIGHT 400

#define SCREEN_WIDTH 800
#define SKY_HEIGHT 200
#define GROUND_HEIGHT 400
#define ENTRANCE_ZONE_WIDTH 200

void initPlayer();

// Structure pour une zone de la carte
typedef struct {
    SDL_Rect rect; // Rectangle définissant la position et la taille de la zone
    SDL_Color color; // Couleur de la zone
} MapZone;

// Structure pour la carte entière
typedef struct {
    MapZone exterior;
    MapZone entrance;
    MapZone base;
    MapZone sky;
} GameMap;


typedef struct {
    SDL_Rect position; // Position et taille du joueur
    SDL_Texture* texture; // Texture du joueur
} Player;

// Fonctions de gestion de la carte
void initGameMap(GameMap* map);
void renderGameMap(GameMap* map, SDL_Renderer* renderer);
void freeGameMap(GameMap* map);
void initMap(GameMap* map, SDL_Renderer* renderer);
void renderMap(GameMap* map, SDL_Renderer* renderer);
void freeMapTextures();
#endif // MAP_H
