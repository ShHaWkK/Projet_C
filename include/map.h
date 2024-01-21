/**********************************************************************/
/* File : map.h */
/* Date : 10/01/2024 */
/* author : ShHaWkK */
/**********************************************************************/

#ifndef MAP_H
#define MAP_H

#include "include.h"

//---------     Constants for the map dimensions    ---------//
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define SKY_HEIGHT 150
#define GROUND_HEIGHT 50
#define MOUNTAIN_WIDTH 300
#define MOUNTAIN_HEIGHT 200
#define ENTRANCE_WIDTH 100
#define ENTRANCE_HEIGHT 50
#define BASE_WIDTH 400
#define BASE_HEIGHT 100
#define BASE_POS_X ((WINDOW_WIDTH - BASE_WIDTH) / 2)
#define BASE_POS_Y (SKY_HEIGHT + GROUND_HEIGHT)
#define MOUNTAIN_POS_X (WINDOW_WIDTH - MOUNTAIN_WIDTH)
#define MOUNTAIN_POS_Y (SKY_HEIGHT - MOUNTAIN_HEIGHT)
#define ENTRANCE_POS_X (MOUNTAIN_POS_X + (MOUNTAIN_WIDTH - ENTRANCE_WIDTH) / 2)
#define ENTRANCE_POS_Y (MOUNTAIN_POS_Y + MOUNTAIN_HEIGHT - ENTRANCE_HEIGHT)
#define NUM_TUNNELS 2
#define OFFSET_Y 25
#define MOUNTAIN_POS_X (WINDOW_WIDTH - MOUNTAIN_WIDTH)
#define MOUNTAIN_POS_Y (SKY_HEIGHT - MOUNTAIN_HEIGHT + OFFSET_Y)
#define GROUND_Y (SKY_HEIGHT + GROUND_HEIGHT)
#define UNDERGROUND_Y (SKY_HEIGHT + GROUND_HEIGHT)
#define TUNNEL_WIDTH 50
#define TUNNEL_HEIGHT 30
#define BASE_POS_Y (GROUND_Y) // Débute juste après le sol
#define BASE_HEIGHT (WINDOW_HEIGHT - BASE_POS_Y)
#define LADDER_WIDTH 30

typedef struct {
    SDL_Rect rect;
    SDL_Texture* texture;
} Tunnel;

typedef struct {
    Tunnel tunnels[NUM_TUNNELS];
    SDL_Rect sky;
    SDL_Rect ground;
    SDL_Rect mountain;
    SDL_Rect entrance;
    SDL_Rect souterraine;
    SDL_Rect undergroundBase;
    SDL_Texture* undergroundBaseTexture;
    SDL_Texture* mountainTexture;
    SDL_Texture* baseTexture;
    SDL_Texture* souterraineTexture;
    SDL_Texture* tunnelEntranceTexture;
    SDL_Texture* ladderTexture;
} GameMap;

// Structure for the map as a whole
typedef struct {
    SDL_Rect position; // Position and size of the player
    SDL_Texture* texture; // Texture of the player
} Player;


typedef struct {
    SDL_Rect rect;       // Position et taille de l'ascenseur
    SDL_Texture* texture; // Texture de l'ascenseur
    int startY;          // Position de départ en Y
    int endY;            // Position de fin en Y
} Elevator;


void initGameMap(GameMap* map, SDL_Renderer* renderer);
void renderGameMap(GameMap* map, SDL_Renderer* renderer);
void freeGameMapResources(GameMap* map);
void loadAllTextures(GameMap* map, SDL_Renderer* renderer);
void freeAllTextures(GameMap* map);
void initElevator(Elevator* elevator, int x, int startY, int endY, SDL_Texture* texture);
void updateElevator(Elevator* elevator);
void renderElevator(SDL_Renderer* renderer, Elevator* elevator);

#endif // MAP_H
