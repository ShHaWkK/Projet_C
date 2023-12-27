// character.h
#ifndef CHARACTER_H
#define CHARACTER_H

typedef struct {
    char name[50];
    int health;
    int hunger;
    int tasks_completed;
} Character;

// Prototypes des fonctions pour la gestion des personnages
Character CreateCharacter(const char* name);
void AssignTask(Character* character, const char* task);
void IncreaseHunger(Character* character);
void CompleteTask(Character* character);
void PrintCharacterInfo(const Character* character);
void InitializeCharacters();
void UpdateCharacters();

extern Character player;

#endif // CHARACTER_H
