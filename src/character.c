/**********************************************************************/
/* File : include.h                                                   */
/* Date : 18/12/2023                                                  */
/* author : ShHaWkK                                                   */
/**********************************************************************/


#include "../include/character.h"
#include "../include/database.h"
#include "../include/Log.h"

// Character player;

Character CreateCharacter(const char* name) {
    Character character;
    strncpy(character.name, name, sizeof(character.name));
    character.health = 100;
    character.hunger = 0;
    character.tasks_completed = 0;
    return character;
}

void AssignTask(Character* character, const char* task) {
    Log(LOG_INFO, "%s is assigned to %s.", character->name, task);
    printf("%s is assigned to %s.\n", character->name, task);
}

void IncreaseHunger(Character* character) {
    Log(LOG_INFO, "Increased hunger for %s.", character->name);
    character->hunger += 10;
}

void CompleteTask(Character* character) {
    Log(LOG_INFO, "%s has completed a task.", character->name);
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


int character_create_table(sqlite3 *db) {
    Log(LOG_INFO, "Creating character table in the database.");
    const char *sql = "CREATE TABLE IF NOT EXISTS SURVIVOR ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "name TEXT NOT NULL, "
                      "health INTEGER, "
                      "hunger INTEGER, "
                      "morale INTEGER);";
    return db_execute(db, sql);
}

int character_insert(sqlite3 *db, Character *character) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO SURVIVORS (name, health, hunger, morale) VALUES (?, ?, ?, ?);";

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, character->name, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, character->health);
        sqlite3_bind_int(stmt, 3, character->hunger);
        sqlite3_bind_int(stmt, 4, character->morale);
        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
    return rc;
}

int character_update(sqlite3 *db, Character *character) {
    sqlite3_stmt *stmt;
    const char *sql = "UPDATE SURVIVOR SET name = ?, health = ?, hunger = ?, morale = ? WHERE id = ?;";

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, character->name, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, character->health);
        sqlite3_bind_int(stmt, 3, character->hunger);
        sqlite3_bind_int(stmt, 4, character->morale);
        sqlite3_bind_int(stmt, 5, character->id);
        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
    return rc;
}

int character_delete(sqlite3 *db, int character_id) {
    sqlite3_stmt *stmt;
    const char *sql = "DELETE FROM SURVIVOR WHERE id = ?;";

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, character_id);
        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
    return rc;
}
