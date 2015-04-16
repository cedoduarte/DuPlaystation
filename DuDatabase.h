#ifndef DUDATABASE_H
#define DUDATABASE_H

#include <QString>

#define DB_FILENAME "./data/data.db"
#define DB_TABLE_GAME_ID "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL"
#define DB_TABLE_GAME_FILENAME "filename TEXT UNIQUE NOT NULL"
#define DB_TABLE_GAME_TITLE "title TEXT UNIQUE NOT NULL"
#define DB_TABLE_GAME_TYPE "type INT NOT NULL"

#define DB_TABLE_GAME \
    "CREATE TABLE IF NOT EXISTS game (" \
        DB_TABLE_GAME_ID \
    "," DB_TABLE_GAME_FILENAME \
    "," DB_TABLE_GAME_TITLE \
    "," DB_TABLE_GAME_TYPE ")"

namespace DuarteCorp
{
#if defined(DU_DEBUG)
void removeDatabase();
void showDatabase();
#endif

void configureDatabase();
void checkData();
void insertData(const QString &path, int type);
bool openDatabase();
} // end namespace DuarteCorp

#endif // DUDATABASE_H
