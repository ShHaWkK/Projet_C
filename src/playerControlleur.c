//
// Created by alexa and ShHawk on 22/01/2024.
//
// player_controller.c

#include "../include/playerControlleur.h"
#include "../include/colision.h"
static PlayerState playerState = PLAYER_STATE_TRAILER;

void SetPlayerState(PlayerState state) {
    playerState = state;
}

PlayerState GetPlayerState(void) {
    return playerState;
}

void InitPlayerObject(PlayerObject* player) {
    player->x = 400;
    player->y = 70;
    player->speed = 5;
}

/*void UpdatePlayerObject(PlayerObject player, const Uint8* keystate) {
    // Déplacement horizontal
    if (keystate[SDL_SCANCODE_LEFT]) {
        player->x -= player->speed;
    }
    if (keystate[SDL_SCANCODE_RIGHT]) {
        player->x += player->speed;
    }
}*/

void RenderPlayerObject(SDL_Renderer* renderer, const PlayerObject* player) {
    SDL_Rect playerRect = {player->x, player->y, 50, 50};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &playerRect);
}

void UpdatePlayerObject(PlayerObject* player, const Uint8* keystate, GameMap* map) {
    // Déplacement horizontal
    if (keystate[SDL_SCANCODE_LEFT]) {
        player->x -= player->speed;
        if (player->x < 0) {
            player->x = 0; // Empêcher le joueur de sortir à gauche de l'écran
        }
    }
    if (keystate[SDL_SCANCODE_RIGHT]) {
        player->x += player->speed;
        if (player->x > WINDOW_WIDTH - PLAYER_WIDTH) {
            player->x = WINDOW_WIDTH - PLAYER_WIDTH; // Empêcher le joueur de sortir à droite de l'écran
        }
    }

    // Appliquer la gravité
    player->y += GRAVITY_SPEED;

    // Vérifiez si le joueur touche le sol (ou la partie inférieure de votre zone de jeu)
    if (player->y > FLOOR_LEVEL - PLAYER_HEIGHT) {
        player->y = FLOOR_LEVEL - PLAYER_HEIGHT; // Empêcher le joueur de descendre en dessous du sol
    }

    SDL_Rect playerRect = {player->x, player->y, PLAYER_WIDTH, PLAYER_HEIGHT};
    if (checkCollision(&playerRect, &map->ground)) {
        // Gérer la collision (par exemple, ajuster la position du joueur)
        player->y = map->ground.y - PLAYER_HEIGHT;
    }
}