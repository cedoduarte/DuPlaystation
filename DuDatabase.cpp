#include "DuDatabase.h"
#include "DuDefines.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>

namespace DuarteCorp
{
#if defined(DU_DEBUG)
void removeDatabase()
{
    QFileInfo finfo(DB_FILENAME);
    QDir dbFilePath(finfo.absolutePath());
    if (dbFilePath.remove(finfo.fileName())) {
        qDebug() << "Database file removed!";
    } else {
        qDebug() << "Database file NOT removed!";
    }
}

void showDatabase()
{
    QSqlQuery qry;
    qry.exec("SELECT * FROM game");
    while (qry.next()) {
        qDebug() << qry.value("id").toInt()
                 << "," << qry.value("filename").toString()
                 << "," << qry.value("title").toString()
                 << "," << qry.value("type").toString();
    }
}
#endif

void configureDatabase()
{
    QSqlQuery qry;
    qry.exec(DB_TABLE_GAME);
}

void checkData()
{
    QSqlQuery qry;
    QList<int> ids;
    qry.exec("SELECT id,filename,type FROM game");
    while (qry.next()) {
        int type = qry.value("type").toInt();
        QString gamePath;
        if (type == PSX) {
            gamePath = PSX_GAMES_PATH;
        } else {
            gamePath = PSX2_GAMES_PATH;
        }
        QFileInfo finfo(gamePath + "/" + qry.value("filename").toString());
        if (!finfo.exists()) {
            ids.append(qry.value("id").toInt());
        }
    }
    for (int id : ids) {
        qry.exec(QString("DELETE FROM game WHERE id = %1").arg(id));
    }
}

void insertData(const QString &path, int type)
{
    QSqlQuery qry;
    QDir dir(path);
    for (unsigned i = 2; i < dir.count(); ++i) {
        auto filename = dir[i];
        qry.exec(QString("INSERT INTO game (filename,title,type)"
                         "VALUES ('%1','%2',%3)")
                 .arg(filename).arg(filename.mid(0, filename.indexOf('.')))
                 .arg(type));
    }
}

bool openDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DB_FILENAME);
    if (!db.open()) {
        // error
        qDebug() << db.lastError().text();
        return false;
    }
    configureDatabase();
    checkData();
    insertData(PSX_GAMES_PATH, PSX);
    insertData(PSX2_GAMES_PATH, PSX2);
    return true;
}
} // end namespace DuarteCorp
