// character.c

#include "../include/character.h"
#include "../include/database.h"
#include "../include/Log.h"
sqlite3 *db;
int rc;

void openDatabaseConnection() {
    rc = sqlite3_open("survivor_colony.db", &db);
    if (rc) {
        Log(LOG_ERROR, "Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        Log(LOG_INFO, "Opened database successfully\n");
    }
}

void closeDatabaseConnection() {
    sqlite3_close(db);
}
/*
 * Create Character
 */
int character_create_table() {
    const char *sql = "CREATE TABLE IF NOT EXISTS characters ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "name TEXT NOT NULL, "
                      "health INTEGER, "
                      "hunger INTEGER, "
                      "morale INTEGER);";
    char *errMsg = 0;
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        Log(LOG_ERROR, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        Log(LOG_INFO, "Table characters created successfully\n");
    }
    return rc;
}

int character_insert(Character *character) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO characters (name, health, hunger, morale) VALUES (?, ?, ?, ?);";

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, character->name, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, character->health);
        sqlite3_bind_int(stmt, 3, character->hunger);
        sqlite3_bind_int(stmt, 4, character->morale);
        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    } else {
        Log(LOG_ERROR, "Failed to prepare insert statement. Error: %s", sqlite3_errmsg(db));
    }
    return rc;
}

/*
 *  met à jour un personnage existant dans la table characters
 */
int character_update(sqlite3 *db, Character *character, int character_id) {

    sqlite3_stmt *stmt;
    const char *sql = "UPDATE characters SET name = ?, health = ?, hunger = ?, morale = ? WHERE id = ?;";

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, character->name, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, character->health);
        sqlite3_bind_int(stmt, 3, character->hunger);
        sqlite3_bind_int(stmt, 4, character->morale);
        sqlite3_bind_int(stmt, 5, character_id);
        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    } else {
        Log(LOG_ERROR, "Failed to prepare update statement. Error: %s", sqlite3_errmsg(db));
    }
    return rc;
}

/*
 * supprime un personnage de la table characters
 */
int character_delete(int character_id) {
    sqlite3_stmt *stmt;
    const char *sql = "DELETE FROM characters WHERE id = ?;";

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, character_id);
        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    } else {
        Log(LOG_ERROR, "Failed to prepare delete statement. Error: %s", sqlite3_errmsg(db));
    }
    return rc;
}
