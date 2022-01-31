<<<<<<< HEAD
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QSqlDatabase>
#include <QTableWidgetItem>
#include <QMenu>

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

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void createActions();
    void createTrayIcon();
    void setTrayIcon();

private slots:
    void on_actionExit_triggered();
    void on_exit();
    void on_save_clicked();
    void initStoryTable();
    void initPictureTable();
    void on_tbl_story_cellClicked(int row, int column);
    void on_edit_clicked();
    void on_pictureUpload_clicked();
    void on_tbl_pic_itemSelectionChanged();

    void on_pictureVoteUp_clicked();

    void on_pictureVoteDown_clicked();

private:
    QSqlDatabase db;
    Ui::MainWindow *ui;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    QAction *quitAction;
};

#endif // MAINWINDOW_H
=======
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QSqlDatabase>
#include <QTableWidgetItem>

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
    void on_save_clicked();
    void initStoryTable();
    void initPictureTable();
    void on_tbl_story_cellClicked(int row, int column);
    void on_edit_clicked();
    void on_pictureUpload_clicked();
    void on_tbl_pic_itemSelectionChanged();

    void on_pictureVoteUp_clicked();

    void on_pictureVoteDown_clicked();

private:
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QSqlDatabase db;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
>>>>>>> 9ce67c128e8c3ff7d12130f682f8558591c33897
