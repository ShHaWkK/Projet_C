/**********************************************************************/
/* File : save.h                                                      */
/* Date : 19/01/2024                                                  */
/* author : ShHaWkK                                                   */
/**********************************************************************/

#ifndef SAVE_H
#define SAVE_H

#include "include.h"

// Sauvegarde l'état du jeu
void saveGame(sqlite3 *db);

// Charge l'état du jeu
void loadGame(sqlite3 *db);

// Déclaration de la fonction qui exécute une requête SQL et sauvegarde les résultats dans un fichier.
void queryToFile(sqlite3 *db, const char *query, const char *filename);

// Fonction lit des données à partir d'un fichier et les insère dans la base de données.
void fileToQuery(sqlite3 *db, const char *filename, const char *table);

#endif // SAVE_H
