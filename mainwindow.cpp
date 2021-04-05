#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include <QSqlQuery>
#include <QDebug>
#include <QDir>
#include <QTimer>
#include <QSound>
#include <downloadmanager.h>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

QString mediadir = "./Resource/";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap oPixmap(32,32);
    oPixmap.load ( mediadir + "meatTracker.png");

    QIcon oIcon( oPixmap );

    trayIcon = new QSystemTrayIcon(oIcon);

    QAction *quit_action = new QAction( "Exit", trayIcon );
    connect( quit_action, SIGNAL(triggered()), this, SLOT(on_exit()) );

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction( quit_action );

    trayIcon->setContextMenu( trayIconMenu);
    trayIcon->setVisible(true);

    createNewsTable();
    //trayIcon->showMessage("Test Message", "Text", QSystemTrayIcon::Information, 1000);
    //trayIcon->show();


//    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

 //   ui->timeCountProgress->setRange(0, int(timerPeriod.toFloat() * 60));
 //   ui->timeCountProgress->setValue(0);

    //QTimer *timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(updateCheck()));
    //timer->start(int(timerPeriod.toFloat() * 60) * 1000); // int(timerPeriod) * 60 * 1000

//    QTimer *timerClock = new QTimer(this);
 //   connect(timerClock,SIGNAL(timeout()), this, SLOT(showTime()));
 //   timerClock->start(1000);


    //Apply style
    QFile stylesheet("./Resource/themes/qdarkstyle/qdarkstyle.qss");
    stylesheet.open(QFile::ReadOnly);
    this->setStyleSheet(stylesheet.readAll());
    stylesheet.close();

    ui->tbl_story->verticalHeader()->setVisible(false);
    ui->txt_storyidea->setReadOnly(true);
    ui->tbl_story->setColumnWidth(0, 150);
    ui->tbl_story->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    initStoryTable();

    ui->tbl_pic->setRowCount(0);
    ui->tbl_pic->verticalHeader()->setVisible(false);
    ui->tbl_pic->setColumnWidth(0, 40);
    ui->tbl_pic->setColumnHidden(2, true);
    ui->tbl_pic->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    initPictureTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
     case QSystemTrayIcon::Trigger:
         this->show();
         break;
     case QSystemTrayIcon::DoubleClick:
         this->show();
         break;
     case QSystemTrayIcon::MiddleClick:
      //  showMessage();
        break;

     default:
         ;
    }
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
    QApplication::quit();
}


void MainWindow::on_exit()
{
    this->close();
    QApplication::quit();
}


void MainWindow::SaveSettings(){

        QSettings settings(QDir::currentPath() + "/ftp.ini", QSettings::IniFormat);
      //  ui->lineEditPort->setText(settings.value("settings/port", defaultPort).toString());

}

void MainWindow::loadSettings(){

    QSettings settings(QDir::currentPath() + "/ftp.ini", QSettings::IniFormat);
  //  settings.setValue("settings/port", ui->lineEditPort->text());
}


void MainWindow::createNewsTable(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QApplication::applicationDirPath() + "/news.sqlite");

    if(db.open()){
        qDebug()<<"Successful database connection";
    }else{
        qDebug()<<"Error: failed database connection";
        return;
    }

    QString query;
    query.append("CREATE TABLE IF NOT EXISTS tbl_idea(people TEXT, animal TEXT, datetime TEXT, title TEXT, idea TEXT, vote TEXT, picture TEXT)");
    QSqlQuery create(db);
    create.prepare(query);

    if (create.exec())
    {
        qDebug()<<"Table exists or has been created";
    }
    else
    {
        qDebug()<<"Table not exists or has not been created";
    }
    query.clear();

    QSqlQuery create1(db);
    query.append("CREATE TABLE IF NOT EXISTS tbl_picture(ordernum TEXT, pic_url TEXT, datetime TEXT)");
    create1.prepare(query);

    if (create1.exec())
    {
        qDebug()<<"Picture Table exists or has been created";
    }
    else
    {
        qDebug()<<"Picture Table not exists or has not been created";
    }
    query.clear();
}

void MainWindow::on_save_clicked()
{
    QString strQuery = "INSERT INTO tbl_idea(people, animal, datetime, title, idea) VALUES('";
            strQuery += ui->txt_people->text() + "','";
            strQuery += ui->txt_animal->text() + "','";
            strQuery += QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + "','";
            strQuery += ui->txt_title->text() + "','";
            strQuery += ui->txt_idea->toPlainText() + "')";

    qDebug()<<strQuery;

    QSqlQuery query(db);
    query.exec(strQuery);
    initStoryTable();
}

void MainWindow::initStoryTable()
{
    ui->tbl_story->setRowCount(0);
    QString strQuery = "SELECT * FROM tbl_idea";
    QSqlQuery query(db);
    if(query.exec(strQuery)){
        int row = 0;
        while(query.next()){
            ui->tbl_story->insertRow(row);
            ui->tbl_story->setItem(row, 0, new QTableWidgetItem(query.value(2).toString()));
            ui->tbl_story->setItem(row, 1, new QTableWidgetItem(query.value(3).toString()));
            ui->tbl_story->setItem(row, 2, new QTableWidgetItem(query.value(5).toString()));
            row++;
        }
    }
}

void MainWindow::initPictureTable()
{
    ui->tbl_pic->setRowCount(0);
    QString strQuery = "SELECT * FROM tbl_picture ORDER BY ordernum";
    QSqlQuery query(db);
    if(query.exec(strQuery)){
        int row = 0;
        while(query.next()){
            ui->tbl_pic->insertRow(row);
            ui->tbl_pic->setItem(row, 0, new QTableWidgetItem(QString::number(row + 1)));
            ui->tbl_pic->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->tbl_pic->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
            row++;
        }
    }
}

void MainWindow::on_tbl_story_cellClicked(int row, int column)
{
    QString strQuery = "SELECT * FROM tbl_idea WHERE datetime = '" + ui->tbl_story->item(row, 0)->text() + "'";
    QSqlQuery query(db);
    if(query.exec(strQuery)){
        while(query.next()){
            ui->txt_storyidea->setPlainText(query.value(4).toString());
            ui->txt_people->setText(query.value(0).toString());
            ui->txt_animal->setText(query.value(1).toString());
            ui->txt_title->setText(query.value(3).toString());
            ui->txt_idea->setPlainText(query.value(4).toString());
        }
    }
}

void MainWindow::on_edit_clicked()
{
    QString strQuery = "UPDATE tbl_idea SET people = '" + ui->txt_people->text() + "',";
            strQuery += "animal = '" + ui->txt_animal->text() + "',";
            strQuery += "title = '" + ui->txt_title->text() + "',";
            strQuery += "idea = '" + ui->txt_idea->toPlainText() + "' WHERE datetime = '";
            strQuery += ui->tbl_story->item(ui->tbl_story->currentRow(), 0)->text() + "'";
    QSqlQuery query(db);
    query.exec(strQuery);
    initStoryTable();
    ui->txt_storyidea->setPlainText(ui->txt_idea->toPlainText());
}

void MainWindow::on_pictureUpload_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    QApplication::applicationDirPath(),
                                                    tr("Sounds (*.jpg *.png *.bmp)"));
    QPixmap pixmap(fileName);
    ui->lbl_pic->setPixmap(pixmap.scaled(ui->lbl_pic->width(), ui->lbl_pic->height(), Qt::KeepAspectRatio));

    int rowCount = 0;
    QSqlQuery selectQuery(db);
    if(selectQuery.exec("SELECT * FROM tbl_picture"))
    {
        while(selectQuery.next())
        {
            rowCount++;
        }
    }

    int maxOrderVal = 0;
    if(rowCount > 0)
    {
        QString strMaxQuery = "SELECT MAX(ordernum) FROM tbl_picture";
        QSqlQuery maxQuery(db);
        if(maxQuery.exec(strMaxQuery))
        {
            while(maxQuery.next())
            {
                maxOrderVal = maxQuery.value(0).toInt();
            }
        }
    }

    QString strQuery = "INSERT INTO tbl_picture(ordernum, pic_url, datetime) VALUES('";
            strQuery += QString::number(maxOrderVal + 1) + "','";
            strQuery += fileName + "','";
            strQuery += QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + "')";

    qDebug()<<strQuery;

    QSqlQuery insertQuery(db);
    insertQuery.exec(strQuery);

    initPictureTable();
}

void MainWindow::on_tbl_pic_itemSelectionChanged()
{
    QString fileName = ui->tbl_pic->item(ui->tbl_pic->currentRow(), 1)->text();
    QPixmap pixmap(fileName);
    ui->lbl_pic->setPixmap(pixmap.scaled(ui->lbl_pic->width(), ui->lbl_pic->height(), Qt::KeepAspectRatio));
}

void MainWindow::on_pictureVoteUp_clicked()
{
    if(ui->tbl_pic->currentRow() == 0)
        return;

    QString strQuery2 = "UPDATE tbl_picture SET ordernum = '";
            strQuery2 += QString::number(ui->tbl_pic->item(ui->tbl_pic->currentRow(), 0)->text().toInt()-1) + "' ";
            strQuery2 += "WHERE ordernum = '" + QString::number(ui->tbl_pic->item(ui->tbl_pic->currentRow(), 0)->text().toInt()-2) + "'";
    QSqlQuery query2(db);
    query2.exec(strQuery2);

    QString strQuery1 = "UPDATE tbl_picture SET ordernum = '";
            strQuery1 += QString::number(ui->tbl_pic->item(ui->tbl_pic->currentRow(), 0)->text().toInt()-2) + "' ";
            strQuery1 += "WHERE datetime = '" + ui->tbl_pic->item(ui->tbl_pic->currentRow(), 2)->text() + "'";
    QSqlQuery query1(db);
    query1.exec(strQuery1);

    QString curl = ui->tbl_pic->item(ui->tbl_pic->currentRow(),1)->text();
    ui->tbl_pic->item(ui->tbl_pic->currentRow(),1)->setText(ui->tbl_pic->item(ui->tbl_pic->currentRow()-1,1)->text());
    ui->tbl_pic->item(ui->tbl_pic->currentRow()-1,1)->setText(curl);
}

void MainWindow::on_pictureVoteDown_clicked()
{
    if(ui->tbl_pic->currentRow() == ui->tbl_pic->rowCount() - 1)
        return;

    QString strQuery2 = "UPDATE tbl_picture SET ordernum = '";
            strQuery2 += QString::number(ui->tbl_pic->item(ui->tbl_pic->currentRow(), 0)->text().toInt()-1) + "' ";
            strQuery2 += "WHERE ordernum = '" + QString::number(ui->tbl_pic->item(ui->tbl_pic->currentRow(), 0)->text().toInt()) + "'";
    QSqlQuery query2(db);
    query2.exec(strQuery2);

    QString strQuery1 = "UPDATE tbl_picture SET ordernum = '";
            strQuery1 += QString::number(ui->tbl_pic->item(ui->tbl_pic->currentRow(), 0)->text().toInt()) + "' ";
            strQuery1 += "WHERE datetime = '" + ui->tbl_pic->item(ui->tbl_pic->currentRow(), 2)->text() + "'";
    QSqlQuery query1(db);
    query1.exec(strQuery1);

    QString curl = ui->tbl_pic->item(ui->tbl_pic->currentRow(),1)->text();
    ui->tbl_pic->item(ui->tbl_pic->currentRow(),1)->setText(ui->tbl_pic->item(ui->tbl_pic->currentRow()+1,1)->text());
    ui->tbl_pic->item(ui->tbl_pic->currentRow()+1,1)->setText(curl);
}
