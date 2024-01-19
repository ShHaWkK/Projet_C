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
    size_t len = 1024; // Taille initiale du buffer
    line = malloc(len * sizeof(char));

    char *err_msg = 0;
    sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, &err_msg);

    char query[1024];
    while (fgets(line, len, f) != NULL) {
        while (strlen(line) == len - 1 && line[len - 2] != '\n') {
            len *= 2;
            line = realloc(line, len);
            fgets(line + strlen(line), len - strlen(line), f);
        }

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
    queryToFile(db, "SELECT * FROM SURVIVOR;", "../savePlayer/survivor_backup.txt");
    queryToFile(db, "SELECT * FROM RESOURCES;", "../savePlayer/resources_backup.txt");
    queryToFile(db, "SELECT * FROM STORAGE;", "../savePlayer/storage_backup.txt");
    queryToFile(db, "SELECT * FROM USE;", "../savePlayer/use_backup.txt");
    queryToFile(db, "SELECT * FROM EQUIPMENT;", "../savePlayer/equipment_backup.txt");

}

void loadGame(sqlite3 *db) {
    fileToQuery(db, "../savePlayer/survivor_backup.txt", "SURVIVOR");
    fileToQuery(db, "../savePlayer/resources_backup.txt", "RESOURCES");
    queryToFile(db, "../savePlayer/storage_backup.txt", "STORAGE");
    queryToFile(db, "../savePlayer/use_backup.txt", "USE");
    queryToFile(db, "../savePlayer/equipment_backup.txt", "Equipment");
}
