#include "../include/survivor.h"
#include "../include/database.h"
#include "../include/Log.h"

void survivor_create_table(sqlite3 *db) {
    const char *sql = "CREATE TABLE IF NOT EXISTS SURVIVOR ("
                      "id_survivor INT PRIMARY KEY, "
                      "name VARCHAR(50) NOT NULL, "
                      "surname VARCHAR(50) NOT NULL, "
                      "heal INT, "
                      "water INT, "
                      "food INT, "
                      "roles INT);";
    char *errMsg = 0;
    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        Log(LOG_ERROR, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        Log(LOG_INFO, "Table SURVIVOR created successfully\n");
    }
}

void survivor_insert(sqlite3 *db, Survivor *survivor) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO SURVIVOR (name, surname, heal, water, food, roles) VALUES (?, ?, ?, ?, ?, ?);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, survivor->name, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, survivor->surname, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 3, survivor->heal);
        sqlite3_bind_int(stmt, 4, survivor->water);
        sqlite3_bind_int(stmt, 5, survivor->food);
        sqlite3_bind_int(stmt, 6, survivor->roles);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    } else {
        Log(LOG_ERROR, "Failed to prepare insert statement. Error: %s", sqlite3_errmsg(db));
    }
}
void UpdateSurvivors() {
    extern Survivor survivors[];
    extern int nombre_de_survivants;

    static Uint32 lastUpdate = 0;
    Uint32 currentTime = SDL_GetTicks();

    // Vérifier si 20 secondes se sont écoulées
    if (currentTime - lastUpdate > 20000) { // 20000 millisecondes = 20 secondes
        for (int i = 0; i < nombre_de_survivants; ++i) {
            // Diminuer l'eau et la nourriture
            survivors[i].water--;
            survivors[i].food--;

            // Vérification des niveaux entre la nourriture et l'eau sont basses
            if (survivors[i].water < 5 || survivors[i].food < 5) {
                // Diminution de la santé de 5%
                survivors[i].heal -= (int)(0.05 * survivors[i].heal);

                // Assurez-vous que la santé ne descend pas en dessous de 0
                if (survivors[i].heal < 0) {
                    survivors[i].heal = 0;
                }
            }

            // D'autres choses a mettre
        }

        lastUpdate = currentTime;
    }
}

void survivor_update(sqlite3 *db, Survivor *survivor, int survivor_id) {
    sqlite3_stmt *stmt;
    const char *sql = "UPDATE SURVIVOR SET name = ?, surname = ?, heal = ?, water = ?, food = ?, roles = ? WHERE id_survivor = ?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, survivor->name, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, survivor->surname, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 3, survivor->heal);
        sqlite3_bind_int(stmt, 4, survivor->water);
        sqlite3_bind_int(stmt, 5, survivor->food);
        sqlite3_bind_int(stmt, 6, survivor->roles);
        sqlite3_bind_int(stmt, 7, survivor_id);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    } else {
        Log(LOG_ERROR, "Failed to prepare update statement. Error: %s", sqlite3_errmsg(db));
    }
}

void survivor_delete(sqlite3 *db, int survivor_id) {
    sqlite3_stmt *stmt;
    const char *sql = "DELETE FROM SURVIVOR WHERE id_survivor = ?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, survivor_id);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    } else {
        Log(LOG_ERROR, "Failed to prepare delete statement. Error: %s", sqlite3_errmsg(db));
    }
}
