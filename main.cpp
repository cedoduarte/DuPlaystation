#include "DuDatabase.h"
#include "MainWindow.h"
#include "DuApplication.h"
#include <QApplication>

using namespace DuarteCorp;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(APP_NAME);
    a.setApplicationVersion(APP_VER);
    a.setOrganizationDomain(ORG_DOM);
    a.setOrganizationName(ORG_NAME);
    a.setStyle("fusion");
#if defined(DU_DEBUG)
    removeDatabase();
#endif
    openDatabase();
#if defined(DU_DEBUG)
    showDatabase();
#endif
    MainWindow w;
    w.show();
    return a.exec();
}


