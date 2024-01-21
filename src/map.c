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
    initElevator(&elevator, WINDOW_WIDTH / 2 - SIZE_BLOCK, mountainBottom - elevator.rect.h, BASE_POS_Y, map->elevatorTexture);
    initElevator(&elevator, WINDOW_WIDTH / 2 - SIZE_BLOCK, map->mountain.y + map->mountain.h, BASE_POS_Y, map->elevatorTexture);
}
//------------                              renderGameMap                 ------------//

void renderGameMap(GameMap* map, SDL_Renderer* renderer) {

    // Render the sky
    SDL_SetRenderDrawColor(renderer, 135, 206, 250, 255); // Sky color
    SDL_RenderFillRect(renderer, &map->sky);

    // Render the mountain
    SDL_RenderCopy(renderer, map->mountainTexture, NULL, &map->mountain);

    elevator.rect.y = map->mountain.y + map->mountain.h; // Assurez-vous que c'est le bord inférieur de la montagne
    SDL_RenderCopy(renderer, elevator.texture, NULL, &elevator.rect);



    int caveHeight = WINDOW_HEIGHT / 2;
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
    SDL_RenderCopy(renderer, elevator.texture, NULL, &elevator.rect);
    renderElevator(renderer, &elevator);


}

//------------                          freeGameMapResources                 ------------//

void freeGameMapResources(GameMap* map) {
    freeAllTextures(map);
}

//------------                                  Elevator                    ------------//

void initElevator(Elevator* elevator, int x, int startY, int endY, SDL_Texture* texture) {
    elevator->rect.x = x;
    elevator->rect.y = startY;
    elevator->rect.w = SIZE_BLOCK * 2;
    elevator->rect.h = SIZE_BLOCK * 4;
    elevator->startY = startY;
    elevator->endY = endY;
    elevator->texture = texture;
    elevator->speed = 2;
    elevator->movingUp = 1;
}


// Implementation of renderElevator function
void renderElevator(SDL_Renderer* renderer, Elevator* elevator) {
    SDL_RenderCopy(renderer, elevator->texture, NULL, &elevator->rect);
}
void updateElevatorPosition(Elevator* elevator) {
    // Déplacer l'ascenseur verticalement entre startY et endY
    static int direction = 1;
    elevator->rect.y += direction * 5; // Déplacez de 5 pixels par frame, ajustez selon vos besoins
    if (elevator->rect.y <= elevator->startY || elevator->rect.y >= elevator->endY) {
        direction *= -1;
    }
}
