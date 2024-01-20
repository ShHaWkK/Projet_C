//
// Created by alexa on 17/01/2024.
//
#include "../include/ressources.h"
#include "../include/database.h"
#include "../include/Log.h"
#include "../include/include.h"

void initializeResources(Resources *resources) {
    resources->food = 100;
    resources->water = 50;
    resources->medicine = 30;
}



void LoadGameResources(SDL_Renderer * renderer) {
    //initialisation du fonts
    SDL_Color textColor = {255, 255, 255};
    TTF_Font* font = TTF_OpenFont("../assets/fonts/arial.ttf", 20);

    //Affiche la barre de fonds
    SDL_Rect resourceBar = {0, 0, 800, 50};
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 0.50);
    SDL_RenderFillRect(renderer, &resourceBar);


    // Définit position cases1 dans la barre
    SDL_Rect resourceCase1 = {10, 10, 100, 30};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &resourceCase1);

    // Définit position iconecases1 dans la barre
    SDL_Rect iconeCase1 = {120, 10, 30, 30};
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 0.50);
    SDL_RenderFillRect(renderer, &iconeCase1);

    //définit icone 1
    SDL_Texture* textureNourriture = IMG_LoadTexture(renderer, "../assets/images/nourriture.png");
    if (textureNourriture == NULL) {
        // Gestion des erreurs lors du chargement de l'image
        SDL_Log("Erreur lors du chargement de l'image : %s", IMG_GetError());
        // Vous pouvez également utiliser une couleur unie à la place de l'image
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    } else {

        SDL_RenderCopy(renderer, textureNourriture, NULL, &iconeCase1);

        SDL_DestroyTexture(textureNourriture);
    }

    //affichage du text
    if (font == NULL) {
        SDL_Log("Erreur lors du chargement de la police : %s", TTF_GetError());
    } else {
        char *textQNourriture = "42";
        SDL_Surface *textSNourriture = TTF_RenderText_Solid(font, textQNourriture, textColor);

        if (textSNourriture == NULL) {
            SDL_Log("Erreur lors du rendu du texte : %s", TTF_GetError());
            /
        } else {
            SDL_Texture * textTNourriture = SDL_CreateTextureFromSurface(renderer, textSNourriture);


        if (textTNourriture == NULL) {
            SDL_Log("Erreur lors de la création de la texture du texte : %s", SDL_GetError());

        } else {
            SDL_Rect textCase1 = {resourceCase1.x + 50, resourceCase1.y + 5, textSNourriture->w, textSNourriture->h};
            SDL_RenderCopy(renderer, textTNourriture, NULL, &textCase1);
            SDL_DestroyTexture(textTNourriture);
        }

        SDL_FreeSurface(textSNourriture);
    }
    }

    SDL_Rect resourceCase2 = {170, 10, 100, 30};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &resourceCase2);

    SDL_Rect iconeCase2 = {280, 10, 30, 30};
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 0.50);
    SDL_RenderFillRect(renderer, &iconeCase2);

    SDL_Texture* textureWater = IMG_LoadTexture(renderer, "../assets/images/water.png");
    if (textureWater == NULL) {

        SDL_Log("Erreur lors du chargement de l'image : %s", IMG_GetError());

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    } else {

        SDL_RenderCopy(renderer, textureWater, NULL, &iconeCase2);

        SDL_DestroyTexture(textureWater);
    }

    if (font == NULL) {
        SDL_Log("Erreur lors du chargement de la police : %s", TTF_GetError());
    } else {
        char *textQWater = "16";
        SDL_Surface *textSWater = TTF_RenderText_Solid(font, textQWater, textColor);

        if (textSWater == NULL) {
            SDL_Log("Erreur lors du rendu du texte : %s", TTF_GetError());

        } else {
            SDL_Texture * textTWater = SDL_CreateTextureFromSurface(renderer, textSWater);


            if (textTWater == NULL) {
                SDL_Log("Erreur lors de la création de la texture du texte : %s", SDL_GetError());

            } else {
                SDL_Rect textCase2 = {resourceCase2.x + 50, resourceCase2.y + 5, textSWater->w, textSWater->h};
                SDL_RenderCopy(renderer, textTWater ,NULL, &textCase2);
                SDL_DestroyTexture(textTWater);
            }

            SDL_FreeSurface(textSWater);
        }
    }

        SDL_Rect resourceCase3 = {330, 10, 100, 30};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &resourceCase3);

    SDL_Rect iconeCase3 = {440, 10, 30, 30};
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 0.50);
    SDL_RenderFillRect(renderer, &iconeCase3);

    SDL_Texture* textureHeart = IMG_LoadTexture(renderer, "../assets/images/heart.png");
    if (textureHeart == NULL) {
        // Gestion des erreurs lors du chargement de l'image
        SDL_Log("Erreur lors du chargement de l'image : %s", IMG_GetError());

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    } else {

        SDL_RenderCopy(renderer, textureHeart, NULL, &iconeCase3);

        SDL_DestroyTexture(textureHeart);
    }

    if (font == NULL) {
        SDL_Log("Erreur lors du chargement de la police : %s", TTF_GetError());
    } else {
        char *textQHeart = "100";
        SDL_Surface *textSHeart = TTF_RenderText_Solid(font, textQHeart, textColor);

        if (textSHeart == NULL) {
            SDL_Log("Erreur lors du rendu du texte : %s", TTF_GetError());

        } else {
            SDL_Texture * textTHeart = SDL_CreateTextureFromSurface(renderer, textSHeart);


            if (textTHeart == NULL) {
                SDL_Log("Erreur lors de la création de la texture du texte : %s", SDL_GetError());

            } else {
                SDL_Rect textCase3 = {resourceCase3.x + 50, resourceCase3.y + 5, textSHeart->w, textSHeart->h};
                SDL_RenderCopy(renderer, textTHeart ,NULL, &textCase3);
                SDL_DestroyTexture(textTHeart);
            }

            SDL_FreeSurface(textSHeart);
        }
    }
        TTF_CloseFont(font);
}
