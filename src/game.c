/**********************************************************************/
/* File : game.c                                                      */
/* Date : 10/01/2024                                                  */
/* author : ShHaWkK                                                   */
/**********************************************************************/


//-------------include----------

#include "../include/include.h"
#include "../include/game.h"
#include "../include/ui.h"
#include "../include/character.h"
#include "../include/Log.h"
#include "../include/config.h"
#include "../include/database.h"
#include "../include/audio.h"
#include "../include/text_input.h"
#include "../include/trailer.h"
#include "../include/logo.h"
#include "../include/map.h"


//-------------------------------

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;
static Mix_Music* bgMusic = NULL;
GameState currentGameState = MENU;
GameState previousGameState = MENU;
static Mix_Chunk* soundEffect = NULL;
ActiveInputField currentInputField = INPUT_FIELD_NONE;
static Trailer trailer;

//-------------- Prototype des fonctions ----------
void InitializeGameWorld();
void InitializeCharacters();
void UpdateGameWorld();
void UpdateCharacters();
static void RenderGameUI(SDL_Renderer* renderer);

GameWorld gameWorld;

void GameState_Menu_Update();
void GameState_Menu_Render(SDL_Renderer* renderer);
void GameState_GameRunning_Update();
void GameState_GameRunning_Render(SDL_Renderer* renderer);
void GameState_CharacterCreation_Update();
void GameState_CharacterCreation_Render(SDL_Renderer* renderer);
//----------------------------------------------------------------
extern int nameCursorPosition;
extern int surnameCursorPosition;


//--------------------Function StartNewSession ---------------------//

void StartNewSession(int* running) {
    Log(LOG_INFO, "Démarrage d'une nouvelle session.");
    ChangeGameState(GAME_STATE_CHARACTER_CREATION); // Changer l'état pour créer un personnage
    inputActive = 1;
    SDL_StartTextInput(); // Activer la saisie de texte pour la création du personnage
    Log(LOG_INFO, "SDL_StartTextInput appelé.");
}


//--------------------Function ChangeGameState ---------------------//

void ChangeGameState(GameState newState)
{
    Log(LOG_INFO, "Changement d'état de %d à %d", currentGameState, newState);
    previousGameState = currentGameState;
    currentGameState = newState;

    Log(LOG_INFO, "État actuel du jeu: %d", currentGameState);

    if (previousGameState == GAME_STATE_CHARACTER_CREATION && currentGameState != GAME_STATE_CHARACTER_CREATION)
    {
        inputActive = 0;
        SDL_StopTextInput();
        Log(LOG_INFO, "SDL_StopTextInput appelé.");
    }

    if (currentGameState != MENU) {
        Log(LOG_INFO, "L'état du jeu n'est plus MENU. Le bouton '<' devrait être affiché.");
    }
}

//--------------------Function SomeActionThatChangesState ---------------------//


void SomeActionThatChangesState() {
    // L'utilisateur a fait quelque chose pour changer l'état, comme cliquer sur un bouton
    ChangeGameState(GAME_STATE_TRAILER); // Changez l'état pour afficher la bande-annonce
}


//--------------------Function InitializeNewGameSession ---------------------//

void InitializeNewGameSession()
{
    //initialiser une nouvelle session de jeu
}

//--------------------Function InitializeGameWorld ---------------------//

void InitializeGameWorld()
{
    gameWorld.day = 1; // Commence au jour 1
}

/*
void UpdateGameWorld() {
    // Mettre à jour le monde du jeu
    // Par exemple, gérer les cycles
}
*/
//--------------------Function Game_HandleCharacterNameInput ---------------------//

void Game_HandleCharacterNameInput(const char* name) {
    Character player = CreateCharacter(name); // Create a new character with the entered name
    // Additional logic to set up the player character
    ChangeGameState(GAME_RUNNING); // Change the game state to running
}

//--------------------Function RenderGameUI ---------------------//

void RenderGameUI(SDL_Renderer* renderer) {
    Log(LOG_INFO, "Rendu de l'interface de jeu.");
    // Implémenter le rendu de l'interface de jeu ici
    // Afficher les personnages, les ressources, le monde...
}

//-------------------- Function Game_Init ----------------------//

void Game_Init() {
    Log_Init("game.log");

    Log(LOG_INFO, "Initialisation du jeu...");

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        Log(LOG_ERROR, "SDL could not initialize!");
        exit(1);
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        Log(LOG_ERROR, "Unable to initialize SDL_image: %s\n", IMG_GetError());
        exit(1);

    }


    window = SDL_CreateWindow("Survivor's Colony", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        Log(LOG_ERROR, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    if (TTF_Init() == -1) {
        Log(LOG_ERROR, "TTF_Init: %s\n", TTF_GetError());
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        Log(LOG_ERROR, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }

    font = TTF_OpenFont("fonts/Roboto-Black.ttf", 28);
    if (!font) {
        Log(LOG_ERROR, "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        exit(1);
    }

    Audio_Init("assets/sounds/Helldivers.mp3", "assets/sounds/click.wav");
    Audio_PlayMusic();

    int windowWidth = 800;
    int windowHeight = 600;

    UI_Init(renderer, font, windowWidth, windowHeight, soundEffect);

    Log(LOG_INFO, "Jeu initialisé avec succès.");
    Character player = CreateCharacter("Player 1");
    AssignTask(&player, "Collect Wood");
    IncreaseHunger(&player);
    CompleteTask(&player);

    currentGameState = MENU;
    SetWindowIcon(window, "../assets/images/Survivor's_Colony.png");

    // Initialisation de la carte et du joueur

    // Load the textures for the game map
    initGameMap(&gameWorld.map, renderer, NULL);
    gameWorld.map.mountainTexture = IMG_LoadTexture(renderer, "../assets/images/mountain.png"); // Load mountain texture
    if (gameWorld.map.mountainTexture == NULL) {
        Log(LOG_ERROR, "Failed to load mountain texture: %s", IMG_GetError());
    }

    // Load the base texture for the underground area
    loadBaseTexture(renderer, &gameWorld.map);

    //initMap(renderer);
   initPlayer(renderer);


}

//--------------------Function Game_Run ---------------------//

void Game_Run() {
    int running = 1;
    SDL_Event event;

    int windowWidth = 800;
    int windowHeight = 600;
    Trailer_Init(&trailer);
    trailer.isActive = 1;

    Uint32 lastTime = SDL_GetTicks();

    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        Uint32 deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        while (SDL_PollEvent(&event)) {
            Log(LOG_INFO, "Événement détecté: Type %d", event.type);
            if (event.type == SDL_QUIT) {
                running = 0;
            }

            // Gestion des événements clavier pour les champs de saisie
            switch (event.type) {
                case SDL_QUIT:
                    Log(LOG_INFO, "Événement SDL_QUIT détecté.");
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    Log(LOG_INFO, "Événement SDL_KEYDOWN détecté.");
                    if (isNameSelected) {
                        handleKeyboardEvent(&event, playerName, &nameCursorPosition);
                    } else if (isSurnameSelected) {
                        handleKeyboardEvent(&event, playerSurname, &surnameCursorPosition);
                    }
                    break;
                default:
                    UI_HandleEvent(&event, &running);
                    break;
            }
        }

        // Gestion du trailer en dehors de la boucle des événements
        if (currentGameState == GAME_STATE_TRAILER) {
            Trailer_Update(&trailer, deltaTime); // Notez que nous passons deltaTime maintenant
            if (!trailer.isActive) {
                // Le trailer est terminé, passer à l'état suivant
                ChangeGameState(GAME_RUNNING);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        switch (currentGameState) {
            case MENU:
                UI_Render(renderer, font);
                break;
            case GAME_RUNNING:
                UpdateCharacters();
                RenderGameUI(renderer);
                renderGameMap(&gameWorld.map, renderer);

               // renderPlayer(renderer);
                break;
            case GAME_STATE_CHARACTER_CREATION:
                RenderCharacterCreationUI(renderer, font);
                break;
            case GAME_STATE_TRAILER:
                if (trailer.isActive) {
                    Trailer_Render(renderer, font, &trailer, windowWidth, windowHeight);
                }
                break;
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Régulation à environ 60 FPS
    }
}

// -----------------Function ------------------ //


//--------------------Function Game_Shutdown ---------------------//

void Game_Shutdown() {
    UI_Shutdown();

    if (bgMusic != NULL) {
        Mix_FreeMusic(bgMusic);
    }

    Mix_CloseAudio();
    TTF_CloseFont(font);
    //freeMapTextures();
    //freePlayerTexture();
    //freeGameMap(&gameWorld.map);
    if (mountainTexture != NULL) {
        SDL_DestroyTexture(mountainTexture);
        mountainTexture = NULL;
    }
    freeGameMapResources();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    Log_Close();

    Log(LOG_INFO, "Jeu fermé.");
}
