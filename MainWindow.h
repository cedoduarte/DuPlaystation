#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class QTableWidgetItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_actionQuit_triggered();
    void on_actionAbout_triggered();
private:
    void readDatabase();
    void connectObjects();

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
