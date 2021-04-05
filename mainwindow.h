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
