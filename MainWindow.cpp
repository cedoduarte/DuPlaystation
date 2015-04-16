#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DuPlayButton.h"
#include "DuDefines.h"

#include <QMessageBox>
#include <QPushButton>
#include <QSqlQuery>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    readDatabase();
    connectObjects();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}

void MainWindow::readDatabase()
{
    QSqlQuery qry;
    qry.exec("SELECT filename,title,type FROM game");
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels({ tr("Título"), tr("Jugar") });
    QString largestTitle;
    while (qry.next()) {
        auto filename = qry.value("filename").toString();
        auto title = qry.value("title").toString();
        int type = qry.value("type").toInt();
        int lastRow = ui->tableWidget->rowCount();
        auto btnPlay = new DuPlayButton(filename, type, tr(""), this);
        QString icon;
        if (type == PSX) {
            icon = ":/psx.png";
        } else {
            icon = ":/psx2.png";
        }
        btnPlay->setIcon(QIcon(":/play.png"));
        //btnPlay->setIconSize(QSize(40, 40));
        ui->tableWidget->insertRow(lastRow);
        auto item = new QTableWidgetItem(title);
        item->setIcon(QIcon(icon));
        ui->tableWidget->setItem(lastRow, 0, item);
        ui->tableWidget->setCellWidget(lastRow, 1, btnPlay);

        if (title.size() > largestTitle.size()) {
            largestTitle = title;
        }

        connect(btnPlay, &DuPlayButton::clickedRef, [&](DuPlayButton *btn) {
            QProcess proc;
            QString emu;
            QString filename;
            if (btn->type() == PSX) {
                emu = PSX_EMU;
                filename = QString("%1/%2").arg(PSX_GAMES_PATH)
                        .arg(btn->filename());
            } else {
                emu = PSX2_EMU;
                filename = QString("%1/%2").arg(PSX2_GAMES_PATH)
                        .arg(btn->filename());
            }
            proc.execute(emu, { filename });
        });
    }
    ui->tableWidget->setColumnWidth(0, largestTitle.size() * 7);
}

void MainWindow::connectObjects()
{
    connect(ui->tableWidget, &QTableWidget::itemChanged,
            [&](QTableWidgetItem *item) {
        auto widget = ui->tableWidget->cellWidget(item->row(), 1);
        auto btn = static_cast<DuPlayButton *>(widget);
        QSqlQuery qry;
        qry.exec(QString("SELECT title FROM game WHERE filename LIKE '%1'")
                 .arg(btn->filename()));
        qry.next();
        auto title = qry.value(0).toString();
        if (title != item->text()) {
            qry.exec(QString("UPDATE game SET title = '%1' "
                             "WHERE filename LIKE '%2'")
                     .arg(item->text()).arg(btn->filename()));
        }
    });
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, windowTitle(),
                       tr("Autor: Carlos Enrique Duarte Ortiz\n"
                          "Fecha: 10/04/2015\n"
                          "Organización: DuarteCorporation"));
}
