#include "../include/map.h"
#include "../include/include.h"


/*
 * ciel=0
 * terre=1
 * montagne=2
 * bois=3
 * caillou=4
 * ble=5
 *
 */

#define ROWS 11
#define COLS 26
//#define CIEL 0
//#define TERRE 1
//#define MONTAGNE 2
//#define BOIS 3
//#define CAILLOU 4
//#define BLE 5
//
//
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
    mountainTexture = IMG_LoadTexture(renderer, "../assets/images/mountain-1728498_1280.png");
    if (mountainTexture == NULL) {
        printf("Failed to load mountain texture: %s\n", IMG_GetError());
    }
}

//--------------------Function initGameMap ---------------------//

void initGameMap(GameMap* map, SDL_Renderer* renderer, SDL_Texture* mountainTexture) {
    // ciel
    map->sky = (SDL_Rect){0, 0, WINDOW_WIDTH, SKY_HEIGHT};

    // sol
    map->ground = (SDL_Rect){0, SKY_HEIGHT, WINDOW_WIDTH, GROUND_HEIGHT};

// montagne
    map->mountain = (SDL_Rect){WINDOW_WIDTH - MOUNTAIN_WIDTH, SKY_HEIGHT, MOUNTAIN_WIDTH, GROUND_HEIGHT - ENTRANCE_WIDTH};

    // l'entrée de la zone
    map->entrance = (SDL_Rect){WINDOW_WIDTH - MOUNTAIN_WIDTH, WINDOW_HEIGHT - ENTRANCE_WIDTH, MOUNTAIN_WIDTH, ENTRANCE_WIDTH};
}

//--------------------Function renderGameMap ---------------------//

void renderGameMap(GameMap* map, SDL_Renderer* renderer) {
    // Rendu du ciel
    SDL_SetRenderDrawColor(renderer, COLOR_SKY.r, COLOR_SKY.g, COLOR_SKY.b, COLOR_SKY.a);
    SDL_RenderFillRect(renderer, &map->sky);

    // Rendu du sol
    SDL_SetRenderDrawColor(renderer, COLOR_GROUND.r, COLOR_GROUND.g, COLOR_GROUND.b, COLOR_GROUND.a);
    SDL_RenderFillRect(renderer, &map->ground);

    // Rendu de la montagne
    SDL_SetRenderDrawColor(renderer, COLOR_MOUNTAIN.r, COLOR_MOUNTAIN.g, COLOR_MOUNTAIN.b, COLOR_MOUNTAIN.a);
    SDL_RenderFillRect(renderer, &map->mountain);

    if (mountainTexture != NULL) {
        SDL_RenderCopy(renderer, mountainTexture, NULL, &map->mountain);
    }
    SDL_SetRenderDrawColor(renderer, COLOR_ENTRANCE.r, COLOR_ENTRANCE.g, COLOR_ENTRANCE.b, COLOR_ENTRANCE.a);
    SDL_RenderFillRect(renderer, &map->entrance);

}
//--------------------Function freeGameMapResources ---------------------//

void freeGameMapResources() {
    if (mountainTexture != NULL) {
        SDL_DestroyTexture(mountainTexture);
        mountainTexture = NULL;
    }
}

