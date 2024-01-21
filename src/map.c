/**********************************************************************/
/* File : map.c */
/* Date : 10/01/2024 */
/* author : ShHaWkK */
/**********************************************************************/

#include "../include/map.h"
#include "../include/include.h"

#define SIZE_BLOCK 32
Player player;
SDL_Texture* baseTexture = NULL;
SDL_Texture* tunnelTextures[NUM_TUNNELS];
Elevator elevator;

//------------      LoadTexture      ------------//
// Fonction générique pour charger une texture
SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath);
    if (texture == NULL) {
        fprintf(stderr, "Failed to load texture %s: %s\n", filePath, IMG_GetError());
    }
    return texture;
}

void loadAllTextures(GameMap* map, SDL_Renderer* renderer) {
    map->mountainTexture = loadTexture("../assets/images/mountain.png", renderer);
    map->baseTexture = loadTexture("../assets/images/stone.png", renderer);
    map->tunnelEntranceTexture = loadTexture("../assets/images/tunnelEntrance.png", renderer);
    map->souterraineTexture = loadTexture("../assets/images/tunnel.png", renderer);
    for (int i = 0; i < NUM_TUNNELS; i++) {
        map->tunnels[i].texture = loadTexture("../assets/images/tunnel.png", renderer);
    }
}

void freeAllTextures(GameMap* map) {
    if (map->mountainTexture) SDL_DestroyTexture(map->mountainTexture);
    if (map->baseTexture) SDL_DestroyTexture(map->baseTexture);
    if (map->tunnelEntranceTexture) SDL_DestroyTexture(map->tunnelEntranceTexture);
    if (map->souterraineTexture) SDL_DestroyTexture(map->souterraineTexture);
    for (int i = 0; i < NUM_TUNNELS; i++) {
        if (map->tunnels[i].texture) SDL_DestroyTexture(map->tunnels[i].texture);
    }
}

void initGameMap(GameMap* map, SDL_Renderer* renderer) {
    // Initialisation des zones
    map->sky = (SDL_Rect) {0, 0, WINDOW_WIDTH, SKY_HEIGHT};
    map->ground = (SDL_Rect) {0, SKY_HEIGHT, WINDOW_WIDTH, GROUND_HEIGHT};
    map->mountain = (SDL_Rect){MOUNTAIN_POS_X, MOUNTAIN_POS_Y, MOUNTAIN_WIDTH, MOUNTAIN_HEIGHT};
    map->entrance = (SDL_Rect){ENTRANCE_POS_X, ENTRANCE_POS_Y, ENTRANCE_WIDTH, ENTRANCE_HEIGHT};
    map->souterraine = (SDL_Rect){BASE_POS_X, BASE_POS_Y, BASE_WIDTH, BASE_HEIGHT};

    // Chargement des textures
    loadAllTextures(map, renderer);
}

void renderGameMap(GameMap* map, SDL_Renderer* renderer) {
    // Rendu du ciel, du sol, de la montagne, de l'entrée et des tunnels
    SDL_SetRenderDrawColor(renderer, 135, 206, 250, 255); // Couleur du ciel
    SDL_RenderFillRect(renderer, &map->sky);

    SDL_RenderCopy(renderer, map->baseTexture, NULL, &map->ground);
    SDL_RenderCopy(renderer, map->mountainTexture, NULL, &map->mountain);
    SDL_RenderCopy(renderer, map->tunnelEntranceTexture, NULL, &map->entrance);

    if (map->souterraineTexture) {
        SDL_RenderCopy(renderer, map->souterraineTexture, NULL, &map->souterraine);
    }
    for (int i = 0; i < NUM_TUNNELS; i++) {
        SDL_RenderCopy(renderer, map->tunnels[i].texture, NULL, &map->tunnels[i].rect);
    }

    SDL_RenderCopy(renderer, map->baseTexture, NULL, &map->souterraine);
}

void freeGameMapResources(GameMap* map) {
    freeAllTextures(map);
}