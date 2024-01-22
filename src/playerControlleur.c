//
// Created by alexa on 22/01/2024.
//
// player_controller.c

#include "../include/playerControlleur.h"

static PlayerState playerState = PLAYER_STATE_TRAILER;

void SetPlayerState(PlayerState state) {
    playerState = state;
}

PlayerState GetPlayerState(void) {
    return playerState;
}

void InitPlayerObject(PlayerObject* player) {
    player->x = 400;
    player->y = 300;
    player->speed = 5;
}

void UpdatePlayerObject(PlayerObject* player, const Uint8* keystate) {
    // Déplacement horizontal
    if (keystate[SDL_SCANCODE_LEFT]) {
        player->x -= player->speed;
    }
    if (keystate[SDL_SCANCODE_RIGHT]) {
        player->x += player->speed;
    }
}

void RenderPlayerObject(SDL_Renderer* renderer, const PlayerObject* player) {

    SDL_Rect playerRect = {player->x, player->y, 50, 50};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &playerRect);
}
