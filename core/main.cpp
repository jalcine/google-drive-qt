#include <QtGui/QApplication>
#include "gui/forms/mainwindow.h"
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QRect r(w.geometry());

    r.moveCenter(a.desktop()->availableGeometry().center());
    w.setGeometry(r);

    w.init();
    w.show();

    return a.exec();
}
