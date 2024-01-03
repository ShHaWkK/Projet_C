// character.h
#ifndef CHARACTER_H
#define CHARACTER_H

#include "include.h"

//--------  --------//
typedef struct {
    int id;
    char name[50];
    int health;
    int hunger;
    int tasks_completed;
    int morale;
} Character;

//--------  --------//
int character_create_table(sqlite3 *db);
int character_insert(sqlite3 *db, Character *character);
int character_update(sqlite3 *db, Character *character);
int character_delete(sqlite3 *db, int character_id);

//-------- Prototypes des fonctions pour la gestion des personnages --------//

Character CreateCharacter(const char* name);
void AssignTask(Character* character, const char* task);
void IncreaseHunger(Character* character);
void CompleteTask(Character* character);
void PrintCharacterInfo(const Character* character);
void InitializeCharacters();
void UpdateCharacters();

//--------  --------//
extern Character player;

#endif // CHARACTER_H
