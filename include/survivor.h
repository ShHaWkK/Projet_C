#ifndef SURVIVOR_H
#define SURVIVOR_H

#include "include.h"

typedef struct {
    int id;
    char name[50];
    char surname[50];
    int heal;
    int water;
    int food;
    int roles;
} Survivor;
//---------     Extern   ---------//
extern Survivor survivors[100];
extern int nombre_de_survivants;
//---------     Functions    ---------//

void survivor_create_table(sqlite3 *db);
void survivor_insert(sqlite3 *db, Survivor *survivor);
void survivor_update(sqlite3 *db, Survivor *survivor, int survivor_id);
void survivor_delete(sqlite3 *db, int survivor_id);
void UpdateSurvivors();

//-------- Prototypes des fonctions pour la gestion des personnages --------//

#endif // SURVIVOR_H
