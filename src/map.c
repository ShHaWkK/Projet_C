/**********************************************************************/
/* File : map.c */
/* Date : 10/01/2024 */
/* author : ShHaWkK */
/**********************************************************************/

#include "../include/map.h"
#include "../include/include.h"

#define SIZE_BLOCK 32
SDL_Texture* baseTexture = NULL;
SDL_Texture* tunnelTextures[NUM_TUNNELS];
MovingBlock elevatorBlock;
//------------      LoadTexture      ------------//
// Fonction générique pour charger une texture
SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath);
    if (texture == NULL) {
        fprintf(stderr, "Failed to load texture %s: %s\n", filePath, IMG_GetError());
    }
    return texture;
}
//------------      loadAllTextures      ------------//

void loadAllTextures(GameMap* map, SDL_Renderer* renderer)
{
    map->mountainTexture = loadTexture("../assets/images/mountain.png", renderer);
    map->baseTexture = loadTexture("../assets/images/stone.png", renderer);
    map->souterraineTexture = loadTexture("../assets/images/tunnel.png", renderer);
    map->undergroundBaseTexture= loadTexture("../assets/images/souterrain.png",renderer);
    map->elevatorTexture = loadTexture("../assets/images/bloc.png", renderer);
}
//------------      freeAllTextures      ------------//

void freeAllTextures(GameMap* map) {
    if (map->mountainTexture) SDL_DestroyTexture(map->mountainTexture);
    if (map->baseTexture) SDL_DestroyTexture(map->baseTexture);
    if (map->tunnelEntranceTexture) SDL_DestroyTexture(map->tunnelEntranceTexture); // C'est pour l'entrée de la montagne
    if (map->souterraineTexture) SDL_DestroyTexture(map->souterraineTexture);
    if(map->undergroundBaseTexture) SDL_DestroyTexture(map->undergroundBaseTexture);

    for (int i = 0; i < NUM_TUNNELS; i++)
    {
        if (map->tunnels[i].texture) SDL_DestroyTexture(map->tunnels[i].texture);
    }
}
//------------                          initGameMap                       ------------//

void initGameMap(GameMap* map, SDL_Renderer* renderer) {
    int mountainBottom = map->mountain.y + map->mountain.h;
    // Initialisation des zones
    map->sky = (SDL_Rect) {0, 0, WINDOW_WIDTH, SKY_HEIGHT};
    map->ground = (SDL_Rect) {0, SKY_HEIGHT, WINDOW_WIDTH, GROUND_HEIGHT};
    map->mountain = (SDL_Rect) {MOUNTAIN_POS_X, MOUNTAIN_POS_Y, MOUNTAIN_WIDTH, MOUNTAIN_HEIGHT};
    map->entrance = (SDL_Rect) {ENTRANCE_POS_X, ENTRANCE_POS_Y, ENTRANCE_WIDTH, ENTRANCE_HEIGHT};
    map->souterraine = (SDL_Rect) {BASE_POS_X, BASE_POS_Y, BASE_WIDTH, BASE_HEIGHT};
    map->mountain = (SDL_Rect) {MOUNTAIN_POS_X, MOUNTAIN_POS_Y, MOUNTAIN_WIDTH, MOUNTAIN_HEIGHT};

    loadAllTextures(map, renderer);
    updateMovingBlockPosition(&elevatorBlock);
    int elevatorStartX = WINDOW_WIDTH - MOUNTAIN_WIDTH - (2 * SIZE_BLOCK);
    int elevatorWidth = 2 * SIZE_BLOCK; // La largeur de l'ascenseur pour deux blocs
    int elevatorHeight = SIZE_BLOCK; // La hauteur de l'ascenseur pour un bloc

    // Initialisation de l'ascenseur
   // initMovingBlock(&elevatorBlock, elevatorStartX, 300, elevatorWidth, elevatorHeight, 2, minY, maxY);
   }
//------------                              renderGameMap                 ------------//

void renderGameMap(GameMap* map, SDL_Renderer* renderer) {

    // Render the sky
    SDL_SetRenderDrawColor(renderer, 135, 206, 250, 255); // Sky color
    SDL_RenderFillRect(renderer, &map->sky);

    // Render the mountain
    SDL_RenderCopy(renderer, map->mountainTexture, NULL, &map->mountain);


    //SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
    SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255);
    int caveHeight = WINDOW_HEIGHT / (2-5);
    int caveCeilingThickness = SIZE_BLOCK * 3;

    for (int x = 0; x < WINDOW_WIDTH; x += SIZE_BLOCK) {
        if (x < map->entrance.x || x > map->entrance.x + map->entrance.w) {
            SDL_Rect groundBlock = {x, SKY_HEIGHT, SIZE_BLOCK, GROUND_HEIGHT};
            SDL_RenderCopy(renderer, map->baseTexture, NULL, &groundBlock);
        }
    }

    for (int x = 0; x < WINDOW_WIDTH; x += SIZE_BLOCK) {
        for (int y = caveHeight; y < caveHeight + caveCeilingThickness; y += SIZE_BLOCK) {
            SDL_Rect stoneBlockRect = {x, y, SIZE_BLOCK, SIZE_BLOCK};
            SDL_RenderCopy(renderer, map->baseTexture, NULL, &stoneBlockRect);
        }
    }

    // Dessiner le sol de la grotte
    int caveCeilingHeight = WINDOW_HEIGHT / 4; // Hauteur du plafond de la grotte.
    int caveFloorHeight = WINDOW_HEIGHT * 3 / 4; // Hauteur du sol de la grotte.

    for (int x = 0; x < WINDOW_WIDTH; x += SIZE_BLOCK) {
        // Render ground blocks only where there's no entrance
        if (x < map->entrance.x || x > map->entrance.x + map->entrance.w) {
            SDL_Rect groundBlock = {x, SKY_HEIGHT, SIZE_BLOCK, GROUND_HEIGHT};
            SDL_RenderCopy(renderer, map->baseTexture, NULL, &groundBlock);
        }

    }

    // Render the lower cave structure
    for (int y = caveFloorHeight; y < WINDOW_HEIGHT; y += SIZE_BLOCK) {
        for (int x = 0; x < WINDOW_WIDTH; x += SIZE_BLOCK) {
            // Render the blocks to form the floor and walls of the cave
            SDL_Rect stoneBlockRect = {x, y, SIZE_BLOCK, SIZE_BLOCK};
            SDL_RenderCopy(renderer, map->baseTexture, NULL, &stoneBlockRect);
        }
    }

    // Render the lower cave structure
    for (int y = caveFloorHeight; y < WINDOW_HEIGHT; y += SIZE_BLOCK) {
        for (int x = 0; x < WINDOW_WIDTH; x += SIZE_BLOCK) {
            // Si les blocs à enlever se trouvent sur la ligne y == 300, par exemple,
            // et entre les colonnes x == 600 et x == 700, ajustez ces valeurs selon vos besoins.
            if (y == 500 && (x >= 600 && x <= 700)) {
                continue; // On saute la dessin des blocs dans cette plage
            }

            // Render the blocks to form the floor and walls of the cave
            SDL_Rect stoneBlockRect = {x, y, SIZE_BLOCK, SIZE_BLOCK};
            SDL_RenderCopy(renderer, map->baseTexture, NULL, &stoneBlockRect);
        }
    }
    //Elevator texture

    renderMovingBlock(renderer, &elevatorBlock, map->elevatorTexture);

}

//------------                          freeGameMapResources                 ------------//

void freeGameMapResources(GameMap* map) {
    freeAllTextures(map);
}


//--------------------------    Elevator    ---------------------------------------//

void initMovingBlock(MovingBlock* block, int x, int y, int w, int h, int speed, int minY, int maxY) {
    block->rect.x = x;
    block->rect.y = y;
    block->rect.w = w;
    block->rect.h = h;
    block->speed = speed;
    block->minY = minY;
    block->maxY = maxY;
    block->movingUp = 1;
    // movingup est pour que ça commence d'abord par le dessus

}


void updateMovingBlockPosition(MovingBlock* block) {
    if (block->movingUp) {
        block->rect.y -= block->speed;
        if (block->rect.y <= block->minY) {
            block->movingUp = 0; // Change direction to down
        }
    } else {
        block->rect.y += block->speed;
        if (block->rect.y >= block->maxY) {
            block->movingUp = 1; // Change direction to up
        }
    }
}


// Fonction de rendu de l'ascenseur
void renderMovingBlock(SDL_Renderer* renderer, MovingBlock* block, SDL_Texture* texture) {
    SDL_RenderCopy(renderer, texture, NULL, &block->rect);
}