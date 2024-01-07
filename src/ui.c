#include "../include/ui.h"
#include "../include/include.h"
#include "../include/game.h"
#include "../include/Log.h"
#include "../include/audio.h"
#include "../include/text_input.h"
#include "../include/trailer.h"

// ------------ Declaration ------------ //

char playerName[256] = "";
char playerSurname[256] = "";
int isNameSelected = 0;
int isSurnameSelected = 0;
int nameCursorPosition = 0;
int surnameCursorPosition = 0;
static Trailer trailer;

// ------------ SDL_react ------------ //

SDL_Rect nameInputRect = {100, 100, 200, 30};
SDL_Rect surnameInputRect = {100, 150, 200, 30};
SDL_Rect submitButtonRect = {100, 250, 200, 50};
Button submitButton;

// ------------ CreateButtonTexture ------------ //

static SDL_Texture* CreateButtonTexture(TTF_Font* font, const char* text, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(uiRenderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

// ------------ QuitGame ------------ //
static void QuitGame(int* running) {
    Log(LOG_INFO, "Quit game initiated.");
    Audio_PlayClickSound();
    *running = 0;
}

// ------------ OpenSettings ------------ //
static void OpenSettings(int* running) {
    Mix_PlayChannel(-1, buttonClickSound, 0);  // Play sound effect
    printf("Opening settings...\n");
    // settings
}
// ------------ UI_Init ------------ //
void RenderTextLabel(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, SDL_Rect rect) {
    // Render the label text
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, textTexture, NULL, &rect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

// ------------ UI_Init ------------ //
void UI_Init(SDL_Renderer* renderer, TTF_Font* font, int windowWidth, int windowHeight, Mix_Chunk* soundEffect) {
    uiRenderer = renderer;
    submitButton.isClickable = 1;
    buttonClickSound = soundEffect;  //  click sound effect
    SDL_Texture* submitButtonTexture;
    SDL_Texture* submitButtonHoverTexture;

    submitButton.rect.x = windowWidth / 2 - BUTTON_WIDTH / 2; // Centré horizontalement
    submitButton.rect.y = windowHeight - MARGIN - BUTTON_HEIGHT; // Positionné en bas avec une marge
    submitButton.rect.w = BUTTON_WIDTH;
    submitButton.rect.h = BUTTON_HEIGHT;

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

    submitButton.texture = CreateButtonTexture(font, "Valider", (SDL_Color){255, 255, 255});
    submitButton.hoverTexture = CreateButtonTexture(font, "Valider", (SDL_Color){255, 0, 0});
    submitButton.rect = submitButtonRect;
}

// ------------ UI_HandleEvent ------------ //

void UI_HandleEvent(SDL_Event* e, int* running) {
    // Handle events for the buttons
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    submitButton.isHovered = SDL_PointInRect(&((SDL_Point){mouseX, mouseY}), &submitButton.rect);

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
            }else if (backButton.isHovered && backButton.onClick) {
                backButton.onClick(running);
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

    if (submitButton.isHovered && e->type == SDL_MOUSEBUTTONDOWN) {
        if (submitButton.isClickable) {
            Log(LOG_INFO, "Submit button clicked.\n");
            SubmitForm(running);
            submitButton.isClickable = 0; // Empêcher les clics supplémentaires
            Trailer_Init(&trailer);
            trailer.isActive = 1;
            submitButton.isClickable = 0;
        }
        if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &submitButton.rect) && submitButton.isClickable) {
            // Bouton soumettre cliqué et est cliquable
            Log(LOG_INFO, "Submit button clicked SDL_PointInRect.\n");
            SubmitForm(running); // Traitez la soumission du formulaire
            Trailer_Init(&trailer); // Initialisez le trailer
            trailer.isActive = 1; // Activez le trailer
            ChangeGameState(GAME_STATE_TRAILER); // Changez l'état du jeu pour afficher le trailer
            submitButton.isClickable = 0; // Désactivez le bouton pour empêcher des clics supplémentaires
        }
    }
}


// ------------Affiche l'interface utilisateur. ------------

void UI_Render(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Texture* currentTexture;

    // Render the buttons only if in the MENU state
    if (currentGameState == MENU) {
        // Start Button
        currentTexture = startButton.isHovered ? startButton.hoverTexture : startButton.texture;
        SDL_RenderCopy(renderer, currentTexture, NULL, &startButton.rect);

        // Quit Button
        currentTexture = quitButton.isHovered ? quitButton.hoverTexture : quitButton.texture;
        SDL_RenderCopy(renderer, currentTexture, NULL, &quitButton.rect);

        // Settings Button
        currentTexture = settingsButton.isHovered ? settingsButton.hoverTexture : settingsButton.texture;
        SDL_RenderCopy(renderer, currentTexture, NULL, &settingsButton.rect);

    }

    // Render the back button only if in a state other than MENU
    if (currentGameState != MENU) {
        SDL_Texture* backTexture = backButton.isHovered ? backButton.hoverTexture : backButton.texture;
        SDL_RenderCopy(renderer, backTexture, NULL, &backButton.rect);
    }

}



// ------------Screen create users (personnage) ------------

void RenderCharacterCreationUI(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Rect nameLabelRect = {MARGIN, MARGIN, LABEL_WIDTH, LABEL_HEIGHT};
    SDL_Rect surnameLabelRect = {MARGIN, 2 * MARGIN + INPUT_HEIGHT + SPACING, LABEL_WIDTH, LABEL_HEIGHT};

    // Positionnez les champs de saisie à côté des étiquettes
    nameInputRect.x = MARGIN + LABEL_WIDTH + SPACING;
    nameInputRect.y = MARGIN;
    nameInputRect.w = INPUT_WIDTH;
    nameInputRect.h = INPUT_HEIGHT;

    surnameInputRect.x = MARGIN + LABEL_WIDTH + SPACING;
    surnameInputRect.y = 2 * MARGIN + INPUT_HEIGHT + SPACING;
    surnameInputRect.w = INPUT_WIDTH;
    surnameInputRect.h = INPUT_HEIGHT;

    // Dessinez les étiquettes et les champs de saisie
    RenderTextLabel(renderer, font, "Name :", (SDL_Color){255, 255, 255}, nameLabelRect);
    RenderTextLabel(renderer, font, "Surname :", (SDL_Color){255, 255, 255}, surnameLabelRect);

    // Dessine et affiche les champs de saisie du nom et du prénom
    RenderTextInputField(renderer, font, &nameInputRect, playerName, isNameSelected);
    RenderTextInputField(renderer, font, &surnameInputRect, playerSurname, isSurnameSelected);

    SDL_Texture* buttonTexture = submitButton.isHovered ? submitButton.hoverTexture : submitButton.texture;
    SDL_RenderCopy(renderer, buttonTexture, NULL, &submitButton.rect);

    // Initialisation du bouton de retour
    backButton.rect = (SDL_Rect){10, 10, 50, 30};
    backButton.texture = CreateButtonTexture(font, "<", (SDL_Color){255, 255, 255});
    backButton.hoverTexture = CreateButtonTexture(font, "<", (SDL_Color){255, 0, 0});
    backButton.onClick = GoBack;
}

// ------------ RenderTextInputField ------------ //

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


// ------------ RenderText ------------ //
void RenderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color textColor, SDL_Rect* rect) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

}

// ------------ GoBack ------------ //

void GoBack(int* running) {
    ChangeGameState(previousGameState);
}

// ------------ SubmitForm ------------ //

void SubmitForm(int* running) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc = sqlite3_open("../survivor_colony.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char *sql = "INSERT INTO characters (name, surname) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, playerName, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, playerSurname, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    } else {
        fprintf(stdout, "Character saved successfully\n");
        submitButton.isClickable = 0;

        // Changement d'état vers le trailer après l'enregistrement réussi
        ChangeGameState(GAME_STATE_TRAILER);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

// ------------ UI_Shutdown ------------ //

void UI_Shutdown() {
    // Free button textures and any other UI resources here
    SDL_DestroyTexture(startButton.texture);
    SDL_DestroyTexture(startButton.hoverTexture);
    SDL_DestroyTexture(quitButton.texture);
    SDL_DestroyTexture(quitButton.hoverTexture);
    SDL_DestroyTexture(settingsButton.texture);
    SDL_DestroyTexture(settingsButton.hoverTexture);
    SDL_DestroyTexture(submitButton.texture);
    SDL_DestroyTexture(submitButton.hoverTexture);
}