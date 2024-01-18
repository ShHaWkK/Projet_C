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

// Constantes pour les dimensions de la fenêtre et les zones de la carte
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define SKY_HEIGHT 150
#define GROUND_HEIGHT (WINDOW_HEIGHT - SKY_HEIGHT)
#define MOUNTAIN_WIDTH 200
#define ENTRANCE_WIDTH 100
#define MOUNTAIN_HEIGHT 300
#define ENTRANCE_HEIGHT 100

// Couleurs pour chaque zone
#define COLOR_SKY (SDL_Color){135, 206, 235, 255} // Couleur bleu ciel
#define COLOR_GROUND (SDL_Color){244, 164, 96, 255} // Couleur sable
#define COLOR_MOUNTAIN (SDL_Color){139, 69, 19, 255} // Couleur marron pour la montagne
#define COLOR_ENTRANCE (SDL_Color){160, 82, 45, 255} // Couleur plus sombre pour l'entrée


static SDL_Texture* mountainTexture = NULL;

typedef struct {
    SDL_Rect sky;
    SDL_Rect ground;
    SDL_Rect mountain;
    SDL_Rect entrance;
} GameMap;


void initPlayer();

// Structure pour une zone de la carte
typedef struct {
    SDL_Rect rect; // Rectangle définissant la position et la taille de la zone
    SDL_Color color; // Couleur de la zone
} MapZone;

// Structure pour la carte entière


typedef struct {
    SDL_Rect position; // Position et taille du joueur
    SDL_Texture* texture; // Texture du joueur
} Player;

// Fonctions de gestion de la carte
void initGameMap(GameMap* map, SDL_Renderer* renderer, SDL_Texture* mountainTexture);
void renderGameMap(GameMap* map, SDL_Renderer* renderer);
void freeGameMap(GameMap* map);
void initMap(GameMap* map, SDL_Renderer* renderer);
void renderMap(GameMap* map, SDL_Renderer* renderer);
void freeMapTextures();
void loadMountainTexture(SDL_Renderer* renderer);
void freeGameMapResources();
#endif // MAP_H
