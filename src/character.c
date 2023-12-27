// character.c

#include "character.h"
#include <stdio.h>
#include <string.h>

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
