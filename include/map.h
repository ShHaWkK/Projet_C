#include "include.h"

#define SizeBlock // a definir

typedef struct {
    SDL_Rect area;
    SDL_Texture* texture;
    enum{TOP,BOT,LEFT,RIGHT};//mouvement joueur
    enum{};//les texture de chaque blocks
} MapZone;