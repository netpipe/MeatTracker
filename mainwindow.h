#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QSqlDatabase>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


    void createNewsTable();
    void SaveSettings();
    void loadSettings();

    void iconActivated(QSystemTrayIcon::ActivationReason reason);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_exit();
private:
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
        QSqlDatabase db;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
