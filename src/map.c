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

/*
 *int map[11][26];

 */
//#include "../include/map.h"
//#define ROWS 11
//#define COLS 26
//#define CIEL 0
//#define TERRE 1
//#define MONTAGNE 2
//#define BOIS 3
//#define CAILLOU 4
//#define BLE 5
//
//
//// Constants for texture file paths
//#define TERRE_TEXTURE_PATH "../assets/images/bloc.png" // Replace with the actual path to your "terre" image
#define PLAYER_TEXTURE_PATH "../assets/images/marioArretDroite.png" // Replace with the actual path to your player image
//#define DEFAULT_TEXTURE_PATH "../assets/images/default.png" // Replace with the actual path to your default image
//
//// Define the size of the block for your map
#define SIZE_BLOCK 32 // You need to define this based on your game's scale
//
//int mapArray[ROWS][COLS] = {
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {CIEL, CIEL, CIEL, CIEL, CIEL, CIEL, CIEL, CIEL, CIEL, CIEL, CIEL, CIEL, CIEL, CIEL, CIEL, CIEL, CIEL, CIEL, CIEL, CIEL, CIEL, CIEL, CIEL, CIEL, CIEL, CIEL},
//        {TERRE, TERRE, TERRE, TERRE, TERRE, TERRE, TERRE, TERRE, TERRE, TERRE, TERRE, TERRE, TERRE, TERRE, TERRE, TERRE, TERRE, TERRE, TERRE, TERRE, TERRE, TERRE, TERRE, TERRE, TERRE, TERRE},
//};
//// Map and player definitions
//MapZone map[ROWS][COLS];
Player player;

SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(filePath);
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", filePath, IMG_GetError());
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", filePath, SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}
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
//
//void freeMapTextures() {
//    for (int i = 0; i < ROWS; i++) {
//        for (int j = 0; j < COLS; j++) {
//            if (map[i][j].texture != NULL) {
//                SDL_DestroyTexture(map[i][j].texture);
//                map[i][j].texture = NULL;
//            }
//        }
//    }
//}
//
void freePlayerTexture() {
    if (player.texture != NULL) {
        SDL_DestroyTexture(player.texture);
        player.texture = NULL;
    }
}





void initGameMap(GameMap* map) {
    // Initialisation du ciel
    map->sky = (SDL_Rect){0, 0, WINDOW_WIDTH, SKY_HEIGHT};

    // Initialisation du sol
    map->ground = (SDL_Rect){0, SKY_HEIGHT, WINDOW_WIDTH - MOUNTAIN_WIDTH, GROUND_HEIGHT};

    // Initialisation de la montagne
    map->mountain = (SDL_Rect){WINDOW_WIDTH - MOUNTAIN_WIDTH, SKY_HEIGHT, MOUNTAIN_WIDTH, GROUND_HEIGHT - ENTRANCE_WIDTH};

    // Initialisation de l'entrée
    map->entrance = (SDL_Rect){WINDOW_WIDTH - MOUNTAIN_WIDTH, WINDOW_HEIGHT - ENTRANCE_WIDTH, MOUNTAIN_WIDTH, ENTRANCE_WIDTH};
}

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

    // Rendu de l'entrée
    SDL_SetRenderDrawColor(renderer, COLOR_ENTRANCE.r, COLOR_ENTRANCE.g, COLOR_ENTRANCE.b, COLOR_ENTRANCE.a);
    SDL_RenderFillRect(renderer, &map->entrance);
}

void freeGameMap(GameMap* map) {
    // Libérer les ressources de la carte si nécessaire
}

/*
int map[11][26];

map[0][0]=0;
map[0][1]=0;
map[0][2]=0;
map[0][3]=0;
map[0][4]=0;
map[0][5]=0;
map[0][6]=0;
map[0][7]=0;
map[0][8]=0;
map[0][9]=0;
map[0][10]=0;
map[0][11]=0;
map[0][12]=0;
map[0][13]=0;
map[0][14]=0;
map[0][15]=0;
map[0][16]=0;
map[0][17]=0;
map[0][18]=0;
map[0][19]=0;
map[0][20]=0;
map[0][21]=0;
map[0][22]=0;
map[0][23]=0;
map[0][24]=0;
map[0][25]=0;

map[1][0]=0;
map[1][1]=0;
map[1][2]=0;
map[1][3]=0;
map[1][4]=0;
map[1][5]=0;
map[1][6]=0;
map[1][7]=0;
map[1][8]=0;
map[1][9]=0;
map[1][10]=0;
map[1][11]=0;
map[1][12]=0;
map[1][13]=0;
map[1][14]=0;
map[1][15]=0;
map[1][16]=0;
map[1][17]=0;
map[1][18]=0;
map[1][19]=0;
map[1][20]=0;
map[1][21]=0;
map[1][22]=0;
map[1][23]=0;
map[1][24]=0;
map[1][25]=0;

map[2][0]=0;
map[2][1]=0;
map[2][2]=1;
map[2][3]=1;
map[2][4]=1;
map[2][5]=1;
map[2][6]=1;
map[2][7]=1;
map[2][8]=1;
map[2][9]=1;
map[2][10]=0;
map[2][11]=0;
map[2][12]=0;
map[2][13]=0;
map[2][14]=0;
map[2][15]=0;
map[2][16]=0;
map[2][17]=0;
map[2][18]=0;
map[2][19]=0;
map[2][20]=0;
map[2][21]=0;
map[2][22]=0;
map[2][23]=0;
map[2][24]=0;
map[2][25]=0;
map[3][0]=0;
map[3][1]=0;
map[3][2]=1;
map[3][3]=0;
map[3][4]=0;
map[3][5]=0;
map[3][6]=0;
map[3][7]=0;
map[3][8]=0;
map[3][9]=0;
map[3][10]=0;
map[3][11]=0;
map[3][12]=0;
map[3][13]=0;
map[3][14]=0;
map[3][15]=0;
map[3][16]=0;
map[3][17]=0;
map[3][18]=0;
map[3][19]=0;
map[3][20]=0;
map[3][21]=0;
map[3][22]=0;
map[3][23]=0;
map[3][24]=0;
map[3][25]=0;
map[4][0]=0;

map[4][1]=0;
map[4][2]=0;
map[4][3]=0;
map[4][4]=0;
map[4][5]=0;
map[4][6]=0;
map[4][7]=0;
map[4][8]=0;
map[4][9]=0;
map[4][10]=0;
map[4][11]=0;
map[4][12]=0;
map[4][13]=0;
map[4][14]=0;
map[4][15]=0;
map[4][16]=0;
map[4][17]=0;
map[4][18]=0;
map[4][19]=0;
map[4][20]=0;
map[4][21]=0;
map[4][22]=0;
map[4][23]=0;
map[4][24]=0;
map[4][25]=0;
map[5][0]=0;
map[5][1]=0;
map[5][2]=0;
map[5][3]=0;
map[5][4]=0;
map[5][5]=0;
map[5][6]=0;
map[5][7]=0;
map[5][8]=0;
map[5][9]=0;
map[5][10]=0;
map[5][11]=0;
map[5][12]=0;
map[5][13]=0;
map[5][14]=0;
map[5][15]=0;
map[5][16]=0;
map[5][17]=0;
map[5][18]=0;
map[5][19]=0;
map[5][20]=0;
map[5][21]=0;
map[5][22]=0;
map[5][23]=0;
map[5][24]=0;
map[5][25]=0;
map[5][25]=0;
map[6][0]=0;
map[6][1]=0;
map[6][2]=0;

map[6][3]=0;
map[6][4]=0;
map[6][5]=0;
map[6][6]=0;
map[6][7]=0;
map[6][8]=0;
map[6][9]=0;
map[6][10]=0;
map[6][11]=0;
map[6][12]=0;
map[6][13]=0;
map[6][14]=0;
map[6][15]=0;
map[6][16]=0;
map[6][17]=0;
map[6][18]=0;
map[6][19]=0;
map[6][20]=0;
map[6][21]=0;
map[6][22]=0;
map[6][23]=0;
map[6][24]=0;
map[6][25]=0;
map[7][0]=0;
map[7][1]=0;
map[7][2]=0;
map[7][3]=0;
map[7][4]=0;
map[7][5]=0;
map[7][6]=0;
map[7][7]=0;
map[7][8]=0;
map[7][9]=0;
map[7][10]=0;
map[7][11]=0;
map[7][12]=0;
map[7][13]=0;
map[7][14]=0;
map[7][15]=0;
map[7][16]=0;
map[7][17]=0;
map[7][18]=0;
map[7][19]=0;
map[7][20]=0;
map[7][21]=0;
map[7][22]=0;
map[7][23]=0;
map[7][24]=0;
map[7][25]=0;
map[8][0]=0;
map[8][1]=0;
map[8][2]=0;
map[8][3]=0;
map[8][4]=0;

map[8][5]=0;
map[8][6]=0;
map[8][7]=0;
map[8][8]=0;
map[8][9]=0;
map[8][10]=0;
map[8][11]=0;
map[8][12]=0;
map[8][13]=0;
map[8][14]=0;
map[8][15]=0;
map[8][16]=0;
map[8][17]=0;
map[8][18]=0;
map[8][19]=0;
map[8][20]=0;
map[8][21]=0;
map[8][22]=0;
map[8][23]=0;
map[8][24]=0;
map[8][25]=0;
map[9][0]=0;
map[9][1]=0;
map[9][2]=0;
map[9][3]=0;
map[9][4]=0;
map[9][5]=0;
map[9][6]=0;
map[9][7]=0;
map[9][8]=0;
map[9][9]=0;
map[9][10]=0;
map[9][11]=0;
map[9][12]=0;
map[9][13]=0;
map[9][14]=0;
map[9][15]=0;
map[9][16]=0;
map[9][17]=0;
map[9][18]=0;
map[9][19]=0;
map[9][20]=0;
map[9][21]=0;
map[9][22]=0;
map[9][23]=0;
map[9][24]=0;
map[9][25]=0;
map[10][0]=0;
map[10][1]=0;
map[10][2]=0;
map[10][3]=0;
map[10][4]=0;
map[10][5]=0;
map[10][6]=0;
map[10][7]=0;

map[10][8]=0;
map[10][9]=0;
map[10][10]=0;
map[10][11]=0;
map[10][12]=0;
map[10][13]=0;
map[10][14]=0;
map[10][15]=0;
map[10][16]=0;
map[10][17]=0;
map[10][18]=0;
map[10][19]=0;
map[10][20]=0;
map[10][21]=0;
map[10][22]=0;
map[10][23]=0;
map[10][24]=0;
map[10][25]=0;
*/
