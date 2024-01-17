//
// Created by alexa on 17/01/2024.
//

#ifndef PROJET_C_RESSOURCES_H
#define PROJET_C_RESSOURCES_H
#include "include.h"

void LoadGameResources(SDL_Renderer * renderer);
typedef struct {
    int id_resources;
    int type;
    int quantity;
} Ressources;
#endif //PROJET_C_RESSOURCES_H
