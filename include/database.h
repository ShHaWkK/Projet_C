
/**********************************************************************/
/* File : database.h                                                       */
/* Date : 25/12/2023                                                  */
/* author : ShHaWkK                                                   */
/**********************************************************************/

#ifndef DATABASE_H
#define DATABASE_H

#include "include.h"

int db_open(const char *filename, sqlite3 **db);
int db_close(sqlite3 *db);
int db_execute(sqlite3 *db, const char *sql);
int db_begin_transaction(sqlite3 *db);
int db_commit_transaction(sqlite3 *db);
int db_rollback_transaction(sqlite3 *db);
#endif // DATABASE_H
