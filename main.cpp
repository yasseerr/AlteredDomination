#include "mainmenu.h"
#include <QApplication>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTime t;
    qsrand(t.msecsSinceStartOfDay());
    MainMenu w;
    w.showMaximized();

    return a.exec();
}
