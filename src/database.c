// database.c
#include "database.h"
#include "include.h"

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

int db_begin_transaction(sqlite3 *db) {
    return db_execute(db, "BEGIN TRANSACTION;");
}

int db_commit_transaction(sqlite3 *db) {
    return db_execute(db, "COMMIT TRANSACTION;");
}

int db_rollback_transaction(sqlite3 *db) {
    return db_execute(db, "ROLLBACK TRANSACTION;");
}
