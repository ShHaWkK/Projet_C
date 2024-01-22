//
// Created by alexa & ShhHawk on 22/01/2024.
//

#ifndef C_PLAYERCONTROLLEUR_H
#define C_PLAYERCONTROLLEUR_H
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 50
#define GRAVITY_SPEED 5
#define GROUND_HEIGHT 50
#define FLOOR_LEVEL (WINDOW_HEIGHT - GROUND_HEIGHT)
#include "include.h"
#include "map.h"
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
void RenderPlayerObject(SDL_Renderer* renderer, const PlayerObject* player);
void UpdatePlayerObject(PlayerObject* player, const Uint8* keystate, GameMap* map);

#endif //C_PLAYERCONTROLLEUR_H