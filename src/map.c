/**********************************************************************/
/* File : map.c */
/* Date : 10/01/2024 */
/* author : ShHaWkK */
/**********************************************************************/

#include "../include/map.h"
#include "../include/include.h"

//#define TERRE_TEXTURE_PATH "../assets/images/bloc.png" // Replace with the actual path to your "terre" image
#define PLAYER_TEXTURE_PATH "../assets/images/marioArretDroite.png" // Replace with the actual path to your player image
//#define DEFAULT_TEXTURE_PATH "../assets/images/default.png" // Replace with the actual path to your default image
//
//// Define the size of the block for your map
#define SIZE_BLOCK 32
Player player;
/*

/*
void initMap(SDL_Renderer* renderer) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            map[i][j].area.x = j * SIZE_BLOCK;
            map[i][j].area.y = i * SIZE_BLOCK;
            map[i][j].area.w = SIZE_BLOCK;
            map[i][j].area.h = SIZE_BLOCK;

            // Assign the correct texture based on the map type
            if (mapArray[i][j] == TERRE) {
                map[i][j].texture = loadTexture(TERRE_TEXTURE_PATH, renderer);
            } else {
                map[i][j].texture = loadTexture(DEFAULT_TEXTURE_PATH, renderer);
            }
        }
    }
}
*/
void initPlayer(SDL_Renderer* renderer) {
    player.position.x = 0; // Starting position
    player.position.y = 0;
    player.position.w = SIZE_BLOCK; // Player's size
    player.position.h = SIZE_BLOCK;
    //player.texture = loadTexture(PLAYER_TEXTURE_PATH, renderer); // Load the player texture
}
//
//void movePlayer(int x, int y) {
//    // Update the player's position
//    player.position.x += x * SIZE_BLOCK;
//    player.position.y += y * SIZE_BLOCK;
//    // Add boundary and collision checks here
//}
//
//void renderMap(SDL_Renderer* renderer) {
//    for (int i = 0; i < ROWS; i++) {
//        for (int j = 0; j < COLS; j++) {
//            SDL_RenderCopy(renderer, map[i][j].texture, NULL, &map[i][j].area);
//        }
//    }
//}
//
void renderPlayer(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, player.texture, NULL, &player.position);
}

void freePlayerTexture() {
    if (player.texture != NULL) {
        SDL_DestroyTexture(player.texture);
        player.texture = NULL;
    }
}





void loadMountainTexture(SDL_Renderer* renderer) {
    mountainTexture = IMG_LoadTexture(renderer, "../assets/images/mountain.png");
    if (mountainTexture == NULL) {
        printf("Failed to load mountain texture: %s\n", IMG_GetError());
    }
}

//--------------------Function initGameMap ---------------------//
void initGameMap(GameMap* map, SDL_Renderer* renderer, SDL_Texture* mountainTexture) {
    // Ciel
    map->sky = (SDL_Rect) {0, 0, WINDOW_WIDTH, SKY_HEIGHT};

    // Sol
    map->ground = (SDL_Rect) {0, SKY_HEIGHT, WINDOW_WIDTH, GROUND_HEIGHT};

    // Montagne
    int mountainPosX = 0;
    int mountainPosY = MOUNTAIN_POS_Y;
    map->mountain = (SDL_Rect){MOUNTAIN_POS_X, mountainPosY, MOUNTAIN_WIDTH, MOUNTAIN_HEIGHT};

    int entrancePosY = mountainPosY + MOUNTAIN_HEIGHT - ENTRANCE_HEIGHT; 
    map->entrance = (SDL_Rect) {ENTRANCE_POS_X, ENTRANCE_POS_Y, ENTRANCE_WIDTH, ENTRANCE_HEIGHT};
    // Zone souterraine
    map->souterraine = (SDL_Rect) {0, SKY_HEIGHT + GROUND_HEIGHT, WINDOW_WIDTH, UNDERGROUND_Y};
}

//--------------------Function renderGameMap ---------------------//

void renderGameMap(GameMap* map, SDL_Renderer* renderer) {
    // Rendu du ciel
    SDL_SetRenderDrawColor(renderer, 135, 206, 250, 255);
    SDL_RenderFillRect(renderer, &map->sky);

    // Rendu du sol
    SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);
    SDL_RenderFillRect(renderer, &map->ground);

    // Rendu de la montagne
    SDL_SetRenderDrawColor(renderer, 139, 137, 137, 255);
    SDL_RenderCopy(renderer, map->tunnelEntrance.texture, NULL, &map->entrance);

    // Rendu de la texture de montagne
    if (mountainTexture != NULL) {
        SDL_RenderCopy(renderer, mountainTexture, NULL, &map->mountain);
    }

    // Rendu de l'entrée de la montagne avec une couleur gris foncé
    SDL_SetRenderDrawColor(renderer, 105, 105, 105, 255);
    SDL_RenderFillRect(renderer, &map->entrance);

    // Rendu de la zone souterraine  un espace souterrain
    SDL_SetRenderDrawColor(renderer, 101, 67, 33, 255);
    SDL_RenderFillRect(renderer, &map->souterraine);
    // Souterraine
    SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255); 
    SDL_RenderFillRect(renderer, &map->souterraine);    
    if (map->tunnelEntrance.texture != NULL) {
        SDL_Rect entranceRect = {map->entrance.x, map->entrance.y, ENTRANCE_WIDTH, ENTRANCE_HEIGHT};
        SDL_RenderCopy(renderer, map->tunnelEntrance.texture, NULL, &entranceRect);
    }

    SDL_Rect levelRect;
    for (int i = 0; i < 3; i++) {
        levelRect = (SDL_Rect){0, UNDERGROUND_Y + (UNDERGROUND_LEVEL_HEIGHT * i), WINDOW_WIDTH, UNDERGROUND_LEVEL_HEIGHT};
        SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255);
        SDL_RenderFillRect(renderer, &levelRect);
    }


}
//--------------------Function freeGameMapResources ---------------------//

void freeGameMapResources() {
    if (mountainTexture != NULL) {
        SDL_DestroyTexture(mountainTexture);
        mountainTexture = NULL;
    }
}

void initTunnelEntrance(GameMap* map, SDL_Renderer* renderer) {
    // Chargez la texture du tunnel
    SDL_Texture* tunnelTexture = IMG_LoadTexture(renderer, "chemin/vers/texture_tunnel.png");
    if (tunnelTexture == NULL) {
        printf("Failed to load tunnel texture: %s\n", IMG_GetError());
    }

    // Configurez le rectangle pour l'entrée du tunnel
    int tunnelPosX = WINDOW_WIDTH - MOUNTAIN_WIDTH; // Ajustez si nécessaire
    int tunnelPosY = GROUND_Y;
    map->tunnelEntrance.rect = (SDL_Rect){tunnelPosX, tunnelPosY, TUNNEL_WIDTH, TUNNEL_HEIGHT};
    map->tunnelEntrance.texture = tunnelTexture;
}