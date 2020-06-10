#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>

QString mediadir2 = "./Resource/";
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(mediadir2 + "meatTracker.png"));
    a.setQuitOnLastWindowClosed(false);

    QPixmap m(mediadir2 + "meatTracker.png");


MainWindow w;

QSplashScreen splash(m);
splash.show();

splash.finish(&w);

    w.setWindowFlags( Qt::Dialog  | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowStaysOnTopHint);

    w.show();

    return a.exec();
}
