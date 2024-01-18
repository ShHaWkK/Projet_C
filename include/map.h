/**********************************************************************/
/* File : map.h */
/* Date : 10/01/2024 */
/* author : ShHaWkK */
/**********************************************************************/

#ifndef MAP_H
#define MAP_H

#include "include.h"


// Constantes pour les dimensions de la fenêtre et les zones de la carte
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define SKY_HEIGHT 200
#define GROUND_HEIGHT 100
#define MOUNTAIN_WIDTH 300
#define MOUNTAIN_HEIGHT 150
#define ENTRANCE_WIDTH 50
#define ENTRANCE_HEIGHT 100



static SDL_Texture* mountainTexture = NULL;

typedef struct {
    SDL_Rect sky;
    SDL_Rect ground;
    SDL_Rect mountain;
    SDL_Rect entrance;
    SDL_Rect souterraine;
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
