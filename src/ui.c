#include "../include/ui.h"
#include "../include/include.h"
#include "../include/game.h"
#include "../include/Log.h"
#include "../include/audio.h"
#include "../include/text_input.h"

char playerName[256] = "";
char playerSurname[256] = "";
int isNameSelected = 0;
int isSurnameSelected = 0;
SDL_Rect nameInputRect = {100, 100, 200, 30};
SDL_Rect surnameInputRect = {100, 150, 200, 30};

int nameCursorPosition = 0;
int surnameCursorPosition = 0;

/****************************************************************************/
static SDL_Texture* CreateButtonTexture(TTF_Font* font, const char* text, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(uiRenderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

static void QuitGame(int* running) {
    Log(LOG_INFO, "Quit game initiated.");
    Audio_PlayClickSound();
    *running = 0;
}

static void OpenSettings(int* running) {
    Mix_PlayChannel(-1, buttonClickSound, 0);  // Play sound effect
    printf("Opening settings...\n");
    // settings
}

void UI_Init(SDL_Renderer* renderer, TTF_Font* font, int windowWidth, int windowHeight, Mix_Chunk* soundEffect) {
    uiRenderer = renderer;
    buttonClickSound = soundEffect;  //  click sound effect

    // Set up the start button
    startButton.rect = (SDL_Rect){(windowWidth - 200) / 2, windowHeight / 2 - 75, 200, 50};
    startButton.texture = CreateButtonTexture(font, "Start New Session", (SDL_Color){255, 255, 255});
    startButton.hoverTexture = CreateButtonTexture(font, "Start New Session", (SDL_Color){255, 0, 0});
    startButton.onClick = StartNewSession;

    // Set up the quit button
    quitButton.rect = (SDL_Rect){(windowWidth - 200) / 2, windowHeight - 75, 200, 50};
    quitButton.texture = CreateButtonTexture(font, "Quit", (SDL_Color){255, 255, 255});
    quitButton.hoverTexture = CreateButtonTexture(font, "Quit", (SDL_Color){255, 0, 0});
    quitButton.onClick = QuitGame;

    // Set up the settings button
    settingsButton.rect = (SDL_Rect){(windowWidth - 200) / 2, windowHeight / 2, 200, 50};
    settingsButton.texture = CreateButtonTexture(font, "Settings", (SDL_Color){255, 255, 255});
    settingsButton.hoverTexture = CreateButtonTexture(font, "Settings", (SDL_Color){255, 0, 0});
    settingsButton.onClick = OpenSettings;

    //return
    backButton.rect = (SDL_Rect){10, 10, 50, 30}; // Position et taille
    backButton.texture = CreateButtonTexture(font, "<", (SDL_Color){255, 255, 255});
    backButton.hoverTexture = CreateButtonTexture(font, "<", (SDL_Color){255, 0, 0});
    backButton.onClick = GoBack;

}


void UI_HandleEvent(SDL_Event* e, int* running) {
    // Handle events for the buttons
    int mouseX, mouseY;
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN) {
        Log(LOG_INFO, "Back button clicked.");
        SDL_GetMouseState(&mouseX, &mouseY);
        // Debug print
        printf("Mouse Position - X: %d, Y: %d\n", mouseX, mouseY);

        startButton.isHovered = SDL_PointInRect(&((SDL_Point) {mouseX, mouseY}), &startButton.rect);
        quitButton.isHovered = SDL_PointInRect(&((SDL_Point) {mouseX, mouseY}), &quitButton.rect);
        settingsButton.isHovered = SDL_PointInRect(&((SDL_Point) {mouseX, mouseY}), &settingsButton.rect);
        backButton.isHovered = SDL_PointInRect(&((SDL_Point) {mouseX, mouseY}), &backButton.rect);
        if (e->type == SDL_MOUSEBUTTONDOWN && backButton.isHovered && backButton.onClick) {
            backButton.onClick(running);
        }
        if (e->type == SDL_MOUSEBUTTONDOWN) {
            if (startButton.isHovered && startButton.onClick) {
                startButton.onClick(running);
            } else if (quitButton.isHovered && quitButton.onClick) {
                quitButton.onClick(running);
            } else if (settingsButton.isHovered && settingsButton.onClick) {
                settingsButton.onClick(running);
            }

            if (SDL_PointInRect(&(SDL_Point) {mouseX, mouseY}, &nameInputRect)) {
                isNameSelected = 1;
                isSurnameSelected = 0;
                SDL_StartTextInput(); // Active la saisie de texte pour le champ nom
            } else if (SDL_PointInRect(&(SDL_Point) {mouseX, mouseY}, &surnameInputRect)) {
                isNameSelected = 0;
                isSurnameSelected = 1;
                SDL_StartTextInput(); // Active la saisie de texte pour le champ prénom
            } else {
                isNameSelected = 0;
                isSurnameSelected = 0;
                SDL_StopTextInput(); // Désactive la saisie de texte
            }
        }
    }
    if (e->type == SDL_TEXTINPUT) {
        if (isNameSelected) {
            handleTextInputEvent(e, playerName, &nameCursorPosition); // Utilisez la fonction modifiée
        } else if (isSurnameSelected) {
            handleTextInputEvent(e, playerSurname, &surnameCursorPosition); // Utilisez la fonction modifiée
        }
    }
}


/*
 * Affiche l'interface utilisateur.
 */
void UI_Render(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Texture* currentTexture;

    // Render the start, quit, and settings buttons only if in the MENU state
    if (currentGameState == MENU) {
        currentTexture = startButton.isHovered ? startButton.hoverTexture : startButton.texture;
        SDL_RenderCopy(renderer, currentTexture, NULL, &startButton.rect);

        currentTexture = quitButton.isHovered ? quitButton.hoverTexture : quitButton.texture;
        SDL_RenderCopy(renderer, currentTexture, NULL, &quitButton.rect);

        currentTexture = settingsButton.isHovered ? settingsButton.hoverTexture : settingsButton.texture;
        SDL_RenderCopy(renderer, currentTexture, NULL, &settingsButton.rect);
    }

    // Render the back button only if in a game session state (not MENU)
    if (currentGameState != MENU) {
        currentTexture = backButton.isHovered ? backButton.hoverTexture : backButton.texture;
        SDL_RenderCopy(renderer, currentTexture, NULL, &backButton.rect);
    }
}


// ------------Screen create users (personnage) ------------
void RenderCharacterCreationUI(SDL_Renderer* renderer, TTF_Font* font) {
    // Dessine et affiche les champs de saisie du nom et du prénom
    RenderTextInputField(renderer, font, &nameInputRect, playerName, isNameSelected);
    RenderTextInputField(renderer, font, &surnameInputRect, playerSurname, isSurnameSelected);
}
void RenderTextInputField(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect* rect, const char* text, int isSelected) {
    SDL_Color backgroundColor = isSelected ? (SDL_Color){200, 200, 255, 255} : (SDL_Color){255, 255, 255, 255};
    SDL_Color textColor = {0, 0, 0, 255};

    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderFillRect(renderer, rect);
    RenderText(renderer, font, text, textColor, rect);

    if (isSelected) {
        // Ici, vous pourriez ajouter le rendu du curseur clignotant
    }
}

void RenderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color textColor, SDL_Rect* rect) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

}
void GoBack(int* running) {
    ChangeGameState(previousGameState);
}
void UI_Shutdown() {
    // Free button textures and any other UI resources here
    SDL_DestroyTexture(startButton.texture);
    SDL_DestroyTexture(startButton.hoverTexture);
    SDL_DestroyTexture(quitButton.texture);
    SDL_DestroyTexture(quitButton.hoverTexture);
    SDL_DestroyTexture(settingsButton.texture);
    SDL_DestroyTexture(settingsButton.hoverTexture);
}