/**********************************************************************/
/* File : database.c                                                   */
/* Date : 22/12/2023                                                  */
/* author : ShHaWkK                                                   */
/**********************************************************************/


/*****************************Includes**************************************/
#include "../include/database.h"
#include "../include/include.h"
#include "../include/Log.h"
#include "../include/ui.h"

int db_open(const char *filename, sqlite3 **db) {
    return sqlite3_open(filename, db);
}

int db_close(sqlite3 *db) {
    return sqlite3_close(db);
}

int db_execute(sqlite3 *db, const char *sql) {
    char *errmsg;
    int rc = sqlite3_exec(db, sql, 0, 0, &errmsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errmsg);
    }
    return rc;
}

// Démarre une transaction
int db_begin_transaction(sqlite3* db) {
    Log(LOG_INFO, "Début de la transaction");
    int result = db_execute(db, "BEGIN TRANSACTION;");
    if (result != 0) {
        Log(LOG_ERROR, "Erreur lors du début de la transaction: %s", sqlite3_errmsg(db));
    }
    return result;
}

// Valide une transaction
int db_commit_transaction(sqlite3* db) {
    Log(LOG_INFO, "Validation de la transaction");
    int result = db_execute(db, "COMMIT;");
    if (result != 0) {
        Log(LOG_ERROR, "Erreur lors de la validation de la transaction: %s", sqlite3_errmsg(db));
    }
    return result;
}

// Annule une transaction
int db_rollback_transaction(sqlite3* db) {
    Log(LOG_INFO, "Annulation de la transaction");
    int result = db_execute(db, "ROLLBACK;");
    if (result != 0) {
        Log(LOG_ERROR, "Erreur lors de l'annulation de la transaction: %s", sqlite3_errmsg(db));
    }
    return result;
}
