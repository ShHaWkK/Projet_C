#include "../include/save.h"

void queryToFile(sqlite3 *db, const char *query, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier %s\n", filename);
        return;
    }

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Erreur de préparation de la requête: %s\n", sqlite3_errmsg(db));
        fclose(f);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int col_count = sqlite3_column_count(stmt);
        for (int i = 0; i < col_count; i++) {
            const char *val = (const char*)sqlite3_column_text(stmt, i);
            fprintf(f, "%s;", val ? val : "NULL");
        }
        fprintf(f, "\n");
    }

    sqlite3_finalize(stmt);
    fclose(f);
}


void fileToQuery(sqlite3 *db, const char *filename, const char *table) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier %s\n", filename);
        return;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    char *err_msg = 0;
    sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, &err_msg);

    char query[1024];
    while ((read = getline(&line, &len, f)) != -1) {
        snprintf(query, sizeof(query), "INSERT INTO %s VALUES (%s);", table, line);
        if (sqlite3_exec(db, query, NULL, NULL, &err_msg) != SQLITE_OK) {
            fprintf(stderr, "Erreur SQL: %s\n", err_msg);
            sqlite3_free(err_msg);
            break;
        }
    }

    sqlite3_exec(db, "END TRANSACTION;", NULL, NULL, &err_msg);

    free(line);
    fclose(f);
}

void saveGame(sqlite3 *db) {
    queryToFile(db, "SELECT * FROM SURVIVOR;", "../save/survivor_backup.txt");
    queryToFile(db, "SELECT * FROM RESOURCES;", "../save/resources_backup.txt");
    queryToFile(db, "SELECT * FROM STORAGE;", "../save/storage_backup.txt");
    queryToFile(db, "SELECT * FROM USE;", "../save/use_backup.txt");
    queryToFile(db, "SELECT * FROM EQUIPMENT;", "../save/equipment_backup.txt");

}

void loadGame(sqlite3 *db) {
    fileToQuery(db, "../save/survivor_backup.txt", "SURVIVOR");
    fileToQuery(db, "../save/resources_backup.txt", "RESOURCES");
    queryToFile(db, "../save/storage_backup.txt", "STORAGE");
    queryToFile(db, "../save/use_backup.txt", "USE");
    queryToFile(db, "../save/equipment_backup.txt", "Equipment");
}
