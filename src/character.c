// character.c

#include "character.h"
#include <stdio.h>
#include <string.h>

Character player;
Character CreateCharacter(const char* name) {
    Character character;
    strncpy(character.name, name, sizeof(character.name));
    character.health = 100;
    character.hunger = 0;
    character.tasks_completed = 0;
    return character;
}

void AssignTask(Character* character, const char* task) {
    printf("%s is assigned to %s.\n", character->name, task);
}

void IncreaseHunger(Character* character) {
    character->hunger += 10;
}

void CompleteTask(Character* character) {
    character->tasks_completed++;
}

void PrintCharacterInfo(const Character* character) {
    printf("Name: %s\n", character->name);
    printf("Health: %d\n", character->health);
    printf("Hunger: %d\n", character->hunger);
    printf("Tasks Completed: %d\n", character->tasks_completed);
}
void InitializeCharacters() {
    strcpy(player.name, "Player");
    player.health = 100;
    player.hunger = 0;
    // Initialiser ici d'autres personnages si nécessaire
}

void UpdateCharacters() {
    player.hunger++; // Augmente la faim du joueur
    if (player.hunger > 10) {
        player.health--; // Diminue la santé si la faim est élevée
    }
    // Mettre à jour d'autres personnages ici
}