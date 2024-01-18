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
    mountainTexture = IMG_LoadTexture(renderer, "../assets/images/mountain.png");
    if (mountainTexture == NULL) {
        printf("Failed to load mountain texture: %s\n", IMG_GetError());
    }
}

//--------------------Function initGameMap ---------------------//

void initGameMap(GameMap* map, SDL_Renderer* renderer, SDL_Texture* mountainTexture) {
    // Ciel
    map->sky = (SDL_Rect){0, 0, WINDOW_WIDTH, SKY_HEIGHT};

    // Sol
    map->ground = (SDL_Rect){0, SKY_HEIGHT, WINDOW_WIDTH, 100};

    // Montagne
    map->mountain = (SDL_Rect){WINDOW_WIDTH - MOUNTAIN_WIDTH, SKY_HEIGHT, MOUNTAIN_WIDTH, GROUND_HEIGHT};
    int mountainPosX = WINDOW_WIDTH - MOUNTAIN_WIDTH;
    int GROUND_Y = SKY_HEIGHT;
    int mountainPosY = GROUND_Y - MOUNTAIN_HEIGHT;
    map->mountain = (SDL_Rect){mountainPosX, mountainPosY, MOUNTAIN_WIDTH, MOUNTAIN_HEIGHT};

    map->entrance = (SDL_Rect){WINDOW_WIDTH - MOUNTAIN_WIDTH, WINDOW_HEIGHT - ENTRANCE_WIDTH, MOUNTAIN_WIDTH, ENTRANCE_WIDTH};

    map->souterraine = (SDL_Rect){0, SKY_HEIGHT + 100, WINDOW_WIDTH, GROUND_HEIGHT - 100};

    // map->souterraine = (SDL_Rect){0, SKY_HEIGHT + 2, WINDOW_WIDTH, GROUND_HEIGHT - 2};
}

//--------------------Function renderGameMap ---------------------//

void renderGameMap(GameMap* map, SDL_Renderer* renderer) {
    // Rendu du ciel
    SDL_SetRenderDrawColor(renderer, 135, 206, 250, 255); // Couleur ciel
    SDL_RenderFillRect(renderer, &map->sky);

    // Rendu du sol
    SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); // Couleur sol
    SDL_RenderFillRect(renderer, &map->ground);

    // Rendu de la montagne
    SDL_SetRenderDrawColor(renderer, 139, 137, 137, 255); // Couleur montagne
    SDL_RenderFillRect(renderer, &map->mountain);

    // Rendu du ciel (zone extérieure)
    SDL_SetRenderDrawColor(renderer, 135, 206, 250, 255); // Couleur ciel (extérieur)
    SDL_RenderFillRect(renderer, &map->sky);

// Rendu du sol (zone extérieure)
    SDL_SetRenderDrawColor(renderer, 245, 222, 179, 255);
    SDL_RenderFillRect(renderer, &map->ground);

    // Souterraine
    SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); // Couleur marron foncé (souterraine)
    SDL_RenderFillRect(renderer, &map->souterraine);

    // Rendu de la texture de montagne
    if (mountainTexture != NULL) {
        SDL_RenderCopy(renderer, mountainTexture, NULL, &map->mountain);
    }

    // Rendu de l'entrée de la zone
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Couleur d'entrée
    SDL_RenderFillRect(renderer, &map->entrance);

}
//--------------------Function freeGameMapResources ---------------------//

void freeGameMapResources() {
    if (mountainTexture != NULL) {
        SDL_DestroyTexture(mountainTexture);
        mountainTexture = NULL;
    }
}

