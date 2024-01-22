//
// Created by alexa on 22/01/2024.
//

#ifndef C_PLAYERCONTROLLEUR_H
#define C_PLAYERCONTROLLEUR_H

#include "include.h"

typedef struct {
    int x, y;
    int speed;
} PlayerObject;

typedef enum {
    PLAYER_STATE_TRAILER,
    PLAYER_STATE_ACTIVE,
} PlayerState;

void SetPlayerState(PlayerState state);
PlayerState GetPlayerState(void);

void InitPlayerObject(PlayerObject* player);
void UpdatePlayerObject(PlayerObject* player, const Uint8* keystate);
void RenderPlayerObject(SDL_Renderer* renderer, const PlayerObject* player);


#endif //C_PLAYERCONTROLLEUR_H
