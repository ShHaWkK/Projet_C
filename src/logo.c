/**********************************************************************/
/* File : logo.c */
/* Date : 10/12/2023 */
/* author : ShHaWkK */
/**********************************************************************/
#include "../include/logo.h"

void SetWindowIcon(SDL_Window* window, const char* filepath) {
    if (!window || !filepath) {
        fprintf(stderr, "Invalid window or filepath provided to SetWindowIcon\n");
        return;
    }

    // Charger l'image pour l'icône
    SDL_Surface* icon = IMG_Load(filepath);
    if (icon == NULL) {
        fprintf(stderr, "Unable to load icon: %s\n", IMG_GetError());
        return;
    }

    SDL_SetWindowIcon(window, icon);

    SDL_FreeSurface(icon);
}
