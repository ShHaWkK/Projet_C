#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>

SDL_Window* window;
SDL_Renderer* renderer;

// Définition des boutons
SDL_Rect startButton = {300, 200, 200, 50}; // x, y, largeur, hauteur
SDL_Rect quitButton = {300, 300, 200, 50}; // x, y, largeur, hauteur

int main(int argc, char* argv[]) {
    int quit = 0;
    SDL_Event event;

    int w = 800;
    int h = 600;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return -1;

    window = SDL_CreateWindow("Basic Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
    if (window == NULL) return -1;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) return -1;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &startButton)) {
                    // Logique du bouton Start
                    printf("Start button clicked\n");
                } else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &quitButton)) {
                    // Logique du bouton Quit
                    quit = 1;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderClear(renderer);

        // Dessiner les boutons
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rouge pour le bouton Start
        SDL_RenderFillRect(renderer, &startButton);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Vert pour le bouton Quit
        SDL_RenderFillRect(renderer, &quitButton);

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}