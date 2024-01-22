#include "../include/include.h"


int checkCollision(SDL_Rect* a, SDL_Rect* b) {
    // Les côtés des rectangles A et B
    int leftA = a->x;
    int rightA = a->x + a->w;
    int topA = a->y;
    int bottomA = a->y + a->h;

    int leftB = b->x;
    int rightB = b->x + b->w;
    int topB = b->y;
    int bottomB = b->y + b->h;

    // Si un des côtés de A est en dehors de B
    if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB) {
        return 0; // Pas de collision
    }

    return 1; // Il y a une collision
}