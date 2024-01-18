/**********************************************************************/
/* File : map.h */
/* Date : 10/01/2024 */
/* author : ShHaWkK */
/**********************************************************************/

#ifndef MAP_H
#define MAP_H

#include "include.h"

// Constants for the map dimensions
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define SKY_HEIGHT 150
#define GROUND_HEIGHT 50
#define MOUNTAIN_WIDTH 300
#define MOUNTAIN_HEIGHT 200
#define ENTRANCE_WIDTH 100
#define ENTRANCE_HEIGHT 50

// Mountain position on the map
#define MOUNTAIN_POS_X ((WINDOW_WIDTH - MOUNTAIN_WIDTH) / 2)
#define MOUNTAIN_POS_Y (SKY_HEIGHT)

// Entrance position based on the mountain's position and size
#define ENTRANCE_POS_X (MOUNTAIN_POS_X + (MOUNTAIN_WIDTH - ENTRANCE_WIDTH) / 2)
#define ENTRANCE_POS_Y (MOUNTAIN_POS_Y + MOUNTAIN_HEIGHT - ENTRANCE_HEIGHT)

// Tunnel entrance dimensions
#define TUNNEL_WIDTH 50
#define TUNNEL_HEIGHT 30

// Ground level position
#define GROUND_Y (SKY_HEIGHT + GROUND_HEIGHT)

static SDL_Texture* mountainTexture = NULL;

typedef struct {
    SDL_Rect rect;
    SDL_Texture* texture;
} TunnelEntrance;

typedef struct {
    SDL_Rect sky;
    SDL_Rect ground;
    SDL_Rect mountain;
    SDL_Rect entrance;
    SDL_Rect souterraine;
    TunnelEntrance tunnelEntrance; // Adding the tunnel entrance
} GameMap;

void initPlayer();

// Structure for a map zone
typedef struct {
    SDL_Rect rect; // Rectangle defining the position and size of the zone
    SDL_Color color; // Color of the zone
} MapZone;

// Structure for the map as a whole
typedef struct {
    SDL_Rect position; // Position and size of the player
    SDL_Texture* texture; // Texture of the player
} Player;

// Map management functions
void initGameMap(GameMap* map, SDL_Renderer* renderer, SDL_Texture* mountainTexture);
void renderGameMap(GameMap* map, SDL_Renderer* renderer);
void freeGameMapResources();
void initTunnelEntrance(GameMap* map, SDL_Renderer* renderer);

#endif // MAP_H
