//
// Created by alexa on 17/01/2024.
//

#ifndef PROJET_C_RESSOURCES_H
#define PROJET_C_RESSOURCES_H
#include "include.h"

void LoadGameResources(SDL_Renderer* renderer);
typedef struct {
    int x, y, width, height;
} ProductionZone;

typedef struct {
    int food;
    int water;
    int medicine;
} Resources;

extern Resources resources;

void initializeResources(Resources *resources);

void deductResources(Resources *resources, int survivors);
void HandleResourceGeneration(Resources *resources);
int playerIsInsideProductionZone(int playerX, int playerY, ProductionZone *productionZone);

#endif //PROJET_C_RESSOURCES_H
